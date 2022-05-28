//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_NETCOREDTO_H
#define HELLOWORLDCOIN_CPP_NETCOREDTO_H

#include <string>
#include <cstdint>
#include <vector>
#include <stack>
#include "../thirdpart/nlohmann/json.hpp"

using json = nlohmann::json;

using namespace std;

namespace dto {

    typedef vector<string> ScriptDto;
    typedef ScriptDto InputScriptDto;
    typedef ScriptDto OutputScriptDto;
    struct TransactionInputDto{
        string transactionHash;
        uint64_t transactionOutputIndex;
        InputScriptDto inputScript;
    };
    struct TransactionOutputDto{
        OutputScriptDto outputScript;
        uint64_t value;
    };
    struct TransactionDto{
        vector<TransactionInputDto> inputs;
        vector<TransactionOutputDto> outputs;
    };
    struct BlockDto{
        uint64_t timestamp;
        string previousHash;
        vector<TransactionDto> transactions;
        string nonce;
    };

    void to_json(json& j, const TransactionInputDto& p);
    void from_json(const json& j, TransactionInputDto& p);

    void to_json(json& j, const TransactionOutputDto& p);
    void from_json(const json& j, TransactionOutputDto& p);

    void to_json(json& j, const TransactionDto& p);
    void from_json(const json& j, TransactionDto& p);

    void to_json(json& j, const BlockDto& p);
    void from_json(const json& j, BlockDto& p);



    namespace API{
        extern string PING;

        extern string GET_NODES;

        extern string GET_BLOCKCHAIN_HEIGHT;
        extern string POST_BLOCKCHAIN_HEIGHT;

        extern string GET_BLOCK;
        extern string POST_BLOCK;

        extern string GET_UNCONFIRMED_TRANSACTIONS;
        extern string POST_TRANSACTION;
    };



    struct NodeDto{
        string ip;
    };
    struct PingRequest {
    };
    struct PingResponse {
    };
    struct GetBlockRequest {
        int64_t blockHeight;
    };
    struct GetBlockResponse {
     BlockDto block;
    };
    struct PostTransactionRequest{
        TransactionDto transaction;
    };
    struct PostTransactionResponse{

    };
    struct PostBlockRequest{
        BlockDto block;
    };
    struct PostBlockResponse{

    };
    struct GetNodesRequest{

    };
    struct GetNodesResponse{
        vector<NodeDto> nodes;
    };
    struct PostBlockchainHeightRequest{
        uint64_t blockchainHeight;
    };
    struct PostBlockchainHeightResponse{

    };
    struct GetBlockchainHeightRequest{

    };
    struct GetBlockchainHeightResponse{
        uint64_t blockchainHeight;
    };
    struct GetUnconfirmedTransactionsRequest{

    };
    struct GetUnconfirmedTransactionsResponse{
        vector<TransactionDto> transactions;
    };

    void to_json(json& j, const NodeDto& p);
    void from_json(const json& j, NodeDto& p);

    void to_json(json& j, const PingRequest& p);
    void from_json(const json& j, PingRequest& p);
    void to_json(json& j, const PingResponse& p);
    void from_json(const json& j, PingResponse& p);

    void to_json(json& j, const GetBlockRequest& p);
    void from_json(const json& j, GetBlockRequest& p);
    void to_json(json& j, const GetBlockResponse& p);
    void from_json(const json& j, GetBlockResponse& p);

    void to_json(json& j, const PostTransactionRequest& p);
    void from_json(const json& j, PostTransactionRequest& p);
    void to_json(json& j, const PostTransactionResponse& p);
    void from_json(const json& j, PostTransactionResponse& p);

    void to_json(json& j, const PostBlockRequest& p);
    void from_json(const json& j, PostBlockRequest& p);
    void to_json(json& j, const PostBlockResponse& p);
    void from_json(const json& j, PostBlockResponse& p);

    void to_json(json& j, const GetNodesRequest& p);
    void from_json(const json& j, GetNodesRequest& p);
    void to_json(json& j, const GetNodesResponse& p);
    void from_json(const json& j, GetNodesResponse& p);

    void to_json(json& j, const PostBlockchainHeightRequest& p);
    void from_json(const json& j, PostBlockchainHeightRequest& p);
    void to_json(json& j, const PostBlockchainHeightResponse& p);
    void from_json(const json& j, PostBlockchainHeightResponse& p);

    void to_json(json& j, const GetBlockchainHeightRequest& p);
    void from_json(const json& j, GetBlockchainHeightRequest& p);
    void to_json(json& j, const GetBlockchainHeightResponse& p);
    void from_json(const json& j, GetBlockchainHeightResponse& p);

    void to_json(json& j, const GetUnconfirmedTransactionsRequest& p);
    void from_json(const json& j, GetUnconfirmedTransactionsRequest& p);
    void to_json(json& j, const GetUnconfirmedTransactionsResponse& p);
    void from_json(const json& j, GetUnconfirmedTransactionsResponse& p);
};


#endif //HELLOWORLDCOIN_CPP_NETCOREDTO_H
