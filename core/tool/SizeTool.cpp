//
// author x.king xdotking@gmail.com
//

#include "SizeTool.h"
#include "DtoSizeTool.h"
#include "Model2DtoTool.h"

namespace SizeTool{

    //region check Size
    bool checkBlockSize(Block *block) {
        BlockDto blockDto = Model2DtoTool::block2BlockDto(block);
        return DtoSizeTool::checkBlockSize(&blockDto);
    }
    bool checkTransactionSize(Transaction *transaction) {
        TransactionDto transactionDto = Model2DtoTool::transaction2TransactionDto(transaction);
        return DtoSizeTool::checkTransactionSize(&transactionDto);
    }
    //endregion


    //region calculate Size
    uint64_t calculateBlockSize(Block *block) {
        BlockDto blockDto = Model2DtoTool::block2BlockDto(block);
        return DtoSizeTool::calculateBlockSize(&blockDto);
    }
    uint64_t calculateTransactionSize(Transaction *transaction) {
        TransactionDto transactionDto = Model2DtoTool::transaction2TransactionDto(transaction);
        return DtoSizeTool::calculateTransactionSize(&transactionDto);
    }
    //endregion
}