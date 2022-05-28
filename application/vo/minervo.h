//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_MINERVO_H
#define HELLOWORLDCOIN_CPP_MINERVO_H


#include <cstdint>
#include <string>
#include <vector>
#include "../../thirdpart/nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;



namespace vo {

    struct ActiveMinerRequest {};
    struct ActiveMinerResponse {};

    struct DeactiveMinerRequest {};
    struct DeactiveMinerResponse {};

    struct IsMinerActiveRequest {};
    struct IsMinerActiveResponse {
        bool minerInActiveState;
    };
    struct GetMaxBlockHeightRequest {};
    struct GetMinerMineMaxBlockHeightRequest {};
    struct GetMinerMineMaxBlockHeightResponse {
        uint64_t maxBlockHeight;
    };
    struct SetMinerMineMaxBlockHeightRequest {
        uint64_t maxBlockHeight;
    };
    struct SetMinerMineMaxBlockHeightResponse {};



    void to_json(json& j, const ActiveMinerRequest& p);
    void from_json(const json& j, ActiveMinerRequest& p);
    void to_json(json& j, const ActiveMinerResponse& p);
    void from_json(const json& j, ActiveMinerResponse& p);


    void to_json(json& j, const DeactiveMinerRequest& p);
    void from_json(const json& j, DeactiveMinerRequest& p);
    void to_json(json& j, const DeactiveMinerResponse& p);
    void from_json(const json& j, DeactiveMinerResponse& p);


    void to_json(json& j, const IsMinerActiveRequest& p);
    void from_json(const json& j, IsMinerActiveRequest& p);
    void to_json(json& j, const IsMinerActiveResponse& p);
    void from_json(const json& j, IsMinerActiveResponse& p);


    void to_json(json& j, const GetMaxBlockHeightRequest& p);
    void from_json(const json& j, GetMaxBlockHeightRequest& p);


    void to_json(json& j, const GetMinerMineMaxBlockHeightRequest& p);
    void from_json(const json& j, GetMinerMineMaxBlockHeightRequest& p);
    void to_json(json& j, const GetMinerMineMaxBlockHeightResponse& p);
    void from_json(const json& j, GetMinerMineMaxBlockHeightResponse& p);


    void to_json(json& j, const SetMinerMineMaxBlockHeightRequest& p);
    void from_json(const json& j, SetMinerMineMaxBlockHeightRequest& p);
    void to_json(json& j, const SetMinerMineMaxBlockHeightResponse& p);
    void from_json(const json& j, SetMinerMineMaxBlockHeightResponse& p);
};


#endif //HELLOWORLDCOIN_CPP_MINERVO_H
