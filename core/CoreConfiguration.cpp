//
// author x.king xdotking@gmail.com
//

#include "CoreConfiguration.h"
#include "../util/FileUtil.h"
#include "../util/ByteUtil.h"
#include "../util/KvDbUtil.h"

namespace core{

    const string  CONFIGURATION_DATABASE_NAME = "ConfigurationDatabase";

    const string MINE_OPTION_KEY = "IS_MINER_ACTIVE";

    const string MINER_MINE_MAX_BLOCK_HEIGHT_KEY = "MINER_MINE_MAX_BLOCK_HEIGHT";



    const bool MINE_OPTION_DEFAULT_VALUE = false;

    const uint64_t MINE_TIMESTAMP_PER_ROUND = 1000 * 10;




    string CoreConfiguration::getCorePath() {
        return this->corePath;
    }


    bool CoreConfiguration::isMinerActive() {
        vector<unsigned char> mineOption = getConfigurationValue(ByteUtil::stringToUtf8Bytes(MINE_OPTION_KEY));
        if(mineOption.empty()){
            return MINE_OPTION_DEFAULT_VALUE;
        }
        return ByteUtil::utf8BytesToBoolean(mineOption);
    }


    void CoreConfiguration::activeMiner() {
        addOrUpdateConfiguration(ByteUtil::stringToUtf8Bytes(MINE_OPTION_KEY),ByteUtil::booleanToUtf8Bytes(true));
    }


    void CoreConfiguration::deactiveMiner() {
        addOrUpdateConfiguration(ByteUtil::stringToUtf8Bytes(MINE_OPTION_KEY),ByteUtil::booleanToUtf8Bytes(false));
    }

    void CoreConfiguration::setMinerMineMaxBlockHeight(uint64_t maxHeight) {
        addOrUpdateConfiguration(ByteUtil::stringToUtf8Bytes(MINER_MINE_MAX_BLOCK_HEIGHT_KEY),ByteUtil::uint64ToBytes(maxHeight));
    }

    uint64_t CoreConfiguration::getMinerMineMaxBlockHeight() {
        vector<unsigned char> bytesMineMaxBlockHeight = getConfigurationValue(ByteUtil::stringToUtf8Bytes(MINER_MINE_MAX_BLOCK_HEIGHT_KEY));
        if(bytesMineMaxBlockHeight.empty()){
            return 10000000000000000L;
        }
        return ByteUtil::bytesToUint64(bytesMineMaxBlockHeight);
    }

    uint64_t CoreConfiguration::getMinerMineTimeInterval() {
        return MINE_TIMESTAMP_PER_ROUND;
    }







    string CoreConfiguration::getConfigurationDatabasePath(){
        return FileUtil::newPath(corePath, CONFIGURATION_DATABASE_NAME);
    }
    vector<unsigned char> CoreConfiguration::getConfigurationValue(vector<unsigned char> configurationKey) {
        return KvDbUtil::get(getConfigurationDatabasePath(), configurationKey);
    }
    void CoreConfiguration::addOrUpdateConfiguration(vector<unsigned char> configurationKey, vector<unsigned char> configurationValue) {
        KvDbUtil::put(getConfigurationDatabasePath(), configurationKey, configurationValue);
    }

    CoreConfiguration::CoreConfiguration(string corePath) {
        FileUtil::makeDirectory(corePath);
        this->corePath = corePath;
    }
}