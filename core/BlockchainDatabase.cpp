//
// author x.king xdotking@gmail.com
//

#include "BlockchainDatabase.h"
#include "tool/StructureTool.h"
#include "tool/SizeTool.h"
#include "tool/BlockchainDatabaseKeyTool.h"
#include "tool/BlockTool.h"
#include "tool/TransactionTool.h"
#include "tool/ScriptTool.h"
#include "tool/ScriptDtoTool.h"
#include "tool/TransactionDtoTool.h"
#include "../setting/GenesisBlockSetting.h"
#include "../crypto/AccountUtil.h"
#include "../util/ByteUtil.h"
#include "../util/LogUtil.h"
#include "../util/FileUtil.h"
#include "../util/EncodeDecodeTool.h"

using namespace model;
using namespace BlockchainActionEnum;
using namespace TransactionTypeEnum;
namespace core{


    const string BLOCKCHAIN_DATABASE_NAME = "BlockchainDatabase";


    //region add block、delete block
    bool BlockchainDatabase::addBlockDto(BlockDto *blockDto) {
        try {
            mutex.lock();
            unique_ptr<Block> block = blockDto2Block(blockDto);
            bool checkBlock0 = checkBlock(block.get());
            if(!checkBlock0){
                mutex.unlock();
                return false;
            }
            KvWriteBatch kvWriteBatch = createBlockWriteBatch(block.get(), ADD_BLOCK);
            KvDbUtil::write(getBlockchainDatabasePath(), kvWriteBatch);
            mutex.unlock();
            return true;
        } catch(exception e){
            mutex.unlock();
            return false;
        };
    }

    void BlockchainDatabase::deleteTailBlock() {
        try {
            mutex.lock();
            unique_ptr<Block> tailBlock = queryTailBlock();
            if(!tailBlock.get()){
                mutex.unlock();
                return;
            }
            KvWriteBatch kvWriteBatch = createBlockWriteBatch(tailBlock.get(), DELETE_BLOCK);
            KvDbUtil::write(getBlockchainDatabasePath(),kvWriteBatch);
            mutex.unlock();
        } catch(exception e){
            mutex.unlock();
        };
    }

    void BlockchainDatabase::deleteBlocks(uint64_t blockHeight) {
        try {
            mutex.lock();
            while (true){
                unique_ptr<Block> tailBlock = queryTailBlock();
                if(!tailBlock.get()){
                    break;
                }
                if(tailBlock->height < blockHeight){
                    break;
                }
                KvWriteBatch kvWriteBatch = createBlockWriteBatch(tailBlock.get(), DELETE_BLOCK);
                KvDbUtil::write(getBlockchainDatabasePath(),kvWriteBatch);
            }
            mutex.unlock();
        } catch(exception e){
            mutex.unlock();
        };
    }
    //endregion



    //region
    bool BlockchainDatabase::checkBlock(Block *block) {

        //check block structure
        if(!StructureTool::checkBlockStructure(block)){
            LogUtil::debug("The block data is abnormal. Please verify the block structure.");
            return false;
        }
        //check block size
        if(!SizeTool::checkBlockSize(block)){
            LogUtil::debug("The block data is abnormal, please check the size of the block.");
            return false;
        }


        //check business
        unique_ptr<Block> previousBlock = queryTailBlock();
        //check block height
        if(!BlockTool::checkBlockHeight(previousBlock,block)){
            LogUtil::debug("Wrong block height for block write.");
            return false;
        }
        //check previous block hash
        if(!BlockTool::checkPreviousBlockHash(previousBlock,block)){
            LogUtil::debug("The previous block hash of the block write was wrong.");
            return false;
        }
        //check block timestamp
        if(!BlockTool::checkBlockTimestamp(previousBlock,block)){
            LogUtil::debug("Block generation is too late.");
            return false;
        }
        //check block new hash
        if(!checkBlockNewHash(block)){
            LogUtil::debug("The block data is abnormal, and the newly generated hash in the block is abnormal.");
            return false;
        }
        //check block new address
        if(!checkBlockNewAddress(block)){
            LogUtil::debug("The block data is abnormal, and the newly generated hash in the block is abnormal.");
            return false;
        }
        //check block double spend
        if(!checkBlockDoubleSpend(block)){
            LogUtil::debug("The block data is abnormal, and a double-spending attack is detected.");
            return false;
        }
        //check consensus
        if(!consensus->checkConsensus(this,block)){
            LogUtil::debug("The block data is abnormal and the consensus rules are not met.");
            return false;
        }
        //check incentive
        if(!incentive->checkIncentive(this,block)){
            LogUtil::debug("The block data is abnormal, and the incentive verification fails.");
            return false;
        }

        //check transaction
        for(Transaction transaction : block->transactions){
            bool transactionCanAddToNextBlock = checkTransaction(&transaction);
            if(!transactionCanAddToNextBlock){
                LogUtil::debug("The block data is abnormal, and the transaction is abnormal.");
                return false;
            }
        }
        return true;
    }


    bool BlockchainDatabase::checkTransaction(Transaction *transaction) {
        //check Transaction Structure
        if(!StructureTool::checkTransactionStructure(transaction)){
            LogUtil::debug("The transaction data is abnormal, please verify the structure of the transaction.");
            return false;
        }
        //check Transaction Size
        if(!SizeTool::checkTransactionSize(transaction)){
            LogUtil::debug("The transaction data is abnormal, please check the size of the transaction.");
            return false;
        }


        //Check if the address in the transaction is a P2PKH address
        if(!TransactionTool::checkPayToPublicKeyHashAddress(transaction)){
            return false;
        }
        //Check if the script in the transaction is a P2PKH script
        if(!TransactionTool::checkPayToPublicKeyHashScript(transaction)){
            return false;
        }

        //business verification
        //check Transaction New Hash
        if(!checkTransactionNewHash(transaction)){
            LogUtil::debug("The block data is abnormal, and the newly generated hash in the block is abnormal.");
            return false;
        }
        //check Transaction New Address
        if(!checkTransactionNewAddress(transaction)){
            LogUtil::debug("The block data is abnormal, and the newly generated hash in the block is abnormal.");
            return false;
        }
        //check Transaction Value
        if(!TransactionTool::checkTransactionValue(transaction)){
            LogUtil::debug("The block data is abnormal and the transaction amount is illegal");
            return false;
        }
        //check Transaction Double Spend
        if(!checkTransactionDoubleSpend(transaction)){
            LogUtil::debug("The transaction data is abnormal, and a double-spending attack is detected.");
            return false;
        }
        //check Transaction Script
        if(!checkTransactionScript(transaction)) {
            LogUtil::debug("Transaction verification failed: transaction [input script] unlock transaction [output script] exception.");
            return false;
        }
        return true;
    }
    //endregion



    //region Blockchain query related
    uint64_t BlockchainDatabase::queryBlockchainHeight() {
        vector<unsigned char> bytesBlockchainHeight = KvDbUtil::get(getBlockchainDatabasePath(), BlockchainDatabaseKeyTool::buildBlockchainHeightKey());
        if(bytesBlockchainHeight.empty()){
            return GenesisBlockSetting::HEIGHT;
        }
        return ByteUtil::bytesToUint64(bytesBlockchainHeight);
    }


    uint64_t BlockchainDatabase::queryBlockchainTransactionHeight() {
        vector<unsigned char> byteTotalTransactionCount = KvDbUtil::get(getBlockchainDatabasePath(), BlockchainDatabaseKeyTool::buildBlockchainTransactionHeightKey());
        if(byteTotalTransactionCount.empty()){
            return 0;
        }
        return ByteUtil::bytesToUint64(byteTotalTransactionCount);
    }

    uint64_t BlockchainDatabase::queryBlockchainTransactionOutputHeight() {
        vector<unsigned char> byteTotalTransactionCount = KvDbUtil::get(getBlockchainDatabasePath(), BlockchainDatabaseKeyTool::buildBlockchainTransactionOutputHeightKey());
        if(byteTotalTransactionCount.empty()){
            return 0;
        }
        return ByteUtil::bytesToUint64(byteTotalTransactionCount);
    }
    //endregion



    //region
    unique_ptr<Block> BlockchainDatabase::queryTailBlock() {
        uint64_t blockchainHeight = queryBlockchainHeight();
        if(blockchainHeight <= GenesisBlockSetting::HEIGHT){
            return unique_ptr<Block>(nullptr);
        }
        return queryBlockByBlockHeight(blockchainHeight);
    }

    unique_ptr<Block> BlockchainDatabase::queryBlockByBlockHeight(uint64_t blockHeight) {
        vector<unsigned char> bytesBlock = KvDbUtil::get(getBlockchainDatabasePath(), BlockchainDatabaseKeyTool::buildBlockHeightToBlockKey(blockHeight));
        if(bytesBlock.empty()){
            return unique_ptr<Block>(nullptr);
        }
        Block block = EncodeDecodeTool::decode(bytesBlock,Block{});
        return unique_ptr<Block>(new Block(block));
    }

    unique_ptr<Block> BlockchainDatabase::queryBlockByBlockHash(string blockHash) {
        vector<unsigned char> bytesBlockHeight = KvDbUtil::get(getBlockchainDatabasePath(), BlockchainDatabaseKeyTool::buildBlockHashToBlockHeightKey(blockHash));
        if(bytesBlockHeight.empty()){
            return unique_ptr<Block>(nullptr);
        }
        return queryBlockByBlockHeight(ByteUtil::bytesToUint64(bytesBlockHeight));
    }
    //endregion



    //region Transaction query related
    unique_ptr<Transaction> BlockchainDatabase::queryTransactionByTransactionHash(string transactionHash) {
        vector<unsigned char> transactionHeight = KvDbUtil::get(getBlockchainDatabasePath(), BlockchainDatabaseKeyTool::buildTransactionHashToTransactionHeightKey(transactionHash));
        if(transactionHeight.empty()){
            return unique_ptr<Transaction>(nullptr);
        }
        return queryTransactionByTransactionHeight(ByteUtil::bytesToUint64(transactionHeight));
    }


    unique_ptr<Transaction> BlockchainDatabase::querySourceTransactionByTransactionOutputId(string transactionHash,uint64_t transactionOutputIndex) {
        vector<unsigned char> sourceTransactionHeight = KvDbUtil::get(getBlockchainDatabasePath(), BlockchainDatabaseKeyTool::buildTransactionOutputIdToSourceTransactionHeightKey(transactionHash,transactionOutputIndex));
        if(sourceTransactionHeight.empty()){
            return unique_ptr<Transaction>(nullptr);
        }
        return queryTransactionByTransactionHeight(ByteUtil::bytesToUint64(sourceTransactionHeight));
    }


    unique_ptr<Transaction> BlockchainDatabase::queryDestinationTransactionByTransactionOutputId(string transactionHash,uint64_t transactionOutputIndex) {
        vector<unsigned char> destinationTransactionHeight = KvDbUtil::get(getBlockchainDatabasePath(), BlockchainDatabaseKeyTool::buildTransactionOutputIdToDestinationTransactionHeightKey(transactionHash,transactionOutputIndex));
        if(destinationTransactionHeight.empty()){
            return unique_ptr<Transaction>(nullptr);
        }
        return queryTransactionByTransactionHeight(ByteUtil::bytesToUint64(destinationTransactionHeight));
    }


    unique_ptr<TransactionOutput> BlockchainDatabase::queryTransactionOutputByTransactionOutputHeight(uint64_t transactionOutputHeight) {
        vector<unsigned char> bytesTransactionOutput = KvDbUtil::get(getBlockchainDatabasePath(), BlockchainDatabaseKeyTool::buildTransactionOutputHeightToTransactionOutputKey(transactionOutputHeight));
        if(bytesTransactionOutput.empty()){
            return unique_ptr<TransactionOutput>(nullptr);
        }
        TransactionOutput transactionOutput = EncodeDecodeTool::decode(bytesTransactionOutput,TransactionOutput{});
        return unique_ptr<TransactionOutput>(new TransactionOutput(transactionOutput));
    }


    unique_ptr<Transaction> BlockchainDatabase::queryTransactionByTransactionHeight(uint64_t transactionHeight) {
        vector<unsigned char> byteTransaction = KvDbUtil::get(getBlockchainDatabasePath(), BlockchainDatabaseKeyTool::buildTransactionHeightToTransactionKey(transactionHeight));
        if(byteTransaction.empty()){
            return unique_ptr<Transaction>(nullptr);
        }
        Transaction transaction = EncodeDecodeTool::decode(byteTransaction,Transaction{});
        return unique_ptr<Transaction>(new Transaction(transaction));
    }
    //endregion



    //region Transaction Output Query related
    unique_ptr<TransactionOutput> BlockchainDatabase::queryTransactionOutputByTransactionOutputId(string transactionHash,uint64_t transactionOutputIndex) {
        vector<unsigned char> bytesTransactionOutputHeight = KvDbUtil::get(getBlockchainDatabasePath(), BlockchainDatabaseKeyTool::buildTransactionOutputIdToTransactionOutputHeightKey(transactionHash,transactionOutputIndex));
        if(bytesTransactionOutputHeight.empty()){
            return unique_ptr<TransactionOutput>(nullptr);
        }
        return queryTransactionOutputByTransactionOutputHeight(ByteUtil::bytesToUint64(bytesTransactionOutputHeight));
    }


    unique_ptr<TransactionOutput> BlockchainDatabase::queryUnspentTransactionOutputByTransactionOutputId(string transactionHash,uint64_t transactionOutputIndex) {
        vector<unsigned char> bytesTransactionOutputHeight = KvDbUtil::get(getBlockchainDatabasePath(), BlockchainDatabaseKeyTool::buildTransactionOutputIdToUnspentTransactionOutputHeightKey(transactionHash,transactionOutputIndex));
        if(bytesTransactionOutputHeight.empty()){
            return unique_ptr<TransactionOutput>(nullptr);
        }
        return queryTransactionOutputByTransactionOutputHeight(ByteUtil::bytesToUint64(bytesTransactionOutputHeight));
    }


    unique_ptr<TransactionOutput> BlockchainDatabase::querySpentTransactionOutputByTransactionOutputId(string transactionHash,uint64_t transactionOutputIndex) {
        vector<unsigned char> bytesTransactionOutputHeight = KvDbUtil::get(getBlockchainDatabasePath(), BlockchainDatabaseKeyTool::buildTransactionOutputIdToSpentTransactionOutputHeightKey(transactionHash,transactionOutputIndex));
        if(bytesTransactionOutputHeight.empty()){
            return unique_ptr<TransactionOutput>(nullptr);
        }
        return queryTransactionOutputByTransactionOutputHeight(ByteUtil::bytesToUint64(bytesTransactionOutputHeight));
    }


    unique_ptr<TransactionOutput> BlockchainDatabase::queryTransactionOutputByAddress(string address) {
        vector<unsigned char> bytesTransactionOutputHeight = KvDbUtil::get(getBlockchainDatabasePath(), BlockchainDatabaseKeyTool::buildAddressToTransactionOutputHeightKey(address));
        if(bytesTransactionOutputHeight.empty()){
            return unique_ptr<TransactionOutput>(nullptr);
        }
        return queryTransactionOutputByTransactionOutputHeight(ByteUtil::bytesToUint64(bytesTransactionOutputHeight));
    }


    unique_ptr<TransactionOutput> BlockchainDatabase::queryUnspentTransactionOutputByAddress(string address) {
        vector<unsigned char> bytesTransactionOutputHeight = KvDbUtil::get(getBlockchainDatabasePath(), BlockchainDatabaseKeyTool::buildAddressToUnspentTransactionOutputHeightKey(address));
        if(bytesTransactionOutputHeight.empty()){
            return unique_ptr<TransactionOutput>(nullptr);
        }
        return queryTransactionOutputByTransactionOutputHeight(ByteUtil::bytesToUint64(bytesTransactionOutputHeight));
    }


    unique_ptr<TransactionOutput> BlockchainDatabase::querySpentTransactionOutputByAddress(string address) {
        vector<unsigned char> bytesTransactionOutputHeight = KvDbUtil::get(getBlockchainDatabasePath(), BlockchainDatabaseKeyTool::buildAddressToSpentTransactionOutputHeightKey(address));
        if(bytesTransactionOutputHeight.empty()){
            return unique_ptr<TransactionOutput>(nullptr);
        }
        return queryTransactionOutputByTransactionOutputHeight(ByteUtil::bytesToUint64(bytesTransactionOutputHeight));
    }
    //endregion

    Incentive* BlockchainDatabase::getIncentive() {
        return incentive;
    }

    Consensus* BlockchainDatabase::getConsensus() {
        return consensus;
    }







    //region Assemble WriteBatch
    KvWriteBatch BlockchainDatabase::createBlockWriteBatch(Block *block, BlockchainAction blockchainAction) {
        KvWriteBatch kvWriteBatch;

        storeHash(&kvWriteBatch,block,blockchainAction);
        storeAddress(&kvWriteBatch,block,blockchainAction);

        storeBlockchainHeight(&kvWriteBatch,block,blockchainAction);
        storeBlockchainTransactionHeight(&kvWriteBatch,block,blockchainAction);
        storeBlockchainTransactionOutputHeight(&kvWriteBatch,block,blockchainAction);

        storeBlockHeightToBlock(&kvWriteBatch,block,blockchainAction);
        storeBlockHashToBlockHeight(&kvWriteBatch,block,blockchainAction);

        storeTransactionHeightToTransaction(&kvWriteBatch,block,blockchainAction);
        storeTransactionHashToTransactionHeight(&kvWriteBatch,block,blockchainAction);

        storeTransactionOutputHeightToTransactionOutput(&kvWriteBatch,block,blockchainAction);
        storeTransactionOutputIdToTransactionOutputHeight(&kvWriteBatch,block,blockchainAction);
        storeTransactionOutputIdToUnspentTransactionOutputHeight(&kvWriteBatch,block,blockchainAction);
        storeTransactionOutputIdToSpentTransactionOutputHeight(&kvWriteBatch,block,blockchainAction);
        storeTransactionOutputIdToSourceTransactionHeight(&kvWriteBatch,block,blockchainAction);
        storeTransactionOutputIdToDestinationTransactionHeight(&kvWriteBatch,block,blockchainAction);

        storeAddressToTransactionOutputHeight(&kvWriteBatch,block,blockchainAction);
        storeAddressToUnspentTransactionOutputHeight(&kvWriteBatch,block,blockchainAction);
        storeAddressToSpentTransactionOutputHeight(&kvWriteBatch,block,blockchainAction);
        return kvWriteBatch;
    };
    void BlockchainDatabase::storeTransactionOutputIdToSourceTransactionHeight(KvWriteBatch *kvWriteBatch, Block *block, BlockchainAction blockchainAction) {
        vector<Transaction> transactions = block->transactions;
        if(!transactions.empty()){
            for(Transaction transaction:transactions){
                vector<TransactionOutput> outputs = transaction.outputs;
                if(!outputs.empty()){
                    for(TransactionOutput transactionOutput:outputs){
                        vector<unsigned char> transactionOutputIdToToSourceTransactionHeightKey = BlockchainDatabaseKeyTool::buildTransactionOutputIdToSourceTransactionHeightKey(transactionOutput.transactionHash,transactionOutput.transactionOutputIndex);
                        if(ADD_BLOCK == blockchainAction){
                            kvWriteBatch->put(transactionOutputIdToToSourceTransactionHeightKey, ByteUtil::uint64ToBytes(transaction.transactionHeight));
                        } else {
                            kvWriteBatch->delete0(transactionOutputIdToToSourceTransactionHeightKey);
                        }
                    }
                }
            }
        }
    }
    void BlockchainDatabase::storeTransactionOutputIdToDestinationTransactionHeight(KvWriteBatch *kvWriteBatch, Block *block, BlockchainAction blockchainAction) {
        vector<Transaction> transactions = block->transactions;
        if(!transactions.empty()){
            for(Transaction transaction:transactions){
                vector<TransactionInput> inputs = transaction.inputs;
                if(!inputs.empty()){
                    for(TransactionInput transactionInput:inputs){
                        TransactionOutput unspentTransactionOutput = transactionInput.unspentTransactionOutput;
                        vector<unsigned char> transactionOutputIdToToDestinationTransactionHeightKey = BlockchainDatabaseKeyTool::buildTransactionOutputIdToDestinationTransactionHeightKey(unspentTransactionOutput.transactionHash,unspentTransactionOutput.transactionOutputIndex);
                        if(ADD_BLOCK == blockchainAction){
                            kvWriteBatch->put(transactionOutputIdToToDestinationTransactionHeightKey, ByteUtil::uint64ToBytes(transaction.transactionHeight));
                        } else {
                            kvWriteBatch->delete0(transactionOutputIdToToDestinationTransactionHeightKey);
                        }
                    }
                }
            }
        }
    }
    void BlockchainDatabase::storeTransactionOutputIdToTransactionOutputHeight(KvWriteBatch *kvWriteBatch, Block *block, BlockchainAction blockchainAction) {
        vector<Transaction> transactions = block->transactions;
        if(!transactions.empty()){
            for(Transaction transaction:transactions){
                vector<TransactionOutput> outputs = transaction.outputs;
                if(!outputs.empty()){
                    for(TransactionOutput output:outputs){
                        vector<unsigned char> transactionOutputIdToTransactionOutputHeightKey = BlockchainDatabaseKeyTool::buildTransactionOutputIdToTransactionOutputHeightKey(output.transactionHash,output.transactionOutputIndex);
                        if(ADD_BLOCK == blockchainAction){
                            kvWriteBatch->put(transactionOutputIdToTransactionOutputHeightKey, ByteUtil::uint64ToBytes(output.transactionOutputHeight));
                        } else {
                            kvWriteBatch->delete0(transactionOutputIdToTransactionOutputHeightKey);
                        }
                    }
                }
            }
        }
    }
    void BlockchainDatabase::storeTransactionOutputHeightToTransactionOutput(KvWriteBatch *kvWriteBatch, Block *block, BlockchainAction blockchainAction) {
        vector<Transaction> transactions = block->transactions;
        if(!transactions.empty()){
            for(Transaction transaction:transactions){
                vector<TransactionOutput> outputs = transaction.outputs;
                if(!outputs.empty()){
                    for(TransactionOutput output:outputs){
                        vector<unsigned char> transactionOutputHeightToTransactionOutputKey = BlockchainDatabaseKeyTool::buildTransactionOutputHeightToTransactionOutputKey(output.transactionOutputHeight);
                        if(ADD_BLOCK == blockchainAction){
                            kvWriteBatch->put(transactionOutputHeightToTransactionOutputKey, EncodeDecodeTool::encode(output));
                        } else {
                            kvWriteBatch->delete0(transactionOutputHeightToTransactionOutputKey);
                        }
                    }
                }
            }
        }
    }
    void BlockchainDatabase::storeTransactionOutputIdToUnspentTransactionOutputHeight(KvWriteBatch *kvWriteBatch, Block *block, BlockchainAction blockchainAction) {
        vector<Transaction> transactions = block->transactions;
        if(!transactions.empty()){
            for(Transaction transaction:transactions){
                vector<TransactionInput> inputs = transaction.inputs;
                if(!inputs.empty()){
                    for(TransactionInput transactionInput:inputs){
                        TransactionOutput unspentTransactionOutput = transactionInput.unspentTransactionOutput;
                        vector<unsigned char> transactionOutputIdToUnspentTransactionOutputHeightKey = BlockchainDatabaseKeyTool::buildTransactionOutputIdToUnspentTransactionOutputHeightKey(unspentTransactionOutput.transactionHash,unspentTransactionOutput.transactionOutputIndex);
                        if(ADD_BLOCK == blockchainAction){
                            kvWriteBatch->delete0(transactionOutputIdToUnspentTransactionOutputHeightKey);
                        } else {
                            kvWriteBatch->put(transactionOutputIdToUnspentTransactionOutputHeightKey, ByteUtil::uint64ToBytes(unspentTransactionOutput.transactionOutputHeight));
                        }
                    }
                }
                vector<TransactionOutput> outputs = transaction.outputs;
                if(!outputs.empty()){
                    for(TransactionOutput output:outputs){
                        vector<unsigned char> transactionOutputIdToUnspentTransactionOutputHeightKey = BlockchainDatabaseKeyTool::buildTransactionOutputIdToUnspentTransactionOutputHeightKey(output.transactionHash,output.transactionOutputIndex);
                        if(ADD_BLOCK == blockchainAction){
                            kvWriteBatch->put(transactionOutputIdToUnspentTransactionOutputHeightKey, ByteUtil::uint64ToBytes(output.transactionOutputHeight));
                        } else {
                            kvWriteBatch->delete0(transactionOutputIdToUnspentTransactionOutputHeightKey);
                        }
                    }
                }
            }
        }
    }
    void BlockchainDatabase::storeTransactionOutputIdToSpentTransactionOutputHeight(KvWriteBatch *kvWriteBatch, Block *block, BlockchainAction blockchainAction) {
        vector<Transaction> transactions = block->transactions;
        if(!transactions.empty()){
            for(Transaction transaction:transactions){
                vector<TransactionInput> inputs = transaction.inputs;
                if(!inputs.empty()){
                    for(TransactionInput transactionInput:inputs){
                        TransactionOutput unspentTransactionOutput = transactionInput.unspentTransactionOutput;
                        vector<unsigned char> transactionOutputIdToSpentTransactionOutputHeightKey = BlockchainDatabaseKeyTool::buildTransactionOutputIdToSpentTransactionOutputHeightKey(unspentTransactionOutput.transactionHash,unspentTransactionOutput.transactionOutputIndex);
                        if(ADD_BLOCK == blockchainAction){
                            kvWriteBatch->put(transactionOutputIdToSpentTransactionOutputHeightKey, ByteUtil::uint64ToBytes(unspentTransactionOutput.transactionOutputHeight));
                        } else {
                            kvWriteBatch->delete0(transactionOutputIdToSpentTransactionOutputHeightKey);
                        }
                    }
                }
                vector<TransactionOutput> outputs = transaction.outputs;
                if(!outputs.empty()){
                    for(TransactionOutput output:outputs){
                        vector<unsigned char> transactionOutputIdToSpentTransactionOutputHeightKey = BlockchainDatabaseKeyTool::buildTransactionOutputIdToSpentTransactionOutputHeightKey(output.transactionHash,output.transactionOutputIndex);
                        if(ADD_BLOCK == blockchainAction){
                            kvWriteBatch->delete0(transactionOutputIdToSpentTransactionOutputHeightKey);
                        } else {
                            kvWriteBatch->put(transactionOutputIdToSpentTransactionOutputHeightKey, ByteUtil::uint64ToBytes(output.transactionOutputHeight));
                        }
                    }
                }
            }
        }
    }
    void BlockchainDatabase::storeTransactionHeightToTransaction(KvWriteBatch *kvWriteBatch, Block *block, BlockchainAction blockchainAction) {
        vector<Transaction> transactions = block->transactions;
        if(!transactions.empty()){
            for(Transaction transaction:transactions){
                vector<unsigned char> transactionHeightToTransactionKey = BlockchainDatabaseKeyTool::buildTransactionHeightToTransactionKey(transaction.transactionHeight);
                if(ADD_BLOCK == blockchainAction){
                    kvWriteBatch->put(transactionHeightToTransactionKey, EncodeDecodeTool::encode(transaction));
                } else {
                    kvWriteBatch->delete0(transactionHeightToTransactionKey);
                }
            }
        }
    }
    void BlockchainDatabase::storeTransactionHashToTransactionHeight(KvWriteBatch *kvWriteBatch, Block *block, BlockchainAction blockchainAction) {
        vector<Transaction> transactions = block->transactions;
        if(!transactions.empty()){
            for(Transaction transaction:transactions){
                vector<unsigned char> transactionHashToTransactionHeightKey = BlockchainDatabaseKeyTool::buildTransactionHashToTransactionHeightKey(transaction.transactionHash);
                if(ADD_BLOCK == blockchainAction){
                    kvWriteBatch->put(transactionHashToTransactionHeightKey, ByteUtil::uint64ToBytes(transaction.transactionHeight));
                } else {
                    kvWriteBatch->delete0(transactionHashToTransactionHeightKey);
                }
            }
        }
    }
    void BlockchainDatabase::storeBlockchainHeight(KvWriteBatch *kvWriteBatch, Block *block, BlockchainAction blockchainAction) {
        vector<unsigned char> blockchainHeightKey = BlockchainDatabaseKeyTool::buildBlockchainHeightKey();
        if(ADD_BLOCK == blockchainAction){
            kvWriteBatch->put(blockchainHeightKey, ByteUtil::uint64ToBytes(block->height));
        }else{
            kvWriteBatch->put(blockchainHeightKey, ByteUtil::uint64ToBytes(block->height-1));
        }
    }
    void BlockchainDatabase::storeBlockHashToBlockHeight(KvWriteBatch *kvWriteBatch, Block *block, BlockchainAction blockchainAction) {
        vector<unsigned char> blockHashBlockHeightKey = BlockchainDatabaseKeyTool::buildBlockHashToBlockHeightKey(block->hash);
        if(ADD_BLOCK == blockchainAction){
            kvWriteBatch->put(blockHashBlockHeightKey, ByteUtil::uint64ToBytes(block->height));
        }else{
            kvWriteBatch->delete0(blockHashBlockHeightKey);
        }
    }
    void BlockchainDatabase::storeBlockchainTransactionHeight(KvWriteBatch *kvWriteBatch, Block *block, BlockchainAction blockchainAction) {
        uint64_t transactionCount = queryBlockchainTransactionHeight();
        vector<unsigned char> bytesBlockchainTransactionCountKey = BlockchainDatabaseKeyTool::buildBlockchainTransactionHeightKey();
        if(ADD_BLOCK == blockchainAction){
            kvWriteBatch->put(bytesBlockchainTransactionCountKey, ByteUtil::uint64ToBytes(transactionCount + BlockTool::getTransactionCount(block)));
        }else{
            kvWriteBatch->put(bytesBlockchainTransactionCountKey, ByteUtil::uint64ToBytes(transactionCount - BlockTool::getTransactionCount(block)));
        }
    }
    void BlockchainDatabase::storeBlockchainTransactionOutputHeight(KvWriteBatch *kvWriteBatch, Block *block, BlockchainAction blockchainAction) {
        uint64_t transactionOutputCount = queryBlockchainTransactionOutputHeight();
        vector<unsigned char> bytesBlockchainTransactionOutputHeightKey = BlockchainDatabaseKeyTool::buildBlockchainTransactionOutputHeightKey();
        if(ADD_BLOCK == blockchainAction){
            kvWriteBatch->put(bytesBlockchainTransactionOutputHeightKey, ByteUtil::uint64ToBytes(transactionOutputCount + BlockTool::getTransactionOutputCount(block)));
        }else{
            kvWriteBatch->put(bytesBlockchainTransactionOutputHeightKey, ByteUtil::uint64ToBytes(transactionOutputCount - BlockTool::getTransactionOutputCount(block)));
        }
    }
    void BlockchainDatabase::storeBlockHeightToBlock(KvWriteBatch *kvWriteBatch, Block *block, BlockchainAction blockchainAction) {
        vector<unsigned char> blockHeightKey = BlockchainDatabaseKeyTool::buildBlockHeightToBlockKey(block->height);
        if(ADD_BLOCK == blockchainAction){
            kvWriteBatch->put(blockHeightKey, EncodeDecodeTool::encode(*block));
        }else{
            kvWriteBatch->delete0(blockHeightKey);
        }
    }
    void BlockchainDatabase::storeHash(KvWriteBatch *kvWriteBatch, Block *block, BlockchainAction blockchainAction) {
        vector<unsigned char> blockHashKey = BlockchainDatabaseKeyTool::buildHashKey(block->hash);
        if(ADD_BLOCK == blockchainAction){
            kvWriteBatch->put(blockHashKey, blockHashKey);
        } else {
            kvWriteBatch->delete0(blockHashKey);
        }
        vector<Transaction> transactions = block->transactions;
        if(!transactions.empty()){
            for(Transaction transaction:transactions){
                vector<unsigned char> transactionHashKey = BlockchainDatabaseKeyTool::buildHashKey(transaction.transactionHash);
                if(ADD_BLOCK == blockchainAction){
                    kvWriteBatch->put(transactionHashKey, transactionHashKey);
                } else {
                    kvWriteBatch->delete0(transactionHashKey);
                }
            }
        }
    }
    void BlockchainDatabase::storeAddress(KvWriteBatch *kvWriteBatch, Block *block, BlockchainAction blockchainAction) {
        vector<Transaction> transactions = block->transactions;
        if(!transactions.empty()){
            for(Transaction transaction:transactions){
                vector<TransactionOutput> outputs = transaction.outputs;
                if(!outputs.empty()){
                    for(TransactionOutput output:outputs){
                        vector<unsigned char> addressKey = BlockchainDatabaseKeyTool::buildAddressKey(output.address);
                        if(ADD_BLOCK == blockchainAction){
                            kvWriteBatch->put(addressKey, addressKey);
                        } else {
                            kvWriteBatch->delete0(addressKey);
                        }
                    }
                }
            }
        }
    }
    void BlockchainDatabase::storeAddressToUnspentTransactionOutputHeight(KvWriteBatch *kvWriteBatch, Block *block, BlockchainAction blockchainAction) {
        vector<Transaction> transactions = block->transactions;
        if(transactions.empty()){
            return;
        }
        for(Transaction transaction : transactions){
            vector<TransactionInput> inputs = transaction.inputs;
            if(!inputs.empty()){
                for (TransactionInput transactionInput:inputs){
                    TransactionOutput utxo = transactionInput.unspentTransactionOutput;
                    vector<unsigned char> addressToUnspentTransactionOutputHeightKey = BlockchainDatabaseKeyTool::buildAddressToUnspentTransactionOutputHeightKey(utxo.address);
                    if(blockchainAction == ADD_BLOCK){
                        kvWriteBatch->delete0(addressToUnspentTransactionOutputHeightKey);
                    }else{
                        kvWriteBatch->put(addressToUnspentTransactionOutputHeightKey, ByteUtil::uint64ToBytes(utxo.transactionOutputHeight));
                    }
                }
            }
            vector<TransactionOutput> outputs = transaction.outputs;
            if(!outputs.empty()){
                for (TransactionOutput transactionOutput:outputs){
                    vector<unsigned char> addressToUnspentTransactionOutputHeightKey = BlockchainDatabaseKeyTool::buildAddressToUnspentTransactionOutputHeightKey(transactionOutput.address);
                    if(blockchainAction == ADD_BLOCK){
                        kvWriteBatch->put(addressToUnspentTransactionOutputHeightKey, ByteUtil::uint64ToBytes(transactionOutput.transactionOutputHeight));
                    }else{
                        kvWriteBatch->delete0(addressToUnspentTransactionOutputHeightKey);
                    }
                }
            }
        }
    }
    void BlockchainDatabase::storeAddressToTransactionOutputHeight(KvWriteBatch *kvWriteBatch, Block *block, BlockchainAction blockchainAction) {
        vector<Transaction> &transactions = block->transactions;
        if(transactions.empty()){
            return;
        }
        for(Transaction &transaction : transactions){
            vector<TransactionOutput> outputs = transaction.outputs;
            if(!outputs.empty()){
                for (TransactionOutput &transactionOutput:outputs){
                    vector<unsigned char> addressToTransactionOutputHeightKey = BlockchainDatabaseKeyTool::buildAddressToTransactionOutputHeightKey(transactionOutput.address);
                    if(blockchainAction == ADD_BLOCK){
                        kvWriteBatch->put(addressToTransactionOutputHeightKey, ByteUtil::uint64ToBytes(transactionOutput.transactionOutputHeight));
                    }else{
                        kvWriteBatch->delete0(addressToTransactionOutputHeightKey);
                    }
                }
            }
        }
    }
    void BlockchainDatabase::storeAddressToSpentTransactionOutputHeight(KvWriteBatch *kvWriteBatch, Block *block, BlockchainAction blockchainAction) {
        vector<Transaction> transactions = block->transactions;
        if(transactions.empty()){
            return;
        }
        for(Transaction transaction : transactions){
            vector<TransactionInput> inputs = transaction.inputs;
            if(!inputs.empty()){
                for (TransactionInput transactionInput:inputs){
                    TransactionOutput utxo = transactionInput.unspentTransactionOutput;
                    vector<unsigned char> addressToSpentTransactionOutputHeightKey = BlockchainDatabaseKeyTool::buildAddressToSpentTransactionOutputHeightKey(utxo.address);
                    if(blockchainAction == ADD_BLOCK){
                        kvWriteBatch->put(addressToSpentTransactionOutputHeightKey, ByteUtil::uint64ToBytes(utxo.transactionOutputHeight));
                    }else{
                        kvWriteBatch->delete0(addressToSpentTransactionOutputHeightKey);
                    }
                }
            }
        }
    }
    //endregion

    string BlockchainDatabase::getBlockchainDatabasePath(){
        return FileUtil::newPath(coreConfiguration->getCorePath(), BLOCKCHAIN_DATABASE_NAME);
    }

    //region block hash related
    /**
     * check Block New Hash
     */
    bool BlockchainDatabase::checkBlockNewHash(Block *block) {
        if(BlockTool::isExistDuplicateNewHash(block)){
            LogUtil::debug("The block data is abnormal, exist duplicate hash.");
            return false;
        }

        string blockHash = block->hash;
        if(isHashUsed(blockHash)){
            LogUtil::debug("The block data is abnormal, and the block hash has been used.");
            return false;
        }

        vector<Transaction> blockTransactions = block->transactions;
        if(!blockTransactions.empty()){
            for(Transaction transaction:blockTransactions){
                if(!checkTransactionNewHash(&transaction)){
                    return false;
                }
            }
        }
        return true;
    }
    bool BlockchainDatabase::checkTransactionNewHash(Transaction *transaction) {
        string transactionHash = transaction->transactionHash;
        if(isHashUsed(transactionHash)){
            return false;
        }
        return true;
    }
    bool BlockchainDatabase::isHashUsed(string hash){
        vector<unsigned char> bytesHash = KvDbUtil::get(getBlockchainDatabasePath(), BlockchainDatabaseKeyTool::buildHashKey(hash));
        return !bytesHash.empty();
    }
    //endregion


    //region address related
    bool BlockchainDatabase::checkBlockNewAddress(Block *block) {
        if(BlockTool::isExistDuplicateNewAddress(block)){
            return false;
        }
        vector<Transaction> transactions = block->transactions;
        if(!transactions.empty()){
            for(Transaction transaction:transactions){
                if(!checkTransactionNewAddress(&transaction)){
                    return false;
                }
            }
        }
        return true;
    }
    bool BlockchainDatabase::checkTransactionNewAddress(Transaction *transaction) {
        if(TransactionTool::isExistDuplicateNewAddress(transaction)){
            return false;
        }
        vector<TransactionOutput> outputs = transaction->outputs;
        if(!outputs.empty()){
            for (TransactionOutput output:outputs){
                string address = output.address;
                if(isAddressUsed(address)){
                    return false;
                }
            }
        }
        return true;
    }
    bool BlockchainDatabase::isAddressUsed(string address) {
        vector<unsigned char> bytesAddress = KvDbUtil::get(getBlockchainDatabasePath(), BlockchainDatabaseKeyTool::buildAddressKey(address));
        return !bytesAddress.empty();
    }
    //endregion


    //region Double spend attack
    bool BlockchainDatabase::checkBlockDoubleSpend(Block *block) {
        if(BlockTool::isExistDuplicateUtxo(block)){
            LogUtil::debug("Abnormal block data: a double-spend transaction occurred.");
            return false;
        }
        vector<Transaction> transactions = block->transactions;
        if(!transactions.empty()){
            for(Transaction transaction:transactions){
                if(!checkTransactionDoubleSpend(&transaction)){
                    LogUtil::debug("Abnormal block data: a double-spend transaction occurred.");
                    return false;
                }
            }
        }
        return true;
    }
    /**
     * check Transaction Double Spend
     */
    bool BlockchainDatabase::checkTransactionDoubleSpend(Transaction *transaction) {
        //Double spend transaction: there is a duplicate [unspent transaction output] inside the transaction
        if(TransactionTool::isExistDuplicateUtxo(transaction)){
            LogUtil::debug("The transaction data is abnormal, and a double-spending attack is detected.");
            return false;
        }
        //Double spend transaction: transaction uses [spent [unspent transaction output]] inside the transaction
        if(!checkStxoIsUtxo(transaction)){
            LogUtil::debug("The transaction data is abnormal, and a double-spending attack is detected.");
            return false;
        }
        return true;
    }
    /**
     * Check if [spent transaction outputs] are all [unspent transaction outputs] ?
     */
    bool BlockchainDatabase::checkStxoIsUtxo(Transaction *transaction) {
        vector<TransactionInput> inputs = transaction->inputs;
        if(!inputs.empty()){
            for(TransactionInput transactionInput : inputs) {
                TransactionOutput unspentTransactionOutput = transactionInput.unspentTransactionOutput;
                unique_ptr<TransactionOutput> transactionOutput = queryUnspentTransactionOutputByTransactionOutputId(unspentTransactionOutput.transactionHash,unspentTransactionOutput.transactionOutputIndex);
                if(!transactionOutput.get()){
                    LogUtil::debug("Transaction data exception: transaction input is not unspent transaction output.");
                    return false;
                }
            }
        }
        return true;
    }
    bool BlockchainDatabase::checkTransactionScript(Transaction *transaction){
        try{
            vector<TransactionInput> inputs = transaction->inputs;
            if(!inputs.empty()){
                for(TransactionInput transactionInput:inputs){
                    OutputScript outputScript = transactionInput.unspentTransactionOutput.outputScript;
                    InputScript inputScript = transactionInput.inputScript;
                    Script script = ScriptTool::createScript(inputScript,outputScript);
                    ScriptExecuteResult scriptExecuteResult = virtualMachine->executeScript(*transaction,script);
                    bool executeSuccess = scriptExecuteResult.size()==1 && ByteUtil::equals(BooleanCodeEnum::TRUE00.code, ByteUtil::hexStringToBytes(scriptExecuteResult.top()));
                    if(!executeSuccess){
                        return false;
                    }
                }
            }
        }catch (exception e){
            LogUtil::error("Transaction verification failed: transaction [input script] unlock transaction [output script] exception.",e);
            return false;
        }
        return true;
    }
    //endregion





    //region dto to model
    unique_ptr<Block> BlockchainDatabase::blockDto2Block(BlockDto *blockDto) {
        string previousBlockHash = blockDto->previousHash;
        unique_ptr<Block> previousBlock = queryBlockByBlockHash(previousBlockHash);

        Block block;
        block.timestamp=blockDto->timestamp;
        block.previousHash=previousBlockHash;
        block.nonce=blockDto->nonce;

        uint64_t blockHeight = BlockTool::getNextBlockHeight(previousBlock);
        block.height=blockHeight;

        vector<Transaction> transactions = transactionDtos2Transactions(&blockDto->transactions);
        block.transactions=transactions;

        string merkleTreeRoot = BlockTool::calculateBlockMerkleTreeRoot(&block);
        block.merkleTreeRoot=merkleTreeRoot;

        string blockHash = BlockTool::calculateBlockHash(&block);
        block.hash=blockHash;

        string difficult = getConsensus()->calculateDifficult(this,&block);
        block.difficulty=difficult;

        fillBlockProperty(&block);

        if(!getConsensus()->checkConsensus(this,&block)){
            throw exception("Check Block Consensus Failed.");
        }
        return unique_ptr<Block>(new Block(block));

    }
    vector<Transaction> BlockchainDatabase::transactionDtos2Transactions(vector<TransactionDto> *transactionDtos) {
        vector<Transaction> transactions;
        if(transactionDtos != nullptr){
            for(TransactionDto &transactionDto:*transactionDtos){
                unique_ptr<Transaction> transaction = transactionDto2Transaction(&transactionDto);
                transactions.push_back(*transaction.get());
            }
        }
        return transactions;
    }
    unique_ptr<Transaction> BlockchainDatabase::transactionDto2Transaction(TransactionDto *transactionDto) {
        vector<TransactionInput> inputs;
        vector<TransactionInputDto> transactionInputDtos = transactionDto->inputs;
        if(!transactionInputDtos.empty()){
            for (TransactionInputDto transactionInputDto:transactionInputDtos){
                unique_ptr<TransactionOutput> unspentTransactionOutput = queryUnspentTransactionOutputByTransactionOutputId(transactionInputDto.transactionHash,transactionInputDto.transactionOutputIndex);
                if(!unspentTransactionOutput.get()){
                    throw exception("Illegal transaction. the transaction input is not an unspent transaction output.");
                }
                TransactionInput transactionInput;
                transactionInput.unspentTransactionOutput = *unspentTransactionOutput.get();
                InputScript inputScript = inputScriptDto2InputScript(&transactionInputDto.inputScript);
                transactionInput.inputScript = inputScript;
                inputs.push_back(transactionInput);
            }
        }

        vector<TransactionOutput> outputs;
        vector<TransactionOutputDto> transactionOutputDtos = transactionDto->outputs;
        if(!transactionOutputDtos.empty()){
            for(TransactionOutputDto transactionOutputDto:transactionOutputDtos){
                TransactionOutput transactionOutput = transactionOutputDto2TransactionOutput(&transactionOutputDto);
                outputs.push_back(transactionOutput);
            }
        }

        Transaction transaction;
        TransactionType transactionType = obtainTransactionDto(transactionDto);
        transaction.transactionType=transactionType;
        transaction.transactionHash=TransactionDtoTool::calculateTransactionHash(*transactionDto);
        transaction.inputs=inputs;
        transaction.outputs=outputs;
        return unique_ptr<Transaction>(new Transaction(transaction));
    }
    TransactionOutput BlockchainDatabase::transactionOutputDto2TransactionOutput(TransactionOutputDto *transactionOutputDto) {
        TransactionOutput transactionOutput;
        string publicKeyHash = ScriptDtoTool::getPublicKeyHashFromPayToPublicKeyHashOutputScript(transactionOutputDto->outputScript);
        string address = AccountUtil::addressFromPublicKeyHash(publicKeyHash);
        transactionOutput.address=address;
        transactionOutput.value=transactionOutputDto->value;
        OutputScript outputScript = outputScriptDto2OutputScript(&transactionOutputDto->outputScript);
        transactionOutput.outputScript=outputScript;
        return transactionOutput;
    }
    TransactionType BlockchainDatabase::obtainTransactionDto(TransactionDto *transactionDto) {
        if(transactionDto->inputs.empty()){
            return TransactionTypeEnum::COINBASE_TRANSACTION;
        }
        return TransactionTypeEnum::STANDARD_TRANSACTION;
    }
    OutputScript BlockchainDatabase::outputScriptDto2OutputScript(OutputScriptDto *outputScriptDto) {
        if(outputScriptDto == nullptr){
            return OutputScript{};
        }
        OutputScript outputScript;
        for (string s:*outputScriptDto) {
            outputScript.push_back(s);
        }
        return outputScript;
    }
    InputScript BlockchainDatabase::inputScriptDto2InputScript(InputScriptDto *inputScriptDto) {
        if(inputScriptDto == nullptr){
            return InputScript{};
        }
        InputScript inputScript;
        for (string s:*inputScriptDto) {
            inputScript.push_back(s);
        }
        return inputScript;
    }

    void BlockchainDatabase::fillBlockProperty(Block *block) {
        uint64_t transactionIndex = 0;
        uint64_t transactionHeight = queryBlockchainTransactionHeight();
        uint64_t transactionOutputHeight = queryBlockchainTransactionOutputHeight();
        uint64_t blockHeight = block->height;
        string blockHash = block->hash;
        vector<Transaction> &transactions = block->transactions;
        uint64_t transactionCount = BlockTool::getTransactionCount(block);
        block->transactionCount=transactionCount;
        block->previousTransactionHeight=transactionHeight;
        if(!transactions.empty()){
            for(Transaction &transaction:transactions){
                transactionIndex++;
                transactionHeight++;
                transaction.blockHeight=blockHeight;
                transaction.transactionIndex=transactionIndex;
                transaction.transactionHeight=transactionHeight;

                vector<TransactionOutput> &outputs = transaction.outputs;
                if(!outputs.empty()){
                    for (int i=0; i <outputs.size(); i++){
                        transactionOutputHeight++;
                        TransactionOutput &output = outputs[i];
                        output.blockHeight=blockHeight;
                        output.blockHash=blockHash;
                        output.transactionHeight=transactionHeight;
                        output.transactionHash=transaction.transactionHash;
                        output.transactionOutputIndex=i+1;
                        output.transactionIndex=transaction.transactionIndex;
                        output.transactionOutputHeight=transactionOutputHeight;
                    }
                }
            }
        }
    }

    BlockchainDatabase::BlockchainDatabase(CoreConfiguration *coreConfiguration, Incentive *incentive,
                                           Consensus *consensus, VirtualMachine *virtualMachine) {
        this->coreConfiguration = coreConfiguration;
        this->incentive = incentive;
        this->consensus = consensus;
        this->virtualMachine = virtualMachine;
    }
    //endregion
}