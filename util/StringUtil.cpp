//
// author x.king xdotking@gmail.com
//

#include "StringUtil.h"


bool StringUtil::equals(string str1, string str2){
    return str1.compare(str2) == 0;
}

bool StringUtil::isEmpty(string str){
    return str.empty() ;
}

string StringUtil::prefixPadding(string rawValue,int targetLength,string paddingValue){
    string target = rawValue;
    while (target.length() < targetLength){
        target = paddingValue + target;
    }
    return target;
}

string StringUtil::concatenate(string str1,string str2){
    return str1 + str2;
}

string StringUtil::concatenate3(string str1, string str2, string str3){
    return str1 + str2 + str3;
}

string StringUtil::valueOfUint64(uint64_t number){
    return to_string(number);
}
uint64_t StringUtil::length(string value) {
    return value.length();
}
