//
// author x.king xdotking@gmail.com
//

#include "BlockSearcher.h"
#include "../util/LogUtil.h"
#include "../util/ThreadUtil.h"
#include "../core/tool/BlockTool.h"
#include "../core/tool/Model2DtoTool.h"
#include "../core/tool/BlockDtoTool.h"
#include "../netcoreclient/NodeClient.h"
#include "../util/StringUtil.h"
#include "../setting/GenesisBlockSetting.h"

using namespace netcoreclient;


namespace netcore{

    BlockSearcher::BlockSearcher(NetCoreConfiguration *netCoreConfiguration, BlockchainCore *blockchainCore
            , BlockchainCore *slaveBlockchainCore, NodeService *nodeService){
        this->netCoreConfiguration = netCoreConfiguration;
        this->nodeService = nodeService;
        this->blockchainCore = blockchainCore;
        this->slaveBlockchainCore = slaveBlockchainCore;
    }


    void BlockSearcher::start() {
        try {
            while (true){
                searchNodesBlocks();
                ThreadUtil::millisecondSleep(netCoreConfiguration->getBlockSearchTimeInterval());
            }
        } catch (exception e) {
            LogUtil::error("'search for blocks in the blockchain network' error.",e);
        }
    }

    /**
     * Search for new blocks and sync these blocks to the local blockchain system
     */
    void BlockSearcher::searchNodesBlocks() {
        vector<Node> nodes = nodeService->queryAllNodes();
        if(nodes.empty()){
            return;
        }

        for(Node node:nodes){
            searchNodeBlocks(blockchainCore,slaveBlockchainCore,node);
        }
    }

    /**
     * search blocks
     */
    void BlockSearcher::searchNodeBlocks(BlockchainCore *masterBlockchainCore, BlockchainCore *slaveBlockchainCore, Node node) {
        if(!netCoreConfiguration->isAutoSearchBlock()){
            return;
        }
        uint64_t masterBlockchainHeight = masterBlockchainCore->queryBlockchainHeight();
        if(masterBlockchainHeight >= node.blockchainHeight){
            return;
        }
        boolean fork = isForkNode(masterBlockchainCore,node);
        if(fork){
            boolean isHardFork = isHardForkNode(masterBlockchainCore,node);
            if(!isHardFork){
                uint64_t forkBlockHeight = getForkBlockHeight(masterBlockchainCore,node);
                duplicateBlockchainCore(masterBlockchainCore, slaveBlockchainCore);
                slaveBlockchainCore->deleteBlocks(forkBlockHeight);
                synchronizeBlocks(slaveBlockchainCore,node,forkBlockHeight);
                promoteBlockchainCore(slaveBlockchainCore, masterBlockchainCore);
            }
        } else {
            uint64_t nextBlockHeight = masterBlockchainCore->queryBlockchainHeight()+1;
            synchronizeBlocks(masterBlockchainCore,node,nextBlockHeight);
        }
    }

    /**
     * duplicate BlockchainCore
     */
    void BlockSearcher::duplicateBlockchainCore(BlockchainCore *fromBlockchainCore,BlockchainCore *toBlockchainCore) {
        //delete blocks
        while (true){
            unique_ptr<Block> toBlockchainTailBlock = toBlockchainCore->queryTailBlock() ;
            if(!toBlockchainTailBlock.get()){
                break;
            }
            unique_ptr<Block> fromBlockchainBlock = fromBlockchainCore->queryBlockByBlockHeight(toBlockchainTailBlock->height);
            if(BlockTool::isBlockEquals(fromBlockchainBlock.get(),toBlockchainTailBlock.get())){
                break;
            }
            toBlockchainCore->deleteTailBlock();
        }
        //add blocks
        while (true){
            uint64_t toBlockchainHeight = toBlockchainCore->queryBlockchainHeight();
            unique_ptr<Block> nextBlock = fromBlockchainCore->queryBlockByBlockHeight(toBlockchainHeight+1) ;
            if(!nextBlock.get()){
                break;
            }
            toBlockchainCore->addBlock(nextBlock.get());
        }
    }
    /**
     * promote BlockchainCore
     */
    void BlockSearcher::promoteBlockchainCore(BlockchainCore *fromBlockchainCore, BlockchainCore *toBlockchainCore) {
        if(toBlockchainCore->queryBlockchainHeight() >= fromBlockchainCore->queryBlockchainHeight()){
            return;
        }
        //hard fork
        if(isHardFork(toBlockchainCore,fromBlockchainCore)){
            return;
        }
        duplicateBlockchainCore(fromBlockchainCore,toBlockchainCore);
    }

    uint64_t BlockSearcher::getForkBlockHeight(BlockchainCore *blockchainCore, Node node) {
        uint64_t masterBlockchainHeight = blockchainCore->queryBlockchainHeight();
        uint64_t forkBlockHeight = masterBlockchainHeight;
        while (true) {
            if (forkBlockHeight <= GenesisBlockSetting::HEIGHT) {
                break;
            }
            GetBlockRequest getBlockRequest{};
            getBlockRequest.blockHeight=forkBlockHeight;
            NodeClient nodeClient(node.ip);
            unique_ptr<GetBlockResponse> getBlockResponse = nodeClient.getBlock(getBlockRequest);
            if(!getBlockResponse.get()){
                break;
            }
            BlockDto &remoteBlock = getBlockResponse->block;
/* TODO           if(NullUtil::isNullBlockDto(remoteBlock)){
                break;
            }*/
            unique_ptr<Block> localBlock = blockchainCore->queryBlockByBlockHeight(forkBlockHeight);
            BlockDto blockDtoTemp = Model2DtoTool::block2BlockDto(localBlock.get());
            if(BlockDtoTool::isBlockEquals(&blockDtoTemp,&remoteBlock)){
                break;
            }
            forkBlockHeight--;
        }
        forkBlockHeight++;
        return forkBlockHeight;
    }

    void BlockSearcher::synchronizeBlocks(BlockchainCore *blockchainCore, Node node, uint64_t startBlockHeight) {
        while (true){
            GetBlockRequest getBlockRequest;
            getBlockRequest.blockHeight=startBlockHeight;
            NodeClient nodeClient(node.ip);
            unique_ptr<GetBlockResponse> getBlockResponse = nodeClient.getBlock(getBlockRequest);
            if(!getBlockResponse.get()){
                break;
            }
            BlockDto remoteBlock = getBlockResponse->block;
/*TODO            if(NullUtil::isNullBlockDto(remoteBlock)){
                break;
            }*/
            boolean isAddBlockSuccess = blockchainCore->addBlockDto(&remoteBlock);
            if(!isAddBlockSuccess){
                break;
            }
            startBlockHeight++;
        }
    }

    bool BlockSearcher::isForkNode(BlockchainCore *blockchainCore, Node node) {
        unique_ptr<Block> block = blockchainCore->queryTailBlock();
        if(!block.get()){
            return false;
        }
        GetBlockRequest getBlockRequest;
        getBlockRequest.blockHeight=block->height;
        NodeClient nodeClient(node.ip);
        unique_ptr<GetBlockResponse> getBlockResponse = nodeClient.getBlock(getBlockRequest);
        //no block with this height exist, so no fork.
        if(!getBlockResponse.get()){
            return false;
        }
        BlockDto &blockDto = getBlockResponse->block;
/*TODO        if(NullUtil::isNullBlockDto(blockDto)){
            return false;
        }*/
        string blockHash = BlockDtoTool::calculateBlockHash(&blockDto);
        return !StringUtil::equals(block->hash, blockHash);
    }

    bool BlockSearcher::isHardFork(BlockchainCore *blockchainCore1, BlockchainCore *blockchainCore2) {
        BlockchainCore *longer;
        BlockchainCore *shorter;
        if(blockchainCore1->queryBlockchainHeight()>=blockchainCore2->queryBlockchainHeight()){
            longer = blockchainCore1;
            shorter = blockchainCore2;
        }else {
            longer = blockchainCore2;
            shorter = blockchainCore1;
        }

        uint64_t shorterBlockchainHeight = shorter->queryBlockchainHeight();
        if(shorterBlockchainHeight < netCoreConfiguration->getHardForkBlockCount()){
            return false;
        }

        uint64_t criticalPointBlocHeight = shorterBlockchainHeight-netCoreConfiguration->getHardForkBlockCount()+1;
        unique_ptr<Block> longerBlock = longer->queryBlockByBlockHeight(criticalPointBlocHeight);
        unique_ptr<Block> shorterBlock = shorter->queryBlockByBlockHeight(criticalPointBlocHeight);
        return !BlockTool::isBlockEquals(longerBlock.get(), shorterBlock.get());
    }

    bool BlockSearcher::isHardForkNode(BlockchainCore *blockchainCore, Node node) {
        uint64_t blockchainHeight = blockchainCore->queryBlockchainHeight();
        if (blockchainHeight < netCoreConfiguration->getHardForkBlockCount()) {
            return false;
        }
        uint64_t criticalPointBlocHeight = blockchainHeight-netCoreConfiguration->getHardForkBlockCount()+1;
        if(criticalPointBlocHeight <= GenesisBlockSetting::HEIGHT){
            return false;
        }
        GetBlockRequest getBlockRequest{};
        getBlockRequest.blockHeight=criticalPointBlocHeight;
        NodeClient nodeClient(node.ip);
        unique_ptr<GetBlockResponse> getBlockResponse = nodeClient.getBlock(getBlockRequest);
        if(!getBlockResponse.get()){
            return false;
        }
        BlockDto &remoteBlock = getBlockResponse->block;
/*
 * TODO        if(NullUtil::isNullBlockDto(remoteBlock)){
            return false;
        }*/
        unique_ptr<Block> localBlock = blockchainCore->queryBlockByBlockHeight(criticalPointBlocHeight);
        BlockDto blockDtoTemp = Model2DtoTool::block2BlockDto(localBlock.get());
        return !BlockDtoTool::isBlockEquals(&blockDtoTemp,&remoteBlock);
    }
}
