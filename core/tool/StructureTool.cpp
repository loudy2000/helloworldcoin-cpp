//
// author x.king xdotking@gmail.com
//

#include "StructureTool.h"
#include "ScriptTool.h"
#include "../../util/LogUtil.h"
#include "../../util/StringUtil.h"
#include "BlockTool.h"
#include "../../setting/BlockSetting.h"

using namespace model;

namespace StructureTool{


    bool checkBlockStructure(Block *block) {
        vector<Transaction> transactions = block->transactions;
        if(transactions.empty()){
            LogUtil::debug("Block data error: The number of transactions in the block is 0. A block must have a coinbase transaction.");
            return false;
        }
        //Check the number of transactions in the block
        uint64_t transactionCount = BlockTool::getTransactionCount(block);
        if(transactionCount > BlockSetting::BLOCK_MAX_TRANSACTION_COUNT){
            LogUtil::debug("Block data error: The number of transactions in the block exceeds the limit.");
            return false;
        }
        for(int i=0; i<transactions.size(); i++){
            Transaction transaction = transactions[i];
            if(i == 0){
                if(transaction.transactionType != TransactionTypeEnum::COINBASE_TRANSACTION){
                    LogUtil::debug("Block data error: The first transaction of the block must be a coinbase transaction.");
                    return false;
                }
            }else {
                if(transaction.transactionType != TransactionTypeEnum::STANDARD_TRANSACTION){
                    LogUtil::debug("Block data error: The non-first transaction of the block must be a standard transaction.");
                    return false;
                }
            }
        }
        //Check the structure of the transaction
        for(Transaction transaction:transactions){
            if(!checkTransactionStructure(&transaction)){
                LogUtil::debug("Transaction data error: The transaction structure is abnormal.");
                return false;
            }
        }
        return true;
    }

    bool checkTransactionStructure(Transaction *transaction) {
        if(transaction->transactionType == TransactionTypeEnum::COINBASE_TRANSACTION){
            vector<TransactionInput> inputs = transaction->inputs;
            if(!inputs.empty()){
                LogUtil::debug("Transaction data error: The coinbase transaction cannot have transaction input.");
                return false;
            }
            vector<TransactionOutput> outputs = transaction->outputs;
            if(outputs.size() != 1){
                LogUtil::debug("Transaction data error: The coinbase transaction has one and only one transaction output.");
                return false;
            }
        }else if(transaction->transactionType == TransactionTypeEnum::STANDARD_TRANSACTION){
            vector<TransactionInput> inputs = transaction->inputs;
            if(inputs.size() < 1){
                LogUtil::debug("Transaction data error: The number of transaction inputs for a standard transaction is at least 1.");
                return false;
            }
            vector<TransactionOutput> outputs = transaction->outputs;
            if(outputs.size() < 1){
                LogUtil::debug("Transaction data error: The transaction output number of a standard transaction is at least 1.");
                return false;
            }
        }else {
            throw exception();
        }
        //Check Transaction Input Script
        vector<TransactionInput> inputs = transaction->inputs;
        if(!inputs.empty()){
            for (TransactionInput input:inputs) {
                //Strict Check: must be a P2PKH input script.
                if(!ScriptTool::isPayToPublicKeyHashInputScript(&input.inputScript)){
                    LogUtil::debug("Transaction data error: The transaction input script is not a P2PKH input script.");
                    return false;
                }
            }
        }
        //Check Transaction Output Script
        vector<TransactionOutput> outputs = transaction->outputs;
        if(!outputs.empty()){
            for (TransactionOutput output:outputs) {
                //Strict Check: must be a P2PKH output script.
                if(!ScriptTool::isPayToPublicKeyHashOutputScript(&output.outputScript)){
                    LogUtil::debug("Transaction data error: The transaction output script is not a P2PKH output script.");
                    return false;
                }
            }
        }
        return true;
    }
}