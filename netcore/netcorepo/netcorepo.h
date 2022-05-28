//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_NETCOREPO_H
#define HELLOWORLDCOIN_CPP_NETCOREPO_H

#include <string>
#include <cstdint>
#include "../../thirdpart/nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

namespace netcorepo {
    struct NodePo {
        string ip;
        uint64_t blockchainHeight;
    };

    void to_json(json& j, const NodePo& p);
    void from_json(const json& j, NodePo& p);
};


#endif //HELLOWORLDCOIN_CPP_NETCOREPO_H
