//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_SEEDNODEINITIALIZER_H
#define HELLOWORLDCOIN_CPP_SEEDNODEINITIALIZER_H


#include "netcoreconfiguration/NetCoreConfiguration.h"
#include "netcoreserver/NodeServer.h"
#include "../netcoredto/netcoredto.h"

using namespace netcoreconfiguration;
using namespace dto;


namespace netcore{

    class SeedNodeInitializer {
    private:
        NetCoreConfiguration *netCoreConfiguration;
        NodeService *nodeService;
    public:
        SeedNodeInitializer(NetCoreConfiguration *netCoreConfiguration, NodeService *nodeService);
    public:
        void start();
    private:
        void addSeedNodes();
    };

}

#endif //HELLOWORLDCOIN_CPP_SEEDNODEINITIALIZER_H
