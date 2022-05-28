//
// author x.king xdotking@gmail.com
//

#include "Consensus.h"
#include "../util/StringUtil.h"
#include "tool/BlockTool.h"
#include "../setting/IncentiveSetting.h"
#include "../setting/GenesisBlockSetting.h"
#include "../util/ByteUtil.h"

namespace core{

    bool Consensus::checkConsensus(BlockchainDatabase *blockchainDatabase, Block *block) {
        string difficulty = block->difficulty;
        if(StringUtil::isEmpty(difficulty)){
            difficulty = calculateDifficult(blockchainDatabase,block);
        }

        string hash = block->hash;
        if(StringUtil::isEmpty(hash)){
            hash = BlockTool::calculateBlockHash(block);
        }
        return ByteUtil::greatThan(difficulty,hash);
    }

    string Consensus::calculateDifficult(BlockchainDatabase *blockchainDatabase, Block *targetBlock) {
        string targetDifficult;
        uint64_t targetBlockHeight = targetBlock->height;
        if(targetBlockHeight <= IncentiveSetting::INTERVAL_BLOCK_COUNT * 2){
            targetDifficult = GenesisBlockSetting::DIFFICULTY;
            return targetDifficult;
        }

        unique_ptr<Block> targetBlockPreviousBlock = blockchainDatabase->queryBlockByBlockHeight(targetBlockHeight-1);
        if (targetBlockPreviousBlock->height % IncentiveSetting::INTERVAL_BLOCK_COUNT != 0){
            targetDifficult = targetBlockPreviousBlock->difficulty;
            return targetDifficult;
        }

        unique_ptr<Block> &previousIntervalLastBlock = targetBlockPreviousBlock;
        unique_ptr<Block> previousPreviousIntervalLastBlock = blockchainDatabase->queryBlockByBlockHeight(previousIntervalLastBlock->height- IncentiveSetting::INTERVAL_BLOCK_COUNT);
        uint64_t previousIntervalActualTimespan = previousIntervalLastBlock->timestamp - previousPreviousIntervalLastBlock->timestamp;


        string hexPreviousIntervalActualTimespan = ByteUtil::bytesToHexString(ByteUtil::uint64ToBytes(previousIntervalActualTimespan));
        string hexIntervalTime = ByteUtil::bytesToHexString(ByteUtil::uint64ToBytes(IncentiveSetting::INTERVAL_TIME));
        return ByteUtil::divide(ByteUtil::multiply(previousIntervalLastBlock->difficulty,hexPreviousIntervalActualTimespan),hexIntervalTime);
    }
}