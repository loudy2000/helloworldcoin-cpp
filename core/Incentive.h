//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_INCENTIVE_H
#define HELLOWORLDCOIN_CPP_INCENTIVE_H


#include "BlockchainDatabase.h"
#include "model/model.h"
using namespace model;

namespace core{
    class BlockchainDatabase;
    /**
     * Incentive
     * How much digital currency should the system reward miners? It will be determined here.
     *
     * @author x.king xdotking@gmail.com
     */
    class Incentive {
    public:
        /**
         * Determine how much digital currency to reward miner
         */
        uint64_t incentiveValue(BlockchainDatabase *blockchainDatabase, Block *block) ;

        /**
         * Check Incentive
         */
        bool checkIncentive(BlockchainDatabase *blockchainDatabase, Block *block) ;
    };
}


#endif //HELLOWORLDCOIN_CPP_INCENTIVE_H
