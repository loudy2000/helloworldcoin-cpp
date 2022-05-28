//
// author x.king xdotking@gmail.com
//

#include "NodeBroadcaster.h"
#include "../netcoreclient/NodeClient.h"
#include "../util/LogUtil.h"
#include "../util/ThreadUtil.h"

using namespace netcoreclient;





namespace netcore{


    NodeBroadcaster::NodeBroadcaster(NetCoreConfiguration *netCoreConfiguration, NodeService *nodeService){
        this->netCoreConfiguration = netCoreConfiguration;
        this->nodeService = nodeService;
    }
    void NodeBroadcaster::start(){
        try {
            while (true){
                broadcastNode();
                ThreadUtil::millisecondSleep(netCoreConfiguration->getNodeBroadcastTimeInterval());
            }
        } catch (exception e) {
            LogUtil::error("'broadcasts itself to the whole network' error.",e);
        }
    }
    void NodeBroadcaster::broadcastNode(){
        vector<Node> nodes = nodeService->queryAllNodes();
        if(nodes.empty()){
            return;
        }

        for(Node node:nodes){
            NodeClient nodeClient(node.ip);
            PingRequest pingRequest;
            nodeClient.pingNode(pingRequest);
        }
    }

}