//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_BLOCKTOOL_H
#define HELLOWORLDCOIN_CPP_BLOCKTOOL_H


#include "../model/model.h"
#include <string>

using namespace std;
using namespace model;

namespace BlockTool {

    string calculateBlockHash(Block *block) ;
    string calculateBlockMerkleTreeRoot(Block *block) ;
    bool isExistDuplicateNewHash(Block *block) ;
    bool isExistDuplicateNewAddress(Block *block) ;
    bool isExistDuplicateUtxo(Block *block) ;
    bool checkPreviousBlockHash(unique_ptr<Block> &previousBlock, Block *currentBlock) ;
    bool checkBlockHeight(unique_ptr<Block> &previousBlock, Block *currentBlock) ;
    bool checkBlockTimestamp(unique_ptr<Block> &previousBlock, Block *currentBlock) ;
    uint64_t getTransactionCount(Block *block) ;
    bool isBlockEquals(Block *block1, Block *block2) ;
    uint64_t getWritedIncentiveValue(Block *block) ;
    string formatDifficulty(string difficulty) ;
    uint64_t getTransactionOutputCount(Block *block) ;
    uint64_t getBlockFee(Block *block) ;
    uint64_t getNextBlockHeight(unique_ptr<Block> &currentBlock) ;
};


#endif //HELLOWORLDCOIN_CPP_BLOCKTOOL_H
