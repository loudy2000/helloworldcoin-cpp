//
// author x.king xdotking@gmail.com
//

#include "TransactionDtoTool.h"

#include "BlockDtoTool.h"
#include "../../util/ByteUtil.h"
#include "../../crypto/Sha256Util.h"
#include "../../crypto/AccountUtil.h"
#include "ScriptDtoTool.h"


namespace TransactionDtoTool{

    vector<TransactionOutputDto> transactionOutputDtos(vector<unsigned char> *bytesTransactionOutputs) ;
    TransactionOutputDto transactionOutputDto(vector<unsigned char> bytesTransactionOutput) ;
    vector<TransactionInputDto> transactionInputDtos(vector<unsigned char> *bytesTransactionInputDtos, bool omitInputScript) ;
    TransactionInputDto transactionInputDto(vector<unsigned char> bytesTransactionInputDto, bool omitInputScript) ;




    string calculateTransactionHash(dto::TransactionDto &transactionDto){
        vector<unsigned char> bytesTransaction1 = bytesTransaction(transactionDto,false);
        vector<unsigned char> bytesTransactionHash = Sha256Util::doubleDigest(bytesTransaction1);
        return ByteUtil::bytesToHexString(bytesTransactionHash);
    }

    string getSignatureHashAllRawMaterial(TransactionDto &transactionDto) {
        vector<unsigned char> bytesTransaction0 = bytesTransaction(transactionDto,true);
        vector<unsigned char> sha256Digest = Sha256Util::doubleDigest(bytesTransaction0);
        return ByteUtil::bytesToHexString(sha256Digest);
    }

    string signature(string &privateKey, TransactionDto &transactionDto) {
        string message = getSignatureHashAllRawMaterial(transactionDto);
        vector<unsigned char> bytesMessage = ByteUtil::hexStringToBytes(message);
        string signature0 = AccountUtil::signature(privateKey,bytesMessage);
        return signature0;
    }

    bool verifySignature(TransactionDto &transaction, string &publicKey, vector<unsigned char> &bytesSignature) {
        string message = getSignatureHashAllRawMaterial(transaction);
        vector<unsigned char> bytesMessage = ByteUtil::hexStringToBytes(message);
        return AccountUtil::verifySignature(publicKey,bytesMessage,bytesSignature);
    }

    //region Serialization and Deserialization
    vector<unsigned char> bytesTransaction(TransactionDto &transactionDto, bool omitInputScript) {
        vector<vector<unsigned char>> bytesUnspentTransactionOutputs;
        vector<dto::TransactionInputDto> inputs = transactionDto.inputs;
        if(!inputs.empty()){
            for(dto::TransactionInputDto transactionInputDto:inputs){
                vector<unsigned char>  bytesUnspentTransactionOutput;
                if(omitInputScript){
                    vector<unsigned char>  bytesTransactionHash = ByteUtil::hexStringToBytes(transactionInputDto.transactionHash);
                    vector<unsigned char>  bytesTransactionOutputIndex = ByteUtil::uint64ToBytes(transactionInputDto.transactionOutputIndex);
                    bytesUnspentTransactionOutput = ByteUtil::concatenate(ByteUtil::concatenateLength(bytesTransactionHash),
                                                                          ByteUtil::concatenateLength(bytesTransactionOutputIndex));
                }else {
                    vector<unsigned char>  bytesTransactionHash = ByteUtil::hexStringToBytes(transactionInputDto.transactionHash);
                    vector<unsigned char>  bytesTransactionOutputIndex = ByteUtil::uint64ToBytes(transactionInputDto.transactionOutputIndex);
                    vector<unsigned char> bytesInputScript = ScriptDtoTool::inputScript2Bytes(
                            transactionInputDto.inputScript);
                    bytesUnspentTransactionOutput = ByteUtil::concatenate3(ByteUtil::concatenateLength(bytesTransactionHash),
                                                                           ByteUtil::concatenateLength(bytesTransactionOutputIndex),ByteUtil::concatenateLength(bytesInputScript));
                }
                bytesUnspentTransactionOutputs.push_back(ByteUtil::concatenateLength(bytesUnspentTransactionOutput));
            }
        }

        vector<vector<unsigned char>> bytesTransactionOutputs;
        vector<dto::TransactionOutputDto> outputs = transactionDto.outputs;
        if(!outputs.empty()){
            for(dto::TransactionOutputDto transactionOutputDto:outputs){
                vector<unsigned char>  bytesOutputScript = ScriptDtoTool::outputScript2Bytes(
                        transactionOutputDto.outputScript);
                vector<unsigned char>  bytesValue = ByteUtil::uint64ToBytes(transactionOutputDto.value);
                vector<unsigned char>  bytesTransactionOutput = ByteUtil::concatenate(ByteUtil::concatenateLength(bytesOutputScript),ByteUtil::concatenateLength(bytesValue));
                bytesTransactionOutputs.push_back(ByteUtil::concatenateLength(bytesTransactionOutput));
            }
        }

        vector<unsigned char>  data = ByteUtil::concatenate(ByteUtil::flatAndConcatenateLength(bytesUnspentTransactionOutputs),
                                                            ByteUtil::flatAndConcatenateLength(bytesTransactionOutputs));
        return data;
    }
    TransactionDto transactionDto(vector<unsigned char> bytesTransaction, bool omitInputScript) {
        TransactionDto transactionDto;
        uint64_t start = 0;
        uint64_t bytesTransactionInputDtosLength = ByteUtil::bytesToUint64(ByteUtil::copy(bytesTransaction,start,start + ByteUtil::BYTE8_BYTE_COUNT));
        start += ByteUtil::BYTE8_BYTE_COUNT;
        vector<unsigned char> bytesTransactionInputDtos = ByteUtil::copy(bytesTransaction,start, start+bytesTransactionInputDtosLength);
        start += bytesTransactionInputDtosLength;
        vector<TransactionInputDto> transactionInputDtos0 = transactionInputDtos(&bytesTransactionInputDtos,omitInputScript);
        transactionDto.inputs = transactionInputDtos0;

        uint64_t bytesTransactionOutputsLength = ByteUtil::bytesToUint64(ByteUtil::copy(bytesTransaction,start,start + ByteUtil::BYTE8_BYTE_COUNT));
        start += ByteUtil::BYTE8_BYTE_COUNT;
        vector<unsigned char> bytesTransactionOutputs = ByteUtil::copy(bytesTransaction,start, start+bytesTransactionOutputsLength);
        start += bytesTransactionOutputsLength;
        vector<TransactionOutputDto> transactionOutputDtos0 = transactionOutputDtos(&bytesTransactionOutputs);
        transactionDto.outputs=transactionOutputDtos0;
        return transactionDto;
    }
    vector<TransactionOutputDto> transactionOutputDtos(vector<unsigned char> *bytesTransactionOutputs) {
        if(bytesTransactionOutputs == nullptr || bytesTransactionOutputs->size() == 0){
            return {};
        }
        uint64_t start = 0;
        vector<TransactionOutputDto> transactionOutputDtos;
        while (start < bytesTransactionOutputs->size()){
            uint64_t bytesTransactionOutputDtoLength = ByteUtil::bytesToUint64(ByteUtil::copy(*bytesTransactionOutputs,start,start + ByteUtil::BYTE8_BYTE_COUNT));
            start += ByteUtil::BYTE8_BYTE_COUNT;
            vector<unsigned char> bytesTransactionOutput = ByteUtil::copy(*bytesTransactionOutputs,start, start+bytesTransactionOutputDtoLength);
            start += bytesTransactionOutputDtoLength;
            TransactionOutputDto transactionOutputDto0 = transactionOutputDto(bytesTransactionOutput);
            transactionOutputDtos.push_back(transactionOutputDto0);
            if(start >= bytesTransactionOutputs->size()){
                break;
            }
        }
        return transactionOutputDtos;
    }
    TransactionOutputDto transactionOutputDto(vector<unsigned char> bytesTransactionOutput) {
        uint64_t start = 0;
        uint64_t bytesOutputScriptLength = ByteUtil::bytesToUint64(ByteUtil::copy(bytesTransactionOutput,start,start + ByteUtil::BYTE8_BYTE_COUNT));
        start += ByteUtil::BYTE8_BYTE_COUNT;
        vector<unsigned char> bytesOutputScript = ByteUtil::copy(bytesTransactionOutput,start, start+bytesOutputScriptLength);
        start += bytesOutputScriptLength;
        OutputScriptDto outputScriptDto = ScriptDtoTool::bytes2OutputScript(&bytesOutputScript);

        uint64_t bytesValueLength = ByteUtil::bytesToUint64(ByteUtil::copy(bytesTransactionOutput,start,start + ByteUtil::BYTE8_BYTE_COUNT));
        start += ByteUtil::BYTE8_BYTE_COUNT;
        vector<unsigned char> bytesValue = ByteUtil::copy(bytesTransactionOutput,start, start+bytesValueLength);
        start += bytesValueLength;

        TransactionOutputDto transactionOutputDto;
        transactionOutputDto.outputScript=outputScriptDto;
        transactionOutputDto.value=ByteUtil::bytesToUint64(bytesValue);
        return transactionOutputDto;
    }
    vector<TransactionInputDto> transactionInputDtos(vector<unsigned char> *bytesTransactionInputDtos, bool omitInputScript) {
        if(bytesTransactionInputDtos == nullptr || bytesTransactionInputDtos->size() == 0){
            return {};
        }
        uint64_t start = 0;
        vector<TransactionInputDto> transactionInputDtos;
        while (start < bytesTransactionInputDtos->size()){
            uint64_t bytesTransactionInputDtoLength = ByteUtil::bytesToUint64(ByteUtil::copy(*bytesTransactionInputDtos,start,start + ByteUtil::BYTE8_BYTE_COUNT));
            start += ByteUtil::BYTE8_BYTE_COUNT;
            vector<unsigned char> bytesTransactionInput = ByteUtil::copy(*bytesTransactionInputDtos,start, start+bytesTransactionInputDtoLength);
            start += bytesTransactionInputDtoLength;
            TransactionInputDto transactionInputDto0 = transactionInputDto(bytesTransactionInput,omitInputScript);
            transactionInputDtos.push_back(transactionInputDto0);
            if(start >= bytesTransactionInputDtos->size()){
                break;
            }
        }
        return transactionInputDtos;
    }
    TransactionInputDto transactionInputDto(vector<unsigned char> bytesTransactionInputDto, bool omitInputScript) {
        uint64_t start = 0;
        uint64_t bytesTransactionHashLength = ByteUtil::bytesToUint64(ByteUtil::copy(bytesTransactionInputDto,start,start + ByteUtil::BYTE8_BYTE_COUNT));
        start += ByteUtil::BYTE8_BYTE_COUNT;
        vector<unsigned char> bytesTransactionHash = ByteUtil::copy(bytesTransactionInputDto,start, start+bytesTransactionHashLength);
        start += bytesTransactionHashLength;

        uint64_t bytesTransactionOutputIndexLength = ByteUtil::bytesToUint64(ByteUtil::copy(bytesTransactionInputDto,start,start + ByteUtil::BYTE8_BYTE_COUNT));
        start += ByteUtil::BYTE8_BYTE_COUNT;
        vector<unsigned char> bytesTransactionOutputIndex = ByteUtil::copy(bytesTransactionInputDto,start, start+bytesTransactionOutputIndexLength);
        start += bytesTransactionOutputIndexLength;

        TransactionInputDto transactionInputDto;
        if(!omitInputScript){
            uint64_t bytesOutputScriptLength = ByteUtil::bytesToUint64(ByteUtil::copy(bytesTransactionInputDto,start,start + ByteUtil::BYTE8_BYTE_COUNT));
            start += ByteUtil::BYTE8_BYTE_COUNT;
            vector<unsigned char> bytesOutputScript = ByteUtil::copy(bytesTransactionInputDto,start, start+bytesOutputScriptLength);
            start += bytesOutputScriptLength;
            InputScriptDto inputScriptDto = ScriptDtoTool::bytes2InputScript(&bytesOutputScript);
            transactionInputDto.inputScript=inputScriptDto;
        }
        transactionInputDto.transactionHash=ByteUtil::bytesToHexString(bytesTransactionHash);
        transactionInputDto.transactionOutputIndex=ByteUtil::bytesToUint64(bytesTransactionOutputIndex);
        return transactionInputDto;
    }
    //endregion
}
