//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_BLOCKCHAINNETCORE_H
#define HELLOWORLDCOIN_CPP_BLOCKCHAINNETCORE_H


#include "UnconfirmedTransactionsSearcher.h"
#include "netcoreserver/NodeServer.h"

#include "SeedNodeInitializer.h"
#include "NodeSearcher.h"
#include "NodeBroadcaster.h"
#include "NodeCleaner.h"

#include "BlockchainHeightSearcher.h"
#include "BlockchainHeightBroadcaster.h"

#include "BlockSearcher.h"
#include "BlockBroadcaster.h"

using namespace server;


namespace netcore {

    class BlockchainNetCore {
    private:
        NetCoreConfiguration *netCoreConfiguration;
        NodeService *nodeService;

        BlockchainCore *blockchainCore;
        NodeServer *nodeServer;

        SeedNodeInitializer *seedNodeInitializer;
        NodeSearcher *nodeSearcher;
        NodeBroadcaster *nodeBroadcaster;
        NodeCleaner *nodeCleaner;

        BlockchainHeightSearcher *blockchainHeightSearcher;
        BlockchainHeightBroadcaster *blockchainHeightBroadcaster;

        BlockSearcher *blockSearcher;
        BlockBroadcaster *blockBroadcaster;

        UnconfirmedTransactionsSearcher *unconfirmedTransactionsSearcher;

    public:
        BlockchainNetCore(NetCoreConfiguration *netCoreConfiguration, BlockchainCore *blockchainCore,
                          NodeServer *nodeServer, NodeService *nodeService, SeedNodeInitializer *seedNodeInitializer,
                          NodeSearcher *nodeSearcher, NodeBroadcaster *nodeBroadcaster, NodeCleaner *nodeCleaner,
                          BlockchainHeightSearcher *blockchainHeightSearcher,
                          BlockchainHeightBroadcaster *blockchainHeightBroadcaster, BlockSearcher *blockSearcher,
                          BlockBroadcaster *blockBroadcaster,
                          UnconfirmedTransactionsSearcher *unconfirmedTransactionsSearcher
        );

    public:
        void start();


    public:
        NetCoreConfiguration *getNetCoreConfiguration();

        BlockchainCore *getBlockchainCore();

        NodeServer *getNodeServer();

        NodeService *getNodeService();

        SeedNodeInitializer *getSeedNodeInitializer();

        NodeSearcher *getNodeSearcher();

        NodeBroadcaster *getNodeBroadcaster();

        NodeCleaner *getNodeCleaner();

        BlockchainHeightSearcher *getBlockchainHeightSearcher();

        BlockchainHeightBroadcaster *getBlockchainHeightBroadcaster();

        BlockSearcher *getBlockSearcher();

        BlockBroadcaster *getBlockBroadcaster();

        UnconfirmedTransactionsSearcher *getUnconfirmedTransactionsSearcher();
    };

}

#endif //HELLOWORLDCOIN_CPP_BLOCKCHAINNETCORE_H
