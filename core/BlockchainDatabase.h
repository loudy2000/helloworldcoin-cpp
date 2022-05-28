//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_BLOCKCHAINDATABASE_H
#define HELLOWORLDCOIN_CPP_BLOCKCHAINDATABASE_H


#include "Incentive.h"
#include "Consensus.h"
#include "VirtualMachine.h"
#include "CoreConfiguration.h"
#include "../util/KvDbUtil.h"
#include <mutex>

using namespace BlockchainActionEnum;
using namespace TransactionTypeEnum;
using namespace KvDbUtil;

namespace core{
    class Incentive;
    class Consensus;
    /**
     * Blockchain Database
     * This class is used for persistence of blockchain data.
     *
     * @author x.king xdotking@gmail.com
     */
    class BlockchainDatabase {
    private:
        Consensus *consensus ;
        Incentive *incentive ;
        VirtualMachine *virtualMachine;
        CoreConfiguration *coreConfiguration;
    public:
        BlockchainDatabase(CoreConfiguration *coreConfiguration, Incentive *incentive, Consensus *consensus,
                           VirtualMachine *virtualMachine);
    public:
        //region add block、delete block
        /**
         * Add a block to the tail of the blockchain.
         */
        bool addBlockDto(BlockDto *blockDto);

        /**
        * Delete the tail block (the last block) of the blockchain
         */
        void deleteTailBlock();

        /**
         * Delete blocks with block height greater than or equal to @blockHeight@
         */
        void deleteBlocks(uint64_t blockHeight);
        //endregion



        //region check blocks, check transactions
        /**
         * Check if a block can be added to the blockchain
         * There is only one case where a block can be added to the blockchain, namely: the block is the next block on the blockchain.
         */
        bool checkBlock(Block *block);

        /**
         * Check that the transaction can be added to the next block.
         */
        bool checkTransaction(Transaction *transaction);
        //endregion



        //region Blockchain query related
        /**
         * query Blockchain Height
         */
        uint64_t queryBlockchainHeight();
        /**
         * Query the total number of transactions in the blockchain
         */
        uint64_t queryBlockchainTransactionHeight();
        /**
         * Query the total number of transaction outputs in the blockchain
         */
        uint64_t queryBlockchainTransactionOutputHeight();
        //endregion



        //region block query related
        /**
         * Query the last block on the blockchain
         */
        unique_ptr<Block> queryTailBlock();
        /**
         * query Block By Block Height
         */
        unique_ptr<Block> queryBlockByBlockHeight(uint64_t blockHeight);
        /**
         * query Block By Block Hash
         */
        unique_ptr<Block> queryBlockByBlockHash(string blockHash);
        //endregion



        //region transaction query related
        /**
         * query Transaction By Transaction Height. The transaction height starts at 1.
         */
        unique_ptr<Transaction> queryTransactionByTransactionHeight(uint64_t transactionHeight);
        /**
         * query Transaction By TransactionHash
         */
        unique_ptr<Transaction> queryTransactionByTransactionHash(string transactionHash);
        /**
         * query Source Transaction By Transaction Output Id
         * Source Transaction: The transaction from which the transaction output was generated
         */
        unique_ptr<Transaction>
        querySourceTransactionByTransactionOutputId(string transactionHash, uint64_t transactionOutputIndex);
        /**
         * query Destination Transaction By Transaction Output Id
         * Destination Transaction: The transaction that use the transaction output
         */
        unique_ptr<Transaction>
        queryDestinationTransactionByTransactionOutputId(string transactionHash, uint64_t transactionOutputIndex);
        //endregion



        //region Transaction output query related
        /**
         * query Transaction Output By Transaction Output Height
         */
        unique_ptr<TransactionOutput> queryTransactionOutputByTransactionOutputHeight(uint64_t transactionOutputHeight);
        /**
         * query Transaction Output By Transaction Output Id
         */
        unique_ptr<TransactionOutput>
        queryTransactionOutputByTransactionOutputId(string transactionHash, uint64_t transactionOutputIndex);
        /**
         * query Unspent Transaction Output By Transaction Output Id
         */
        unique_ptr<TransactionOutput>
        queryUnspentTransactionOutputByTransactionOutputId(string transactionHash, uint64_t transactionOutputIndex);
        /**
         * query Spent Transaction Output By Transaction Output Id
         */
        unique_ptr<TransactionOutput>
        querySpentTransactionOutputByTransactionOutputId(string transactionHash, uint64_t transactionOutputIndex);
        //endregion



        //region Address query related
        /**
         * query Transaction Output By Address
         */
        unique_ptr<TransactionOutput> queryTransactionOutputByAddress(string address);
        /**
         * query Unspent Transaction Output By Address
         */
        unique_ptr<TransactionOutput> queryUnspentTransactionOutputByAddress(string address);
        /**
         * query Spent Transaction Output By Address
         */
        unique_ptr<TransactionOutput> querySpentTransactionOutputByAddress(string address);
        //endregion

        //region
        /**
         * block dto to block model
         */
        unique_ptr<Block> blockDto2Block(BlockDto *blockDto);

        /**
         * transaction dto to transaction model
         */
        unique_ptr<Transaction> transactionDto2Transaction(TransactionDto *transactionDto);
        //endregion
    public:
        Incentive* getIncentive();
        Consensus* getConsensus();

    private:
        mutex mutex;
    private:
        KvWriteBatch createBlockWriteBatch(Block *block, BlockchainAction blockchainAction);

        void storeTransactionOutputIdToSourceTransactionHeight(KvWriteBatch *kvWriteBatch, Block *block,
                                                               BlockchainAction blockchainAction);

        void storeTransactionOutputIdToDestinationTransactionHeight(KvWriteBatch *kvWriteBatch, Block *block,
                                                                    BlockchainAction blockchainAction);

        void storeTransactionOutputIdToTransactionOutputHeight(KvWriteBatch *kvWriteBatch, Block *block,
                                                               BlockchainAction blockchainAction);

        void storeTransactionOutputHeightToTransactionOutput(KvWriteBatch *kvWriteBatch, Block *block,
                                                             BlockchainAction blockchainAction);

        void storeTransactionOutputIdToUnspentTransactionOutputHeight(KvWriteBatch *kvWriteBatch, Block *block,
                                                                      BlockchainAction blockchainAction);

        void storeTransactionOutputIdToSpentTransactionOutputHeight(KvWriteBatch *kvWriteBatch, Block *block,
                                                                    BlockchainAction blockchainAction);

        void storeTransactionHeightToTransaction(KvWriteBatch *kvWriteBatch, Block *block,
                                                 BlockchainAction blockchainAction);

        void storeTransactionHashToTransactionHeight(KvWriteBatch *kvWriteBatch, Block *block,
                                                     BlockchainAction blockchainAction);

        void storeBlockchainHeight(KvWriteBatch *kvWriteBatch, Block *block, BlockchainAction blockchainAction);

        void
        storeBlockHashToBlockHeight(KvWriteBatch *kvWriteBatch, Block *block, BlockchainAction blockchainAction);

        void storeBlockchainTransactionHeight(KvWriteBatch *kvWriteBatch, Block *block,
                                              BlockchainAction blockchainAction);

        void storeBlockchainTransactionOutputHeight(KvWriteBatch *kvWriteBatch, Block *block,
                                                    BlockchainAction blockchainAction);

        void storeBlockHeightToBlock(KvWriteBatch *kvWriteBatch, Block *block, BlockchainAction blockchainAction);

        void storeHash(KvWriteBatch *kvWriteBatch, Block *block, BlockchainAction blockchainAction);

        void storeAddress(KvWriteBatch *kvWriteBatch, Block *block, BlockchainAction blockchainAction);

        void storeAddressToUnspentTransactionOutputHeight(KvWriteBatch *kvWriteBatch, Block *block,
                                                          BlockchainAction blockchainAction);

        void storeAddressToTransactionOutputHeight(KvWriteBatch *kvWriteBatch, Block *block,
                                                   BlockchainAction blockchainAction);

        void storeAddressToSpentTransactionOutputHeight(KvWriteBatch *kvWriteBatch, Block *block,
                                                        BlockchainAction blockchainAction);

        string getBlockchainDatabasePath();

        //region block hash related
        bool checkBlockNewHash(Block *block);
        bool checkTransactionNewHash(Transaction *transaction);
        bool isHashUsed(string hash);
        //endregion

        //region address related
        bool checkBlockNewAddress(Block *block);
        bool checkTransactionNewAddress(Transaction *transaction);
        bool isAddressUsed(string address);
        //endregion


        //region Double spend attack
        /**
         * check Block Double Spend
         */
        bool checkBlockDoubleSpend(Block *block);

        /**
         * check Transaction Double Spend
         */
        bool checkTransactionDoubleSpend(Transaction *transaction);

        /**
         * Check if [spent transaction outputs] are all [unspent transaction outputs] ?
         */
        bool checkStxoIsUtxo(Transaction *transaction);
        //endregion


        void fillBlockProperty(Block *block);

        bool checkTransactionScript(Transaction *transaction);

        vector<Transaction> transactionDtos2Transactions(vector<TransactionDto> *transactionDtos) ;
        TransactionOutput transactionOutputDto2TransactionOutput(TransactionOutputDto *transactionOutputDto) ;
        TransactionType obtainTransactionDto(TransactionDto *transactionDto) ;
        OutputScript outputScriptDto2OutputScript(OutputScriptDto *outputScriptDto) ;
        InputScript inputScriptDto2InputScript(InputScriptDto *inputScriptDto) ;
    };

}


#endif //HELLOWORLDCOIN_CPP_BLOCKCHAINDATABASE_H
