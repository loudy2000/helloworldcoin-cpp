//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_NODECLIENT_H
#define HELLOWORLDCOIN_CPP_NODECLIENT_H

#include "../netcoredto/netcoredto.h"

using namespace dto;

namespace netcoreclient{
    /**
     * node client
     *
     * @author x.king xdotking@gmail.com
     */
    class NodeClient {
    private:
        string ip;
    private:
        string getUrl(string api);
    public:
        NodeClient(string ip);
    public:
        /**
         * post transaction to node
         */
        unique_ptr<PostTransactionResponse> postTransaction(PostTransactionRequest request);

        /**
         * ping node
         */
        unique_ptr<PingResponse> pingNode(PingRequest request);

        /**
         * get block by block height
         */
        unique_ptr<GetBlockResponse> getBlock(GetBlockRequest request);

        /**
         * get nodes
         */
        unique_ptr<GetNodesResponse> getNodes(GetNodesRequest request);

        /**
         * post block to node
         */
        unique_ptr<PostBlockResponse> postBlock(PostBlockRequest request);

        /**
         * post blockchain height to node
         */
        unique_ptr<PostBlockchainHeightResponse> postBlockchainHeight(PostBlockchainHeightRequest request);

        /**
         * get blockchain height
         */
        unique_ptr<GetBlockchainHeightResponse> getBlockchainHeight(GetBlockchainHeightRequest request);

        /**
         * get unconfirmed transactions
         */
        unique_ptr<GetUnconfirmedTransactionsResponse> getUnconfirmedTransactions(GetUnconfirmedTransactionsRequest getUnconfirmedTransactionsRequest);
    };
}



#endif //HELLOWORLDCOIN_CPP_NODECLIENT_H
