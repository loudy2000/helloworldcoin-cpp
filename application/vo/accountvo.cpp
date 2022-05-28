//
// author x.king xdotking@gmail.com
//

#include "accountvo.h"



namespace vo {

    void to_json(json& j, const AccountVo& p){
        j = json{
                { "privateKey", p.privateKey },
                { "publicKey", p.publicKey },
                { "publicKeyHash", p.publicKeyHash },
                { "address", p.address }
        };
    }
    void from_json(const json& j, AccountVo& p){
        j.at("privateKey").get_to(p.privateKey);
        j.at("publicKey").get_to(p.publicKey);
        j.at("publicKeyHash").get_to(p.publicKeyHash);
        j.at("address").get_to(p.address);
    }

    void to_json(json& j, const AccountVo2& p){
        j = json{
                { "privateKey", p.privateKey },
                { "address", p.address },
                { "value", p.value }
        };
    }
    void from_json(const json& j, AccountVo2& p){
        j.at("privateKey").get_to(p.privateKey);
        j.at("address").get_to(p.address);
        j.at("value").get_to(p.value);
    }


    void to_json(json& j, const CreateAccountRequest& p){
        j = json{
        };
    }
    void from_json(const json& j, CreateAccountRequest& p){
    }
    void to_json(json& j, const CreateAccountResponse& p){
        j = json{
                { "account", p.account }
        };
    }
    void from_json(const json& j, CreateAccountResponse& p){
        j.at("account").get_to(p.account);
    }

    void to_json(json& j, const CreateAndSaveAccountRequest& p){
        j = json{
        };
    }
    void from_json(const json& j, CreateAndSaveAccountRequest& p){
    }
    void to_json(json& j, const CreateAndSaveAccountResponse& p){
        j = json{
                { "account", p.account }
        };
    }
    void from_json(const json& j, CreateAndSaveAccountResponse& p){
        j.at("account").get_to(p.account);
    }

    void to_json(json& j, const DeleteAccountRequest& p){
        j = json{
                { "address", p.address }
        };
    }
    void from_json(const json& j, DeleteAccountRequest& p){
        j.at("address").get_to(p.address);
    }
    void to_json(json& j, const DeleteAccountResponse& p){
        j = json{
        };
    }
    void from_json(const json& j, DeleteAccountResponse& p){
    }

    void to_json(json& j, const QueryAllAccountsRequest& p){
        j = json{
        };
    }
    void from_json(const json& j, QueryAllAccountsRequest& p){
    }
    void to_json(json& j, const QueryAllAccountsResponse& p){
        j = json{
                { "balance", p.balance },
                { "accounts", p.accounts }
        };
    }
    void from_json(const json& j, QueryAllAccountsResponse& p){
        j.at("balance").get_to(p.balance);
        j.at("accounts").get_to(p.accounts);
    }

    void to_json(json& j, const SaveAccountRequest& p){
        j = json{
                { "privateKey", p.privateKey }
        };
    }
    void from_json(const json& j, SaveAccountRequest& p){
        j.at("privateKey").get_to(p.privateKey);
    }
    void to_json(json& j, const SaveAccountResponse& p){
        j = json{
        };
    }
    void from_json(const json& j, SaveAccountResponse& p){
    }
};