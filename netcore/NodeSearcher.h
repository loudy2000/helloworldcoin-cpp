//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_NODESEARCHER_H
#define HELLOWORLDCOIN_CPP_NODESEARCHER_H

#include "netcoreconfiguration/NetCoreConfiguration.h"
#include "netcoreserver/NodeServer.h"
#include "../netcoredto/netcoredto.h"

using namespace netcoreconfiguration;
using namespace dto;


namespace netcore{

    class NodeSearcher {
    private:
        NetCoreConfiguration *netCoreConfiguration;
        NodeService *nodeService;
    public:
        NodeSearcher(NetCoreConfiguration *netCoreConfiguration, NodeService *nodeService);
    public:
        void start();
    private:
        void searchNodes();
        void handleGetNodesResponse(unique_ptr<GetNodesResponse>& getNodesResponse);
    };

}


#endif //HELLOWORLDCOIN_CPP_NODESEARCHER_H
