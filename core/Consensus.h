//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_CONSENSUS_H
#define HELLOWORLDCOIN_CPP_CONSENSUS_H


#include "BlockchainDatabase.h"
#include "model/model.h"

using namespace model;

namespace core{
    class BlockchainDatabase;
    class Consensus {
    public:
        /**
         * Check whether the block satisfies the consensus
         */
        bool checkConsensus(BlockchainDatabase *blockchainDatabase, Block *block) ;

        /**
         * Calculate mining difficulty of the target block
         */
        string calculateDifficult(BlockchainDatabase *blockchainDatabase, Block *block) ;
    };
}


#endif //HELLOWORLDCOIN_CPP_CONSENSUS_H
