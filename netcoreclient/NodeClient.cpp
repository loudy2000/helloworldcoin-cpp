//
// author x.king xdotking@gmail.com
//

#include "NodeClient.h"
#include "../util/JsonUtil.h"
#include "../util/NetUtil.h"
#include "../setting/NetworkSetting.h"
#include "../util/StringUtil.h"
#include "../util/LogUtil.h"


namespace netcoreclient{



    NodeClient::NodeClient(string ip) {
        this->ip = ip;
    }


    unique_ptr<PostTransactionResponse> NodeClient::postTransaction(PostTransactionRequest request) {
        try {
            string requestUrl = getUrl(API::POST_TRANSACTION);
            string requestBody = JsonUtil::toString(request);
            string responseHtml = NetUtil::get(requestUrl,requestBody);
            PostTransactionResponse postTransactionResponse = JsonUtil::toObject(responseHtml,PostTransactionResponse{});
            return unique_ptr<PostTransactionResponse>(new PostTransactionResponse(postTransactionResponse));
        }catch (exception e){
            LogUtil::error("client error.",e);
            return unique_ptr<PostTransactionResponse>(nullptr);
        }
    }


    unique_ptr<PingResponse> NodeClient::pingNode(PingRequest request) {
        try {
            string requestUrl = getUrl(API::PING);
            string requestBody = JsonUtil::toString(request);
            string responseHtml = NetUtil::get(requestUrl,requestBody);
            PingResponse pingResponse = JsonUtil::toObject(responseHtml,PingResponse{});
            return unique_ptr<PingResponse>(new PingResponse(pingResponse));
        }catch (exception e){
            LogUtil::error("client error.",e);
            return unique_ptr<PingResponse>(nullptr);
        }
    }


    unique_ptr<GetBlockResponse> NodeClient::getBlock(GetBlockRequest request) {
        try {
            string requestUrl = getUrl(API::GET_BLOCK);
            string requestBody = JsonUtil::toString(request);
            string responseHtml = NetUtil::get(requestUrl,requestBody);
            GetBlockResponse getBlockResponse = JsonUtil::toObject(responseHtml,GetBlockResponse{});
            return unique_ptr<GetBlockResponse>(new GetBlockResponse(getBlockResponse));
        }catch (exception e){
            LogUtil::error("client error.",e);
            return unique_ptr<GetBlockResponse>(nullptr);
        }
    }


    unique_ptr<GetNodesResponse> NodeClient::getNodes(GetNodesRequest request) {
        try {
            string requestUrl = getUrl(API::GET_NODES);
            string requestBody = JsonUtil::toString(request);
            string responseHtml = NetUtil::get(requestUrl,requestBody);
            GetNodesResponse getNodesResponse = JsonUtil::toObject(responseHtml,GetNodesResponse{});
            return unique_ptr<GetNodesResponse>(new GetNodesResponse(getNodesResponse));
        }catch (exception e){
            LogUtil::error("client error.",e);
            return unique_ptr<GetNodesResponse>(nullptr);
        }
    }


    unique_ptr<PostBlockResponse> NodeClient::postBlock(PostBlockRequest request) {
        try {
            string requestUrl = getUrl(API::POST_BLOCK);
            string requestBody = JsonUtil::toString(request);
            string responseHtml = NetUtil::get(requestUrl,requestBody);
            PostBlockResponse postBlockResponse = JsonUtil::toObject(responseHtml,PostBlockResponse{});
            return unique_ptr<PostBlockResponse>(new PostBlockResponse(postBlockResponse));
        }catch (exception e){
            LogUtil::error("client error.",e);
            return unique_ptr<PostBlockResponse>(nullptr);
        }
    }


    unique_ptr<PostBlockchainHeightResponse> NodeClient::postBlockchainHeight(PostBlockchainHeightRequest request) {
        try {
            string requestUrl = getUrl(API::POST_BLOCKCHAIN_HEIGHT);
            string requestBody = JsonUtil::toString(request);
            string responseHtml = NetUtil::get(requestUrl,requestBody);
            PostBlockchainHeightResponse postBlockchainHeightResponse = JsonUtil::toObject(responseHtml,PostBlockchainHeightResponse{});
            return unique_ptr<PostBlockchainHeightResponse>(new PostBlockchainHeightResponse(postBlockchainHeightResponse));
        }catch (exception e){
            LogUtil::error("client error.",e);
            return unique_ptr<PostBlockchainHeightResponse>(nullptr);
        }
    }


    unique_ptr<GetBlockchainHeightResponse> NodeClient::getBlockchainHeight(GetBlockchainHeightRequest request) {
        try {
            string requestUrl = getUrl(API::GET_BLOCKCHAIN_HEIGHT);
            string requestBody = JsonUtil::toString(request);
            string responseHtml = NetUtil::get(requestUrl,requestBody);
            GetBlockchainHeightResponse getBlockchainHeightResponse = JsonUtil::toObject(responseHtml,GetBlockchainHeightResponse{});
            return unique_ptr<GetBlockchainHeightResponse>(new GetBlockchainHeightResponse(getBlockchainHeightResponse));
        }catch (exception e){
            LogUtil::error("client error.",e);
            return unique_ptr<GetBlockchainHeightResponse>(nullptr);
        }
    }


    unique_ptr<GetUnconfirmedTransactionsResponse> NodeClient::getUnconfirmedTransactions(GetUnconfirmedTransactionsRequest request) {
        try {
            string requestUrl = getUrl(API::GET_UNCONFIRMED_TRANSACTIONS);
            string requestBody = JsonUtil::toString(request);
            string responseHtml = NetUtil::get(requestUrl,requestBody);
            GetUnconfirmedTransactionsResponse getUnconfirmedTransactionsResponse = JsonUtil::toObject(responseHtml,GetUnconfirmedTransactionsResponse{});
            return unique_ptr<GetUnconfirmedTransactionsResponse>(new GetUnconfirmedTransactionsResponse(getUnconfirmedTransactionsResponse));
        }catch (exception e){
            LogUtil::error("client error.",e);
            return unique_ptr<GetUnconfirmedTransactionsResponse>(nullptr);
        }
    }





    string NodeClient::getUrl(string api) {
        return "http://" + ip + ":" + StringUtil::valueOfUint64(NetworkSetting::PORT) + api;
    }

}