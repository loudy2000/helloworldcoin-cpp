//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_INCENTIVESETTING_H
#define HELLOWORLDCOIN_CPP_INCENTIVESETTING_H


#include <cstdint>

namespace IncentiveSetting {

    //expected time to mine a block (unit: millisecond)
    extern uint64_t BLOCK_TIME;
    //the number of blocks in a mining difficulty cycle
    extern uint64_t INTERVAL_BLOCK_COUNT;
    //the expected cycle time in a mining cycle (unit: milliseconds)
    extern uint64_t INTERVAL_TIME;
    //block initialization incentive
    extern uint64_t BLOCK_INIT_INCENTIVE;
    //incentive amount halving cycle: incentives are halved every 210,000 blocks
    extern uint64_t INCENTIVE_HALVE_INTERVAL;
};


#endif //HELLOWORLDCOIN_CPP_INCENTIVESETTING_H
