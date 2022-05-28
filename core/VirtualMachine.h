//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_VIRTUALMACHINE_H
#define HELLOWORLDCOIN_CPP_VIRTUALMACHINE_H

#include "model/model.h"
using namespace std;
using namespace model;

namespace core{

    class VirtualMachine {
    public:
        ScriptExecuteResult executeScript(Transaction transactionEnvironment, Script script);
    };
}



#endif //HELLOWORLDCOIN_CPP_VIRTUALMACHINE_H
