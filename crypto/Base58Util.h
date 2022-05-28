//
// author x.king xdotking@gmail.com
//

#ifndef UNTITLED_BASE58UTIL_H
#define UNTITLED_BASE58UTIL_H

#include <string>
#include <vector>
using namespace std;


namespace Base58Util {

    string encode(vector<unsigned char> input) ;
    vector<unsigned char> decode(string input) ;
};


#endif //UNTITLED_BASE58UTIL_H
