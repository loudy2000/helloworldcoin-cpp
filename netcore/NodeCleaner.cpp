//
// author x.king xdotking@gmail.com
//

#include "NodeCleaner.h"
#include "../netcoreclient/NodeClient.h"
#include "../util/LogUtil.h"
#include "../util/ThreadUtil.h"

using namespace netcoreclient;


namespace netcore{


    NodeCleaner::NodeCleaner(NetCoreConfiguration *netCoreConfiguration, NodeService *nodeService){
        this->netCoreConfiguration = netCoreConfiguration;
        this->nodeService = nodeService;
    }

    void NodeCleaner::start(){
        try {
            while (true){
                cleanDeadNodes();
                ThreadUtil::millisecondSleep(netCoreConfiguration->getNodeCleanTimeInterval());
            }
        } catch (exception e) {
            LogUtil::error("'clean up dead nodes' error.",e);
        }
    }

    void NodeCleaner::cleanDeadNodes(){
        vector<Node> nodes = nodeService->queryAllNodes();
        if(nodes.empty()){
            return;
        }

        for(Node node:nodes){
            NodeClient nodeClient(node.ip);
            PingRequest pingRequest;
            unique_ptr<PingResponse> pingResponse = nodeClient.pingNode(pingRequest);
            if(!pingResponse.get()){
                nodeService->deleteNode(node.ip);
            }
        }
    }

}
