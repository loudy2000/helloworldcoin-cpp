//
// author x.king xdotking@gmail.com
//

#include "IncentiveSetting.h"
#include <cstdint>

namespace IncentiveSetting {

    uint64_t BLOCK_TIME = 1000 * 60 * 10;
    uint64_t INTERVAL_BLOCK_COUNT = 6 * 24 * 7 * 2;
    uint64_t INTERVAL_TIME = BLOCK_TIME * INTERVAL_BLOCK_COUNT;
    uint64_t BLOCK_INIT_INCENTIVE = uint64_t(50) * uint64_t(100000000);
    uint64_t INCENTIVE_HALVE_INTERVAL = 210000L;
};