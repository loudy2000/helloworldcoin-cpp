//
// author x.king xdotking@gmail.com
//

#include "synchronizervo.h"



namespace vo {



    void to_json(json& j, const ActiveAutoSearchBlockRequest& p){}
    void from_json(const json& j, ActiveAutoSearchBlockRequest& p){}
    void to_json(json& j, const ActiveAutoSearchBlockResponse& p){}
    void from_json(const json& j, ActiveAutoSearchBlockResponse& p){}

    void to_json(json& j, const DeactiveAutoSearchBlockRequest& p){}
    void from_json(const json& j, DeactiveAutoSearchBlockRequest& p){}
    void to_json(json& j, const DeactiveAutoSearchBlockResponse& p){}
    void from_json(const json& j, DeactiveAutoSearchBlockResponse& p){}

    void to_json(json& j, const IsAutoSearchBlockRequest& p){}
    void from_json(const json& j, IsAutoSearchBlockRequest& p){}
    void to_json(json& j, const IsAutoSearchBlockResponse& p){
        j = json{
                { "autoSearchBlock", p.autoSearchBlock }
        };
    }
    void from_json(const json& j, IsAutoSearchBlockResponse& p){
        j.at("autoSearchBlock").get_to(p.autoSearchBlock);
    }
}