//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_NODEBROADCASTER_H
#define HELLOWORLDCOIN_CPP_NODEBROADCASTER_H


#include "netcoreconfiguration/NetCoreConfiguration.h"
#include "netcoreserver/NodeServer.h"

using namespace netcoreconfiguration;


namespace netcore{

    class NodeBroadcaster {
    private:
        NetCoreConfiguration *netCoreConfiguration;
        NodeService *nodeService;
    public:
        NodeBroadcaster(NetCoreConfiguration *netCoreConfiguration, NodeService *nodeService);
    public:
        void start();
    private:
        void broadcastNode();
    };

}

#endif //HELLOWORLDCOIN_CPP_NODEBROADCASTER_H
