//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_WALLETVO_H
#define HELLOWORLDCOIN_CPP_WALLETVO_H

#include <cstdint>
#include <string>
#include <vector>
#include "../../netcoredto/netcoredto.h"
#include "../../thirdpart/nlohmann/json.hpp"

using namespace std;
using namespace dto;
using json = nlohmann::json;



namespace vo {

    struct PayerVo {
        string privateKey;
        string transactionHash;
        uint64_t transactionOutputIndex;
        uint64_t value;
        string address;
    };
    struct PayeeVo {
        string address;
        uint64_t value;
    };

    struct AutomaticBuildTransactionRequest {
        vector<PayeeVo> nonChangePayees;
    };
    struct AutomaticBuildTransactionResponse {
        bool buildTransactionSuccess;
        string transactionHash;
        uint64_t fee;
        vector<PayerVo> payers;
        vector<PayeeVo> nonChangePayees;
        PayeeVo changePayee;
        vector<PayeeVo> payees;
        TransactionDto transaction;
    };

    void to_json(json& j, const PayerVo& p);
    void from_json(const json& j, PayerVo& p);

    void to_json(json& j, const PayeeVo& p);
    void from_json(const json& j, PayeeVo& p);

    void to_json(json& j, const AutomaticBuildTransactionRequest& p);
    void from_json(const json& j, AutomaticBuildTransactionRequest& p);
    void to_json(json& j, const AutomaticBuildTransactionResponse& p);
    void from_json(const json& j, AutomaticBuildTransactionResponse& p);
};

#endif //HELLOWORLDCOIN_CPP_WALLETVO_H