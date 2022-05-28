//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_ACCOUNTVO_H
#define HELLOWORLDCOIN_CPP_ACCOUNTVO_H

#include <cstdint>
#include <string>
#include <vector>
#include "../../thirdpart/nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;



namespace vo {

    struct AccountVo {
        string privateKey;
        string publicKey;
        string publicKeyHash;
        string address;
    };
    struct AccountVo2 {
        string privateKey;
        string address;
        uint64_t value;
    };
    struct CreateAccountRequest {};
    struct CreateAccountResponse {
        AccountVo account;
    };

    struct CreateAndSaveAccountRequest {};
    struct CreateAndSaveAccountResponse {
        AccountVo account;
    };

    struct DeleteAccountRequest {
        string address;
    };
    struct DeleteAccountResponse {};

    struct QueryAllAccountsRequest {};
    struct QueryAllAccountsResponse {
        uint64_t balance;
        vector<AccountVo2> accounts;
    };

    struct SaveAccountRequest {
        string privateKey;
    };
    struct SaveAccountResponse {};


    void to_json(json& j, const AccountVo& p);
    void from_json(const json& j, AccountVo& p);

    void to_json(json& j, const AccountVo2& p);
    void from_json(const json& j, AccountVo2& p);


    void to_json(json& j, const CreateAccountRequest& p);
    void from_json(const json& j, CreateAccountRequest& p);
    void to_json(json& j, const CreateAccountResponse& p);
    void from_json(const json& j, CreateAccountResponse& p);

    void to_json(json& j, const CreateAndSaveAccountRequest& p);
    void from_json(const json& j, CreateAndSaveAccountRequest& p);
    void to_json(json& j, const CreateAndSaveAccountResponse& p);
    void from_json(const json& j, CreateAndSaveAccountResponse& p);

    void to_json(json& j, const DeleteAccountRequest& p);
    void from_json(const json& j, DeleteAccountRequest& p);
    void to_json(json& j, const DeleteAccountResponse& p);
    void from_json(const json& j, DeleteAccountResponse& p);

    void to_json(json& j, const QueryAllAccountsRequest& p);
    void from_json(const json& j, QueryAllAccountsRequest& p);
    void to_json(json& j, const QueryAllAccountsResponse& p);
    void from_json(const json& j, QueryAllAccountsResponse& p);

    void to_json(json& j, const SaveAccountRequest& p);
    void from_json(const json& j, SaveAccountRequest& p);
    void to_json(json& j, const SaveAccountResponse& p);
    void from_json(const json& j, SaveAccountResponse& p);
};

#endif //HELLOWORLDCOIN_CPP_ACCOUNTVO_H