//
// author x.king xdotking@gmail.com
//

#include "ScriptDtoTool.h"
#include "../model/model.h"
#include "../../util/StringUtil.h"
#include "../../util/ByteUtil.h"
#include "../../crypto/AccountUtil.h"

using namespace model;

namespace ScriptDtoTool{

    //region Serialization and Deserialization
    vector<unsigned char> inputScript2Bytes(dto::InputScriptDto inputScript){
        return script2Bytes(inputScript);
    }
    vector<unsigned char> outputScript2Bytes(dto::OutputScriptDto outputScript){
        return script2Bytes(outputScript);
    }
    vector<unsigned char> script2Bytes(dto::ScriptDto script) {
        vector<unsigned char> bytesScript;
        for(int i=0;i<script.size();i++){
            string operationCode = script[i];
            vector<unsigned char> bytesOperationCode = ByteUtil::hexStringToBytes(operationCode);
            if(ByteUtil::equals(model::OperationCodeEnum::OP_DUP.code,bytesOperationCode) ||
               ByteUtil::equals(model::OperationCodeEnum::OP_HASH160.code,bytesOperationCode) ||
               ByteUtil::equals(model::OperationCodeEnum::OP_EQUALVERIFY.code,bytesOperationCode) ||
               ByteUtil::equals(model::OperationCodeEnum::OP_CHECKSIG.code,bytesOperationCode)){
                bytesScript = ByteUtil::concatenate(bytesScript, ByteUtil::concatenateLength(bytesOperationCode));
            }else if(ByteUtil::equals(model::OperationCodeEnum::OP_PUSHDATA.code,bytesOperationCode)){
                string operationData = script[++i];
                vector<unsigned char> bytesOperationData = ByteUtil::hexStringToBytes(operationData);
                bytesScript = ByteUtil::concatenate3(bytesScript, ByteUtil::concatenateLength(bytesOperationCode), ByteUtil::concatenateLength(bytesOperationData));
            }else {
                throw exception("Unrecognized OperationCode.");
            }
        }
        return bytesScript;
    }
    InputScriptDto bytes2InputScript(vector<unsigned char> *bytesScript) {
        if(bytesScript == nullptr || bytesScript->size() == 0){
            return InputScriptDto{};
        }
        InputScriptDto inputScriptDto;
        vector<string> script0 = bytes2Script(bytesScript);
        for (string s:script0) {
            inputScriptDto.push_back(s);
        }
        return inputScriptDto;
    }
    OutputScriptDto bytes2OutputScript(vector<unsigned char> *bytesScript) {
        if(bytesScript == nullptr || bytesScript->size() == 0){
            return OutputScriptDto{};
        }
        OutputScriptDto outputScriptDto;
        vector<string> script0 = bytes2Script(bytesScript);
        for (string s:script0) {
            outputScriptDto.push_back(s);
        }
        return outputScriptDto;
    }
    vector<string> bytes2Script(vector<unsigned char> *bytesScript) {
        if(bytesScript == nullptr || bytesScript->size() == 0){
            return {};
        }
        uint64_t start = 0;
        vector<string> script;
        while (start<bytesScript->size()){
            uint64_t bytesOperationCodeLength = ByteUtil::bytesToUint64(ByteUtil::copy(*bytesScript,start,start + ByteUtil::BYTE8_BYTE_COUNT));
            start += ByteUtil::BYTE8_BYTE_COUNT;
            vector<unsigned char> bytesOperationCode = ByteUtil::copy(*bytesScript,start, start+bytesOperationCodeLength);
            start += bytesOperationCodeLength;
            if(ByteUtil::equals(OperationCodeEnum::OP_DUP.code,bytesOperationCode) ||
               ByteUtil::equals(OperationCodeEnum::OP_HASH160.code,bytesOperationCode) ||
               ByteUtil::equals(OperationCodeEnum::OP_EQUALVERIFY.code,bytesOperationCode) ||
               ByteUtil::equals(OperationCodeEnum::OP_CHECKSIG.code,bytesOperationCode)){
                string stringOperationCode = ByteUtil::bytesToHexString(bytesOperationCode);
                script.push_back(stringOperationCode);
            }else if(ByteUtil::equals(OperationCodeEnum::OP_PUSHDATA.code,bytesOperationCode)){
                string stringOperationCode = ByteUtil::bytesToHexString(bytesOperationCode);
                script.push_back(stringOperationCode);

                uint64_t bytesOperationDataLength = ByteUtil::bytesToUint64(ByteUtil::copy(*bytesScript,start,start + ByteUtil::BYTE8_BYTE_COUNT));
                start += ByteUtil::BYTE8_BYTE_COUNT;
                vector<unsigned char> bytesOperationData = ByteUtil::copy(*bytesScript,start, start+bytesOperationDataLength);
                start += bytesOperationDataLength;
                string stringOperationData = ByteUtil::bytesToHexString(bytesOperationData);
                script.push_back(stringOperationData);
            }else {
                throw exception("Unrecognized OperationCode.");
            }
        }
        return script;
    }
    //endregion



    InputScriptDto createPayToPublicKeyHashInputScript(string sign, string publicKey) {
        InputScriptDto script;
        script.push_back(ByteUtil::bytesToHexString(OperationCodeEnum::OP_PUSHDATA.code));
        script.push_back(sign);
        script.push_back(ByteUtil::bytesToHexString(OperationCodeEnum::OP_PUSHDATA.code));
        script.push_back(publicKey);
        return script;
    }
    OutputScriptDto createPayToPublicKeyHashOutputScript(string address) {
        OutputScriptDto script;
        script.push_back(ByteUtil::bytesToHexString(OperationCodeEnum::OP_DUP.code));
        script.push_back(ByteUtil::bytesToHexString(OperationCodeEnum::OP_HASH160.code));
        script.push_back(ByteUtil::bytesToHexString(OperationCodeEnum::OP_PUSHDATA.code));
        string publicKeyHash = AccountUtil::publicKeyHashFromAddress(address);
        script.push_back(publicKeyHash);
        script.push_back(ByteUtil::bytesToHexString(OperationCodeEnum::OP_EQUALVERIFY.code));
        script.push_back(ByteUtil::bytesToHexString(OperationCodeEnum::OP_CHECKSIG.code));
        return script;
    }
    bool isPayToPublicKeyHashInputScript(InputScriptDto inputScriptDto) {
        return (inputScriptDto.size() == 4) &&
               (StringUtil::equals(ByteUtil::bytesToHexString(OperationCodeEnum::OP_PUSHDATA.code), inputScriptDto[0])) &&
               (136 <= inputScriptDto[1].length() && 144 >= inputScriptDto[1].length()) &&
               (StringUtil::equals(ByteUtil::bytesToHexString(OperationCodeEnum::OP_PUSHDATA.code), inputScriptDto[2])) &&
               (66 == inputScriptDto[3].length());
    }
    bool isPayToPublicKeyHashOutputScript(OutputScriptDto outputScriptDto) {
        return (outputScriptDto.size() == 6) &&
               (StringUtil::equals(ByteUtil::bytesToHexString(OperationCodeEnum::OP_DUP.code), outputScriptDto[0])) &&
               (StringUtil::equals(ByteUtil::bytesToHexString(OperationCodeEnum::OP_HASH160.code), outputScriptDto[1])) &&
               (StringUtil::equals(ByteUtil::bytesToHexString(OperationCodeEnum::OP_PUSHDATA.code), outputScriptDto[2])) &&
               (40 == outputScriptDto[3].length()) &&
               (StringUtil::equals(ByteUtil::bytesToHexString(OperationCodeEnum::OP_EQUALVERIFY.code),
                                   outputScriptDto[4])) &&
               (StringUtil::equals(ByteUtil::bytesToHexString(OperationCodeEnum::OP_CHECKSIG.code), outputScriptDto[5]));
    }
    string getPublicKeyHashFromPayToPublicKeyHashOutputScript(OutputScriptDto outputScript) {
        return outputScript[3];
    }

}