//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_BLOCKCHAINCORE_H
#define HELLOWORLDCOIN_CPP_BLOCKCHAINCORE_H


#include "BlockchainDatabase.h"
#include "UnconfirmedTransactionDatabase.h"
#include "Miner.h"

namespace core{
    /**
     * Blockchain core
     * This class represents a complete stand-alone version (without network interaction function) of the blockchain core system,
     * which maintains the complete data of a blockchain at the bottom.
     *
     * At the beginning of the design, in order to simplify, it is designed without network module.
     * Except that it does not contain network modules, it contains all the functions that a blockchain system should have, including
     * 1. Blockchain account generation 2. Transfer 3. Submit transaction to blockchain
     * 4. Mining 5. Add blocks to the blockchain 6. Data verification: block verification, transaction verification
     * 7. On-chain block rollback 8. On-chain block query, transaction query, account fund query... etc.
     *
     * Blockchain core consists of the following parts:
     * @see BlockchainDatabase
     * @see UnconfirmedTransactionDatabase
     * @see Miner
     * @see Wallet
     *
     * @author x.king xdotking@gmail.com
     */
    class BlockchainCore {
    private:
        CoreConfiguration *coreConfiguration;
        BlockchainDatabase *blockchainDatabase;
        UnconfirmedTransactionDatabase *unconfirmedTransactionDatabase;
        Wallet *wallet;
        Miner *miner;
    public:
        BlockchainCore(CoreConfiguration *coreConfiguration, BlockchainDatabase *blockchainDatabase,
                       UnconfirmedTransactionDatabase *unconfirmedTransactionDatabase, Wallet *wallet, Miner *miner);

    public:
        /**
         * start BlockchainCore
         */
        void start();
        /**
         * Add a block to the tail of the blockchain.
         */
        bool addBlockDto(BlockDto *blockDto);
        /**
         * Add a block to the tail of the blockchain.
         */
        bool addBlock(Block *block);
        /**
         * Delete the tail block (the last block) of the blockchain
         */
        void deleteTailBlock();
        /**
         * Delete blocks with block height greater than or equal to @blockHeight@
         */
        void deleteBlocks(uint64_t blockHeight) ;
        /**
         * query Blockchain Height
         */
        uint64_t queryBlockchainHeight() ;
        /**
         * query Block By Block Height
         */
        unique_ptr<Block> queryBlockByBlockHeight(uint64_t blockHeight);
        /**
         * query Block By Block Hash
         */
        unique_ptr<Block> queryBlockByBlockHash(string blockHash);
        /**
         * query Tail Block
         */
        unique_ptr<Block> queryTailBlock();




        /**
         * query Transaction By Transaction Hash
         */
        unique_ptr<Transaction> queryTransactionByTransactionHash(string transactionHash) ;
        /**
         * query Transaction By Transaction Height
         * @param transactionHeight  transaction height starts at 1.
         */
        unique_ptr<Transaction> queryTransactionByTransactionHeight(uint64_t transactionHeight) ;




        /**
         * query Transaction Output By Address
         */
        unique_ptr<TransactionOutput> queryTransactionOutputByAddress(string address) ;
        /**
         * query Unspent Transaction Output By Address
         */
        unique_ptr<TransactionOutput> queryUnspentTransactionOutputByAddress(string address) ;
        /**
         * query Spent Transaction Output By Address
         */
        unique_ptr<TransactionOutput> querySpentTransactionOutputByAddress(string address) ;




        /**
         * Build Transaction
         */
        AutoBuildTransactionResponse autoBuildTransaction(AutoBuildTransactionRequest *request) ;
        /**
         * Post Transaction To Blockchain
         */
        void postTransaction(TransactionDto *transactionDto) ;
        /**
         * query Unconfirmed Transactions
         */
        vector<TransactionDto> queryUnconfirmedTransactions(uint64_t from, uint64_t size) ;
        /**
         * query Unconfirmed Transaction By Transaction Hash
         */
        unique_ptr<TransactionDto> queryUnconfirmedTransactionByTransactionHash(string transactionHash) ;



        //region
        /**
         * block dto to block model
         */
        unique_ptr<Block> blockDto2Block(BlockDto *blockDto) ;
        /**
         * transaction dto to transaction model
         */
        unique_ptr<Transaction> transactionDto2Transaction(TransactionDto *transactionDto) ;
        //endregion

    public:
        //region get set
        BlockchainDatabase * getBlockchainDatabase() ;

        UnconfirmedTransactionDatabase * getUnconfirmedTransactionDatabase()  ;

        Miner * getMiner() ;

        Wallet * getWallet()  ;

        CoreConfiguration * getCoreConfiguration() ;
        //endregion
    };
}


#endif //HELLOWORLDCOIN_CPP_BLOCKCHAINCORE_H
