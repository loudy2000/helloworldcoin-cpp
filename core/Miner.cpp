//
// author x.king xdotking@gmail.com
//

#include <set>
#include "Miner.h"
#include "../util/ThreadUtil.h"
#include "../util/TimeUtil.h"
#include "../util/ByteUtil.h"
#include "../util/LogUtil.h"
#include "../util/StringUtil.h"
#include "tool/Model2DtoTool.h"
#include "tool/ScriptTool.h"
#include "../setting/BlockSetting.h"
#include "tool/SizeTool.h"
#include "tool/TransactionTool.h"
#include "../setting/GenesisBlockSetting.h"
#include "tool/BlockTool.h"
#include "tool/TransactionDtoTool.h"


namespace core{

    Miner::Miner(CoreConfiguration *coreConfiguration, Wallet *wallet, BlockchainDatabase *blockchainDatabase,
                 UnconfirmedTransactionDatabase *unconfirmedTransactionDatabase) {
        this->coreConfiguration= coreConfiguration;
        this->wallet = wallet;
        this->blockchainDatabase = blockchainDatabase;
        this->unconfirmedTransactionDatabase = unconfirmedTransactionDatabase;
    }


    void Miner::start() {
        while (true){
            ThreadUtil::millisecondSleep(10);
            if(!isActive()){
                continue;
            }
            if(isMiningHeightExceedsLimit()){
                continue;
            }

            Account minerAccount = wallet->createAccount();
            Block block = buildMiningBlock(blockchainDatabase,unconfirmedTransactionDatabase,&minerAccount);
            uint64_t startTimestamp = TimeUtil::millisecondTimestamp();
            while (true){
                if(!isActive()){
                    break;
                }
                if(TimeUtil::millisecondTimestamp()-startTimestamp > coreConfiguration->getMinerMineTimeInterval()){
                    break;
                }
                block.nonce = ByteUtil::bytesToHexString(ByteUtil::random32Bytes());
                block.hash = BlockTool::calculateBlockHash(&block);
                if(blockchainDatabase->getConsensus()->checkConsensus(blockchainDatabase,&block)){
                    wallet->saveAccount(minerAccount);
                    LogUtil::debug("Congratulations! Mining success! Block height:"+StringUtil::valueOfUint64(block.height)+", Block hash:"+block.hash);
                    BlockDto blockDto = Model2DtoTool::block2BlockDto(&block);
                    bool isAddBlockToBlockchainSuccess = blockchainDatabase->addBlockDto(&blockDto);
                    if(!isAddBlockToBlockchainSuccess){
                        LogUtil::debug("Mining succeeded, but the block failed to be put into the blockchain.");
                    }
                    break;
                }
            }
        }
    }


    void Miner::deactive() {
        coreConfiguration->deactiveMiner();
    }


    void Miner::active() {
        coreConfiguration->activeMiner();
    }


    bool Miner::isActive() {
        return coreConfiguration->isMinerActive();
    }



    void Miner::setMinerMineMaxBlockHeight(uint64_t maxHeight) {
        coreConfiguration->setMinerMineMaxBlockHeight(maxHeight);
    }


    uint64_t Miner::getMinerMineMaxBlockHeight( ) {
        return coreConfiguration->getMinerMineMaxBlockHeight();
    }

    Block Miner::buildMiningBlock(BlockchainDatabase *blockchainDatabase, UnconfirmedTransactionDatabase *unconfirmedTransactionDatabase, Account *minerAccount) {
        uint64_t timestamp = TimeUtil::millisecondTimestamp();

        unique_ptr<Block> tailBlock = blockchainDatabase->queryTailBlock();
        Block nonNonceBlock;
        nonNonceBlock.timestamp=timestamp;

        if(!tailBlock.get()){
            nonNonceBlock.height=GenesisBlockSetting::HEIGHT +1;
            nonNonceBlock.previousHash=GenesisBlockSetting::HASH;
        } else {
            nonNonceBlock.height=tailBlock->height+1;
            nonNonceBlock.previousHash=tailBlock->hash;
        }
        vector<Transaction> packingTransactions0 = packingTransactions(blockchainDatabase,unconfirmedTransactionDatabase);
        nonNonceBlock.transactions=packingTransactions0;

        Incentive *incentive = blockchainDatabase->getIncentive();
        uint64_t incentiveValue = incentive->incentiveValue(blockchainDatabase,&nonNonceBlock);

        Transaction mineAwardTransaction = buildIncentiveTransaction(minerAccount->address,incentiveValue);
        nonNonceBlock.transactions.insert(nonNonceBlock.transactions.begin(),mineAwardTransaction);

        string merkleTreeRoot = BlockTool::calculateBlockMerkleTreeRoot(&nonNonceBlock);
        nonNonceBlock.merkleTreeRoot=merkleTreeRoot;

        nonNonceBlock.difficulty=blockchainDatabase->getConsensus()->calculateDifficult(blockchainDatabase,&nonNonceBlock);
        return nonNonceBlock;
    }

    Transaction Miner::buildIncentiveTransaction(string address,uint64_t incentiveValue) {
        Transaction transaction;
        transaction.transactionType=TransactionTypeEnum::COINBASE_TRANSACTION;

        vector<TransactionOutput> outputs;
        TransactionOutput output;
        output.address=address;
        output.value=incentiveValue;
        output.outputScript=ScriptTool::createPayToPublicKeyHashOutputScript(address);
        outputs.push_back(output);

        transaction.outputs=outputs;
        transaction.transactionHash=TransactionTool::calculateTransactionHash(&transaction);
        return transaction;
    }

    vector<Transaction> Miner::packingTransactions(BlockchainDatabase *blockchainDatabase, UnconfirmedTransactionDatabase *unconfirmedTransactionDatabase) {
        vector<TransactionDto> forMineBlockTransactionDtos = unconfirmedTransactionDatabase->selectTransactions(1,10000);

        vector<Transaction> transactions;
        vector<Transaction> backupTransactions;

        if(!forMineBlockTransactionDtos.empty()){
            for(TransactionDto transactionDto:forMineBlockTransactionDtos){
                try {
                    unique_ptr<Transaction> transaction = blockchainDatabase->transactionDto2Transaction(&transactionDto);
                    transactions.push_back(*transaction.get());
                } catch (exception e) {
                    string transactionHash = TransactionDtoTool::calculateTransactionHash(transactionDto);
                    LogUtil::error("Abnormal transaction, transaction hash:"+transactionHash,e);
                    unconfirmedTransactionDatabase->deleteByTransactionHash(transactionHash);
                }
            }
        }

        backupTransactions.clear();
        backupTransactions=transactions;
        transactions.clear();
        for(Transaction &transaction : backupTransactions){
            bool checkTransaction = blockchainDatabase->checkTransaction(&transaction);
            if(checkTransaction){
                transactions.push_back(transaction);
            }else {
                string transactionHash = TransactionTool::calculateTransactionHash(&transaction);
                LogUtil::debug("Abnormal transaction, transaction hash:"+transactionHash);
                unconfirmedTransactionDatabase->deleteByTransactionHash(transactionHash);
            }
        }

        backupTransactions.clear();
        backupTransactions=transactions;
        transactions.clear();

        //prevent double spending
        set<string> transactionOutputIdSet;
        for(Transaction transaction : backupTransactions){
            vector<TransactionInput> inputs = transaction.inputs;
            if(!inputs.empty()){
                bool canAdd = true;
                for(TransactionInput transactionInput : inputs) {
                    TransactionOutput unspentTransactionOutput = transactionInput.unspentTransactionOutput;
                    string transactionOutputId = TransactionTool::getTransactionOutputId(&unspentTransactionOutput);
                    if(transactionOutputIdSet.count(transactionOutputId)>0){
                        canAdd = false;
                        break;
                    }else {
                        transactionOutputIdSet.insert(transactionOutputId);
                    }
                }
                if(canAdd){
                    transactions.push_back(transaction);
                }else {
                    string transactionHash = TransactionTool::calculateTransactionHash(&transaction);
                    LogUtil::debug("Abnormal transaction, transaction hash:"+transactionHash);
                    unconfirmedTransactionDatabase->deleteByTransactionHash(transactionHash);
                }
            }
        }



        backupTransactions.clear();
        backupTransactions=transactions;
        transactions.clear();

        //Prevent an address used multiple times
        set<string> addressSet;
        for(Transaction transaction : backupTransactions){
            vector<TransactionOutput> outputs = transaction.outputs;
            if(!outputs.empty()){
                bool canAdd = true;
                for (TransactionOutput output:outputs){
                    string address = output.address;
                    if(addressSet.count(address)>0){
                        canAdd = false;
                        break;
                    }else {
                        addressSet.insert(address);
                    }
                }
                if(canAdd){
                    transactions.push_back(transaction);
                }else {
                    string transactionHash = TransactionTool::calculateTransactionHash(&transaction);
                    LogUtil::debug("Abnormal transaction, transaction hash:"+transactionHash);
                    unconfirmedTransactionDatabase->deleteByTransactionHash(transactionHash);
                }
            }
        }


        TransactionTool::sortByTransactionFeeRateDescend(&transactions);


        backupTransactions.clear();
        backupTransactions=transactions;
        transactions.clear();

        uint64_t size = 0;
        for(int i=0; i<backupTransactions.size(); i++){
            if(i+1 > BlockSetting::BLOCK_MAX_TRANSACTION_COUNT-1){
                break;
            }
            Transaction transaction = backupTransactions[i];
            size += SizeTool::calculateTransactionSize(&transaction);
            if(size > BlockSetting::BLOCK_MAX_CHARACTER_COUNT){
                break;
            }
            transactions.push_back(transaction);
        }
        return transactions;
    }

    bool Miner::isMiningHeightExceedsLimit(){
        uint64_t blockChainHeight = blockchainDatabase->queryBlockchainHeight();
        return blockChainHeight >= coreConfiguration->getMinerMineMaxBlockHeight();
    }

    //region get set
    Wallet * Miner::getWallet() {
        return this->wallet;
    }
    BlockchainDatabase * Miner::getBlockchainDatabase() {
        return this->blockchainDatabase;
    }
    UnconfirmedTransactionDatabase * Miner::getUnconfirmedTransactionDatabase() {
        return this->unconfirmedTransactionDatabase;
    }
    CoreConfiguration * Miner::getCoreConfiguration() {
        return this->coreConfiguration;
    }
    //endregion
}