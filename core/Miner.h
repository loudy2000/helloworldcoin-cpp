//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_MINER_H
#define HELLOWORLDCOIN_CPP_MINER_H

#include "Wallet.h"
#include "UnconfirmedTransactionDatabase.h"
#include "CoreConfiguration.h"
#include "BlockchainDatabase.h"

namespace core{

    class Miner {
    private:
        CoreConfiguration *coreConfiguration;
        Wallet *wallet;
        BlockchainDatabase *blockchainDatabase;
        UnconfirmedTransactionDatabase *unconfirmedTransactionDatabase;
    public:
        Miner(CoreConfiguration *coreConfiguration, Wallet *wallet, BlockchainDatabase *blockchainDatabase,
              UnconfirmedTransactionDatabase *unconfirmedTransactionDatabase);

    public:
        /**
         * start miner
         * Miners have two states: active and deactive.
         * If the miner is in active state, the miner will do work , such as mining.
         * If the miner is in deactive, the miner will not do any work.
         */
        void start() ;

        /**
         * Whether the miner is active status?
         */
        bool isActive() ;

        /**
         * active Miner: Set the miner as active status.
         */
        void active() ;

        /**
         * deactive Miner: Set the miner as deactive status.
         */
        void deactive() ;

        /**
         * Set the maximum block height that miners can mine
         */
        void setMinerMineMaxBlockHeight(uint64_t maxHeight) ;
        /**
         * Get the maximum block height that miner can mine
         */
        uint64_t getMinerMineMaxBlockHeight( ) ;
        //endregion

    public:
        //region get set
        Wallet * getWallet() ;

        BlockchainDatabase * getBlockchainDatabase() ;

        UnconfirmedTransactionDatabase * getUnconfirmedTransactionDatabase() ;

        CoreConfiguration * getCoreConfiguration();
        //endregion
    private:
        Block Miner::buildMiningBlock(BlockchainDatabase *blockchainDatabase, UnconfirmedTransactionDatabase *unconfirmedTransactionDatabase, Account *minerAccount);
        Transaction Miner::buildIncentiveTransaction(string address,uint64_t incentiveValue);
        vector<Transaction> Miner::packingTransactions(BlockchainDatabase *blockchainDatabase, UnconfirmedTransactionDatabase *unconfirmedTransactionDatabase);
        bool isMiningHeightExceedsLimit();
    };
}


#endif //HELLOWORLDCOIN_CPP_MINER_H
