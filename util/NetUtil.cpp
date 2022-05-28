//
// author x.king xdotking@gmail.com
//

#include "NetUtil.h"
#include "../thirdpart/httplib/httplib.h"


string  NetUtil::get(string requestUrl, string requestBody){

    int position = requestUrl.find_last_of("/");
    string scheme_host_port = requestUrl.substr(0,position);
    string path = requestUrl.substr(position);

    httplib::Client cli(scheme_host_port);
    if (auto res = cli.Post(&path[0] ,requestBody,"application/json")) {
        if (res->status == 200) {
            return res->body ;
        }
    }
    return "";
}


