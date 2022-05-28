//
// author x.king xdotking@gmail.com
//

#include "Incentive.h"
#include "tool/BlockTool.h"
#include "../setting/IncentiveSetting.h"

namespace core{

    uint64_t getMinerSubsidy(Block *block);

    uint64_t Incentive::incentiveValue(BlockchainDatabase *blockchainDatabase, Block *block) {
        uint64_t minerSubsidy = getMinerSubsidy(block);
        uint64_t minerFee = BlockTool::getBlockFee(block);
        return minerSubsidy + minerFee;
    }

    bool Incentive::checkIncentive(BlockchainDatabase *blockchainDatabase, Block *block) {
        uint64_t writeIncentiveValue = BlockTool::getWritedIncentiveValue(block);
        uint64_t targetIncentiveValue = incentiveValue(blockchainDatabase,block);
        if(writeIncentiveValue != targetIncentiveValue){
            return false;
        }
        return true;
    }

    uint64_t getMinerSubsidy(Block *block) {
        uint64_t initCoin = IncentiveSetting::BLOCK_INIT_INCENTIVE;
        uint64_t multiple = (block->height - 1L) / IncentiveSetting::INCENTIVE_HALVE_INTERVAL;
        while (multiple > 0){
            initCoin = initCoin / 2L;
            --multiple;
        }
        return initCoin;
    }
}