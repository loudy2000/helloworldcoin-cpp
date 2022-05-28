//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_STRINGSUTIL_H
#define HELLOWORLDCOIN_CPP_STRINGSUTIL_H

#include <vector>
#include <string>

using namespace std;


namespace StringsUtil {

    bool hasDuplicateElement(vector<string> list) ;
    bool contains(vector<string> values, string value) ;
    vector<string> split(string values, string valueSeparator) ;

};


#endif //HELLOWORLDCOIN_CPP_STRINGSUTIL_H
