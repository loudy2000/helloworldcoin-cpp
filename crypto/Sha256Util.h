//
// author x.king xdotking@gmail.com
//
#ifndef UNTITLED_SHA256UTIL_H
#define UNTITLED_SHA256UTIL_H
#include <string>
#include <vector>
using namespace std;


namespace Sha256Util{

    vector<unsigned char> digest(vector<unsigned char> input);
    vector<unsigned char> doubleDigest(vector<unsigned char> input);
}


#endif //UNTITLED_SHA256UTIL_H
