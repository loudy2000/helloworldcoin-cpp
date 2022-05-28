//
// author x.king xdotking@gmail.com
//

#include "BlockchainNetCore.h"
namespace netcore {


        BlockchainNetCore::BlockchainNetCore(NetCoreConfiguration *netCoreConfiguration, BlockchainCore *blockchainCore,
                          NodeServer *nodeServer, NodeService *nodeService, SeedNodeInitializer *seedNodeInitializer,
                          NodeSearcher *nodeSearcher, NodeBroadcaster *nodeBroadcaster, NodeCleaner *nodeCleaner,
                          BlockchainHeightSearcher *blockchainHeightSearcher,
                          BlockchainHeightBroadcaster *blockchainHeightBroadcaster, BlockSearcher *blockSearcher,
                          BlockBroadcaster *blockBroadcaster,
                          UnconfirmedTransactionsSearcher *unconfirmedTransactionsSearcher
        ){
            this->netCoreConfiguration = netCoreConfiguration;

            this->blockchainCore = blockchainCore;
            this->nodeServer = nodeServer;
            this->nodeService = nodeService;
            this->nodeCleaner = nodeCleaner;

            this->seedNodeInitializer = seedNodeInitializer;
            this->nodeBroadcaster = nodeBroadcaster;
            this->nodeSearcher = nodeSearcher;

            this->blockchainHeightSearcher = blockchainHeightSearcher;
            this->blockchainHeightBroadcaster = blockchainHeightBroadcaster;

            this->blockBroadcaster = blockBroadcaster;
            this->blockSearcher = blockSearcher;

            this->unconfirmedTransactionsSearcher = unconfirmedTransactionsSearcher;
        }




        void startBlockchainCore(BlockchainCore *blockchainCore){
            blockchainCore->start();
        }
        void startNodeServer(NodeServer *nodeServer){
            nodeServer->start();
        }

        void startSeedNodeInitializer(SeedNodeInitializer *seedNodeInitializer){
            seedNodeInitializer->start();
        }
        void startNodeBroadcaster(NodeBroadcaster *nodeBroadcaster){
            nodeBroadcaster->start();
        }
        void startNodeSearcher(NodeSearcher *nodeSearcher){
            nodeSearcher->start();
        }
        void startNodeCleaner(NodeCleaner *nodeCleaner){
            nodeCleaner->start();
        }

        void startBlockchainHeightBroadcaster(BlockchainHeightBroadcaster *blockchainHeightBroadcaster){
            blockchainHeightBroadcaster->start();
        }
        void startBlockchainHeightSearcher(BlockchainHeightSearcher *blockchainHeightSearcher){
            blockchainHeightSearcher->start();
        }

        void startBlockBroadcaster(BlockBroadcaster *blockBroadcaster){
            blockBroadcaster->start();
        }
        void startBlockSearcher(BlockSearcher *blockSearcher){
            blockSearcher->start();
        }

        void startUnconfirmedTransactionsSearcher(UnconfirmedTransactionsSearcher *unconfirmedTransactionsSearcher){
            unconfirmedTransactionsSearcher->start();
        }

        void BlockchainNetCore::start(){
            thread t11(startBlockchainCore, this->blockchainCore);
            t11.detach();
            thread t12(startNodeServer, this->nodeServer);
            t12.detach();


            thread t21(startSeedNodeInitializer, this->seedNodeInitializer);
            t21.detach();
            thread t22(startNodeBroadcaster, this->nodeBroadcaster);
            t22.detach();
            thread t23(startNodeSearcher, this->nodeSearcher);
            t23.detach();
            thread t24(startNodeCleaner, this->nodeCleaner);
            t24.detach();

            thread t31(startBlockchainHeightBroadcaster, this->blockchainHeightBroadcaster);
            t31.detach();
            thread t32(startBlockchainHeightSearcher, this->blockchainHeightSearcher);
            t32.detach();

            thread t41(startBlockBroadcaster, this->blockBroadcaster);
            t41.detach();
            thread t42(startBlockSearcher, this->blockSearcher);
            t42.detach();

            thread t43(startUnconfirmedTransactionsSearcher, this->unconfirmedTransactionsSearcher);
            t43.detach();
        }





        NetCoreConfiguration *BlockchainNetCore::getNetCoreConfiguration(){
            return netCoreConfiguration;
        }

        BlockchainCore *BlockchainNetCore::getBlockchainCore(){
            return blockchainCore;
        }

        NodeServer *BlockchainNetCore::getNodeServer(){
            return nodeServer;
        }

        NodeService *BlockchainNetCore::getNodeService(){
            return nodeService;
        }

        SeedNodeInitializer *BlockchainNetCore::getSeedNodeInitializer(){
            return seedNodeInitializer;
        }

        NodeSearcher *BlockchainNetCore::getNodeSearcher(){
            return nodeSearcher;
        }

        NodeBroadcaster *BlockchainNetCore::getNodeBroadcaster(){
            return nodeBroadcaster;
        }

        NodeCleaner *BlockchainNetCore::getNodeCleaner(){
            return nodeCleaner;
        }

        BlockchainHeightSearcher *BlockchainNetCore::getBlockchainHeightSearcher(){
            return blockchainHeightSearcher;
        }

        BlockchainHeightBroadcaster *BlockchainNetCore::getBlockchainHeightBroadcaster(){
            return blockchainHeightBroadcaster;
        }

        BlockSearcher *BlockchainNetCore::getBlockSearcher(){
            return blockSearcher;
        }

        BlockBroadcaster *BlockchainNetCore::getBlockBroadcaster(){
            return blockBroadcaster;
        }

        UnconfirmedTransactionsSearcher *BlockchainNetCore::getUnconfirmedTransactionsSearcher(){
            return unconfirmedTransactionsSearcher;
        }

}