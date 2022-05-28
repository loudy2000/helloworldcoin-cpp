//
// author x.king xdotking@gmail.com
//

#include "BlockchainBrowserApplicationController.h"
#include "CommonController.h"
#include "../../setting/GenesisBlockSetting.h"
#include "../vo/nodevo.h"
#include "../../core/tool/BlockTool.h"
#include "../../core/tool/SizeTool.h"
#include "../../core/tool/TransactionDtoTool.h"
#include "../../util/LogUtil.h"
#include "../../util/TimeUtil.h"



namespace controller{


    BlockchainBrowserApplicationController::BlockchainBrowserApplicationController(BlockchainNetCore *blockchainNetCore,BlockchainBrowserApplicationService *blockchainBrowserApplicationService){
        this->blockchainNetCore = blockchainNetCore;
        this->blockchainBrowserApplicationService = blockchainBrowserApplicationService;
    }
    void BlockchainBrowserApplicationController::queryTransactionByTransactionHash(const httplib::Request &req, httplib::Response &res){
        try {
            QueryTransactionByTransactionHashRequest request = JsonUtil::toObject(req.body, QueryTransactionByTransactionHashRequest{});

            unique_ptr<TransactionVo> transactionVo = blockchainBrowserApplicationService->queryTransactionByTransactionHash(request.transactionHash);
            QueryTransactionByTransactionHashResponse response;
            response.transaction=*transactionVo;
            success(res,response);
        } catch (exception e){
            string message = "'query transaction by transaction hash' error.";
            LogUtil::error(message,e);
            serviceUnavailable(res);
        }
    }
    void BlockchainBrowserApplicationController::queryTransactionsByBlockHashTransactionHeight(const httplib::Request &req, httplib::Response &res){
        try {
            QueryTransactionsByBlockHashTransactionHeightRequest request = JsonUtil::toObject(req.body, QueryTransactionsByBlockHashTransactionHeightRequest{});

            PageCondition pageCondition = request.pageCondition;
            vector<TransactionVo> transactionVos = blockchainBrowserApplicationService->queryTransactionListByBlockHashTransactionHeight(request.blockHash,pageCondition.from,pageCondition.size);
            QueryTransactionsByBlockHashTransactionHeightResponse response;
            response.transactions=transactionVos;
            success(res,response);
        } catch (exception e){
            string message = "'query transactions by (block hash and transaction height)' error.";
            LogUtil::error(message,e);
            serviceUnavailable(res);
        }
    }
    void BlockchainBrowserApplicationController::queryTransactionOutputByAddress(const httplib::Request &req, httplib::Response &res){
        try {
            QueryTransactionOutputByAddressRequest request = JsonUtil::toObject(req.body, QueryTransactionOutputByAddressRequest{});

            unique_ptr<TransactionOutputVo3> transactionOutputVo3 = blockchainBrowserApplicationService->queryTransactionOutputByAddress(request.address);
            QueryTransactionOutputByAddressResponse response;
            response.transactionOutput=*transactionOutputVo3;
            success(res,response);
        } catch (exception e){
            string message = "'query transaction output by address' error.";
            LogUtil::error(message,e);
            serviceUnavailable(res);
        }
    }
    void BlockchainBrowserApplicationController::queryTransactionOutputByTransactionOutputId(const httplib::Request &req, httplib::Response &res){
        try {
            QueryTransactionOutputByTransactionOutputIdRequest request = JsonUtil::toObject(req.body, QueryTransactionOutputByTransactionOutputIdRequest{});

            unique_ptr<TransactionOutputVo3> transactionOutputVo3 = blockchainBrowserApplicationService->queryTransactionOutputByTransactionOutputId(request.transactionHash,request.transactionOutputIndex);
            QueryTransactionOutputByTransactionOutputIdResponse response;
            response.transactionOutput=*transactionOutputVo3;
            success(res,response);
        } catch (exception e){
            string message = "'query transaction output by transaction output id' error.";
            LogUtil::error(message,e);
            serviceUnavailable(res);
        }
    }
    void BlockchainBrowserApplicationController::queryBlockchainHeight(const httplib::Request &req, httplib::Response &res){
        try {
            uint64_t blockchainHeight = blockchainNetCore->getBlockchainCore()->queryBlockchainHeight();
            QueryBlockchainHeightResponse response;
            response.blockchainHeight=blockchainHeight;
            success(res,response);
        } catch (exception e){
            string message = "'query blockchain height' error.";
            LogUtil::error(message,e);
            serviceUnavailable(res);
        }
    }
    void BlockchainBrowserApplicationController::queryUnconfirmedTransactionByTransactionHash(const httplib::Request &req, httplib::Response &res){
        try {
            QueryUnconfirmedTransactionByTransactionHashRequest request = JsonUtil::toObject(req.body, QueryUnconfirmedTransactionByTransactionHashRequest{});

            unique_ptr<UnconfirmedTransactionVo> unconfirmedTransactionVo = blockchainBrowserApplicationService->queryUnconfirmedTransactionByTransactionHash(request.transactionHash);
            QueryUnconfirmedTransactionByTransactionHashResponse response;
            response.transaction=*unconfirmedTransactionVo;
            success(res,response);
        } catch (exception e){
            string message = "'query unconfirmed transaction by transaction hash' error.";
            LogUtil::error(message,e);
            serviceUnavailable(res);
        }
    }
    void BlockchainBrowserApplicationController::queryUnconfirmedTransactions(const httplib::Request &req, httplib::Response &res){
        try {
            QueryUnconfirmedTransactionsRequest request = JsonUtil::toObject(req.body, QueryUnconfirmedTransactionsRequest{});

            PageCondition pageCondition = request.pageCondition;
            vector<TransactionDto> transactionDtos = blockchainNetCore->getBlockchainCore()->queryUnconfirmedTransactions(pageCondition.from,pageCondition.size);
            if(transactionDtos.empty()){
                QueryUnconfirmedTransactionsResponse response;
                success(res,response);
                return;
            }

            vector<UnconfirmedTransactionVo> unconfirmedTransactionVos;
            for(TransactionDto &transactionDto : transactionDtos){
                unique_ptr<UnconfirmedTransactionVo> unconfirmedTransactionVo = blockchainBrowserApplicationService->queryUnconfirmedTransactionByTransactionHash(TransactionDtoTool::calculateTransactionHash(transactionDto));
                if(unconfirmedTransactionVo.get()){
                    unconfirmedTransactionVos.push_back(*unconfirmedTransactionVo);
                }
            }
            QueryUnconfirmedTransactionsResponse response;
            response.unconfirmedTransactions=unconfirmedTransactionVos;
            success(res,response);
        } catch (exception e){
            string message = "'query unconfirmed transactions' error.";
            LogUtil::error(message,e);
            serviceUnavailable(res);
        }
    }
    void BlockchainBrowserApplicationController::queryBlockByBlockHeight(const httplib::Request &req, httplib::Response &res){
        try {
            QueryBlockByBlockHeightRequest request = JsonUtil::toObject(req.body, QueryBlockByBlockHeightRequest{});

            unique_ptr<BlockVo> blockVo = blockchainBrowserApplicationService->queryBlockViewByBlockHeight(request.blockHeight);
            QueryBlockByBlockHeightResponse response;
            response.block=*blockVo;
            success(res,response);
        } catch (exception e){
            string message = "'query block by block height' error.";
            LogUtil::error(message,e);
            serviceUnavailable(res);
        }
    }
    void BlockchainBrowserApplicationController::queryBlockByBlockHash(const httplib::Request &req, httplib::Response &res){
        try {
            QueryBlockByBlockHashRequest request = JsonUtil::toObject(req.body, QueryBlockByBlockHashRequest{});

            unique_ptr<Block> block = blockchainNetCore->getBlockchainCore()->queryBlockByBlockHash(request.blockHash);
            if(!block.get()){
                QueryBlockByBlockHashResponse response;
                success(res,response);
                return;
            }
            unique_ptr<BlockVo> blockVo = blockchainBrowserApplicationService->queryBlockViewByBlockHeight(block->height);
            QueryBlockByBlockHashResponse response;
            response.block=*blockVo;
            success(res,response);
        } catch (exception e){
            string message = "'query block by block hash' error.";
            LogUtil::error(message,e);
            serviceUnavailable(res);
        }
    }
    void BlockchainBrowserApplicationController::queryLatest10Blocks(const httplib::Request &req, httplib::Response &res){
        try {
            vector<Block> blocks;
            uint64_t blockHeight = blockchainNetCore->getBlockchainCore()->queryBlockchainHeight();
            while (true){
                if(blockHeight <= GenesisBlockSetting::HEIGHT){
                    break;
                }
                unique_ptr<Block> block = blockchainNetCore->getBlockchainCore()->queryBlockByBlockHeight(blockHeight);
                blocks.push_back(*block.get());
                if(blocks.size() >= 10){
                    break;
                }
                blockHeight--;
            }

            vector<BlockVo2> blockVos;
            for(Block &block : blocks){
                BlockVo2 blockVo;
                blockVo.height=block.height;
                blockVo.blockSize=SizeTool::calculateBlockSize(&block);
                blockVo.transactionCount=BlockTool::getTransactionCount(&block);
                blockVo.minerIncentiveValue=BlockTool::getWritedIncentiveValue(&block);
                blockVo.time=TimeUtil::formatMillisecondTimestamp(block.timestamp);
                blockVo.hash=block.hash;
                blockVos.push_back(blockVo);
            }

            QueryLatest10BlocksResponse response;
            response.blocks=blockVos;
            success(res,response);
        } catch (exception e){
            string message = "'query latest 10 blocks' error.";
            LogUtil::error(message,e);
            serviceUnavailable(res);
        }
    }

}

