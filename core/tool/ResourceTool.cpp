//
// author x.king xdotking@gmail.com
//

#include "ResourceTool.h"
#include "../../util/SystemUtil.h"
#include "../../util/FileUtil.h"

namespace ResourceTool{

    string getDataRootPath() {
        string dataRootPath;
        if(SystemUtil::isWindowsOperateSystem()){
            dataRootPath = "C:\\helloworldcoin-cpp\\";
        }else if(SystemUtil::isMacOperateSystem()){
            dataRootPath = "/tmp/helloworldcoin-cpp/";
        }else if(SystemUtil::isLinuxOperateSystem()){
            dataRootPath = "/tmp/helloworldcoin-cpp/";
        }else{
            dataRootPath = "/tmp/helloworldcoin-cpp/";
        }
        FileUtil::makeDirectory(dataRootPath);
        return dataRootPath;
    }

    string getTestDataRootPath() {
        string dataRootPath;
        if(SystemUtil::isWindowsOperateSystem()){
            dataRootPath = "C:\\helloworldcoin-cpp-test\\";
        }else if(SystemUtil::isMacOperateSystem()){
            dataRootPath = "/tmp/helloworldcoin-cpp-test/";
        }else if(SystemUtil::isLinuxOperateSystem()){
            dataRootPath = "/tmp/helloworldcoin-cpp-test/";
        }else{
            dataRootPath = "/tmp/helloworldcoin-cpp-test/";
        }
        FileUtil::makeDirectory(dataRootPath);
        return dataRootPath;
    }
}