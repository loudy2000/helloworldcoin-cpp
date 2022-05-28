//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_BLOCKBROADCASTER_H
#define HELLOWORLDCOIN_CPP_BLOCKBROADCASTER_H


#include "netcoreconfiguration/NetCoreConfiguration.h"
#include "netcoreserver/NodeServer.h"


using namespace netcoreconfiguration;

namespace netcore{

    class BlockBroadcaster {
    private:
        NetCoreConfiguration *netCoreConfiguration;
        BlockchainCore *blockchainCore;
        NodeService *nodeService;
    public:
        BlockBroadcaster(NetCoreConfiguration *netCoreConfiguration, BlockchainCore *blockchainCore, NodeService *nodeService);
    public:
        void start();
    private:
        void broadcastBlock();
    };

}


#endif //HELLOWORLDCOIN_CPP_BLOCKBROADCASTER_H
