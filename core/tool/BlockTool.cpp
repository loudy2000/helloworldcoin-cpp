//
// author x.king xdotking@gmail.com
//

#include "BlockTool.h"
#include "BlockDtoTool.h"
#include "../../util/StringsUtil.h"
#include "../../util/StringUtil.h"
#include "../../util/TimeUtil.h"

#include "../../setting/GenesisBlockSetting.h"
#include "Model2DtoTool.h"
#include "TransactionTool.h"

using namespace dto;

namespace BlockTool {

    string calculateBlockHash(Block *block) {
        BlockDto blockDto = Model2DtoTool::block2BlockDto(block);
        return BlockDtoTool::calculateBlockHash(&blockDto);
    }

    string calculateBlockMerkleTreeRoot(Block *block) {
        BlockDto blockDto = Model2DtoTool::block2BlockDto(block);
        return BlockDtoTool::calculateBlockMerkleTreeRoot(&blockDto);
    }

    bool isExistDuplicateNewHash(Block *block) {
        vector<string> newHashs;
        string blockHash = block->hash;
        newHashs.push_back(blockHash);
        vector<Transaction> transactions = block->transactions;
        if(!transactions.empty()){
            for(Transaction transaction : transactions){
                string transactionHash = transaction.transactionHash;
                newHashs.push_back(transactionHash);
            }
        }
        return StringsUtil::hasDuplicateElement(newHashs);
    }

    bool isExistDuplicateNewAddress(Block *block) {
        vector<string> newAddresss;
        vector<Transaction> transactions = block->transactions;
        if(!transactions.empty()){
            for(Transaction transaction : transactions){
                vector<TransactionOutput> outputs = transaction.outputs;
                if(!outputs.empty()){
                    for (TransactionOutput output:outputs){
                        string address = output.address;
                        newAddresss.push_back(address);
                    }
                }
            }
        }
        return StringsUtil::hasDuplicateElement(newAddresss);
    }

    bool isExistDuplicateUtxo(Block *block) {
        vector<string> utxoIds;
        vector<Transaction> transactions = block->transactions;
        if(!transactions.empty()) {
            for(Transaction transaction : transactions){
                vector<TransactionInput> inputs = transaction.inputs;
                if(!inputs.empty()){
                    for(TransactionInput transactionInput : inputs) {
                        TransactionOutput unspentTransactionOutput = transactionInput.unspentTransactionOutput;
                        string utxoId = TransactionTool::getTransactionOutputId(&unspentTransactionOutput);
                        utxoIds.push_back(utxoId);
                    }
                }
            }
        }
        return StringsUtil::hasDuplicateElement(utxoIds);
    }

    bool checkPreviousBlockHash(unique_ptr<Block> &previousBlock, Block *currentBlock) {
        if(!previousBlock.get()){
            return StringUtil::equals(GenesisBlockSetting::HASH, currentBlock->previousHash);
        } else {
            return StringUtil::equals(previousBlock->hash, currentBlock->previousHash);
        }
    }

    bool checkBlockHeight(unique_ptr<Block> &previousBlock, Block *currentBlock) {
        if(!previousBlock.get()){
            return (GenesisBlockSetting::HEIGHT +1) == currentBlock->height;
        } else {
            return (previousBlock->height+1) == currentBlock->height;
        }
    }

    bool checkBlockTimestamp(unique_ptr<Block> &previousBlock, Block *currentBlock) {
        if(currentBlock->timestamp > TimeUtil::millisecondTimestamp()){
            return false;
        }
        if(!previousBlock.get()){
            return true;
        } else {
            return currentBlock->timestamp > previousBlock->timestamp;
        }
    }

    uint64_t getTransactionCount(Block *block) {
        vector<Transaction> transactions = block->transactions;
        return transactions.empty()?0:transactions.size();
    }

    bool isBlockEquals(Block *block1, Block *block2) {
        if(block1 == nullptr || block2 == nullptr){
            return false;
        }
        return StringUtil::equals(block1->hash, block2->hash);
    }

    uint64_t getWritedIncentiveValue(Block *block) {
        return ((block->transactions)[0].outputs)[0].value;
    }

    string formatDifficulty(string difficulty) {
        return StringUtil::prefixPadding(difficulty,64,"0");
    }

    uint64_t getTransactionOutputCount(Block *block) {
        uint64_t transactionOutputCount = 0;
        vector<Transaction> transactions = block->transactions;
        if(!transactions.empty()){
            for(Transaction transaction:transactions){
                transactionOutputCount += TransactionTool::getTransactionOutputCount(&transaction);
            }
        }
        return transactionOutputCount;
    }

    uint64_t getBlockFee(Block *block) {
        uint64_t blockFee = 0;
        vector<Transaction> transactions = block->transactions;
        if(!transactions.empty()){
            for(Transaction transaction:transactions){
                if(transaction.transactionType == TransactionTypeEnum::COINBASE_TRANSACTION){
                    continue;
                }else if(transaction.transactionType == TransactionTypeEnum::STANDARD_TRANSACTION){
                    uint64_t fee = TransactionTool::getTransactionFee(&transaction);
                    blockFee += fee;
                }else{
                    throw exception();
                }
            }
        }
        return blockFee;
    }

    uint64_t getNextBlockHeight(unique_ptr<Block> &currentBlock) {
        uint64_t nextBlockHeight = !currentBlock.get() ? GenesisBlockSetting::HEIGHT + 1 : currentBlock->height + 1;
        return nextBlockHeight;
    }
    
}