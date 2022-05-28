//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_BLOCKCHAINCOREFACTORY_H
#define HELLOWORLDCOIN_CPP_BLOCKCHAINCOREFACTORY_H


#include "BlockchainCore.h"

namespace core{
    namespace BlockchainCoreFactory {
        BlockchainCore* createDefaultBlockchainCore();
        BlockchainCore* createBlockchainCore(string corePath);
    };
}


#endif //HELLOWORLDCOIN_CPP_BLOCKCHAINCOREFACTORY_H
