//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_SYSTEMUTIL_H
#define HELLOWORLDCOIN_CPP_SYSTEMUTIL_H

#include <string>

using namespace std;

namespace SystemUtil {
    bool isWindowsOperateSystem();
    bool isMacOperateSystem();
    bool isLinuxOperateSystem();

    void errorExit(string message, exception exception);
    string systemRootDirectory();
    void callDefaultBrowser(string url);
};


#endif //HELLOWORLDCOIN_CPP_SYSTEMUTIL_H
