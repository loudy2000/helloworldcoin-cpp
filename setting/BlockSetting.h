//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_BLOCKSETTING_H
#define HELLOWORLDCOIN_CPP_BLOCKSETTING_H


#include <cstdint>

namespace BlockSetting {

    //max transaction count of block
    extern uint64_t BLOCK_MAX_TRANSACTION_COUNT;
    //max character count of block
    extern uint64_t BLOCK_MAX_CHARACTER_COUNT;
    //the character count of nonce
    extern uint64_t NONCE_CHARACTER_COUNT;
};


#endif //HELLOWORLDCOIN_CPP_BLOCKSETTING_H
