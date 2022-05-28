//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_NODEVO_H
#define HELLOWORLDCOIN_CPP_NODEVO_H

#include <cstdint>
#include <string>
#include <vector>
#include "../../thirdpart/nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;



namespace vo {

    struct ActiveAutoSearchNodeRequest {};
    struct ActiveAutoSearchNodeResponse {};
    struct AddNodeRequest {
        string ip;
    };
    struct AddNodeResponse {
        bool addNodeSuccess;
    };
    struct DeactiveAutoSearchNodeRequest {};
    struct DeactiveAutoSearchNodeResponse {};
    struct DeleteNodeRequest {
        string ip;
    };
    struct DeleteNodeResponse {};
    struct IsAutoSearchNodeRequest {};
    struct IsAutoSearchNodeResponse {
        bool autoSearchNode;
    };
    struct NodeVo {
        string ip;
        uint64_t blockchainHeight;
    };
    struct QueryAllNodesRequest {};
    struct QueryAllNodesResponse {
        vector<NodeVo> nodes;
    };
    struct QueryBlockchainHeightRequest {};
    struct QueryBlockchainHeightResponse {
        uint64_t blockchainHeight;
    };
    struct UpdateNodeRequest {
        string ip;
        uint64_t blockchainHeight;
    };
    struct UpdateNodeResponse {};


    void to_json(json& j, const ActiveAutoSearchNodeRequest& p);
    void from_json(const json& j, ActiveAutoSearchNodeRequest& p);
    void to_json(json& j, const ActiveAutoSearchNodeResponse& p);
    void from_json(const json& j, ActiveAutoSearchNodeResponse& p);

    void to_json(json& j, const AddNodeRequest& p);
    void from_json(const json& j, AddNodeRequest& p);
    void to_json(json& j, const AddNodeResponse& p);
    void from_json(const json& j, AddNodeResponse& p);

    void to_json(json& j, const DeactiveAutoSearchNodeRequest& p);
    void from_json(const json& j, DeactiveAutoSearchNodeRequest& p);
    void to_json(json& j, const DeactiveAutoSearchNodeResponse& p);
    void from_json(const json& j, DeactiveAutoSearchNodeResponse& p);

    void to_json(json& j, const DeleteNodeRequest& p);
    void from_json(const json& j, DeleteNodeRequest& p);
    void to_json(json& j, const DeleteNodeResponse& p);
    void from_json(const json& j, DeleteNodeResponse& p);

    void to_json(json& j, const IsAutoSearchNodeRequest& p);
    void from_json(const json& j, IsAutoSearchNodeRequest& p);
    void to_json(json& j, const IsAutoSearchNodeResponse& p);
    void from_json(const json& j, IsAutoSearchNodeResponse& p);

    void to_json(json& j, const NodeVo& p);
    void from_json(const json& j, NodeVo& p);

    void to_json(json& j, const QueryAllNodesRequest& p);
    void from_json(const json& j, QueryAllNodesRequest& p);
    void to_json(json& j, const QueryAllNodesResponse& p);
    void from_json(const json& j, QueryAllNodesResponse& p);

    void to_json(json& j, const QueryBlockchainHeightRequest& p);
    void from_json(const json& j, QueryBlockchainHeightRequest& p);
    void to_json(json& j, const QueryBlockchainHeightResponse& p);
    void from_json(const json& j, QueryBlockchainHeightResponse& p);

    void to_json(json& j, const UpdateNodeRequest& p);
    void from_json(const json& j, UpdateNodeRequest& p);
    void to_json(json& j, const UpdateNodeResponse& p);
    void from_json(const json& j, UpdateNodeResponse& p);
};

#endif //HELLOWORLDCOIN_CPP_NODEVO_H