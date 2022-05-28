//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_NODESERVER_H
#define HELLOWORLDCOIN_CPP_NODESERVER_H

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "../../thirdpart/httplib/httplib.h"
#include "../../netcoredto/netcoredto.h"
#include "../../core/BlockchainCore.h"
#include "../netcoreservice/NodeService.h"

using namespace dto;
using namespace core;
using namespace service;

namespace server{

    class NodeServer {
    private:
        BlockchainCore *blockchainCore;
        NodeService *nodeService;
        NetCoreConfiguration *netCoreConfiguration;
    public:
        NodeServer(NetCoreConfiguration *netCoreConfiguration,BlockchainCore *blockchainCore, NodeService *nodeService);
    public:
        void start() ;
    private:
        PingResponse ping(string requestIp, PingRequest request);
        GetBlockResponse getBlock(GetBlockRequest request);
        PostTransactionResponse postTransaction(PostTransactionRequest request);
        PostBlockResponse postBlock(PostBlockRequest request);
        GetNodesResponse getNodes(GetNodesRequest request);
        PostBlockchainHeightResponse postBlockchainHeight(string requestIp, PostBlockchainHeightRequest request);
        GetBlockchainHeightResponse getBlockchainHeight(GetBlockchainHeightRequest request);
        GetUnconfirmedTransactionsResponse getUnconfirmedTransactions(GetUnconfirmedTransactionsRequest request);
    };

}




#endif //HELLOWORLDCOIN_CPP_NODESERVER_H
