//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_FILEUTIL_H
#define HELLOWORLDCOIN_CPP_FILEUTIL_H

#include <string>

using namespace std;

namespace FileUtil {
    string newPath(string parent, string child);
    void makeDirectory(string path);
    void deleteDirectory(string path);
    string read(string path);
};


#endif //HELLOWORLDCOIN_CPP_FILEUTIL_H
