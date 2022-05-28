//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_BLOCKCHAINNETCOREFACTORY_H
#define HELLOWORLDCOIN_CPP_BLOCKCHAINNETCOREFACTORY_H

#include "BlockchainNetCore.h"



namespace netcore {


    namespace BlockchainNetCoreFactory{

        BlockchainNetCore *createDefaultBlockchainNetCore();
        BlockchainNetCore *createBlockchainNetCore(string netcorePath);
    }
};


#endif //HELLOWORLDCOIN_CPP_BLOCKCHAINNETCOREFACTORY_H
