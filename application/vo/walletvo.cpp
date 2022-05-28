//
// author x.king xdotking@gmail.com
//

#include "walletvo.h"



namespace vo {


    void to_json(json& j, const PayerVo& p){
        j = json{
                { "privateKey", p.privateKey },
                { "transactionHash", p.transactionHash },
                { "transactionOutputIndex", p.transactionOutputIndex },
                { "value", p.value },
                { "address", p.address }
        };
    }
    void from_json(const json& j, PayerVo& p){
        j.at("privateKey").get_to(p.privateKey);
        j.at("transactionHash").get_to(p.transactionHash);
        j.at("transactionOutputIndex").get_to(p.transactionOutputIndex);
        j.at("value").get_to(p.value);
        j.at("address").get_to(p.address);
    }

    void to_json(json& j, const PayeeVo& p){
        j = json{
                { "address", p.address },
                { "value", p.value }
        };
    }
    void from_json(const json& j, PayeeVo& p){
        j.at("address").get_to(p.address);
        j.at("value").get_to(p.value);
    }

    void to_json(json& j, const AutomaticBuildTransactionRequest& p){
        j = json{
                { "nonChangePayees", p.nonChangePayees }
        };
    }
    void from_json(const json& j, AutomaticBuildTransactionRequest& p){
        j.at("nonChangePayees").get_to(p.nonChangePayees);
    }
    void to_json(json& j, const AutomaticBuildTransactionResponse& p){
        j = json{
                { "buildTransactionSuccess", p.buildTransactionSuccess },
                { "transactionHash", p.transactionHash },
                { "fee", p.fee },
                { "payers", p.payers },
                { "nonChangePayees", p.nonChangePayees },
                { "changePayee", p.changePayee },
                { "payees", p.payees },
                { "transaction", p.transaction }
        };
    }
    void from_json(const json& j, AutomaticBuildTransactionResponse& p){
        j.at("buildTransactionSuccess").get_to(p.buildTransactionSuccess);
        j.at("transactionHash").get_to(p.transactionHash);
        j.at("fee").get_to(p.fee);
        j.at("payers").get_to(p.payers);
        j.at("nonChangePayees").get_to(p.nonChangePayees);
        j.at("changePayee").get_to(p.changePayee);
        j.at("payees").get_to(p.payees);
        j.at("transaction").get_to(p.transaction);
    }
};