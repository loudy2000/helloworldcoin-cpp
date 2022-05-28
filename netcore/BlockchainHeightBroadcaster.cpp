//
// author x.king xdotking@gmail.com
//

#include "BlockchainHeightBroadcaster.h"
#include "../netcoreclient/NodeClient.h"
#include "../util/LogUtil.h"
#include "../util/ThreadUtil.h"

using namespace netcoreclient;

namespace netcore{

    BlockchainHeightBroadcaster::BlockchainHeightBroadcaster(NetCoreConfiguration *netCoreConfiguration, BlockchainCore *blockchainCore, NodeService *nodeService){
        this->netCoreConfiguration = netCoreConfiguration;
        this->blockchainCore = blockchainCore;
        this->nodeService = nodeService;
    }
    void BlockchainHeightBroadcaster::start(){
        try {
            while (true){
                broadcastBlockchainHeight();
                ThreadUtil::millisecondSleep(netCoreConfiguration->getBlockchainHeightBroadcastTimeInterval());
            }
        } catch (exception e) {
            LogUtil::error("'broadcast the blockchain height to the whole network' error",e);
        }
    }
    void BlockchainHeightBroadcaster::broadcastBlockchainHeight(){
        vector<Node> nodes = nodeService->queryAllNodes();
        if(nodes.empty()){
            return;
        }

        for(Node node:nodes){
            uint64_t blockchainHeight = blockchainCore->queryBlockchainHeight();
            if(blockchainHeight <= node.blockchainHeight){
                continue;
            }
            NodeClient nodeClient(node.ip);
            PostBlockchainHeightRequest postBlockchainHeightRequest;
            postBlockchainHeightRequest.blockchainHeight=blockchainHeight;
            nodeClient.postBlockchainHeight(postBlockchainHeightRequest);
        }
    }

}