//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_LOGUTIL_H
#define HELLOWORLDCOIN_CPP_LOGUTIL_H
#include <string>

using namespace std;

namespace LogUtil {
    void error(string message, exception exception);
    void debug(string message);
};


#endif //HELLOWORLDCOIN_CPP_LOGUTIL_H
