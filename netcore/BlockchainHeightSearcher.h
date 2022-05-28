//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_BLOCKCHAINHEIGHTSEARCHER_H
#define HELLOWORLDCOIN_CPP_BLOCKCHAINHEIGHTSEARCHER_H
#include "netcoreconfiguration/NetCoreConfiguration.h"
#include "netcoreserver/NodeServer.h"

using namespace netcoreconfiguration;


namespace netcore{

    class BlockchainHeightSearcher {
    private:
        NetCoreConfiguration *netCoreConfiguration;
        NodeService *nodeService;
    public:
        BlockchainHeightSearcher(NetCoreConfiguration *netCoreConfiguration, NodeService *nodeService);
    public:
        void start();
    private:
        void searchBlockchainHeight();
    };

}

#endif //HELLOWORLDCOIN_CPP_BLOCKCHAINHEIGHTSEARCHER_H
