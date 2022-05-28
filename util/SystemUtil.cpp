//
// author x.king xdotking@gmail.com
//
#include <iostream>
#include "SystemUtil.h"
#include "LogUtil.h"

#if defined _WIN32 || defined _WIN64
#include <windows.h>
#include <string>
#include <iostream>
#include <shellapi.h>
#else
#include <unistd.h>
#endif

bool SystemUtil::isWindowsOperateSystem(){
#ifdef _WIN32
    return true;
#else
    return false;
#endif
}

bool SystemUtil::isMacOperateSystem(){
#ifdef __APPLE__
    return true;
#else
    return false;
#endif
}

bool SystemUtil::isLinuxOperateSystem(){
#ifdef __linux
    return true;
#else
    return false;
#endif
}

void SystemUtil::errorExit(string message, exception exception){
    LogUtil::error("system error occurred, and exited, please check the error！"+message,exception);
    exit(-1);
}
#if defined _WIN32 || defined _WIN64
string SystemUtil::systemRootDirectory(){
    string path;
    TCHAR buffer[MAX_PATH] = { 0 };
    GetModuleFileName( NULL, buffer, MAX_PATH );
    path = string(buffer);
    size_t position = path.find_last_of("/\\");
    path = path.substr(0,position);
    position = path.find_last_of("/\\");
    path = path.substr(0,position);
    return path;
}
#else
string SystemUtil::systemRootDirectory(){
    return getcwd(NULL,0);
}
#endif


#if 0
int main()
{
    cout << SystemUtil::systemRootDirectory() << endl;
}
#endif



void SystemUtil::callDefaultBrowser(string url){
#if defined _WIN32 || defined _WIN64
    ShellExecuteA(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL);
#else

#endif
}



