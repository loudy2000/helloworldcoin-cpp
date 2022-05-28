//
// author x.king xdotking@gmail.com
//

#include "BlockchainNetCoreFactory.h"
#include "../core/tool/ResourceTool.h"
#include "../util/FileUtil.h"
#include "../core/BlockchainCoreFactory.h"


namespace netcore {


    namespace BlockchainNetCoreFactory{

        BlockchainNetCore *createDefaultBlockchainNetCore(){
            return createBlockchainNetCore(ResourceTool::getDataRootPath());
        }
        BlockchainNetCore *createBlockchainNetCore(string netcorePath){
            NetCoreConfiguration *netCoreConfiguration = new NetCoreConfiguration(netcorePath);

            string blockchainCorePath = FileUtil::newPath(netcorePath,"BlockchainCore");
            BlockchainCore *blockchainCore = BlockchainCoreFactory::createBlockchainCore(blockchainCorePath);
            string slaveBlockchainCorePath = FileUtil::newPath(netcorePath,"SlaveBlockchainCore");
            BlockchainCore *slaveBlockchainCore = BlockchainCoreFactory::createBlockchainCore(slaveBlockchainCorePath);


            NodeDao *nodeDao = new NodeDao(netCoreConfiguration);
            NodeService *nodeService = new NodeService(nodeDao);
            NodeServer *nodeServer = new NodeServer(netCoreConfiguration,blockchainCore,nodeService);

            SeedNodeInitializer *seedNodeInitializer = new SeedNodeInitializer(netCoreConfiguration,nodeService);
            NodeSearcher *nodeSearcher = new NodeSearcher(netCoreConfiguration,nodeService);
            NodeBroadcaster *nodeBroadcaster = new NodeBroadcaster(netCoreConfiguration,nodeService);
            NodeCleaner *nodeCleaner = new NodeCleaner(netCoreConfiguration,nodeService);

            BlockchainHeightSearcher *blockchainHeightSearcher = new BlockchainHeightSearcher(netCoreConfiguration,nodeService);
            BlockchainHeightBroadcaster *blockchainHeightBroadcaster = new BlockchainHeightBroadcaster(netCoreConfiguration,blockchainCore,nodeService);

            BlockSearcher *blockSearcher = new BlockSearcher(netCoreConfiguration,blockchainCore,slaveBlockchainCore,nodeService);
            BlockBroadcaster *blockBroadcaster = new BlockBroadcaster(netCoreConfiguration,blockchainCore,nodeService);

            UnconfirmedTransactionsSearcher *unconfirmedTransactionsSearcher = new UnconfirmedTransactionsSearcher(netCoreConfiguration,blockchainCore,nodeService);

            BlockchainNetCore *blockchainNetCore
                    = new BlockchainNetCore(netCoreConfiguration, blockchainCore, nodeServer, nodeService
                            , seedNodeInitializer, nodeSearcher, nodeBroadcaster, nodeCleaner
                            , blockchainHeightSearcher, blockchainHeightBroadcaster
                            , blockSearcher, blockBroadcaster
                            , unconfirmedTransactionsSearcher
                    );
            return blockchainNetCore;
        }
    }
};