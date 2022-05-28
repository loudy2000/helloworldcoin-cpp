//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_SCRIPTTOOL_H
#define HELLOWORLDCOIN_CPP_SCRIPTTOOL_H


#include <string>
#include "../model/model.h"

using namespace model;
using namespace std;

namespace ScriptTool {

    string inputScript2String(InputScript inputScript) ;
    string outputScript2String(OutputScript outputScript) ;
    string script2String(Script script) ;


    Script createScript(InputScript inputScript, OutputScript outputScript) ;
    InputScript createPayToPublicKeyHashInputScript(string sign, string publicKey) ;
    OutputScript createPayToPublicKeyHashOutputScript(string address) ;


    bool isPayToPublicKeyHashInputScript(InputScript *inputScript) ;
    bool isPayToPublicKeyHashOutputScript(OutputScript *outputScript) ;
};


#endif //HELLOWORLDCOIN_CPP_SCRIPTTOOL_H
