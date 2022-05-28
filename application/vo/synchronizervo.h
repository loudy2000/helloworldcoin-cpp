//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_SYNCHRONIZERVO_H
#define HELLOWORLDCOIN_CPP_SYNCHRONIZERVO_H

#include <cstdint>
#include <string>
#include <vector>
#include "../../thirdpart/nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;



namespace vo {

    struct ActiveAutoSearchBlockRequest {};
    struct ActiveAutoSearchBlockResponse {};
    struct DeactiveAutoSearchBlockRequest {};
    struct DeactiveAutoSearchBlockResponse {};
    struct IsAutoSearchBlockRequest {};
    struct IsAutoSearchBlockResponse {
        bool autoSearchBlock;
    };


    void to_json(json& j, const ActiveAutoSearchBlockRequest& p);
    void from_json(const json& j, ActiveAutoSearchBlockRequest& p);
    void to_json(json& j, const ActiveAutoSearchBlockResponse& p);
    void from_json(const json& j, ActiveAutoSearchBlockResponse& p);

    void to_json(json& j, const DeactiveAutoSearchBlockRequest& p);
    void from_json(const json& j, DeactiveAutoSearchBlockRequest& p);
    void to_json(json& j, const DeactiveAutoSearchBlockResponse& p);
    void from_json(const json& j, DeactiveAutoSearchBlockResponse& p);

    void to_json(json& j, const IsAutoSearchBlockRequest& p);
    void from_json(const json& j, IsAutoSearchBlockRequest& p);
    void to_json(json& j, const IsAutoSearchBlockResponse& p);
    void from_json(const json& j, IsAutoSearchBlockResponse& p);

};

#endif //HELLOWORLDCOIN_CPP_SYNCHRONIZERVO_H