//
// author x.king xdotking@gmail.com
//

#include "BlockchainHeightSearcher.h"
#include "../netcoreclient/NodeClient.h"
#include "../util/LogUtil.h"
#include "../util/ThreadUtil.h"

using namespace netcoreclient;


namespace netcore{


    BlockchainHeightSearcher::BlockchainHeightSearcher(NetCoreConfiguration *netCoreConfiguration,NodeService *nodeService){
        this->netCoreConfiguration = netCoreConfiguration;
        this->nodeService = nodeService;
    }

    void BlockchainHeightSearcher::start(){
        try {
            while (true){
                searchBlockchainHeight();
                ThreadUtil::millisecondSleep(netCoreConfiguration->getBlockchainHeightSearchTimeInterval());
            }
        } catch (exception e) {
            LogUtil::error("'search for node‘s Blockchain Height in the blockchain network' error.",e);
        }
    }

    void BlockchainHeightSearcher::searchBlockchainHeight(){
        vector<Node> nodes = nodeService->queryAllNodes();
        if(nodes.empty()){
            return;
        }

        for(Node node:nodes){
            NodeClient nodeClient(node.ip);
            GetBlockchainHeightRequest getBlockchainHeightRequest;
            unique_ptr<GetBlockchainHeightResponse> getBlockchainHeightResponse = nodeClient.getBlockchainHeight(getBlockchainHeightRequest);
            if(getBlockchainHeightResponse.get()){
                node.blockchainHeight=getBlockchainHeightResponse->blockchainHeight;
                nodeService->updateNode(node);
            }
        }
    }

}