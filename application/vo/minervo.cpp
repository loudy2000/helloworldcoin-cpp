//
// author x.king xdotking@gmail.com
//

#include "minervo.h"

namespace vo{




    void to_json(json& j, const ActiveMinerRequest& p){
        j = json{
        };
    }
    void from_json(const json& j, ActiveMinerRequest& p){
    }
    void to_json(json& j, const ActiveMinerResponse& p){
        j = json{
        };
    }
    void from_json(const json& j, ActiveMinerResponse& p){
    }


    void to_json(json& j, const DeactiveMinerRequest& p){
        j = json{
        };
    }
    void from_json(const json& j, DeactiveMinerRequest& p){
    }
    void to_json(json& j, const DeactiveMinerResponse& p){
        j = json{
        };
    }
    void from_json(const json& j, DeactiveMinerResponse& p){
    }


    void to_json(json& j, const IsMinerActiveRequest& p){
        j = json{
        };
    }
    void from_json(const json& j, IsMinerActiveRequest& p){
    }
    void to_json(json& j, const IsMinerActiveResponse& p){
        j = json{
                { "minerInActiveState", p.minerInActiveState }
        };
    }
    void from_json(const json& j, IsMinerActiveResponse& p){
        j.at("minerInActiveState").get_to(p.minerInActiveState);
    }


    void to_json(json& j, const GetMaxBlockHeightRequest& p){
        j = json{
        };
    }
    void from_json(const json& j, GetMaxBlockHeightRequest& p){
    }


    void to_json(json& j, const GetMinerMineMaxBlockHeightRequest& p){
        j = json{
        };
    }
    void from_json(const json& j, GetMinerMineMaxBlockHeightRequest& p){
    }
    void to_json(json& j, const GetMinerMineMaxBlockHeightResponse& p){
        j = json{
                { "maxBlockHeight", p.maxBlockHeight }
        };
    }
    void from_json(const json& j, GetMinerMineMaxBlockHeightResponse& p){
        j.at("maxBlockHeight").get_to(p.maxBlockHeight);
    }


    void to_json(json& j, const SetMinerMineMaxBlockHeightRequest& p){
        j = json{
                { "maxBlockHeight", p.maxBlockHeight }
        };
    }
    void from_json(const json& j, SetMinerMineMaxBlockHeightRequest& p){
        j.at("maxBlockHeight").get_to(p.maxBlockHeight);
    }
    void to_json(json& j, const SetMinerMineMaxBlockHeightResponse& p){
        j = json{
        };
    }
    void from_json(const json& j, SetMinerMineMaxBlockHeightResponse& p){
    }
}