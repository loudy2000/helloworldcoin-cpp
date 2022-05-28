//
// author x.king xdotking@gmail.com
//

#include "BlockchainBrowserApplicationService.h"
#include "../../core/tool/BlockTool.h"
#include "../../core/tool/SizeTool.h"
#include "../../core/tool/TransactionTool.h"
#include "../../core/tool/ScriptTool.h"
#include "../../util/StringUtil.h"
#include "../../util/TimeUtil.h"
#include "../../util/LogUtil.h"


namespace service {


        BlockchainBrowserApplicationService::BlockchainBrowserApplicationService(BlockchainNetCore *blockchainNetCore){
            this->blockchainNetCore = blockchainNetCore;
        }
        unique_ptr<TransactionOutputVo3> BlockchainBrowserApplicationService::queryTransactionOutputByTransactionOutputId(string transactionHash, uint64_t transactionOutputIndex){
            unique_ptr<TransactionOutput> transactionOutput = blockchainNetCore->getBlockchainCore()->getBlockchainDatabase()->queryTransactionOutputByTransactionOutputId(transactionHash,transactionOutputIndex);
            if(!transactionOutput.get()){
                return unique_ptr<TransactionOutputVo3>(nullptr);
            }

            TransactionOutputVo3 transactionOutputVo3;
            transactionOutputVo3.fromBlockHeight=transactionOutput->blockHeight;
            transactionOutputVo3.fromBlockHash=transactionOutput->blockHash;
            transactionOutputVo3.fromTransactionHash=transactionOutput->transactionHash;
            transactionOutputVo3.value=transactionOutput->value;
            transactionOutputVo3.fromOutputScript= ScriptTool::outputScript2String(transactionOutput->outputScript);
            transactionOutputVo3.fromTransactionOutputIndex=transactionOutput->transactionOutputIndex;

            unique_ptr<TransactionOutput> transactionOutputTemp = blockchainNetCore->getBlockchainCore()->getBlockchainDatabase()->queryUnspentTransactionOutputByTransactionOutputId(transactionOutput->transactionHash,transactionOutput->transactionOutputIndex);
            transactionOutputVo3.unspentTransactionOutput=transactionOutputTemp.get();

            unique_ptr<TransactionVo> inputTransactionVo = queryTransactionByTransactionHash(transactionOutput->transactionHash);
            transactionOutputVo3.inputTransaction=*inputTransactionVo;
            transactionOutputVo3.transactionType=inputTransactionVo->transactionType;


            if(!transactionOutputTemp.get()){
                unique_ptr<Transaction> destinationTransaction = blockchainNetCore->getBlockchainCore()->getBlockchainDatabase()->queryDestinationTransactionByTransactionOutputId(transactionOutput->transactionHash,transactionOutput->transactionOutputIndex);
                vector<TransactionInput> &inputs = destinationTransaction->inputs;
                if(!inputs.empty()){
                    for(int inputIndex=0; inputIndex<inputs.size(); inputIndex++){
                        TransactionInput &transactionInput = inputs[inputIndex];
                        TransactionOutput unspentTransactionOutput = transactionInput.unspentTransactionOutput;
                        if(StringUtil::equals(transactionOutput->transactionHash,unspentTransactionOutput.transactionHash) &&
                           transactionOutput->transactionOutputIndex==unspentTransactionOutput.transactionOutputIndex){
                            transactionOutputVo3.toTransactionInputIndex=inputIndex+1;
                            transactionOutputVo3.toInputScript= ScriptTool::inputScript2String(
                                    transactionInput.inputScript);
                            break;
                        }
                    }
                }
                unique_ptr<TransactionVo> outputTransactionVo = queryTransactionByTransactionHash(destinationTransaction->transactionHash);
                transactionOutputVo3.toBlockHeight=outputTransactionVo->blockHeight;
                transactionOutputVo3.toBlockHash=outputTransactionVo->blockHash;
                transactionOutputVo3.toTransactionHash=outputTransactionVo->transactionHash;
                transactionOutputVo3.outputTransaction=*outputTransactionVo;
            }
            return unique_ptr<TransactionOutputVo3>(new TransactionOutputVo3(transactionOutputVo3));
        }
        unique_ptr<TransactionOutputVo3> BlockchainBrowserApplicationService::queryTransactionOutputByAddress(string address){
            unique_ptr<TransactionOutput> transactionOutput = blockchainNetCore->getBlockchainCore()->queryTransactionOutputByAddress(address);
            if(!transactionOutput.get()){
                return unique_ptr<TransactionOutputVo3>(nullptr);
            }
            return queryTransactionOutputByTransactionOutputId(transactionOutput->transactionHash,transactionOutput->transactionOutputIndex);
        }
        unique_ptr<TransactionVo> BlockchainBrowserApplicationService::queryTransactionByTransactionHash(string transactionHash){
            unique_ptr<Transaction> transaction = blockchainNetCore->getBlockchainCore()->queryTransactionByTransactionHash(transactionHash);
            if(!transaction.get()){
                return unique_ptr<TransactionVo>(nullptr);
            }

            TransactionVo transactionVo;
            transactionVo.transactionHash=transaction->transactionHash;
            transactionVo.blockHeight=transaction->blockHeight;

            transactionVo.transactionFee=TransactionTool::getTransactionFee(transaction.get());
            transactionVo.transactionType=transaction->transactionType;
            transactionVo.transactionInputCount=TransactionTool::getTransactionInputCount(transaction.get());
            transactionVo.transactionOutputCount=TransactionTool::getTransactionOutputCount(transaction.get());
            transactionVo.transactionInputValues=TransactionTool::getInputValue(transaction.get());
            transactionVo.transactionOutputValues=TransactionTool::getOutputValue(transaction.get());

            uint64_t blockchainHeight = blockchainNetCore->getBlockchainCore()->queryBlockchainHeight();
            unique_ptr<Block> block = blockchainNetCore->getBlockchainCore()->queryBlockByBlockHeight(transaction->blockHeight);
            transactionVo.blockConfirmations = blockchainHeight-block->height+1;
            transactionVo.blockTime=TimeUtil::formatMillisecondTimestamp(block->timestamp);
            transactionVo.blockHash=block->hash;

            vector<TransactionInput> inputs = transaction->inputs;
            vector<TransactionInputVo> transactionInputVos;
            if(!inputs.empty()){
                for(TransactionInput transactionInput:inputs){
                    TransactionInputVo transactionInputVo;
                    transactionInputVo.address=transactionInput.unspentTransactionOutput.address;
                    transactionInputVo.value=transactionInput.unspentTransactionOutput.value;
                    transactionInputVo.inputScript= ScriptTool::inputScript2String(transactionInput.inputScript);
                    transactionInputVo.transactionHash=transactionInput.unspentTransactionOutput.transactionHash;
                    transactionInputVo.transactionOutputIndex=transactionInput.unspentTransactionOutput.transactionOutputIndex;
                    transactionInputVos.push_back(transactionInputVo);
                }
            }
            transactionVo.transactionInputs=transactionInputVos;

            vector<TransactionOutput> outputs = transaction->outputs;
            vector<TransactionOutputVo> transactionOutputVos;
            if(!outputs.empty()){
                for(TransactionOutput transactionOutput:outputs){
                    TransactionOutputVo transactionOutputVo;
                    transactionOutputVo.address=transactionOutput.address;
                    transactionOutputVo.value=transactionOutput.value;
                    transactionOutputVo.outputScript= ScriptTool::outputScript2String(transactionOutput.outputScript);
                    transactionOutputVo.transactionHash=transactionOutput.transactionHash;
                    transactionOutputVo.transactionOutputIndex=transactionOutput.transactionOutputIndex;
                    transactionOutputVos.push_back(transactionOutputVo);
                }
            }
            transactionVo.transactionOutputs=transactionOutputVos;

            vector<string> inputScripts;
            for (TransactionInputVo transactionInputVo : transactionInputVos){
                inputScripts.push_back(transactionInputVo.inputScript);
            }
            transactionVo.inputScripts=inputScripts;

            vector<string> outputScripts;
            for (TransactionOutputVo transactionOutputVo : transactionOutputVos){
                outputScripts.push_back(transactionOutputVo.outputScript);
            }
            transactionVo.outputScripts=outputScripts;

            return unique_ptr<TransactionVo>(new TransactionVo(transactionVo));
        }
        vector<TransactionVo> BlockchainBrowserApplicationService::queryTransactionListByBlockHashTransactionHeight(string blockHash, uint64_t from, uint64_t size){
            unique_ptr<Block> block = blockchainNetCore->getBlockchainCore()->queryBlockByBlockHash(blockHash);
            if(!block.get()){
                return vector<TransactionVo>();
            }
            vector<TransactionVo> transactionVos;
            for(long i=from; i<from+size; i++){
                if(from < 0){
                    break;
                }
                if(i > block->transactionCount){
                    break;
                }
                uint64_t transactionHeight = block->previousTransactionHeight + i;
                unique_ptr<Transaction> transaction = blockchainNetCore->getBlockchainCore()->queryTransactionByTransactionHeight(transactionHeight);
                unique_ptr<TransactionVo> transactionVo = queryTransactionByTransactionHash(transaction->transactionHash);
                transactionVos.push_back(*transactionVo);
            }
            return transactionVos;
        }
        unique_ptr<BlockVo> BlockchainBrowserApplicationService::queryBlockViewByBlockHeight(uint64_t blockHeight){
            unique_ptr<Block> block = blockchainNetCore->getBlockchainCore()->queryBlockByBlockHeight(blockHeight);
            if(!block.get()){
                return unique_ptr<BlockVo>(nullptr);
            }
            uint64_t blockchainHeight = blockchainNetCore->getBlockchainCore()->queryBlockchainHeight();
            unique_ptr<Block> nextBlock = blockchainNetCore->getBlockchainCore()->queryBlockByBlockHeight(block->height+1);

            BlockVo blockVo;
            blockVo.height=block->height;
            blockVo.blockConfirmations = blockchainHeight-block->height+1;;
            blockVo.blockSize=SizeTool::calculateBlockSize(block.get());
            blockVo.transactionCount=BlockTool::getTransactionCount(block.get());
            blockVo.time=TimeUtil::formatMillisecondTimestamp(block->timestamp);
            blockVo.minerIncentiveValue=BlockTool::getWritedIncentiveValue(block.get());
            blockVo.difficulty=BlockTool::formatDifficulty(block->difficulty);
            blockVo.nonce=block->nonce;
            blockVo.hash=block->hash;
            blockVo.previousBlockHash=block->previousHash;
            blockVo.nextBlockHash=!nextBlock.get()?"":nextBlock->hash;
            blockVo.merkleTreeRoot=block->merkleTreeRoot;
            return unique_ptr<BlockVo>(new BlockVo(blockVo));
        }
        unique_ptr<UnconfirmedTransactionVo> BlockchainBrowserApplicationService::queryUnconfirmedTransactionByTransactionHash(string transactionHash){
            try {
                unique_ptr<TransactionDto> transactionDto = blockchainNetCore->getBlockchainCore()->queryUnconfirmedTransactionByTransactionHash(transactionHash);
                if(!transactionDto.get()){
                    return unique_ptr<UnconfirmedTransactionVo>(nullptr);
                }
                unique_ptr<Transaction> transaction = blockchainNetCore->getBlockchainCore()->getBlockchainDatabase()->transactionDto2Transaction(transactionDto.get());
                UnconfirmedTransactionVo transactionDtoVo;
                transactionDtoVo.transactionHash=transaction->transactionHash;

                vector<TransactionInputVo2> inputDtos;
                vector<TransactionInput> &inputs = transaction->inputs;
                if(!inputs.empty()){
                    for(TransactionInput &input:inputs){
                        TransactionInputVo2 transactionInputVo;
                        transactionInputVo.address=input.unspentTransactionOutput.address;
                        transactionInputVo.transactionHash=input.unspentTransactionOutput.transactionHash;
                        transactionInputVo.transactionOutputIndex=input.unspentTransactionOutput.transactionOutputIndex;
                        transactionInputVo.value=input.unspentTransactionOutput.value;
                        inputDtos.push_back(transactionInputVo);
                    }
                }
                transactionDtoVo.transactionInputs=inputDtos;

                vector<TransactionOutputVo2> outputDtos;
                vector<TransactionOutput> outputs = transaction->outputs;
                if(!outputs.empty()){
                    for(TransactionOutput &output:outputs){
                        TransactionOutputVo2 transactionOutputVo;
                        transactionOutputVo.address=output.address;
                        transactionOutputVo.value=output.value;
                        outputDtos.push_back(transactionOutputVo);
                    }
                }
                transactionDtoVo.transactionOutputs=outputDtos;

                return unique_ptr<UnconfirmedTransactionVo>(new UnconfirmedTransactionVo(transactionDtoVo));
            }catch (exception e){
                LogUtil::error("'query unconfirmed transaction by transaction hash' error.",e);
                return unique_ptr<UnconfirmedTransactionVo>(nullptr);
            }
        }
};