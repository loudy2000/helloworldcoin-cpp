//
// author x.king xdotking@gmail.com
//

#include "BlockBroadcaster.h"
#include "../core/tool/Model2DtoTool.h"
#include "../netcoreclient/NodeClient.h"
#include "../util/LogUtil.h"
#include "../util/ThreadUtil.h"

using namespace netcoreclient;

namespace netcore{

    BlockBroadcaster::BlockBroadcaster(NetCoreConfiguration *netCoreConfiguration, BlockchainCore *blockchainCore, NodeService *nodeService){
        this->netCoreConfiguration = netCoreConfiguration;
        this->blockchainCore = blockchainCore;
        this->nodeService = nodeService;
    }
    void BlockBroadcaster::start(){
        try {
            while (true){
                broadcastBlock();
                ThreadUtil::millisecondSleep(netCoreConfiguration->getBlockBroadcastTimeInterval());
            }
        } catch (exception e) {
            LogUtil::error("'broadcast it's latest block to the whole network' error.",e);
        }
    }
    void BlockBroadcaster::broadcastBlock(){
        vector<Node> nodes = nodeService->queryAllNodes();
        if(nodes.empty()){
            return;
        }

        for(Node node:nodes){
            unique_ptr<Block> block = blockchainCore->queryTailBlock();
            if(!block.get()){
                return;
            }
            if(block->height <= node.blockchainHeight){
                continue;
            }
            BlockDto blockDto = Model2DtoTool::block2BlockDto(block.get());
            NodeClient nodeClient(node.ip);
            PostBlockRequest postBlockRequest;
            postBlockRequest.block=blockDto;
            nodeClient.postBlock(postBlockRequest);
        }
    }

}