//
// author x.king xdotking@gmail.com
//

#include "CommonController.h"


namespace controller {

    void fail(httplib::Response &res, string message) {
        string s = "{\"status\":\"fail\",\"message\":\"" + message + "\",\"data\":null" + "}";
        res.set_content(s, "text/json");
    }
    
    void serviceUnavailable(httplib::Response &res) {
        fail(res, "service_unavailable");
    }

    void serviceUnauthorized(httplib::Response &res) {
        fail(res, "service_unauthorized");
    }
}