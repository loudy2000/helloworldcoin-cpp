//
// author x.king xdotking@gmail.com
//

#include "NodeSearcher.h"
#include "../netcoreclient/NodeClient.h"
#include "../util/LogUtil.h"
#include "../util/ThreadUtil.h"

using namespace netcoreclient;


namespace netcore{


    NodeSearcher::NodeSearcher(NetCoreConfiguration *netCoreConfiguration, NodeService *nodeService){
        this->netCoreConfiguration = netCoreConfiguration;
        this->nodeService = nodeService;
    }
    
    void NodeSearcher::start(){
        try {
            while (true){
                searchNodes();
                ThreadUtil::millisecondSleep(netCoreConfiguration->getNodeSearchTimeInterval());
            }
        } catch (exception e) {
            LogUtil::error("'search for nodes in the blockchain network' error.",e);
        }
    }
    
    void NodeSearcher::searchNodes(){
        if(!netCoreConfiguration->isAutoSearchNode()){
            return;
        }
        vector<Node> nodes = nodeService->queryAllNodes();
        if(nodes.empty()){
            return;
        }

        for(Node node:nodes){
            if(!netCoreConfiguration->isAutoSearchNode()){
                return;
            }
            NodeClient nodeClient(node.ip);
            GetNodesRequest getNodesRequest;
            unique_ptr<GetNodesResponse> getNodesResponse = nodeClient.getNodes(getNodesRequest);
            handleGetNodesResponse(getNodesResponse);
        }
    }
    
    void NodeSearcher::handleGetNodesResponse(unique_ptr<GetNodesResponse>& getNodesResponse){
        if(!getNodesResponse.get()){
            return;
        }
        vector<NodeDto> &nodes = getNodesResponse->nodes;
        if(nodes.empty()){
            return;
        }

        for(NodeDto node:nodes){
            if(!netCoreConfiguration->isAutoSearchNode()){
                return;
            }
            NodeClient nodeClient(node.ip);
            PingRequest pingRequest;
            unique_ptr<PingResponse> pingResponse = nodeClient.pingNode(pingRequest);
            if(pingResponse.get()){
                Node n{};
                n.ip=node.ip;
                n.blockchainHeight=0;
                nodeService->addNode(n);
            }
        }
    }

}