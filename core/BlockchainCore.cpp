//
// author x.king xdotking@gmail.com
//

#include "BlockchainCore.h"
#include "tool/Model2DtoTool.h"
#include <thread>

namespace core{
    BlockchainCore::BlockchainCore(CoreConfiguration *coreConfiguration, BlockchainDatabase *blockchainDatabase,
                                   UnconfirmedTransactionDatabase *unconfirmedTransactionDatabase, Wallet *wallet, Miner *miner) {
        this->coreConfiguration = coreConfiguration;
        this->blockchainDatabase = blockchainDatabase;
        this->unconfirmedTransactionDatabase = unconfirmedTransactionDatabase;
        this->wallet = wallet;
        this->miner = miner;
    }
    void startBlockchainCore(Miner *miner){
        miner->start();
    }
    void BlockchainCore::start(){
        thread t(startBlockchainCore, this->miner);
        t.detach();
    }
    bool BlockchainCore::addBlockDto(BlockDto *blockDto){
        return blockchainDatabase->addBlockDto(blockDto);
    }
    bool BlockchainCore::addBlock(Block *block){
        BlockDto blockDto = Model2DtoTool::block2BlockDto(block);
        return addBlockDto(&blockDto);
    }
    void BlockchainCore::deleteTailBlock(){
        blockchainDatabase->deleteTailBlock();
    }
    void BlockchainCore::deleteBlocks(uint64_t blockHeight) {
        blockchainDatabase->deleteBlocks(blockHeight);
    }
    uint64_t BlockchainCore::queryBlockchainHeight() {
        return blockchainDatabase->queryBlockchainHeight();
    }
    unique_ptr<Block> BlockchainCore::queryBlockByBlockHeight(uint64_t blockHeight){
        return blockchainDatabase->queryBlockByBlockHeight(blockHeight);
    }
    unique_ptr<Block> BlockchainCore::queryBlockByBlockHash(string blockHash) {
        return blockchainDatabase->queryBlockByBlockHash(blockHash);
    }
    unique_ptr<Block> BlockchainCore::queryTailBlock(){
        return blockchainDatabase->queryTailBlock();
    }

    unique_ptr<Transaction> BlockchainCore::queryTransactionByTransactionHash(string transactionHash) {
        return blockchainDatabase->queryTransactionByTransactionHash(transactionHash);
    }
    unique_ptr<Transaction> BlockchainCore::queryTransactionByTransactionHeight(uint64_t transactionHeight) {
        return blockchainDatabase->queryTransactionByTransactionHeight(transactionHeight);
    }

    unique_ptr<TransactionOutput> BlockchainCore::queryTransactionOutputByAddress(string address) {
        return blockchainDatabase->queryTransactionOutputByAddress(address);
    }
    unique_ptr<TransactionOutput> BlockchainCore::queryUnspentTransactionOutputByAddress(string address) {
        return blockchainDatabase->queryUnspentTransactionOutputByAddress(address);
    }
    unique_ptr<TransactionOutput> BlockchainCore::querySpentTransactionOutputByAddress(string address) {
        return blockchainDatabase->querySpentTransactionOutputByAddress(address);
    }




    AutoBuildTransactionResponse BlockchainCore::autoBuildTransaction(AutoBuildTransactionRequest *request) {
        return wallet->autoBuildTransaction(*request);
    }
    void BlockchainCore::postTransaction(TransactionDto *transactionDto) {
        unconfirmedTransactionDatabase->insertTransaction(*transactionDto);
    }
    vector<TransactionDto> BlockchainCore::queryUnconfirmedTransactions(uint64_t from, uint64_t size) {
        return unconfirmedTransactionDatabase->selectTransactions(from,size);
    }
    unique_ptr<TransactionDto> BlockchainCore::queryUnconfirmedTransactionByTransactionHash(string transactionHash) {
        return unconfirmedTransactionDatabase->selectTransactionByTransactionHash(transactionHash);
    }



    //region
    unique_ptr<Block> BlockchainCore::blockDto2Block(BlockDto *blockDto) {
        return blockchainDatabase->blockDto2Block(blockDto);
    }
    unique_ptr<Transaction> BlockchainCore::transactionDto2Transaction(TransactionDto *transactionDto) {
        return blockchainDatabase->transactionDto2Transaction(transactionDto);
    }
    //endregion


    //region get set
    BlockchainDatabase * BlockchainCore::getBlockchainDatabase() {
        return this->blockchainDatabase;
    }

    UnconfirmedTransactionDatabase * BlockchainCore::getUnconfirmedTransactionDatabase() {
        return this->unconfirmedTransactionDatabase;
    }

    Miner * BlockchainCore::getMiner() {
        return this->miner;
    }

    Wallet * BlockchainCore::getWallet() {
        return this->wallet;
    }

    CoreConfiguration * BlockchainCore::getCoreConfiguration() {
        return this->coreConfiguration;
    }
    //endregion

}
