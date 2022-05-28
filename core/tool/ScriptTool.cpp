//
// author x.king xdotking@gmail.com
//

#include "ScriptTool.h"
#include "Model2DtoTool.h"
#include "ScriptDtoTool.h"
#include "../../util/ByteUtil.h"
#include "../../crypto/AccountUtil.h"
#include "../../util/StringUtil.h"

using namespace model;

namespace ScriptTool{

    string inputScript2String(InputScript inputScript) {
        return script2String(inputScript);
    }
    string outputScript2String(OutputScript outputScript) {
        return script2String(outputScript);
    }
    string script2String(Script script) {
        string stringScript = "";
        for(int i=0;i<script.size();i++){
            string operationCode = script[i];
            vector<unsigned char> bytesOperationCode = ByteUtil::hexStringToBytes(operationCode);
            if(ByteUtil::equals(OperationCodeEnum::OP_DUP.code,bytesOperationCode)){
                stringScript = StringUtil::concatenate3(stringScript,OperationCodeEnum::OP_DUP.name,StringUtil::BLANKSPACE);
            }else if(ByteUtil::equals(OperationCodeEnum::OP_HASH160.code,bytesOperationCode)){
                stringScript = StringUtil::concatenate3(stringScript,OperationCodeEnum::OP_HASH160.name,StringUtil::BLANKSPACE);
            }else if(ByteUtil::equals(OperationCodeEnum::OP_EQUALVERIFY.code,bytesOperationCode)){
                stringScript = StringUtil::concatenate3(stringScript,OperationCodeEnum::OP_EQUALVERIFY.name,StringUtil::BLANKSPACE);
            }else if(ByteUtil::equals(OperationCodeEnum::OP_CHECKSIG.code,bytesOperationCode)){
                stringScript = StringUtil::concatenate3(stringScript,OperationCodeEnum::OP_CHECKSIG.name,StringUtil::BLANKSPACE);
            }else if(ByteUtil::equals(OperationCodeEnum::OP_PUSHDATA.code,bytesOperationCode)){
                string operationData = script[++i];
                stringScript = StringUtil::concatenate3(stringScript,OperationCodeEnum::OP_PUSHDATA.name,StringUtil::BLANKSPACE);
                stringScript = StringUtil::concatenate3(stringScript,operationData,StringUtil::BLANKSPACE);
            }else {
                throw exception("Unrecognized OperationCode.");
            }
        }
        return stringScript;
    }




    Script createScript(InputScript inputScript, OutputScript outputScript) {
        Script script;
        for (string s:inputScript) {
            script.push_back(s);
        }
        for (string s:outputScript) {
            script.push_back(s);
        }
        return script;
    }
    InputScript createPayToPublicKeyHashInputScript(string sign, string publicKey) {
        InputScript script;
        script.push_back(ByteUtil::bytesToHexString(OperationCodeEnum::OP_PUSHDATA.code));
        script.push_back(sign);
        script.push_back(ByteUtil::bytesToHexString(OperationCodeEnum::OP_PUSHDATA.code));
        script.push_back(publicKey);
        return script;
    }
    OutputScript createPayToPublicKeyHashOutputScript(string address) {
        OutputScript script;
        script.push_back(ByteUtil::bytesToHexString(OperationCodeEnum::OP_DUP.code));
        script.push_back(ByteUtil::bytesToHexString(OperationCodeEnum::OP_HASH160.code));
        script.push_back(ByteUtil::bytesToHexString(OperationCodeEnum::OP_PUSHDATA.code));
        string publicKeyHash = AccountUtil::publicKeyHashFromAddress(address);
        script.push_back(publicKeyHash);
        script.push_back(ByteUtil::bytesToHexString(OperationCodeEnum::OP_EQUALVERIFY.code));
        script.push_back(ByteUtil::bytesToHexString(OperationCodeEnum::OP_CHECKSIG.code));
        return script;
    }




    bool isPayToPublicKeyHashInputScript(InputScript *inputScript) {
        InputScriptDto inputScriptDto = Model2DtoTool::inputScript2InputScriptDto(inputScript);
        return ScriptDtoTool::isPayToPublicKeyHashInputScript(inputScriptDto);
    }
    bool isPayToPublicKeyHashOutputScript(OutputScript *outputScript) {
        OutputScriptDto outputScriptDto = Model2DtoTool::outputScript2OutputScriptDto(outputScript);
        return ScriptDtoTool::isPayToPublicKeyHashOutputScript(outputScriptDto);
    }
}