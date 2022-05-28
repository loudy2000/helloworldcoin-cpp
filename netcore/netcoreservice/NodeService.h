//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_NODESERVICE_H
#define HELLOWORLDCOIN_CPP_NODESERVICE_H


#include "../netcoremodel/netcoremodel.h"
#include "../netcoredao/NodeDao.h"
#include <vector>

using namespace netcoremodel;
using namespace netcoredao;


namespace service {


    class NodeService {
    private:
        NodeDao *nodeDao;
    public:
        NodeService(NodeDao *nodeDao);
    public:
        unique_ptr<Node> queryNode(string ip);
        vector<Node> queryAllNodes();
        void deleteNode(string ip);
        void addNode(Node node);
        void updateNode(Node node);

    private:
        vector<Node> NodeService::nodePo2Nodes(vector<NodePo> nodePos);
        Node NodeService::nodePo2Node(NodePo nodePo);
        NodePo NodeService::node2NodePo(Node node);
    };
};


#endif //HELLOWORLDCOIN_CPP_NODESERVICE_H
