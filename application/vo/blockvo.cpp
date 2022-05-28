//
// author x.king xdotking@gmail.com
//

#include "blockvo.h"



namespace vo {


    void to_json(json& j, const BlockVo& p){
        j = json{
                { "height", p.height },
                { "blockConfirmations", p.blockConfirmations },
                { "blockSize", p.blockSize },
                { "transactionCount", p.transactionCount },
                { "time", p.time },
                { "minerIncentiveValue", p.minerIncentiveValue },
                { "difficulty", p.difficulty },
                { "nonce", p.nonce },
                { "hash", p.hash },
                { "previousBlockHash", p.previousBlockHash },
                { "nextBlockHash", p.nextBlockHash },
                { "merkleTreeRoot", p.merkleTreeRoot }
        };
    }
    void from_json(const json& j, BlockVo& p){
        j.at("height").get_to(p.height);
        j.at("blockConfirmations").get_to(p.blockConfirmations);
        j.at("blockSize").get_to(p.blockSize);
        j.at("transactionCount").get_to(p.transactionCount);
        j.at("time").get_to(p.time);
        j.at("minerIncentiveValue").get_to(p.minerIncentiveValue);
        j.at("difficulty").get_to(p.difficulty);
        j.at("nonce").get_to(p.nonce);
        j.at("hash").get_to(p.hash);
        j.at("previousBlockHash").get_to(p.previousBlockHash);
        j.at("nextBlockHash").get_to(p.nextBlockHash);
        j.at("merkleTreeRoot").get_to(p.merkleTreeRoot);
    }

    void to_json(json& j, const BlockVo2& p){
        j = json{
                { "height", p.height },
                { "blockSize", p.blockSize },
                { "transactionCount", p.transactionCount },
                { "minerIncentiveValue", p.minerIncentiveValue },
                { "time", p.time },
                { "hash", p.hash }
        };
    }
    void from_json(const json& j, BlockVo2& p){
        j.at("height").get_to(p.height);
        j.at("blockSize").get_to(p.blockSize);
        j.at("transactionCount").get_to(p.transactionCount);
        j.at("minerIncentiveValue").get_to(p.minerIncentiveValue);
        j.at("time").get_to(p.time);
        j.at("hash").get_to(p.hash);
    }

    void to_json(json& j, const DeleteBlocksRequest& p){
        j = json{
                { "blockHeight", p.blockHeight }
        };
    }
    void from_json(const json& j, DeleteBlocksRequest& p){
        j.at("blockHeight").get_to(p.blockHeight);
    }
    void to_json(json& j, const DeleteBlocksResponse& p){
        j = json{
        };
    }
    void from_json(const json& j, DeleteBlocksResponse& p){
    }

    void to_json(json& j, const QueryBlockByBlockHashRequest& p){
        j = json{
                { "blockHash", p.blockHash },
        };
    }
    void from_json(const json& j, QueryBlockByBlockHashRequest& p){
        j.at("blockHash").get_to(p.blockHash);
    }
    void to_json(json& j, const QueryBlockByBlockHashResponse& p){
        j = json{
                { "block", p.block },
        };
    }
    void from_json(const json& j, QueryBlockByBlockHashResponse& p){
        j.at("block").get_to(p.block);
    }

    void to_json(json& j, const QueryBlockByBlockHeightRequest& p){
        j = json{
                { "blockHeight", p.blockHeight },
        };
    }
    void from_json(const json& j, QueryBlockByBlockHeightRequest& p){
        j.at("blockHeight").get_to(p.blockHeight);
    }
    void to_json(json& j, const QueryBlockByBlockHeightResponse& p){
        j = json{
                { "block", p.block },
        };
    }
    void from_json(const json& j, QueryBlockByBlockHeightResponse& p){
        j.at("block").get_to(p.block);
    }

    void to_json(json& j, const QueryLatest10BlocksRequest& p){
        j = json{
        };
    }
    void from_json(const json& j, QueryLatest10BlocksRequest& p){
    }
    void to_json(json& j, const QueryLatest10BlocksResponse& p){
        j = json{
                { "blocks", p.blocks },
        };
    }
    void from_json(const json& j, QueryLatest10BlocksResponse& p){
        j.at("blocks").get_to(p.blocks);
    }
}