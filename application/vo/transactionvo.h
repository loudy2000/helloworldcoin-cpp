//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_TRANSACTIONVO_H
#define HELLOWORLDCOIN_CPP_TRANSACTIONVO_H

#include <cstdint>
#include <string>
#include <vector>
#include "../../netcoredto/netcoredto.h"
#include "frameworkvo.h"
#include "../../thirdpart/nlohmann/json.hpp"

using namespace std;
using namespace dto;
using json = nlohmann::json;



namespace vo {

    struct TransactionInputVo {
        string address;
        uint64_t value;
        string inputScript;
        string transactionHash;
        uint64_t transactionOutputIndex;
    };
    struct TransactionOutputVo {
        string address;
        uint64_t value;
        string outputScript;
        string transactionHash;
        uint64_t transactionOutputIndex;
    };
    struct TransactionVo {
        uint64_t blockHeight;
        string blockHash;
        uint64_t blockConfirmations;
        string transactionHash;
        string blockTime;

        uint64_t transactionFee;
        string transactionType;
        uint64_t transactionInputCount;
        uint64_t transactionOutputCount;
        uint64_t transactionInputValues;
        uint64_t transactionOutputValues;

        vector<TransactionInputVo> transactionInputs;
        vector<TransactionOutputVo> transactionOutputs;

        vector<string> inputScripts;
        vector<string> outputScripts;
    };
    struct TransactionOutputVo3 {
        uint64_t value;
        bool unspentTransactionOutput;
        string transactionType;

        uint64_t fromBlockHeight;
        string fromBlockHash;
        string fromTransactionHash;
        uint64_t fromTransactionOutputIndex;
        string fromOutputScript;

        uint64_t toBlockHeight;
        string toBlockHash;
        string toTransactionHash;
        uint64_t toTransactionInputIndex;
        string toInputScript;

        TransactionVo inputTransaction;
        TransactionVo outputTransaction;
    };

    struct TransactionInputVo2 {
        uint64_t value;
        string address;
        string transactionHash;
        uint64_t transactionOutputIndex;
    };
    struct TransactionOutputVo2 {
        uint64_t value;
        string address;
    };
    struct UnconfirmedTransactionVo {
        string transactionHash;
        vector<TransactionInputVo2> transactionInputs;
        vector<TransactionOutputVo2> transactionOutputs;
    };
    struct QueryTransactionByTransactionHashRequest {
        string transactionHash;
    };
    struct QueryTransactionByTransactionHashResponse {
        TransactionVo transaction;
    };
    struct QueryTransactionOutputByAddressRequest {
        string address;
    };
    struct QueryTransactionOutputByAddressResponse {
        TransactionOutputVo3 transactionOutput;
    };
    struct QueryTransactionOutputByTransactionOutputIdRequest {
        string transactionHash;
        uint64_t transactionOutputIndex;
    };
    struct QueryTransactionOutputByTransactionOutputIdResponse {
        TransactionOutputVo3 transactionOutput;
    };
    struct QueryTransactionsByBlockHashTransactionHeightRequest {
        string blockHash;
        PageCondition pageCondition;
    };
    struct QueryTransactionsByBlockHashTransactionHeightResponse {
        vector<TransactionVo> transactions;
    };
    struct QueryUnconfirmedTransactionByTransactionHashRequest {
        string transactionHash;
    };
    struct QueryUnconfirmedTransactionByTransactionHashResponse {
        UnconfirmedTransactionVo transaction;
    };
    struct QueryUnconfirmedTransactionsRequest {
        PageCondition pageCondition;
    };
    struct QueryUnconfirmedTransactionsResponse {
        vector<UnconfirmedTransactionVo> unconfirmedTransactions;
    };
    struct SubmitTransactionToBlockchainNetworkRequest {
        TransactionDto transaction;
    };
    struct SubmitTransactionToBlockchainNetworkResponse {
        TransactionDto transaction;
        vector<string> successSubmitNodes;
        vector<string> failedSubmitNodes;
    };


    void to_json(json& j, const TransactionInputVo& p);
    void from_json(const json& j, TransactionInputVo& p);

    void to_json(json& j, const TransactionOutputVo& p);
    void from_json(const json& j, TransactionOutputVo& p);

    void to_json(json& j, const TransactionVo& p);
    void from_json(const json& j, TransactionVo& p);

    void to_json(json& j, const TransactionOutputVo3& p);
    void from_json(const json& j, TransactionOutputVo3& p);

    void to_json(json& j, const TransactionInputVo2& p);
    void from_json(const json& j, TransactionInputVo2& p);

    void to_json(json& j, const TransactionOutputVo2& p);
    void from_json(const json& j, TransactionOutputVo2& p);

    void to_json(json& j, const UnconfirmedTransactionVo& p);
    void from_json(const json& j, UnconfirmedTransactionVo& p);


    void to_json(json& j, const QueryTransactionByTransactionHashRequest& p);
    void from_json(const json& j, QueryTransactionByTransactionHashRequest& p);
    void to_json(json& j, const QueryTransactionByTransactionHashResponse& p);
    void from_json(const json& j, QueryTransactionByTransactionHashResponse& p);

    void to_json(json& j, const QueryTransactionOutputByAddressRequest& p);
    void from_json(const json& j, QueryTransactionOutputByAddressRequest& p);
    void to_json(json& j, const QueryTransactionOutputByAddressResponse& p);
    void from_json(const json& j, QueryTransactionOutputByAddressResponse& p);

    void to_json(json& j, const QueryTransactionOutputByTransactionOutputIdRequest& p);
    void from_json(const json& j, QueryTransactionOutputByTransactionOutputIdRequest& p);
    void to_json(json& j, const QueryTransactionOutputByTransactionOutputIdResponse& p);
    void from_json(const json& j, QueryTransactionOutputByTransactionOutputIdResponse& p);

    void to_json(json& j, const QueryTransactionsByBlockHashTransactionHeightRequest& p);
    void from_json(const json& j, QueryTransactionsByBlockHashTransactionHeightRequest& p);
    void to_json(json& j, const QueryTransactionsByBlockHashTransactionHeightResponse& p);
    void from_json(const json& j, QueryTransactionsByBlockHashTransactionHeightResponse& p);

    void to_json(json& j, const QueryUnconfirmedTransactionByTransactionHashRequest& p);
    void from_json(const json& j, QueryUnconfirmedTransactionByTransactionHashRequest& p);
    void to_json(json& j, const QueryUnconfirmedTransactionByTransactionHashResponse& p);
    void from_json(const json& j, QueryUnconfirmedTransactionByTransactionHashResponse& p);

    void to_json(json& j, const QueryUnconfirmedTransactionsRequest& p);
    void from_json(const json& j, QueryUnconfirmedTransactionsRequest& p);
    void to_json(json& j, const QueryUnconfirmedTransactionsResponse& p);
    void from_json(const json& j, QueryUnconfirmedTransactionsResponse& p);

    void to_json(json& j, const SubmitTransactionToBlockchainNetworkRequest& p);
    void from_json(const json& j, SubmitTransactionToBlockchainNetworkRequest& p);
    void to_json(json& j, const SubmitTransactionToBlockchainNetworkResponse& p);
    void from_json(const json& j, SubmitTransactionToBlockchainNetworkResponse& p);
};

#endif //HELLOWORLDCOIN_CPP_TRANSACTIONVO_H