//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_CORECONFIGURATION_H
#define HELLOWORLDCOIN_CPP_CORECONFIGURATION_H

#include <string>
#include <vector>
using namespace std;


namespace core{
    /**
     * Core Configuration
     * This class manages the configuration of BlockchainCore.
     * Here you can persist configuration information.
     * In theory, any configuration required by the BlockchainCore module can be obtained from this object.
     *
     * @author x.king xdotking@gmail.com
     */
    class CoreConfiguration {
    private:
        //BlockchainCore data storage path
        string corePath;
    public:
        CoreConfiguration(string corePath);
    public:
        /**
         * get BlockchainCore data storage path
         */
        string getCorePath();
        /**
         * Is the miner active?
         */
        bool isMinerActive();
        /**
         * active Miner
         */
        void activeMiner() ;
        /**
         * deactive Miner
         */
        void deactiveMiner() ;
        /**
         * Set the maximum block height that miners can mine
         */
        void setMinerMineMaxBlockHeight(uint64_t maxHeight) ;

        /**
         * Get the maximum block height that miner can mine
         */
        uint64_t getMinerMineMaxBlockHeight() ;

        /**
         * Miner mining time period
         */
        uint64_t getMinerMineTimeInterval();
    private:
        string getConfigurationDatabasePath();
        vector<unsigned char> getConfigurationValue(vector<unsigned char> configurationKey);
        void addOrUpdateConfiguration(vector<unsigned char> configurationKey, vector<unsigned char> configurationValue);
    };

}

#endif //HELLOWORLDCOIN_CPP_CORECONFIGURATION_H
