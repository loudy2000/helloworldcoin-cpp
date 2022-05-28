//
// author x.king xdotking@gmail.com
//
#include "../thirdpart/httplib/httplib.h"
#include "../core/tool/ResourceTool.h"
#include "../util/SystemUtil.h"
#include "../util/FileUtil.h"
#include "../netcore/BlockchainNetCore.h"
#include "../netcore/BlockchainNetCoreFactory.h"
#include "controller/NodeConsoleApplicationController.h"
#include "controller/WalletApplicationController.h"
#include "controller/BlockchainBrowserApplicationController.h"
#include "vo/BlockchainBrowserApplicationApi/BlockchainBrowserApplicationApi.h"
#include "vo/WalletApplicationApi/WalletApplicationApi.h"
#include "vo/NodeConsoleApplicationApi/NodeConsoleApplicationApi.h"

using namespace netcore;
using namespace controller;

int main()
{
    BlockchainNetCore *blockchainNetCore = BlockchainNetCoreFactory::createBlockchainNetCore(ResourceTool::getDataRootPath());
    blockchainNetCore->start();
    
    httplib::Server server;
    bool mountSuccess = server.set_mount_point("/", FileUtil::newPath(SystemUtil::systemRootDirectory(),"application/resources/static"));
    if(!mountSuccess){
        SystemUtil::errorExit("mount faild.", {});
    }


    NodeConsoleApplicationController *nodeConsoleApplicationController = new NodeConsoleApplicationController(blockchainNetCore);


    server.Post(NodeConsoleApplicationApi::IS_MINER_ACTIVE, [nodeConsoleApplicationController](const httplib::Request &req, httplib::Response &res) {
        nodeConsoleApplicationController->IsMinerActive(req,res);
    });
    server.Post(NodeConsoleApplicationApi::ACTIVE_MINER, [nodeConsoleApplicationController](const httplib::Request &req, httplib::Response &res) {
        nodeConsoleApplicationController->ActiveMiner(req,res);
    });
    server.Post(NodeConsoleApplicationApi::DEACTIVE_MINER, [nodeConsoleApplicationController](const httplib::Request &req, httplib::Response &res) {
        nodeConsoleApplicationController->DeactiveMiner(req,res);
    });
    server.Post(NodeConsoleApplicationApi::IS_AUTO_SEARCH_BLOCK, [nodeConsoleApplicationController](const httplib::Request &req, httplib::Response &res) {
        nodeConsoleApplicationController->IsAutoSearchBlock(req,res);
    });
    server.Post(NodeConsoleApplicationApi::ACTIVE_AUTO_SEARCH_BLOCK, [nodeConsoleApplicationController](const httplib::Request &req, httplib::Response &res) {
        nodeConsoleApplicationController->ActiveAutoSearchBlock(req,res);
    });
    server.Post(NodeConsoleApplicationApi::DEACTIVE_AUTO_SEARCH_BLOCK, [nodeConsoleApplicationController](const httplib::Request &req, httplib::Response &res) {
        nodeConsoleApplicationController->DeactiveAutoSearchBlock(req,res);
    });
    server.Post(NodeConsoleApplicationApi::IS_AUTO_SEARCH_NODE, [nodeConsoleApplicationController](const httplib::Request &req, httplib::Response &res) {
        nodeConsoleApplicationController->IsAutoSearchNode(req,res);
    });
    server.Post(NodeConsoleApplicationApi::ACTIVE_AUTO_SEARCH_NODE, [nodeConsoleApplicationController](const httplib::Request &req, httplib::Response &res) {
        nodeConsoleApplicationController->ActiveAutoSearchNode(req,res);
    });
    server.Post(NodeConsoleApplicationApi::DEACTIVE_AUTO_SEARCH_NODE, [nodeConsoleApplicationController](const httplib::Request &req, httplib::Response &res) {
        nodeConsoleApplicationController->DeactiveAutoSearchNode(req,res);
    });

    server.Post(NodeConsoleApplicationApi::SET_MINER_MINE_MAX_BLOCK_HEIGHT, [nodeConsoleApplicationController](const httplib::Request &req, httplib::Response &res) {
        nodeConsoleApplicationController->SetMinerMineMaxBlockHeight(req,res);
    });
    server.Post(NodeConsoleApplicationApi::GET_MINER_MINE_MAX_BLOCK_HEIGHT, [nodeConsoleApplicationController](const httplib::Request &req, httplib::Response &res) {
        nodeConsoleApplicationController->GetMinerMineMaxBlockHeight(req,res);
    });
    server.Post(NodeConsoleApplicationApi::ADD_NODE, [nodeConsoleApplicationController](const httplib::Request &req, httplib::Response &res) {
        nodeConsoleApplicationController->AddNode(req,res);
    });
    server.Post(NodeConsoleApplicationApi::UPDATE_NODE, [nodeConsoleApplicationController](const httplib::Request &req, httplib::Response &res) {
        nodeConsoleApplicationController->UpdateNode(req,res);
    });
    server.Post(NodeConsoleApplicationApi::DELETE_NODE, [nodeConsoleApplicationController](const httplib::Request &req, httplib::Response &res) {
        nodeConsoleApplicationController->DeleteNode(req,res);
    });
    server.Post(NodeConsoleApplicationApi::QUERY_ALL_NODES, [nodeConsoleApplicationController](const httplib::Request &req, httplib::Response &res) {
        nodeConsoleApplicationController->queryAllNodes(req,res);
    });
    server.Post(NodeConsoleApplicationApi::DELETE_BLOCKS, [nodeConsoleApplicationController](const httplib::Request &req, httplib::Response &res) {
        nodeConsoleApplicationController->DeleteBlocks(req,res);
    });




    WalletApplicationService *walletApplicationService = new WalletApplicationService(blockchainNetCore);
    WalletApplicationController *walletApplicationController = new WalletApplicationController(blockchainNetCore,walletApplicationService);

    server.Post(WalletApplicationApi::CREATE_ACCOUNT, [walletApplicationController](const httplib::Request &req, httplib::Response &res) {
        walletApplicationController->createAccount(req,res);
    });
    server.Post(WalletApplicationApi::CREATE_AND_SAVE_ACCOUNT, [walletApplicationController](const httplib::Request &req, httplib::Response &res) {
        walletApplicationController->createAndSaveAccount(req,res);
    });
    server.Post(WalletApplicationApi::SAVE_ACCOUNT, [walletApplicationController](const httplib::Request &req, httplib::Response &res) {
        walletApplicationController->saveAccount(req,res);
    });
    server.Post(WalletApplicationApi::DELETE_ACCOUNT, [walletApplicationController](const httplib::Request &req, httplib::Response &res) {
        walletApplicationController->deleteAccount(req,res);
    });
    server.Post(WalletApplicationApi::QUERY_ALL_ACCOUNTS, [walletApplicationController](const httplib::Request &req, httplib::Response &res) {
        walletApplicationController->queryAllAccounts(req,res);
    });
    server.Post(WalletApplicationApi::AUTOMATIC_BUILD_TRANSACTION, [walletApplicationController](const httplib::Request &req, httplib::Response &res) {
        walletApplicationController->automaticBuildTransaction(req,res);
    });
    server.Post(WalletApplicationApi::SUBMIT_TRANSACTION_TO_BLOCKCHIAIN_NEWWORK, [walletApplicationController](const httplib::Request &req, httplib::Response &res) {
        walletApplicationController->submitTransactionToBlockchainNetwork(req,res);
    });





    BlockchainBrowserApplicationService *blockchainBrowserApplicationService = new BlockchainBrowserApplicationService(blockchainNetCore);
    BlockchainBrowserApplicationController *blockchainBrowserApplicationController = new BlockchainBrowserApplicationController(blockchainNetCore,blockchainBrowserApplicationService);
    server.Post(BlockchainBrowserApplicationApi::QUERY_BLOCKCHAIN_HEIGHT, [blockchainBrowserApplicationController](const httplib::Request &req, httplib::Response &res) {
        blockchainBrowserApplicationController->queryBlockchainHeight(req,res);
    });
    server.Post(BlockchainBrowserApplicationApi::QUERY_TRANSACTION_BY_TRANSACTION_HASH, [blockchainBrowserApplicationController](const httplib::Request &req, httplib::Response &res) {
        blockchainBrowserApplicationController->queryTransactionByTransactionHash(req,res);
    });
    server.Post(BlockchainBrowserApplicationApi::QUERY_TRANSACTIONS_BY_BLOCK_HASH_TRANSACTION_HEIGHT, [blockchainBrowserApplicationController](const httplib::Request &req, httplib::Response &res) {
        blockchainBrowserApplicationController->queryTransactionsByBlockHashTransactionHeight(req,res);
    });
    server.Post(BlockchainBrowserApplicationApi::QUERY_TRANSACTION_OUTPUT_BY_ADDRESS, [blockchainBrowserApplicationController](const httplib::Request &req, httplib::Response &res) {
        blockchainBrowserApplicationController->queryTransactionOutputByAddress(req,res);
    });
    server.Post(BlockchainBrowserApplicationApi::QUERY_TRANSACTION_OUTPUT_BY_TRANSACTION_OUTPUT_ID, [blockchainBrowserApplicationController](const httplib::Request &req, httplib::Response &res) {
        blockchainBrowserApplicationController->queryTransactionOutputByTransactionOutputId(req,res);
    });
    server.Post(BlockchainBrowserApplicationApi::QUERY_UNCONFIRMED_TRANSACTIONS, [blockchainBrowserApplicationController](const httplib::Request &req, httplib::Response &res) {
        blockchainBrowserApplicationController->queryUnconfirmedTransactions(req,res);
    });
    server.Post(BlockchainBrowserApplicationApi::QUERY_UNCONFIRMED_TRANSACTION_BY_TRANSACTION_HASH, [blockchainBrowserApplicationController](const httplib::Request &req, httplib::Response &res) {
        blockchainBrowserApplicationController->queryUnconfirmedTransactionByTransactionHash(req,res);
    });
    server.Post(BlockchainBrowserApplicationApi::QUERY_BLOCK_BY_BLOCK_HEIGHT, [blockchainBrowserApplicationController](const httplib::Request &req, httplib::Response &res) {
        blockchainBrowserApplicationController->queryBlockByBlockHeight(req,res);
    });
    server.Post(BlockchainBrowserApplicationApi::QUERY_BLOCK_BY_BLOCK_HASH, [blockchainBrowserApplicationController](const httplib::Request &req, httplib::Response &res) {
        blockchainBrowserApplicationController->queryBlockByBlockHash(req,res);
    });
    server.Post(BlockchainBrowserApplicationApi::QUERY_LATEST_10_BLOCKS, [blockchainBrowserApplicationController](const httplib::Request &req, httplib::Response &res) {
        blockchainBrowserApplicationController->queryLatest10Blocks(req,res);
    });


    SystemUtil::callDefaultBrowser("http://localhost/");


    server.listen("0.0.0.0", 80);
}
