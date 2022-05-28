//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_SCRIPTDTOTOOL_H
#define HELLOWORLDCOIN_CPP_SCRIPTDTOTOOL_H


#include "../../netcoredto/netcoredto.h"

using namespace dto;

namespace ScriptDtoTool {


    //region Serialization and Deserialization
    vector<unsigned char> inputScript2Bytes(dto::InputScriptDto inputScript);
    vector<unsigned char> outputScript2Bytes(dto::OutputScriptDto outputScript);
    vector<unsigned char> script2Bytes(dto::ScriptDto script);
    InputScriptDto bytes2InputScript(vector<unsigned char> *bytesScript) ;
    OutputScriptDto bytes2OutputScript(vector<unsigned char> *bytesScript) ;
    vector<string> bytes2Script(vector<unsigned char> *bytesScript) ;
    //endregion


    InputScriptDto createPayToPublicKeyHashInputScript(string sign, string publicKey) ;
    OutputScriptDto createPayToPublicKeyHashOutputScript(string address) ;
    bool isPayToPublicKeyHashInputScript(InputScriptDto inputScriptDto) ;
    bool isPayToPublicKeyHashOutputScript(OutputScriptDto outputScriptDto) ;
    string getPublicKeyHashFromPayToPublicKeyHashOutputScript(OutputScriptDto outputScript) ;

};


#endif //HELLOWORLDCOIN_CPP_SCRIPTDTOTOOL_H
