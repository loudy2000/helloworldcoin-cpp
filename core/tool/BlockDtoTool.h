//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_BLOCKDTOTOOL_H
#define HELLOWORLDCOIN_CPP_BLOCKDTOTOOL_H


#include "../../netcoredto/netcoredto.h"

using namespace std;


namespace BlockDtoTool {

    string calculateBlockHash(dto::BlockDto *blockDto);
    string calculateBlockMerkleTreeRoot(dto::BlockDto *blockDto);
    bool isBlockEquals(dto::BlockDto *block1, dto::BlockDto *block2);
};


#endif //HELLOWORLDCOIN_CPP_BLOCKDTOTOOL_H
