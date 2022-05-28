//
// author x.king xdotking@gmail.com
//

#include "StringsUtil.h"
#include <set>


namespace StringsUtil{

    bool hasDuplicateElement(vector<string> values) {
        set<string> set;
        for (string value : values) {
            set.insert(value);
        }
        return values.size() != set.size();
    }

    bool contains(vector<string> values, string value) {
        for (string v : values) {
            if(value == v){
                return true;
            }
        }
        return false;
    }

    vector<string> split(string values, string valueSeparator) {
        vector<string> res;
        if("" == values) return res;

        char * strs = new char[values.length() + 1] ;
        strcpy(strs, values.c_str());

        char * d = new char[valueSeparator.length() + 1];
        strcpy(d, valueSeparator.c_str());

        char *p = strtok(strs, d);
        while(p) {
            string s = p;
            res.push_back(s);
            p = strtok(NULL, d);
        }

        return res;
    }
}