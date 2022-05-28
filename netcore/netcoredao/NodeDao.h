//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_NODEDAO_H
#define HELLOWORLDCOIN_CPP_NODEDAO_H

#include <string>
#include <vector>
#include <cstdint>
#include "../netcorepo/netcorepo.h"
#include "../netcoreconfiguration/NetCoreConfiguration.h"

using namespace std;
using namespace netcorepo;
using namespace netcoreconfiguration;


namespace netcoredao {

    class NodeDao {
    private:
        NetCoreConfiguration *netCoreConfiguration;
    public:
        NodeDao(NetCoreConfiguration *netCoreConfiguration);
    public:
        unique_ptr<NodePo> queryNode(string ip);
        vector<NodePo> queryAllNodes();
        void addNode(NodePo node);
        void updateNode(NodePo node);
        void deleteNode(string ip);

    private:
        string NodeDao::getNodeDatabasePath();
        vector<unsigned char> NodeDao::getKeyByNodePo(NodePo node);
        vector<unsigned char> NodeDao::getKeyByIp(string ip);
    };
};


#endif //HELLOWORLDCOIN_CPP_NODEDAO_H
