//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_NETCORECONFIGURATION_H
#define HELLOWORLDCOIN_CPP_NETCORECONFIGURATION_H

#include <string>
#include <vector>
#include <cstdint>
using namespace std;

namespace netcoreconfiguration {


    class NetCoreConfiguration{
    private:
        string netCorePath;
    public:
        NetCoreConfiguration(string netCorePath);
    public:
        string getNetCorePath();

        uint64_t getSeedNodeInitializeTimeInterval();
        uint64_t getNodeSearchTimeInterval();
        uint64_t getNodeBroadcastTimeInterval();
        uint64_t getNodeCleanTimeInterval();


        bool isAutoSearchBlock();
        void activeAutoSearchBlock() ;
        void deactiveAutoSearchBlock() ;

        bool isAutoSearchNode();
        void activeAutoSearchNode();
        void deactiveAutoSearchNode();


        uint64_t getBlockSearchTimeInterval();
        uint64_t getBlockBroadcastTimeInterval();

        uint64_t getBlockchainHeightSearchTimeInterval();
        uint64_t getBlockchainHeightBroadcastTimeInterval();

        uint64_t getHardForkBlockCount();
        uint64_t getUnconfirmedTransactionsSearchTimeInterval();

    private:
        vector<unsigned char> getConfigurationValue(vector<unsigned char> configurationKey) ;
        void addOrUpdateConfiguration(vector<unsigned char> configurationKey, vector<unsigned char> configurationValue) ;
        string getNetCoreConfigurationDatabasePath();
    };
};


#endif //HELLOWORLDCOIN_CPP_NETCORECONFIGURATION_H
