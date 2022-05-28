//
// author x.king xdotking@gmail.com
//
#include "model.h"

namespace model{

    namespace BlockchainActionEnum{
        BlockchainAction ADD_BLOCK{true};
        BlockchainAction DELETE_BLOCK{false};
    }

    namespace BooleanCodeEnum{
        BooleanCode FALSE00{{0x00},"false"};
        BooleanCode TRUE00{{0x01}, "true"};
    }

    namespace OperationCodeEnum{
        OperationCode OP_PUSHDATA{{0x00},"OP_PUSHDATA"};
        OperationCode OP_DUP{{0x01},"OP_DUP"};
        OperationCode OP_HASH160{{0x02},"OP_HASH160"};
        OperationCode OP_EQUALVERIFY{{0x03},"OP_EQUALVERIFY"};
        OperationCode OP_CHECKSIG{{0x04},"OP_CHECKSIG"};
    }

    namespace TransactionTypeEnum{
        TransactionType COINBASE_TRANSACTION = "COINBASE_TRANSACTION";
        TransactionType STANDARD_TRANSACTION = "STANDARD_TRANSACTION";
    }



    void to_json(json& j, const TransactionOutput& p){
        j = json{
                { "value", p.value },
                { "outputScript", p.outputScript },
                { "transactionHash", p.transactionHash },
                { "transactionOutputIndex", p.transactionOutputIndex },
                { "address", p.address },
                { "blockHeight", p.blockHeight },
                { "blockHash", p.blockHash },
                { "transactionHeight", p.transactionHeight },
                { "transactionIndex", p.transactionIndex },
                { "transactionOutputHeight", p.transactionOutputHeight }
        };
    }
    void from_json(const json& j, TransactionOutput& p){
        j.at("value").get_to(p.value);
        j.at("outputScript").get_to(p.outputScript);
        j.at("transactionHash").get_to(p.transactionHash);
        j.at("transactionOutputIndex").get_to(p.transactionOutputIndex);
        j.at("address").get_to(p.address);
        j.at("blockHeight").get_to(p.blockHeight);
        j.at("blockHash").get_to(p.blockHash);
        j.at("transactionHeight").get_to(p.transactionHeight);
        j.at("transactionIndex").get_to(p.transactionIndex);
        j.at("transactionOutputHeight").get_to(p.transactionOutputHeight);
    }

    void to_json(json& j, const TransactionInput& p){
        j = json{
                { "unspentTransactionOutput", p.unspentTransactionOutput },
                { "inputScript", p.inputScript }
        };
    }
    void from_json(const json& j, TransactionInput& p){
        j.at("unspentTransactionOutput").get_to(p.unspentTransactionOutput);
        j.at("inputScript").get_to(p.inputScript);
    }

    void to_json(json& j, const Transaction& p){
        j = json{
                { "transactionHash", p.transactionHash },
                { "transactionType", p.transactionType },
                { "inputs", p.inputs },
                { "outputs", p.outputs },
                { "transactionIndex", p.transactionIndex },
                { "transactionHeight", p.transactionHeight },
                { "blockHeight", p.blockHeight }
        };
    }
    void from_json(const json& j, Transaction& p){
        j.at("transactionHash").get_to(p.transactionHash);
        j.at("transactionType").get_to(p.transactionType);
        j.at("inputs").get_to(p.inputs);
        j.at("outputs").get_to(p.outputs);
        j.at("transactionIndex").get_to(p.transactionIndex);
        j.at("transactionHeight").get_to(p.transactionHeight);
        j.at("blockHeight").get_to(p.blockHeight);
    }

    void to_json(json& j, const Block& p) {
        j = json{
                {"timestamp",                 p.timestamp},
                {"height",                    p.height},
                {"previousHash",              p.previousHash},
                {"transactions",              p.transactions},
                {"merkleTreeRoot",            p.merkleTreeRoot},
                {"nonce",                     p.nonce},
                {"hash",                      p.hash},
                {"difficulty",                p.difficulty},
                {"transactionCount",          p.transactionCount},
                {"previousTransactionHeight", p.previousTransactionHeight}
        };
    }
    void from_json(const json& j, Block& p){
        j.at("timestamp").get_to(p.timestamp);
        j.at("height").get_to(p.height);
        j.at("previousHash").get_to(p.previousHash);
        j.at("transactions").get_to(p.transactions);
        j.at("merkleTreeRoot").get_to(p.merkleTreeRoot);
        j.at("nonce").get_to(p.nonce);
        j.at("hash").get_to(p.hash);
        j.at("difficulty").get_to(p.difficulty);
        j.at("transactionCount").get_to(p.transactionCount);
        j.at("previousTransactionHeight").get_to(p.previousTransactionHeight);
    }
}