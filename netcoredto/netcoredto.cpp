//
// author x.king xdotking@gmail.com
//

#include "netcoredto.h"


namespace dto{


    namespace API{
        string PING = "/ping";

        string GET_NODES = "/get_nodes";

        string GET_BLOCKCHAIN_HEIGHT = "/get_blockchain_height";
        string POST_BLOCKCHAIN_HEIGHT = "/post_blockchain_height";

        string GET_BLOCK = "/get_block";
        string POST_BLOCK = "/post_block";

        string GET_UNCONFIRMED_TRANSACTIONS = "/get_unconfirmed_transactions";
        string POST_TRANSACTION = "/post_transaction";
    };







    void to_json(json& j, const TransactionInputDto& p){
        j = json{
                { "transactionHash", p.transactionHash },
                { "transactionOutputIndex", p.transactionOutputIndex },
                { "inputScript", p.inputScript }
        };
    }
    void from_json(const json& j, TransactionInputDto& p){
        j.at("transactionHash").get_to(p.transactionHash);
        j.at("transactionOutputIndex").get_to(p.transactionOutputIndex);
        j.at("inputScript").get_to(p.inputScript);
    }

    void to_json(json& j, const TransactionOutputDto& p){
        j = json{
                { "outputScript", p.outputScript },
                { "value", p.value }
        };
    }
    void from_json(const json& j, TransactionOutputDto& p){
        j.at("outputScript").get_to(p.outputScript);
        j.at("value").get_to(p.value);
    }

    void to_json(json& j, const TransactionDto& p){
        j = json{
                { "inputs", p.inputs },
                { "outputs", p.outputs }
        };
    }
    void from_json(const json& j, TransactionDto& p){
        j.at("inputs").get_to(p.inputs);
        j.at("outputs").get_to(p.outputs);
    }

    void to_json(json& j, const BlockDto& p){
        j = json{
                { "timestamp", p.timestamp },
                { "previousHash", p.previousHash },
                { "transactions", p.transactions },
                { "nonce", p.nonce }
        };
    }
    void from_json(const json& j, BlockDto& p){
        j.at("timestamp").get_to(p.timestamp);
        j.at("previousHash").get_to(p.previousHash);
        j.at("transactions").get_to(p.transactions);
        j.at("nonce").get_to(p.nonce);
    }














    void to_json(json& j, const NodeDto& p){
        j = json{
                { "ip", p.ip }
        };
    }
    void from_json(const json& j, NodeDto& p){
        j.at("ip").get_to(p.ip);
    }

    void to_json(json& j, const PingRequest& p){
        j = json{
        };
    }
    void from_json(const json& j, PingRequest& p){
    }
    void to_json(json& j, const PingResponse& p){
        j = json{
        };
    }
    void from_json(const json& j, PingResponse& p){
    }

    void to_json(json& j, const GetBlockRequest& p){
        j = json{
                { "blockHeight", p.blockHeight }
        };
    }
    void from_json(const json& j, GetBlockRequest& p){
        j.at("blockHeight").get_to(p.blockHeight);
    }
    void to_json(json& j, const GetBlockResponse& p){
        j = json{
                { "block", p.block }
        };
    }
    void from_json(const json& j, GetBlockResponse& p){
        j.at("block").get_to(p.block);
    }

    void to_json(json& j, const PostTransactionRequest& p){
        j = json{
                { "transaction", p.transaction }
        };
    }
    void from_json(const json& j, PostTransactionRequest& p){
        j.at("transaction").get_to(p.transaction);
    }
    void to_json(json& j, const PostTransactionResponse& p){
        j = json{
        };
    }
    void from_json(const json& j, PostTransactionResponse& p){
    }

    void to_json(json& j, const PostBlockRequest& p){
        j = json{
                { "block", p.block }
        };
    }
    void from_json(const json& j, PostBlockRequest& p){
        j.at("block").get_to(p.block);
    }
    void to_json(json& j, const PostBlockResponse& p){
        j = json{
        };
    }
    void from_json(const json& j, PostBlockResponse& p){
    }

    void to_json(json& j, const GetNodesRequest& p){
        j = json{
        };
    }
    void from_json(const json& j, GetNodesRequest& p){
    }
    void to_json(json& j, const GetNodesResponse& p){
        j = json{
                { "nodes", p.nodes }
        };
    }
    void from_json(const json& j, GetNodesResponse& p){
        j.at("nodes").get_to(p.nodes);
    }

    void to_json(json& j, const PostBlockchainHeightRequest& p){
        j = json{
                { "blockchainHeight", p.blockchainHeight }
        };
    }
    void from_json(const json& j, PostBlockchainHeightRequest& p){
        j.at("blockchainHeight").get_to(p.blockchainHeight);
    }
    void to_json(json& j, const PostBlockchainHeightResponse& p){
        j = json{
        };
    }
    void from_json(const json& j, PostBlockchainHeightResponse& p){
    }

    void to_json(json& j, const GetBlockchainHeightRequest& p){
        j = json{
        };
    }
    void from_json(const json& j, GetBlockchainHeightRequest& p){
    }
    void to_json(json& j, const GetBlockchainHeightResponse& p){
        j = json{
                { "blockchainHeight", p.blockchainHeight }
        };
    }
    void from_json(const json& j, GetBlockchainHeightResponse& p){
        j.at("blockchainHeight").get_to(p.blockchainHeight);
    }

    void to_json(json& j, const GetUnconfirmedTransactionsRequest& p){
        j = json{
        };
    }
    void from_json(const json& j, GetUnconfirmedTransactionsRequest& p){
    }
    void to_json(json& j, const GetUnconfirmedTransactionsResponse& p){
        j = json{
                { "transactions", p.transactions }
        };
    }
    void from_json(const json& j, GetUnconfirmedTransactionsResponse& p){
        j.at("transactions").get_to(p.transactions);
    }
}