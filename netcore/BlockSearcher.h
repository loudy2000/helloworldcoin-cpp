//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_BLOCKSEARCHER_H
#define HELLOWORLDCOIN_CPP_BLOCKSEARCHER_H


#include "netcoreconfiguration/NetCoreConfiguration.h"
#include "netcoreserver/NodeServer.h"


using namespace netcoreconfiguration;

namespace netcore{

    class BlockSearcher {
    private:
     NetCoreConfiguration *netCoreConfiguration;
     NodeService *nodeService;
     BlockchainCore *blockchainCore;
     BlockchainCore *slaveBlockchainCore;
    public:
        BlockSearcher(NetCoreConfiguration *netCoreConfiguration, BlockchainCore *blockchainCore
                , BlockchainCore *slaveBlockchainCore, NodeService *nodeService);
    public:
        void start();
    private:
        void searchNodesBlocks();
        void searchNodeBlocks(BlockchainCore *masterBlockchainCore, BlockchainCore *slaveBlockchainCore, Node node);
        void duplicateBlockchainCore(BlockchainCore *fromBlockchainCore,BlockchainCore *toBlockchainCore);
        void promoteBlockchainCore(BlockchainCore *fromBlockchainCore, BlockchainCore *toBlockchainCore);
        uint64_t getForkBlockHeight(BlockchainCore *blockchainCore, Node node);
        void synchronizeBlocks(BlockchainCore *blockchainCore, Node node, uint64_t startBlockHeight);
        bool isForkNode(BlockchainCore *blockchainCore, Node node);
        bool isHardFork(BlockchainCore *blockchainCore1, BlockchainCore *blockchainCore2);
        bool isHardForkNode(BlockchainCore *blockchainCore, Node node);
    };

}


#endif //HELLOWORLDCOIN_CPP_BLOCKSEARCHER_H
