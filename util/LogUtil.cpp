//
// author x.king xdotking@gmail.com
//

#include "LogUtil.h"
#include <iostream>

using namespace std;

void LogUtil::error(string message, exception exception){
    cout << "[ERROR] " << message << " , exception :" << (&exception)->what() << endl;
}
void LogUtil::debug(string message){
    cout << "[DEBUG] " << message << endl;
}