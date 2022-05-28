//
// author x.king xdotking@gmail.com
//

#include "DtoSizeTool.h"
#include "../../setting/BlockSetting.h"
#include "../../util/LogUtil.h"
#include "../../util/StringUtil.h"
#include "../../setting/ScriptSetting.h"
#include "../../setting/TransactionSetting.h"


namespace DtoSizeTool{


    uint64_t calculateTransactionsOutputSize(vector<TransactionOutputDto> *transactionOutputDtos) ;
    uint64_t calculateTransactionOutputSize(TransactionOutputDto *transactionOutputDto) ;
    uint64_t calculateTransactionInputsSize(vector<TransactionInputDto> *inputs) ;
    uint64_t calculateTransactionInputSize(TransactionInputDto *input) ;
    uint64_t calculateScriptSize(ScriptDto *script) ;
    uint64_t sizeOfString(string value) ;
    uint64_t sizeOfNumber(uint64_t number) ;

    //region check Size
    bool checkBlockSize(BlockDto *blockDto) {
        //The length of the timestamp of the block does not need to be verified. If the timestamp length is incorrect, it will not work in the business logic.

        //The length of the previous hash of the block does not need to be verified. If the previous hash length is incorrect, it will not work in the business logic.

        //Check block nonce size
        uint64_t nonceSize = sizeOfString(blockDto->nonce);
        if(nonceSize != BlockSetting::NONCE_CHARACTER_COUNT){
            LogUtil::debug("Illegal nonce length.");
            return false;
        }

        //Check the size of each transaction
        vector<TransactionDto> transactionDtos = blockDto->transactions;
        if(!transactionDtos.empty()){
            for(TransactionDto transactionDto:transactionDtos){
                if(!checkTransactionSize(&transactionDto)){
                    LogUtil::debug("Illegal transaction size.");
                    return false;
                }
            }
        }

        //Check Block size
        uint64_t blockSize = calculateBlockSize(blockDto);
        if(blockSize > BlockSetting::BLOCK_MAX_CHARACTER_COUNT){
            LogUtil::debug("Block size exceeds limit.");
            return false;
        }
        return true;
    }
    bool checkTransactionSize(TransactionDto *transactionDto) {
        //Check transaction input size
        vector<TransactionInputDto> transactionInputDtos = transactionDto->inputs;
        if(!transactionInputDtos.empty()){
            for(TransactionInputDto transactionInputDto:transactionInputDtos){
                //The unspent output size of the transaction does not need to be verified. If the assumption is incorrect, it will not work in the business logic.

                //Check script size
                InputScriptDto inputScriptDto = transactionInputDto.inputScript;
                //Check the size of the input script
                if(!checkInputScriptSize(&inputScriptDto)){
                    return false;
                }
            }
        }

        //Check transaction output size
        vector<TransactionOutputDto> transactionOutputDtos = transactionDto->outputs;
        if(!transactionOutputDtos.empty()){
            for(TransactionOutputDto transactionOutputDto:transactionOutputDtos){
                //The size of the transaction output amount does not need to be verified. If the assumption is incorrect, it will not work in the business logic.

                //Check script size
                OutputScriptDto outputScriptDto = transactionOutputDto.outputScript;
                //Check the size of the output script
                if(!checkOutputScriptSize(&outputScriptDto)){
                    return false;
                }

            }
        }

        //Check transaction size
        uint64_t transactionSize = calculateTransactionSize(transactionDto);
        if(transactionSize > TransactionSetting::TRANSACTION_MAX_CHARACTER_COUNT){
            LogUtil::debug("Transaction size exceeds limit.");
            return false;
        }
        return true;
    }
    bool checkInputScriptSize(InputScriptDto *inputScriptDto) {
        if(!checkScriptSize(inputScriptDto)){
            return false;
        }
        return true;
    }
    bool checkOutputScriptSize(OutputScriptDto *outputScriptDto) {
        if(!checkScriptSize(outputScriptDto)){
            return false;
        }
        return true;
    }
    bool checkScriptSize(ScriptDto *scriptDto) {
        //There is no need to check the size of opcodes and operands in the script.
        //Illegal opcodes, illegal operands cannot constitute a legal script.
        //Illegal script will not work in the business logic.
        if(calculateScriptSize(scriptDto) > ScriptSetting::SCRIPT_MAX_CHARACTER_COUNT){
            LogUtil::debug("Script size exceeds limit.");
            return false;
        }
        return true;
    }
    //endregion



    //region calculate Size
    uint64_t calculateBlockSize(BlockDto *blockDto) {
        uint64_t size = 0;
        uint64_t timestamp = blockDto->timestamp;
        size += sizeOfNumber(timestamp);

        string previousBlockHash = blockDto->previousHash;
        size += sizeOfString(previousBlockHash);

        string nonce = blockDto->nonce;
        size += sizeOfString(nonce);
        vector<TransactionDto> transactionDtos = blockDto->transactions;
        for(TransactionDto transactionDto:transactionDtos){
            size += calculateTransactionSize(&transactionDto);
        }
        return size;
    }
    uint64_t calculateTransactionSize(TransactionDto *transactionDto) {
        uint64_t size = 0;
        vector<TransactionInputDto> transactionInputDtos = transactionDto->inputs;
        size += calculateTransactionInputsSize(&transactionInputDtos);
        vector<TransactionOutputDto> transactionOutputDtos = transactionDto->outputs;
        size += calculateTransactionsOutputSize(&transactionOutputDtos);
        return size;
    }
    uint64_t calculateTransactionsOutputSize(vector<TransactionOutputDto> *transactionOutputDtos) {
        uint64_t size = 0;
        if(transactionOutputDtos == nullptr){
            return size;
        }
        for(TransactionOutputDto transactionOutputDto:*transactionOutputDtos){
            size += calculateTransactionOutputSize(&transactionOutputDto);
        }
        return size;
    }
    uint64_t calculateTransactionOutputSize(TransactionOutputDto *transactionOutputDto) {
        uint64_t size = 0;
        OutputScriptDto outputScriptDto = transactionOutputDto->outputScript;
        size += calculateScriptSize(&outputScriptDto);
        uint64_t value = transactionOutputDto->value;
        size += sizeOfNumber(value);
        return size;
    }
    uint64_t calculateTransactionInputsSize(vector<TransactionInputDto> *inputs) {
        uint64_t size = 0;
        if(inputs == nullptr){
            return size;
        }
        for(TransactionInputDto transactionInputDto:*inputs){
            size += calculateTransactionInputSize(&transactionInputDto);
        }
        return size;
    }
    uint64_t calculateTransactionInputSize(TransactionInputDto *input) {
        uint64_t size = 0;
        string transactionHash = input->transactionHash;
        size += sizeOfString(transactionHash);
        uint64_t transactionOutputIndex = input->transactionOutputIndex;
        size += sizeOfNumber(transactionOutputIndex);
        InputScriptDto inputScriptDto = input->inputScript;
        size += calculateScriptSize(&inputScriptDto);
        return size;
    }
    uint64_t calculateScriptSize(ScriptDto *script) {
        uint64_t size = 0;
        if(script == nullptr){
            return size;
        }
        for(string scriptCode:*script){
            size += sizeOfString(scriptCode);
        }
        return size;
    }

    uint64_t sizeOfString(string value) {
        return StringUtil::length(value);
    }
    uint64_t sizeOfNumber(uint64_t number) {
        return StringUtil::length(StringUtil::valueOfUint64(number));
    }
    //endregion
}