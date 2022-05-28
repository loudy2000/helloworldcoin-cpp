//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_DTOSIZETOOL_H
#define HELLOWORLDCOIN_CPP_DTOSIZETOOL_H


#include "../../netcoredto/netcoredto.h"

using namespace dto;

namespace DtoSizeTool {
    //region check Size
    /**
     * check Block Size: used to limit the size of the block.
     */
    bool checkBlockSize(BlockDto *blockDto) ;
    /**
     * Check transaction size: used to limit the size of the transaction.
     */
    bool checkTransactionSize(TransactionDto *transactionDto) ;
    /**
     * check Input Script Size
     */
    bool checkInputScriptSize(InputScriptDto *inputScriptDto) ;
    /**
     * check Output Script Size
     */
    bool checkOutputScriptSize(OutputScriptDto *outputScriptDto) ;
    /**
     * check Script Size
     */
    bool checkScriptSize(ScriptDto *scriptDto) ;
    //endregion


    //region calculate Size
    uint64_t calculateBlockSize(BlockDto *blockDto) ;
    uint64_t calculateTransactionSize(TransactionDto *transactionDto) ;
    //endregion
};


#endif //HELLOWORLDCOIN_CPP_DTOSIZETOOL_H
