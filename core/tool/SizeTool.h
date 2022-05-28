//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_SIZETOOL_H
#define HELLOWORLDCOIN_CPP_SIZETOOL_H


#include "../model/model.h"

using namespace model;


namespace SizeTool {

    //region check Size
    /**
     * check Block Size: used to limit the size of the block.
     */
    bool checkBlockSize(Block *block) ;
    /**
     * Check transaction size: used to limit the size of the transaction.
     */
    bool checkTransactionSize(Transaction *transaction) ;
    //endregion



    //region calculate Size
    uint64_t calculateBlockSize(Block *block) ;
    uint64_t calculateTransactionSize(Transaction *transaction) ;
    //endregion
};


#endif //HELLOWORLDCOIN_CPP_SIZETOOL_H
