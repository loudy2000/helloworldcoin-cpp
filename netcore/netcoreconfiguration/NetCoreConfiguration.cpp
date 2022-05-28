//
// author x.king xdotking@gmail.com
//

#include "NetCoreConfiguration.h"
#include "../../util/ByteUtil.h"
#include "../../util/FileUtil.h"
#include "../../util/KvDbUtil.h"

namespace netcoreconfiguration {

    string NETCORE_CONFIGURATION_DATABASE_NAME = "NetCoreConfigurationDatabase";

    string AUTO_SEARCH_BLOCK_OPTION_KEY = "IS_AUTO_SEARCH_BLOCK";
    bool AUTO_SEARCH_BLOCK_OPTION_DEFAULT_VALUE = true;

    string AUTO_SEARCH_NODE_OPTION_KEY = "IS_AUTO_SEARCH_NODE";
    bool AUTO_SEARCH_NODE_OPTION_DEFAULT_VALUE = true;

    uint64_t SEARCH_NODE_TIME_INTERVAL = 1000 * 60 * 2;
    uint64_t SEARCH_BLOCKCHAIN_HEIGHT_TIME_INTERVAL = 1000 * 60 * 2;
    uint64_t SEARCH_BLOCKS_TIME_INTERVAL = 1000 * 60 * 2;
    uint64_t BLOCKCHAIN_HEIGHT_BROADCASTER_TIME_INTERVAL = 1000 * 20;
    uint64_t BLOCK_BROADCASTER_TIME_INTERVAL = 1000 * 20;
    uint64_t ADD_SEED_NODE_TIME_INTERVAL = 1000 * 60 * 2;
    uint64_t NODE_BROADCAST_TIME_INTERVAL = 1000 * 60 * 2;
    uint64_t NODE_CLEAN_TIME_INTERVAL = 1000 * 60 * 10;


    uint64_t HARD_FORK_BLOCK_COUNT = 100000000;

    uint64_t SEARCH_UNCONFIRMED_TRANSACTIONS_TIME_INTERVAL = 1000 * 60 * 2;


    NetCoreConfiguration::NetCoreConfiguration(string netCorePath) {
        this->netCorePath = netCorePath;
    }
    
    string NetCoreConfiguration::getNetCorePath() {
        return netCorePath;
    }

    
    bool NetCoreConfiguration::isAutoSearchBlock() {
        vector<unsigned char> bytesConfigurationValue = getConfigurationValue(ByteUtil::stringToUtf8Bytes(AUTO_SEARCH_BLOCK_OPTION_KEY));
        if(bytesConfigurationValue.empty()){
            return AUTO_SEARCH_BLOCK_OPTION_DEFAULT_VALUE;
        }
        return ByteUtil::utf8BytesToBoolean(bytesConfigurationValue);
    }

    
    void NetCoreConfiguration::activeAutoSearchBlock() {
        addOrUpdateConfiguration(ByteUtil::stringToUtf8Bytes(AUTO_SEARCH_BLOCK_OPTION_KEY),ByteUtil::booleanToUtf8Bytes(true));
    }

    
    void NetCoreConfiguration::deactiveAutoSearchBlock() {
        addOrUpdateConfiguration(ByteUtil::stringToUtf8Bytes(AUTO_SEARCH_BLOCK_OPTION_KEY),ByteUtil::booleanToUtf8Bytes(false));
    }

    
    bool NetCoreConfiguration::isAutoSearchNode() {
        vector<unsigned char> bytesConfigurationValue = getConfigurationValue(ByteUtil::stringToUtf8Bytes(AUTO_SEARCH_NODE_OPTION_KEY));
        if(bytesConfigurationValue.empty()){
            return AUTO_SEARCH_NODE_OPTION_DEFAULT_VALUE;
        }
        return ByteUtil::utf8BytesToBoolean(bytesConfigurationValue);
    }

    
    void NetCoreConfiguration::activeAutoSearchNode() {
        addOrUpdateConfiguration(ByteUtil::stringToUtf8Bytes(AUTO_SEARCH_NODE_OPTION_KEY),ByteUtil::booleanToUtf8Bytes(true));
    }

    
    void NetCoreConfiguration::deactiveAutoSearchNode() {
        addOrUpdateConfiguration(ByteUtil::stringToUtf8Bytes(AUTO_SEARCH_NODE_OPTION_KEY),ByteUtil::booleanToUtf8Bytes(false));
    }

    
    uint64_t NetCoreConfiguration::getNodeSearchTimeInterval() {
        return SEARCH_NODE_TIME_INTERVAL;
    }

    
    uint64_t NetCoreConfiguration::getBlockchainHeightSearchTimeInterval() {
        return SEARCH_BLOCKCHAIN_HEIGHT_TIME_INTERVAL;
    }

    
    uint64_t NetCoreConfiguration::getBlockSearchTimeInterval() {
        return SEARCH_BLOCKS_TIME_INTERVAL;
    }

    
    uint64_t NetCoreConfiguration::getBlockchainHeightBroadcastTimeInterval() {
        return BLOCKCHAIN_HEIGHT_BROADCASTER_TIME_INTERVAL;
    }

    
    uint64_t NetCoreConfiguration::getBlockBroadcastTimeInterval() {
        return BLOCK_BROADCASTER_TIME_INTERVAL;
    }

    
    uint64_t NetCoreConfiguration::getSeedNodeInitializeTimeInterval() {
        return ADD_SEED_NODE_TIME_INTERVAL;
    }

    
    uint64_t NetCoreConfiguration::getNodeBroadcastTimeInterval() {
        return NODE_BROADCAST_TIME_INTERVAL;
    }

    
    uint64_t NetCoreConfiguration::getHardForkBlockCount() {
        return HARD_FORK_BLOCK_COUNT;
    }

    
    uint64_t NetCoreConfiguration::getUnconfirmedTransactionsSearchTimeInterval() {
        return SEARCH_UNCONFIRMED_TRANSACTIONS_TIME_INTERVAL;
    }


    uint64_t NetCoreConfiguration::getNodeCleanTimeInterval() {
        return NODE_CLEAN_TIME_INTERVAL;
    }



    vector<unsigned char> NetCoreConfiguration::getConfigurationValue(vector<unsigned char> configurationKey) {
        vector<unsigned char> bytesConfigurationValue = KvDbUtil::get(getNetCoreConfigurationDatabasePath(), configurationKey);
        return bytesConfigurationValue;
    }

    void NetCoreConfiguration::addOrUpdateConfiguration(vector<unsigned char> configurationKey, vector<unsigned char> configurationValue) {
        KvDbUtil::put(getNetCoreConfigurationDatabasePath(), configurationKey, configurationValue);
    }

    string NetCoreConfiguration::getNetCoreConfigurationDatabasePath(){
        return FileUtil::newPath(netCorePath, NETCORE_CONFIGURATION_DATABASE_NAME);
    }
}