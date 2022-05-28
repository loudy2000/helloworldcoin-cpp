//
// author x.king xdotking@gmail.com
//

#include "NodeService.h"

namespace service{

    NodeService::NodeService(NodeDao *nodeDao){
        this->nodeDao = nodeDao;
    }

    void NodeService::deleteNode(string ip){
        nodeDao->deleteNode(ip);
    }

    vector<Node> NodeService::queryAllNodes(){
        vector<NodePo> nodePos = nodeDao->queryAllNodes();
        return nodePo2Nodes(nodePos);
    }

    void NodeService::addNode(Node node){
        if(nodeDao->queryNode(node.ip).get()){
            return;
        }
        NodePo nodePo = node2NodePo(node);
        nodeDao->addNode(nodePo);
    }

    
    void NodeService::updateNode(Node node){
        unique_ptr<NodePo> nodePo = nodeDao->queryNode(node.ip);
        if(!nodePo.get()){
            return;
        }
        NodePo nodePo2 = node2NodePo(node);
        nodeDao->updateNode(nodePo2);
    }

    
    unique_ptr<Node> NodeService::queryNode(string ip){
        unique_ptr<NodePo> nodePo = nodeDao->queryNode(ip);
        if(!nodePo.get()){
            return unique_ptr<Node>(nullptr);
        }
        Node node = nodePo2Node(*nodePo.get());
        return unique_ptr<Node>(new Node(node));
    }

    vector<Node> NodeService::nodePo2Nodes(vector<NodePo> nodePos){
        vector<Node> nodes;
        if(!nodePos.empty()){
            for(NodePo &nodePo : nodePos){
                Node node = nodePo2Node(nodePo);
                nodes.push_back(node);
            }
        }
        return nodes;
    }
    Node NodeService::nodePo2Node(NodePo nodePo){
        Node node;
        node.ip=nodePo.ip;
        node.blockchainHeight=nodePo.blockchainHeight;
        return node;
    }
    NodePo NodeService::node2NodePo(Node node){
        NodePo nodePo;
        nodePo.ip=node.ip;
        nodePo.blockchainHeight=node.blockchainHeight;
        return nodePo;
    }
}