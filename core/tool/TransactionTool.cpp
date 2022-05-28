//
// author x.king xdotking@gmail.com
//

#include "TransactionTool.h"
#include "ScriptTool.h"
#include "Model2DtoTool.h"
#include "BlockchainDatabaseKeyTool.h"
#include "../../crypto/AccountUtil.h"
#include "../../util/LogUtil.h"
#include "TransactionDtoTool.h"
#include "../../util/SystemUtil.h"
#include "SizeTool.h"
#include "../../util/StringsUtil.h"


namespace TransactionTool{

    uint64_t getInputValue(Transaction *transaction) {
        vector<TransactionInput> inputs = transaction->inputs;
        uint64_t total = 0;
        if(!inputs.empty()){
            for(TransactionInput input : inputs) {
                total += input.unspentTransactionOutput.value;
            }
        }
        return total;
    }

    uint64_t getOutputValue(Transaction *transaction) {
        vector<TransactionOutput> outputs = transaction->outputs;
        uint64_t total = 0;
        if(!outputs.empty()){
            for(TransactionOutput output : outputs) {
                total += output.value;
            }
        }
        return total;
    }

    uint64_t getTransactionFee(Transaction *transaction) {
        if(transaction->transactionType == TransactionTypeEnum::STANDARD_TRANSACTION){
            uint64_t transactionFee = getInputValue(transaction) - getOutputValue(transaction);
            return transactionFee;
        }else if(transaction->transactionType == TransactionTypeEnum::COINBASE_TRANSACTION){
            return 0L;
        }else{
            throw exception();
        }
    }

    uint64_t getTransactionFeeRate(Transaction *transaction) {
        if(transaction->transactionType == TransactionTypeEnum::STANDARD_TRANSACTION){
            return getTransactionFee(transaction)/SizeTool::calculateTransactionSize(transaction);
        }else if(transaction->transactionType == TransactionTypeEnum::COINBASE_TRANSACTION){
            return 0L;
        }else {
            throw exception();
        }
    }

    string getSignatureHashAllRawMaterial(Transaction *transaction) {
        TransactionDto transactionDto = Model2DtoTool::transaction2TransactionDto(transaction);
        return TransactionDtoTool::getSignatureHashAllRawMaterial(transactionDto);
    }

    string signature(string privateKey, Transaction *transaction) {
        TransactionDto transactionDto = Model2DtoTool::transaction2TransactionDto(transaction);
        return TransactionDtoTool::signature(privateKey,transactionDto);
    }

    bool verifySignature(Transaction transaction, string publicKey, vector<unsigned char> *bytesSignature) {
        TransactionDto transactionDto = Model2DtoTool::transaction2TransactionDto(&transaction);
        return TransactionDtoTool::verifySignature(transactionDto,publicKey,*bytesSignature);
    }

    string calculateTransactionHash(Transaction *transaction){
        TransactionDto transactionDto = Model2DtoTool::transaction2TransactionDto(transaction);
        return TransactionDtoTool::calculateTransactionHash(transactionDto);
    }

    uint64_t getTransactionInputCount(Transaction *transaction) {
        vector<TransactionInput> inputs = transaction->inputs;
        uint64_t transactionInputCount = inputs.empty()?0:inputs.size();
        return transactionInputCount;
    }

    uint64_t getTransactionOutputCount(Transaction *transaction) {
        vector<TransactionOutput> outputs = transaction->outputs;
        uint64_t transactionOutputCount = outputs.empty()?0:outputs.size();
        return transactionOutputCount;
    }

    string getTransactionOutputId(TransactionOutput *transactionOutput) {
        return BlockchainDatabaseKeyTool::buildTransactionOutputId(transactionOutput->transactionHash,transactionOutput->transactionOutputIndex);
    }

    bool checkTransactionValue(Transaction *transaction) {
        vector<TransactionInput> inputs = transaction->inputs;
        if(!inputs.empty()){
            //Check Transaction Input Value
            for(TransactionInput input:inputs){
                if(!checkValue(input.unspentTransactionOutput.value)){
                    LogUtil::debug("Transaction value is illegal.");
                    return false;
                }
            }
        }

        vector<TransactionOutput> outputs = transaction->outputs;
        if(!outputs.empty()){
            //Check Transaction Output Value
            for(TransactionOutput output:outputs){
                if(!checkValue(output.value)){
                    LogUtil::debug("Transaction value is illegal.");
                    return false;
                }
            }
        }

        //further check by transaction type
        if(transaction->transactionType == TransactionTypeEnum::COINBASE_TRANSACTION){
            //There is no need to check, skip.
        } else if(transaction->transactionType == TransactionTypeEnum::STANDARD_TRANSACTION){
            //The transaction input value must be greater than or equal to the transaction output value
            uint64_t inputsValue = getInputValue(transaction);
            uint64_t outputsValue = getOutputValue(transaction);
            if(inputsValue < outputsValue) {
                LogUtil::debug("Transaction value is illegal.");
                return false;
            }
            return true;
        } else {
            throw exception();
        }
        return true;
    }

    bool checkValue(uint64_t transactionAmount) {
        //The transaction value cannot be less than or equal to 0
        if(transactionAmount <= 0){
            return false;
        }
        //The maximum value is 2^64
        //The reserved decimal place is 0
        return true;
    }

    bool checkPayToPublicKeyHashAddress(Transaction *transaction) {
        vector<TransactionOutput> outputs = transaction->outputs;
        if(!outputs.empty()){
            for(TransactionOutput output:outputs){
                if(!AccountUtil::isPayToPublicKeyHashAddress(output.address)){
                    LogUtil::debug("Transaction address is illegal.");
                    return false;
                }
            }
        }
        return true;
    }

    bool checkPayToPublicKeyHashScript(Transaction *transaction) {
        vector<TransactionInput> inputs = transaction->inputs;
        if(!inputs.empty()){
            for(TransactionInput input:inputs){
                if(!ScriptTool::isPayToPublicKeyHashInputScript(&input.inputScript)){
                    return false;
                }
            }
        }
        vector<TransactionOutput> outputs = transaction->outputs;
        if(!outputs.empty()){
            for (TransactionOutput output:outputs) {
                if(!ScriptTool::isPayToPublicKeyHashOutputScript(&output.outputScript)){
                    return false;
                }
            }
        }
        return true;
    }

    bool isExistDuplicateUtxo(Transaction *transaction) {
        vector<string> utxoIds;
        vector<TransactionInput> inputs = transaction->inputs;
        if(!inputs.empty()){
            for(TransactionInput transactionInput : inputs) {
                TransactionOutput unspentTransactionOutput = transactionInput.unspentTransactionOutput;
                string utxoId = getTransactionOutputId(&unspentTransactionOutput);
                utxoIds.push_back(utxoId);
            }
        }
        return StringsUtil::hasDuplicateElement(utxoIds);
    }

    bool isExistDuplicateNewAddress(Transaction *transaction) {
        vector<string> newAddresss;
        vector<TransactionOutput> outputs = transaction->outputs;
        if(!outputs.empty()){
            for (TransactionOutput output:outputs){
                string address = output.address;
                newAddresss.push_back(address);
            }
        }
        return StringsUtil::hasDuplicateElement(newAddresss);
    }

    void sortByTransactionFeeRateDescend(vector<Transaction> *transactions) {
        if(transactions == nullptr){
            return;
        }
        //TODO
        /*transactions.sort((transaction1, transaction2) -> {
            uint64_t transaction1FeeRate = TransactionTool.getTransactionFeeRate(transaction1);
            uint64_t transaction2FeeRate = TransactionTool.getTransactionFeeRate(transaction2);
            uint64_t diffFeeRate = transaction1FeeRate - transaction2FeeRate;
            if(diffFeeRate>0){
                return -1;
            }else if(diffFeeRate==0){
                return 0;
            }else {
                return 1;
            }
        });*/
    }
}