//
// author x.king xdotking@gmail.com
//

#include "NodeConsoleApplicationController.h"
#include "CommonController.h"
#include "../vo/nodevo.h"
#include "../vo/minervo.h"
#include "../vo/synchronizervo.h"
#include "../vo/blockvo.h"
#include "../../util/StringUtil.h"
#include "../../util/LogUtil.h"

using namespace vo;



namespace controller{


    NodeConsoleApplicationController::NodeConsoleApplicationController(BlockchainNetCore *blockchainNetCore){
        this->blockchainNetCore = blockchainNetCore;
    }



    void NodeConsoleApplicationController::IsMinerActive(const httplib::Request &req, httplib::Response &res){
        try {
            boolean isMinerActive = blockchainNetCore->getBlockchainCore()->getMiner()->isActive();
            IsMinerActiveResponse response;
            response.minerInActiveState=isMinerActive;
            return success(res,response);
        } catch (exception e){
            string message = "'is miner active' error.";
            LogUtil::error(message,e);
            serviceUnavailable(res);
        }
    }
    void NodeConsoleApplicationController::ActiveMiner(const httplib::Request &req, httplib::Response &res){
        try {
            blockchainNetCore->getBlockchainCore()->getMiner()->active();
            ActiveMinerResponse response;
            return success(res,response);
        } catch (exception e){
            string message = "'active miner' error.";
            LogUtil::error(message,e);
            serviceUnavailable(res);
        }
    }
    void NodeConsoleApplicationController::DeactiveMiner(const httplib::Request &req, httplib::Response &res){
        try {
            blockchainNetCore->getBlockchainCore()->getMiner()->deactive();
            DeactiveMinerResponse response;
            return success(res,response);
        } catch (exception e){
            string message = "'deactive miner' error.";
            LogUtil::error(message,e);
            serviceUnavailable(res);
        }
    }
    void NodeConsoleApplicationController::IsAutoSearchBlock(const httplib::Request &req, httplib::Response &res){
        try {
            boolean isAutoSearchBlock = blockchainNetCore->getNetCoreConfiguration()->isAutoSearchBlock();
            IsAutoSearchBlockResponse response;
            response.autoSearchBlock=isAutoSearchBlock;
            return success(res,response);
        } catch (exception e){
            string message = "'is auto search block' error.";
            LogUtil::error(message,e);
            serviceUnavailable(res);
        }
    }
    void NodeConsoleApplicationController::ActiveAutoSearchBlock(const httplib::Request &req, httplib::Response &res){
        try {
            blockchainNetCore->getNetCoreConfiguration()->activeAutoSearchBlock();
            ActiveAutoSearchBlockResponse response;
            return success(res,response);
        } catch (exception e){
            string message = "'active auto search block' error.";
            LogUtil::error(message,e);
            serviceUnavailable(res);
        }
    }
    void NodeConsoleApplicationController::DeactiveAutoSearchBlock(const httplib::Request &req, httplib::Response &res){
        try {
            blockchainNetCore->getNetCoreConfiguration()->deactiveAutoSearchBlock();
            DeactiveAutoSearchBlockResponse response;
            return success(res,response);
        } catch (exception e){
            string message = "'deactive auto search block' error.";
            LogUtil::error(message,e);
            serviceUnavailable(res);
        }
    }
    void NodeConsoleApplicationController::AddNode(const httplib::Request &req, httplib::Response &res){
        try {
            AddNodeRequest request = JsonUtil::toObject(req.body, AddNodeRequest{});

            string ip = request.ip;

            if(!blockchainNetCore->getNodeService()->queryNode(ip).get()){
                AddNodeResponse response;
                response.addNodeSuccess=true;
                return success(res,response);
            }
            Node node;
            node.ip=ip;
            node.blockchainHeight=0;
            blockchainNetCore->getNodeService()->addNode(node);
            AddNodeResponse response;
            response.addNodeSuccess=true;
            return success(res,response);
        } catch (exception e){
            string message = "'add node' error.";
            LogUtil::error(message,e);
            serviceUnavailable(res);
        }
    }
    void NodeConsoleApplicationController::UpdateNode(const httplib::Request &req, httplib::Response &res){
        try {
            UpdateNodeRequest request = JsonUtil::toObject(req.body, UpdateNodeRequest{});

            Node node;
            node.ip=request.ip;
            node.blockchainHeight=request.blockchainHeight;
            blockchainNetCore->getNodeService()->updateNode(node);
            UpdateNodeResponse response;
            return success(res,response);
        } catch (exception e){
            string message = "'update node' error.";
            LogUtil::error(message,e);
            serviceUnavailable(res);
        }
    }
    void NodeConsoleApplicationController::DeleteNode(const httplib::Request &req, httplib::Response &res){
        try {
            DeleteNodeRequest request = JsonUtil::toObject(req.body, DeleteNodeRequest{});

            blockchainNetCore->getNodeService()->deleteNode(request.ip);
            DeleteNodeResponse response;
            return success(res,response);
        } catch (exception e){
            string message = "'delete node' error.";
            LogUtil::error(message,e);
            serviceUnavailable(res);
        }
    }

    void NodeConsoleApplicationController::queryAllNodes(const httplib::Request &req, httplib::Response &res){
        try {
            vector<Node> nodes = blockchainNetCore->getNodeService()->queryAllNodes();

            vector<NodeVo> nodeVos;
            if(!nodes.empty()){
                for (Node node:nodes) {
                    NodeVo nodeVo;
                    nodeVo.ip=node.ip;
                    nodeVo.blockchainHeight=node.blockchainHeight;
                    nodeVos.push_back(nodeVo);
                }
            }

            QueryAllNodesResponse response;
            response.nodes=nodeVos;

            success(res,response);
        } catch (exception e){
            string message = "'query all nodes' error.";
            LogUtil::error(message,e);
            serviceUnavailable(res);
        }
    }
    void NodeConsoleApplicationController::IsAutoSearchNode(const httplib::Request &req, httplib::Response &res){
        try {
            boolean isAutoSearchNode = blockchainNetCore->getNetCoreConfiguration()->isAutoSearchNode();
            IsAutoSearchNodeResponse response;
            response.autoSearchNode=isAutoSearchNode;
            return success(res,response);
        } catch (exception e){
            string message = "'is auto search node' error.";
            LogUtil::error(message,e);
            serviceUnavailable(res);
        }
    }
    void NodeConsoleApplicationController::ActiveAutoSearchNode(const httplib::Request &req, httplib::Response &res){
        try {
            blockchainNetCore->getNetCoreConfiguration()->activeAutoSearchNode();
            ActiveAutoSearchNodeResponse response;
            return success(res,response);
        } catch (exception e){
            string message = "'active auto search node' error.";
            LogUtil::error(message,e);
            serviceUnavailable(res);
        }
    }
    void NodeConsoleApplicationController::DeactiveAutoSearchNode(const httplib::Request &req, httplib::Response &res){
        try {
            blockchainNetCore->getNetCoreConfiguration()->deactiveAutoSearchNode();
            DeactiveAutoSearchNodeResponse response;
            return success(res,response);
        } catch (exception e){
            string message = "'deactive auto search node' error.";
            LogUtil::error(message,e);
            serviceUnavailable(res);
        }
    }
    void NodeConsoleApplicationController::DeleteBlocks(const httplib::Request &req, httplib::Response &res){
        try {
            DeleteBlocksRequest request = JsonUtil::toObject(req.body, DeleteBlocksRequest{});

            blockchainNetCore->getBlockchainCore()->deleteBlocks(request.blockHeight);
            DeleteBlocksResponse response;
            return success(res,response);
        } catch (exception e){
            string message = "'delete blocks' error.";
            LogUtil::error(message,e);
            serviceUnavailable(res);
        }
    }
    void NodeConsoleApplicationController::GetMinerMineMaxBlockHeight(const httplib::Request &req, httplib::Response &res){
        try {
            uint64_t maxBlockHeight = blockchainNetCore->getBlockchainCore()->getMiner()->getMinerMineMaxBlockHeight();

            GetMinerMineMaxBlockHeightResponse response;
            response.maxBlockHeight=maxBlockHeight;
            return success(res,response);
        } catch (exception e){
            string message = "'Get Miner Mine Max Block Height' error.";
            LogUtil::error(message,e);
            serviceUnavailable(res);
        }
    }
    void NodeConsoleApplicationController::SetMinerMineMaxBlockHeight(const httplib::Request &req, httplib::Response &res){
        try {
            SetMinerMineMaxBlockHeightRequest request = JsonUtil::toObject(req.body, SetMinerMineMaxBlockHeightRequest{});

            uint64_t height = request.maxBlockHeight;
            blockchainNetCore->getBlockchainCore()->getMiner()->setMinerMineMaxBlockHeight(height);
            SetMinerMineMaxBlockHeightResponse response;
            return success(res,response);
        } catch (exception e){
            string message = "'Set Miner Mine Max Block Height' error.";
            LogUtil::error(message,e);
            serviceUnavailable(res);
        }
    }
}

