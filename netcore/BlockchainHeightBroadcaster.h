//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_BLOCKCHAINHEIGHTBROADCASTER_H
#define HELLOWORLDCOIN_CPP_BLOCKCHAINHEIGHTBROADCASTER_H
#include "netcoreconfiguration/NetCoreConfiguration.h"
#include "netcoreserver/NodeServer.h"

using namespace netcoreconfiguration;


namespace netcore{

    class BlockchainHeightBroadcaster {
    private:
        NetCoreConfiguration *netCoreConfiguration;
        BlockchainCore *blockchainCore;
        NodeService *nodeService;
    public:
        BlockchainHeightBroadcaster(NetCoreConfiguration *netCoreConfiguration, BlockchainCore *blockchainCore, NodeService *nodeService);
    public:
        void start();
    private:
        void broadcastBlockchainHeight();
    };

}

#endif //HELLOWORLDCOIN_CPP_BLOCKCHAINHEIGHTBROADCASTER_H
