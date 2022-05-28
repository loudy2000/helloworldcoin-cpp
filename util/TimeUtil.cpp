//
// author x.king xdotking@gmail.com
//
#if defined _WIN32 || defined _WIN64
#include <iostream>
#include <ctime>
#include <stdexcept>
#include "TimeUtil.h"
#include <Windows.h>
using namespace std;
#else
#include <iomanip>
#include <chrono>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <string>
#include <stdexcept>
#include <iterator>
#include <sstream>
#include "TimeUtil.h"
#endif

#if defined _WIN32 || defined _WIN64
uint64_t TimeUtil::millisecondTimestamp(){
    string nowTimeUnix;
    string cs_uninxtime;
    string cs_milliseconds;
    SYSTEMTIME sysTime;
    GetLocalTime(&sysTime);
    time_t unixTime;
    time(&unixTime);
    char buf[30], buf1[30];
    sprintf_s(buf, sizeof(buf), "%I64d", (INT64)unixTime);
    sprintf_s(buf1, sizeof(buf1), "%03I64d", (INT64)sysTime.wMilliseconds);
    nowTimeUnix = string(buf) + string(buf1);
    return _atoi64(nowTimeUnix.c_str());
}
#else
uint64_t TimeUtil::millisecondTimestamp(){
    uint64_t ms = duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
    return ms ;
}
#endif


string TimeUtil::formatMillisecondTimestamp(uint64_t millisecondTimestamp){
    time_t t = time_t(millisecondTimestamp/1000);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S",localtime(&t) );
    return tmp;
}

