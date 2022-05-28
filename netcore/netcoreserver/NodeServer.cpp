//
// author x.king xdotking@gmail.com
//

#include "NodeServer.h"
#include "../../util/LogUtil.h"
#include "../../setting/BlockSetting.h"
#include "../../core/tool/Model2DtoTool.h"
#include "../../util/EncodeDecodeTool.h"


namespace server{

    void NodeServer::start() {
        httplib::Server server;

        server.Post(API::PING, [this](const httplib::Request &req, httplib::Response &res) {
            PingRequest pingRequest = JsonUtil::toObject(req.body, PingRequest{});
            PingResponse pingResponse = ping(req.remote_addr,pingRequest);
            res.set_content(JsonUtil::toString(pingResponse), "application/json");
        });

        server.Post(API::GET_NODES, [this](const httplib::Request &req, httplib::Response &res) {
            GetNodesRequest getNodesRequest = JsonUtil::toObject(req.body, GetNodesRequest{});
            GetNodesResponse getNodesResponse = getNodes(getNodesRequest);
            res.set_content(JsonUtil::toString(getNodesResponse), "application/json");
        });

        server.Post(API::GET_BLOCK, [this](const httplib::Request &req, httplib::Response &res) {
            GetBlockRequest getBlockRequest = JsonUtil::toObject(req.body, GetBlockRequest{});
            GetBlockResponse getBlockResponse = getBlock(getBlockRequest);
            res.set_content(JsonUtil::toString(getBlockResponse), "application/json");
        });
        server.Post(API::POST_BLOCK, [this](const httplib::Request &req, httplib::Response &res) {
            PostBlockRequest postBlockRequest = JsonUtil::toObject(req.body, PostBlockRequest{});
            PostBlockResponse postBlockResponse = postBlock(postBlockRequest);
            res.set_content(JsonUtil::toString(postBlockResponse), "application/json");
        });

        server.Post(API::GET_BLOCKCHAIN_HEIGHT, [this](const httplib::Request &req, httplib::Response &res) {
            GetBlockchainHeightRequest getBlockchainHeightRequest = JsonUtil::toObject(req.body, GetBlockchainHeightRequest{});
            GetBlockchainHeightResponse getBlockchainHeightResponse = getBlockchainHeight(getBlockchainHeightRequest);
            res.set_content(JsonUtil::toString(getBlockchainHeightResponse), "application/json");
        });
        server.Post(API::POST_BLOCKCHAIN_HEIGHT, [this](const httplib::Request &req, httplib::Response &res) {
            PostBlockchainHeightRequest postBlockchainHeightRequest = JsonUtil::toObject(req.body, PostBlockchainHeightRequest{});
            PostBlockchainHeightResponse postBlockchainHeightResponse = postBlockchainHeight(req.remote_addr,postBlockchainHeightRequest);
            res.set_content(JsonUtil::toString(postBlockchainHeightResponse), "application/json");
        });

        server.Post(API::GET_UNCONFIRMED_TRANSACTIONS, [this](const httplib::Request &req, httplib::Response &res) {
            GetUnconfirmedTransactionsRequest getUnconfirmedTransactionsRequest = JsonUtil::toObject(req.body, GetUnconfirmedTransactionsRequest{});
            GetUnconfirmedTransactionsResponse getUnconfirmedTransactionsResponse = getUnconfirmedTransactions(getUnconfirmedTransactionsRequest);
            res.set_content(JsonUtil::toString(getUnconfirmedTransactionsResponse), "application/json");
        });

        server.Post(API::POST_TRANSACTION, [this](const httplib::Request &req, httplib::Response &res) {
            PostTransactionRequest postTransactionRequest = JsonUtil::toObject(req.body, PostTransactionRequest{});
            PostTransactionResponse postTransactionResponse = postTransaction(postTransactionRequest);
            res.set_content(JsonUtil::toString(postTransactionResponse), "application/json");
        });

        server.listen("0.0.0.0", 8888);
    }

    NodeServer::NodeServer(NetCoreConfiguration *netCoreConfiguration,BlockchainCore *blockchainCore, NodeService *nodeService){
        this->netCoreConfiguration = netCoreConfiguration;
        this->blockchainCore = blockchainCore;
        this->nodeService = nodeService;
    }


    PingResponse NodeServer::ping(string requestIp, PingRequest request){
        try {
            if(netCoreConfiguration->isAutoSearchNode()){
                Node node;
                node.ip=requestIp;
                node.blockchainHeight=0;
                nodeService->addNode(node);
            }
            PingResponse response;
            return response;
        } catch (exception e){
            string message = "ping node failed";
            LogUtil::error(message,e);
            //return nullptr;
        }
    }


    GetBlockResponse NodeServer::getBlock(GetBlockRequest request){
        try {
            unique_ptr<Block> blockByBlockHeight = blockchainCore->queryBlockByBlockHeight(request.blockHeight);
            BlockDto block = Model2DtoTool::block2BlockDto(blockByBlockHeight.get());
            GetBlockResponse response;
            response.block=block;
            return response;
        } catch (exception e){
            string message = "get block failed";
            LogUtil::error(message,e);
            //TODO return null;
        }
    }


    PostTransactionResponse NodeServer::postTransaction(PostTransactionRequest request){
        try {
            blockchainCore->postTransaction(&request.transaction);
            PostTransactionResponse response;
            return response;
        } catch (exception e){
            string message = "post transaction failed";
            LogUtil::error(message,e);
            //TODO return null;
        }
    }

    PostBlockResponse NodeServer::postBlock(PostBlockRequest request) {
        try {
            blockchainCore->addBlockDto(&request.block);
            PostBlockResponse response;
            return response;
        } catch (exception e){
            string message = "post block failed";
            LogUtil::error(message,e);
            //TODO return null;
        }
    }

    GetNodesResponse NodeServer::getNodes(GetNodesRequest request) {
        try {
            vector<Node> allNodes = nodeService->queryAllNodes();
            vector<NodeDto> nodes;
            if(!allNodes.empty()){
                for (Node node:allNodes) {
                    NodeDto n;
                    n.ip=node.ip;
                    nodes.push_back(n);
                }
            }
            GetNodesResponse response;
            response.nodes=nodes;
            return response;
        }catch (exception e){
            string message = "get nodes failed";
            LogUtil::error(message,e);
            //TODO return null;
        }
    }

    PostBlockchainHeightResponse NodeServer::postBlockchainHeight(string requestIp, PostBlockchainHeightRequest request) {
        try {
            Node node;
            node.ip=requestIp;
            node.blockchainHeight=request.blockchainHeight;
            nodeService->updateNode(node);
            PostBlockchainHeightResponse response;
            return response;
        } catch (exception e){
            string message = "post blockchain height failed";
            LogUtil::error(message,e);
            //TODO return null;
        }
    }

    GetBlockchainHeightResponse NodeServer::getBlockchainHeight(GetBlockchainHeightRequest request) {
        try {
            uint64_t blockchainHeight = blockchainCore->queryBlockchainHeight();
            GetBlockchainHeightResponse response ;
            response.blockchainHeight=blockchainHeight;
            return response;
        } catch (exception e){
            string message = "get blockchain height failed";
            LogUtil::error(message,e);
            //TODO return null;
        }
    }

    GetUnconfirmedTransactionsResponse NodeServer::getUnconfirmedTransactions(GetUnconfirmedTransactionsRequest request) {
        try {
            UnconfirmedTransactionDatabase *unconfirmedTransactionDatabase0 = blockchainCore->getUnconfirmedTransactionDatabase();
            vector<TransactionDto> transactions = unconfirmedTransactionDatabase0->selectTransactions(1, BlockSetting::BLOCK_MAX_TRANSACTION_COUNT);
            GetUnconfirmedTransactionsResponse response;
            response.transactions=transactions;
            return response;
        } catch (exception e){
            string message = "get transaction failed";
            LogUtil::error(message,e);
            //TODO return null;
        }
    }
}