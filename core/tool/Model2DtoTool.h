//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_MODEL2DTOTOOL_H
#define HELLOWORLDCOIN_CPP_MODEL2DTOTOOL_H


#include "../../netcoredto/netcoredto.h"
#include "../model/model.h"

using namespace dto;
using namespace model;


namespace Model2DtoTool {

    BlockDto block2BlockDto(Block *block) ;
    TransactionDto transaction2TransactionDto(Transaction *transaction) ;
    InputScriptDto inputScript2InputScriptDto(InputScript *inputScript) ;
    OutputScriptDto outputScript2OutputScriptDto(OutputScript *outputScript) ;
    TransactionOutputDto transactionOutput2TransactionOutputDto(TransactionOutput *transactionOutput) ;
};


#endif //HELLOWORLDCOIN_CPP_MODEL2DTOTOOL_H
