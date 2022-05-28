//
// author x.king xdotking@gmail.com
//

#include "SeedNodeInitializer.h"
#include "../util/LogUtil.h"
#include "../util/ThreadUtil.h"
#include "../setting/NetworkSetting.h"


namespace netcore{

    SeedNodeInitializer::SeedNodeInitializer(NetCoreConfiguration *netCoreConfiguration, NodeService *nodeService){
        this->netCoreConfiguration = netCoreConfiguration;
        this->nodeService = nodeService;
    }

    void SeedNodeInitializer::start(){
        try {
            while (true){
                addSeedNodes();
                ThreadUtil::millisecondSleep(netCoreConfiguration->getSeedNodeInitializeTimeInterval());
            }
        } catch (exception e) {
            LogUtil::error("'add seed nodes' error.",e);
        }
    }

    void SeedNodeInitializer::addSeedNodes(){
        if(!netCoreConfiguration->isAutoSearchNode()){
            return;
        }

        for(string seedNode: NetworkSetting::SEED_NODES){
            Node node{};
            node.ip=seedNode;
            node.blockchainHeight=0;
            nodeService->addNode(node);
        }
    }

}