//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_COMMONCONTROLLER_H
#define HELLOWORLDCOIN_CPP_COMMONCONTROLLER_H

#include "../../thirdpart/httplib/httplib.h"
#include "../../util/JsonUtil.h"
#include <string>
using namespace std;



namespace controller {

    template <typename T> void success(httplib::Response &res, T const& response) {
        string s = "{\"status\":\"success\",\"message\":null,\"data\":" + JsonUtil::toString(response) + "}";
        res.set_content(s, "text/json");
    }
    void fail(httplib::Response &res, string message) ;
    void serviceUnavailable(httplib::Response &res) ;
};


#endif //HELLOWORLDCOIN_CPP_COMMONCONTROLLER_H
