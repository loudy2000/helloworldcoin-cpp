//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_STRUCTURETOOL_H
#define HELLOWORLDCOIN_CPP_STRUCTURETOOL_H


#include "../model/model.h"

using namespace model;

namespace StructureTool {

    /**
     * Check Block Structure
     */
    bool checkBlockStructure(Block *block) ;
    /**
     * Check Transaction Structure
     */
    bool checkTransactionStructure(Transaction *transaction) ;
};


#endif //HELLOWORLDCOIN_CPP_STRUCTURETOOL_H
