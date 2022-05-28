//
// author x.king xdotking@gmail.com
//

#include "transactionvo.h"



namespace vo {


    void to_json(json& j, const TransactionInputVo& p){
        j = json{
                { "address", p.address },
                { "value", p.value },
                { "inputScript", p.inputScript },
                { "transactionHash", p.transactionHash },
                { "transactionOutputIndex", p.transactionOutputIndex }
        };
    }
    void from_json(const json& j, TransactionInputVo& p){
        j.at("address").get_to(p.address);
        j.at("value").get_to(p.value);
        j.at("inputScript").get_to(p.inputScript);
        j.at("transactionHash").get_to(p.transactionHash);
        j.at("transactionOutputIndex").get_to(p.transactionOutputIndex);
    }

    void to_json(json& j, const TransactionOutputVo& p){
        j = json{
                { "address", p.address },
                { "value", p.value },
                { "outputScript", p.outputScript },
                { "transactionHash", p.transactionHash },
                { "transactionOutputIndex", p.transactionOutputIndex }
        };
    }
    void from_json(const json& j, TransactionOutputVo& p){
        j.at("address").get_to(p.address);
        j.at("value").get_to(p.value);
        j.at("outputScript").get_to(p.outputScript);
        j.at("transactionHash").get_to(p.transactionHash);
        j.at("transactionOutputIndex").get_to(p.transactionOutputIndex);
    }

    void to_json(json& j, const TransactionVo& p){
        j = json{
                { "blockHeight", p.blockHeight },
                { "blockHash", p.blockHash },
                { "blockConfirmations", p.blockConfirmations },
                { "transactionHash", p.transactionHash },
                { "blockTime", p.blockTime },
                { "transactionFee", p.transactionFee },
                { "transactionType", p.transactionType },
                { "transactionInputCount", p.transactionInputCount },
                { "transactionOutputCount", p.transactionOutputCount },
                { "transactionInputValues", p.transactionInputValues },
                { "transactionOutputValues", p.transactionOutputValues },
                { "transactionInputs", p.transactionInputs },
                { "transactionOutputs", p.transactionOutputs },
                { "inputScripts", p.inputScripts },
                { "outputScripts", p.outputScripts }
        };
    }
    void from_json(const json& j, TransactionVo& p){
        j.at("blockHeight").get_to(p.blockHeight);
        j.at("blockHash").get_to(p.blockHash);
        j.at("blockConfirmations").get_to(p.blockConfirmations);
        j.at("transactionHash").get_to(p.transactionHash);
        j.at("blockTime").get_to(p.blockTime);
        j.at("transactionFee").get_to(p.transactionFee);
        j.at("transactionType").get_to(p.transactionType);
        j.at("transactionInputCount").get_to(p.transactionInputCount);
        j.at("transactionOutputCount").get_to(p.transactionOutputCount);
        j.at("transactionInputValues").get_to(p.transactionInputValues);
        j.at("transactionOutputValues").get_to(p.transactionOutputValues);
        j.at("transactionInputs").get_to(p.transactionInputs);
        j.at("transactionOutputs").get_to(p.transactionOutputs);
        j.at("inputScripts").get_to(p.inputScripts);
        j.at("outputScripts").get_to(p.outputScripts);
    }

    void to_json(json& j, const TransactionOutputVo3& p){
        j = json{
                { "value", p.value },
                { "unspentTransactionOutput", p.unspentTransactionOutput },
                { "transactionType", p.transactionType },
                { "fromBlockHeight", p.fromBlockHeight },
                { "fromBlockHash", p.fromBlockHash },
                { "fromTransactionHash", p.fromTransactionHash },
                { "fromTransactionOutputIndex", p.fromTransactionOutputIndex },
                { "fromOutputScript", p.fromOutputScript },
                { "toBlockHeight", p.toBlockHeight },
                { "toBlockHash", p.toBlockHash },
                { "toTransactionHash", p.toTransactionHash },
                { "toTransactionInputIndex", p.toTransactionInputIndex },
                { "toInputScript", p.toInputScript },
                { "inputTransaction", p.inputTransaction },
                { "outputTransaction", p.outputTransaction }
        };
    }
    void from_json(const json& j, TransactionOutputVo3& p){
        j.at("value").get_to(p.value);
        j.at("unspentTransactionOutput").get_to(p.unspentTransactionOutput);
        j.at("transactionType").get_to(p.transactionType);
        j.at("fromBlockHeight").get_to(p.fromBlockHeight);
        j.at("fromBlockHash").get_to(p.fromBlockHash);
        j.at("fromTransactionHash").get_to(p.fromTransactionHash);
        j.at("fromTransactionOutputIndex").get_to(p.fromTransactionOutputIndex);
        j.at("fromOutputScript").get_to(p.fromOutputScript);
        j.at("toBlockHeight").get_to(p.toBlockHeight);
        j.at("toBlockHash").get_to(p.toBlockHash);
        j.at("toTransactionHash").get_to(p.toTransactionHash);
        j.at("toTransactionInputIndex").get_to(p.toTransactionInputIndex);
        j.at("toInputScript").get_to(p.toInputScript);
        j.at("inputTransaction").get_to(p.inputTransaction);
        j.at("outputTransaction").get_to(p.outputTransaction);
    }

    void to_json(json& j, const TransactionInputVo2& p){
        j = json{
                { "value", p.value },
                { "address", p.address },
                { "transactionHash", p.transactionHash },
                { "transactionOutputIndex", p.transactionOutputIndex }
        };
    }
    void from_json(const json& j, TransactionInputVo2& p){
        j.at("value").get_to(p.value);
        j.at("address").get_to(p.address);
        j.at("transactionHash").get_to(p.transactionHash);
        j.at("transactionOutputIndex").get_to(p.transactionOutputIndex);
    }

    void to_json(json& j, const TransactionOutputVo2& p){
        j = json{
                { "value", p.value },
                { "address", p.address }
        };
    }
    void from_json(const json& j, TransactionOutputVo2& p){
        j.at("value").get_to(p.value);
        j.at("address").get_to(p.address);
    }

    void to_json(json& j, const UnconfirmedTransactionVo& p){
        j = json{
                { "transactionHash", p.transactionHash },
                { "transactionInputs", p.transactionInputs },
                { "transactionOutputs", p.transactionOutputs }
        };
    }
    void from_json(const json& j, UnconfirmedTransactionVo& p){
        j.at("transactionHash").get_to(p.transactionHash);
        j.at("transactionInputs").get_to(p.transactionInputs);
        j.at("transactionOutputs").get_to(p.transactionOutputs);
    }


    void to_json(json& j, const QueryTransactionByTransactionHashRequest& p){
        j = json{
                { "transactionHash", p.transactionHash }
        };
    }
    void from_json(const json& j, QueryTransactionByTransactionHashRequest& p){
        j.at("transactionHash").get_to(p.transactionHash);
    }
    void to_json(json& j, const QueryTransactionByTransactionHashResponse& p){
        j = json{
                { "transaction", p.transaction }
        };
    }
    void from_json(const json& j, QueryTransactionByTransactionHashResponse& p){
        j.at("transaction").get_to(p.transaction);
    }

    void to_json(json& j, const QueryTransactionOutputByAddressRequest& p){
        j = json{
                { "address", p.address }
        };
    }
    void from_json(const json& j, QueryTransactionOutputByAddressRequest& p){
        j.at("address").get_to(p.address);
    }
    void to_json(json& j, const QueryTransactionOutputByAddressResponse& p){
        j = json{
                { "transactionOutput", p.transactionOutput }
        };
    }
    void from_json(const json& j, QueryTransactionOutputByAddressResponse& p){
        j.at("transactionOutput").get_to(p.transactionOutput);
    }

    void to_json(json& j, const QueryTransactionOutputByTransactionOutputIdRequest& p){
        j = json{
                { "transactionHash", p.transactionHash },
                { "transactionOutputIndex", p.transactionOutputIndex }
        };
    }
    void from_json(const json& j, QueryTransactionOutputByTransactionOutputIdRequest& p){
        j.at("transactionHash").get_to(p.transactionHash);
        j.at("transactionOutputIndex").get_to(p.transactionOutputIndex);
    }
    void to_json(json& j, const QueryTransactionOutputByTransactionOutputIdResponse& p){
        j = json{
                { "transactionOutput", p.transactionOutput }
        };
    }
    void from_json(const json& j, QueryTransactionOutputByTransactionOutputIdResponse& p){
        j.at("transactionOutput").get_to(p.transactionOutput);
    }

    void to_json(json& j, const QueryTransactionsByBlockHashTransactionHeightRequest& p){
        j = json{
                { "blockHash", p.blockHash },
                { "pageCondition", p.pageCondition }
        };
    }
    void from_json(const json& j, QueryTransactionsByBlockHashTransactionHeightRequest& p){
        j.at("blockHash").get_to(p.blockHash);
        j.at("pageCondition").get_to(p.pageCondition);
    }
    void to_json(json& j, const QueryTransactionsByBlockHashTransactionHeightResponse& p){
        j = json{
                { "transactions", p.transactions },
        };
    }
    void from_json(const json& j, QueryTransactionsByBlockHashTransactionHeightResponse& p){
        j.at("transactions").get_to(p.transactions);
    }

    void to_json(json& j, const QueryUnconfirmedTransactionByTransactionHashRequest& p){
        j = json{
                { "transactionHash", p.transactionHash }
        };
    }
    void from_json(const json& j, QueryUnconfirmedTransactionByTransactionHashRequest& p){
        j.at("transactionHash").get_to(p.transactionHash);
    }
    void to_json(json& j, const QueryUnconfirmedTransactionByTransactionHashResponse& p){
        j = json{
                { "transaction", p.transaction }
        };
    }
    void from_json(const json& j, QueryUnconfirmedTransactionByTransactionHashResponse& p){
        j.at("transaction").get_to(p.transaction);
    }

    void to_json(json& j, const QueryUnconfirmedTransactionsRequest& p){
        j = json{
                { "pageCondition", p.pageCondition }
        };
    }
    void from_json(const json& j, QueryUnconfirmedTransactionsRequest& p){
        j.at("pageCondition").get_to(p.pageCondition);
    }
    void to_json(json& j, const QueryUnconfirmedTransactionsResponse& p){
        j = json{
                { "unconfirmedTransactions", p.unconfirmedTransactions }
        };
    }
    void from_json(const json& j, QueryUnconfirmedTransactionsResponse& p){
        j.at("unconfirmedTransactions").get_to(p.unconfirmedTransactions);
    }

    void to_json(json& j, const SubmitTransactionToBlockchainNetworkRequest& p){
        j = json{
                { "transaction", p.transaction }
        };
    }
    void from_json(const json& j, SubmitTransactionToBlockchainNetworkRequest& p){
        j.at("transaction").get_to(p.transaction);
    }
    void to_json(json& j, const SubmitTransactionToBlockchainNetworkResponse& p){
        j = json{
                { "transaction", p.transaction },
                { "successSubmitNodes", p.successSubmitNodes },
                { "failedSubmitNodes", p.failedSubmitNodes }
        };
    }
    void from_json(const json& j, SubmitTransactionToBlockchainNetworkResponse& p){
        j.at("transaction").get_to(p.transaction);
        j.at("successSubmitNodes").get_to(p.successSubmitNodes);
        j.at("failedSubmitNodes").get_to(p.failedSubmitNodes);
    }
};