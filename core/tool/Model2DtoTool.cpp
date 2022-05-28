//
// author x.king xdotking@gmail.com
//

#include "Model2DtoTool.h"


namespace Model2DtoTool{

    BlockDto block2BlockDto(Block *block) {
        if(block == nullptr){
            throw exception();
        }
        vector<TransactionDto> transactionDtos;
        vector<Transaction> transactions = block->transactions;
        if(!transactions.empty()){
            for(Transaction transaction:transactions){
                TransactionDto transactionDto = transaction2TransactionDto(&transaction);
                transactionDtos.push_back(transactionDto);
            }
        }

        BlockDto blockDto;
        blockDto.timestamp=block->timestamp;
        blockDto.previousHash=block->previousHash;
        blockDto.transactions=transactionDtos;
        blockDto.nonce=block->nonce;
        return blockDto;
    }

    TransactionDto transaction2TransactionDto(Transaction *transaction) {
        vector<TransactionInputDto> inputs;
        vector<TransactionInput> transactionInputs = transaction->inputs;
        if(!transactionInputs.empty()){
            for (TransactionInput transactionInput:transactionInputs){
                TransactionInputDto transactionInputDto;
                transactionInputDto.transactionHash=transactionInput.unspentTransactionOutput.transactionHash;
                transactionInputDto.transactionOutputIndex=transactionInput.unspentTransactionOutput.transactionOutputIndex;
                InputScriptDto is = inputScript2InputScriptDto(&transactionInput.inputScript);
                transactionInputDto.inputScript=is;
                inputs.push_back(transactionInputDto);
            }
        }

        vector<TransactionOutputDto> outputs;
        vector<TransactionOutput> transactionOutputs = transaction->outputs;
        if(!transactionOutputs.empty()){
            for(TransactionOutput transactionOutput:transactionOutputs){
                TransactionOutputDto transactionOutputDto = transactionOutput2TransactionOutputDto(&transactionOutput);
                outputs.push_back(transactionOutputDto);
            }
        }

        TransactionDto transactionDto;
        transactionDto.inputs=inputs;
        transactionDto.outputs=outputs;
        return transactionDto;
    }

    InputScriptDto inputScript2InputScriptDto(InputScript *inputScript) {
        InputScriptDto inputScriptDto;
        if(inputScript != nullptr){
            for (auto script:*inputScript) {
                inputScriptDto.push_back(script);
            }
        }
        return inputScriptDto;
    }

    OutputScriptDto outputScript2OutputScriptDto(OutputScript *outputScript) {
        OutputScriptDto outputScriptDto;
        if(outputScript != nullptr){
            for (auto script:*outputScript) {
                outputScriptDto.push_back(script);
            }
        }
        return outputScriptDto;
    }

    TransactionOutputDto transactionOutput2TransactionOutputDto(TransactionOutput *transactionOutput) {
        TransactionOutputDto transactionOutputDto;
        transactionOutputDto.value=transactionOutput->value;
        OutputScriptDto os=outputScript2OutputScriptDto(&transactionOutput->outputScript);
        transactionOutputDto.outputScript=os;
        return transactionOutputDto;
    }
}
