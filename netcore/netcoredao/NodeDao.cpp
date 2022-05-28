//
// author x.king xdotking@gmail.com
//

#include "NodeDao.h"
#include "../../util/FileUtil.h"
#include "../../util/ByteUtil.h"
#include "../../util/KvDbUtil.h"
#include "../../util/EncodeDecodeTool.h"

namespace netcoredao{


    string NODE_DATABASE_NAME = "NodeDatabase";


    NodeDao::NodeDao(NetCoreConfiguration *netCoreConfiguration){
        this->netCoreConfiguration = netCoreConfiguration;
    }

    unique_ptr<NodePo> NodeDao::queryNode(string ip){
        vector<unsigned char> bytesNodePo = KvDbUtil::get(getNodeDatabasePath(),getKeyByIp(ip));
        if(bytesNodePo.empty()){
            return unique_ptr<NodePo>(nullptr);
        }
        NodePo nodePo = EncodeDecodeTool::decode(bytesNodePo,NodePo{});
        return unique_ptr<NodePo>(new NodePo(nodePo));
    }


    void NodeDao::addNode(NodePo node){
        KvDbUtil::put(getNodeDatabasePath(),getKeyByNodePo(node), EncodeDecodeTool::encode(node));
    }


    void NodeDao::updateNode(NodePo node){
        KvDbUtil::put(getNodeDatabasePath(),getKeyByNodePo(node),EncodeDecodeTool::encode(node));
    }


    void NodeDao::deleteNode(string ip){
        KvDbUtil::delete0(getNodeDatabasePath(),getKeyByIp(ip));
    }


    vector<NodePo> NodeDao::queryAllNodes(){
        vector<NodePo> nodePos;

        vector<vector<unsigned char>> bytesNodePos = KvDbUtil::gets(getNodeDatabasePath(),1,100000000);
        if(!bytesNodePos.empty()){
            for(vector<unsigned char> &bytesNodePo:bytesNodePos){
                NodePo nodePo = EncodeDecodeTool::decode(bytesNodePo,NodePo{});
                nodePos.push_back(nodePo);
            }
        }
        return nodePos;
    }


    string NodeDao::getNodeDatabasePath(){
        return FileUtil::newPath(netCoreConfiguration->getNetCorePath(), NODE_DATABASE_NAME);
    }
    vector<unsigned char> NodeDao::getKeyByNodePo(NodePo node){
        return getKeyByIp(node.ip);
    }
    vector<unsigned char> NodeDao::getKeyByIp(string ip){
        return ByteUtil::stringToUtf8Bytes(ip);
    }

}
