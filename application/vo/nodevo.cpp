//
// author x.king xdotking@gmail.com
//

#include "nodevo.h"



namespace vo{

    void to_json(json& j, const ActiveAutoSearchNodeRequest& p){
        j = json{
        };
    }
    void from_json(const json& j, ActiveAutoSearchNodeRequest& p){
    }
    void to_json(json& j, const ActiveAutoSearchNodeResponse& p){
        j = json{
        };
    }
    void from_json(const json& j, ActiveAutoSearchNodeResponse& p){
    }

    void to_json(json& j, const AddNodeRequest& p){
        j = json{
                { "ip", p.ip }
        };
    }
    void from_json(const json& j, AddNodeRequest& p){
        j.at("ip").get_to(p.ip);
    }
    void to_json(json& j, const AddNodeResponse& p){
        j = json{
                { "addNodeSuccess", p.addNodeSuccess }
        };
    }
    void from_json(const json& j, AddNodeResponse& p){
        j.at("addNodeSuccess").get_to(p.addNodeSuccess);
    }

    void to_json(json& j, const DeactiveAutoSearchNodeRequest& p){
        j = json{
        };
    }
    void from_json(const json& j, DeactiveAutoSearchNodeRequest& p){
    }
    void to_json(json& j, const DeactiveAutoSearchNodeResponse& p){
        j = json{
        };
    }
    void from_json(const json& j, DeactiveAutoSearchNodeResponse& p){
    }

    void to_json(json& j, const DeleteNodeRequest& p){
        j = json{
                { "ip", p.ip }
        };
    }
    void from_json(const json& j, DeleteNodeRequest& p){
        j.at("ip").get_to(p.ip);
    }
    void to_json(json& j, const DeleteNodeResponse& p){
        j = json{
        };
    }
    void from_json(const json& j, DeleteNodeResponse& p){
    }

    void to_json(json& j, const IsAutoSearchNodeRequest& p){
        j = json{
        };
    }
    void from_json(const json& j, IsAutoSearchNodeRequest& p){
    }
    void to_json(json& j, const IsAutoSearchNodeResponse& p){
        j = json{
                { "autoSearchNode", p.autoSearchNode }
        };
    }
    void from_json(const json& j, IsAutoSearchNodeResponse& p){
        j.at("autoSearchNode").get_to(p.autoSearchNode);
    }



    void to_json(json& j, const NodeVo& p){
        j = json{
                { "ip", p.ip },
                { "blockchainHeight", p.blockchainHeight }
        };
    }
    void from_json(const json& j, NodeVo& p){
        j.at("ip").get_to(p.ip);
        j.at("blockchainHeight").get_to(p.blockchainHeight);
    }



    void to_json(json& j, const QueryAllNodesRequest& p){
        j = json{
        };
    }
    void from_json(const json& j, QueryAllNodesRequest& p){
    }
    void to_json(json& j, const QueryAllNodesResponse& p){
        j = json{
                { "nodes", p.nodes }
        };
    }
    void from_json(const json& j, QueryAllNodesResponse& p){
        j.at("nodes").get_to(p.nodes);
    }



    void to_json(json& j, const QueryBlockchainHeightRequest& p){
        j = json{
        };
    }
    void from_json(const json& j, QueryBlockchainHeightRequest& p){
    }
    void to_json(json& j, const QueryBlockchainHeightResponse& p){
        j = json{
                { "blockchainHeight", p.blockchainHeight }
        };
    }
    void from_json(const json& j, QueryBlockchainHeightResponse& p){
        j.at("blockchainHeight").get_to(p.blockchainHeight);
    }

    void to_json(json& j, const UpdateNodeRequest& p){
        j = json{
                { "ip", p.ip },
                { "blockchainHeight", p.blockchainHeight }
        };
    }
    void from_json(const json& j, UpdateNodeRequest& p){
        j.at("ip").get_to(p.ip);
        j.at("blockchainHeight").get_to(p.blockchainHeight);
    }
    void to_json(json& j, const UpdateNodeResponse& p){
        j = json{
        };
    }
    void from_json(const json& j, UpdateNodeResponse& p){
    }
}