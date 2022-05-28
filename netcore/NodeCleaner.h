//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_NODECLEANER_H
#define HELLOWORLDCOIN_CPP_NODECLEANER_H


#include "netcoreconfiguration/NetCoreConfiguration.h"
#include "netcoreserver/NodeServer.h"

using namespace netcoreconfiguration;


namespace netcore{

    class NodeCleaner {
    private:
        NetCoreConfiguration *netCoreConfiguration;
        NodeService *nodeService;
    public:
        NodeCleaner(NetCoreConfiguration *netCoreConfiguration, NodeService *nodeService);
    public:
        void start();
    private:
        void cleanDeadNodes();
    };

}


#endif //HELLOWORLDCOIN_CPP_NODECLEANER_H
