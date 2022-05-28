//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_BLOCKCHAINBROWSERAPPLICATIONCONTROLLER_H
#define HELLOWORLDCOIN_CPP_BLOCKCHAINBROWSERAPPLICATIONCONTROLLER_H

#include "../../thirdpart/httplib/httplib.h"
#include "../../netcore/BlockchainNetCore.h"
#include "../service/BlockchainBrowserApplicationService.h"
#include "../service/WalletApplicationService.h"

using namespace netcore;
using namespace service;



namespace controller{



    class BlockchainBrowserApplicationController {
    private:
        BlockchainNetCore *blockchainNetCore;
        BlockchainBrowserApplicationService *blockchainBrowserApplicationService;
    public:
        BlockchainBrowserApplicationController(BlockchainNetCore *blockchainNetCore,BlockchainBrowserApplicationService *blockchainBrowserApplicationService);
    public:
        void queryTransactionByTransactionHash(const httplib::Request &req, httplib::Response &res);
        void queryTransactionsByBlockHashTransactionHeight(const httplib::Request &req, httplib::Response &res);
        void queryTransactionOutputByAddress(const httplib::Request &req, httplib::Response &res);
        void queryTransactionOutputByTransactionOutputId(const httplib::Request &req, httplib::Response &res);
        void queryBlockchainHeight(const httplib::Request &req, httplib::Response &res);
        void queryUnconfirmedTransactionByTransactionHash(const httplib::Request &req, httplib::Response &res);
        void queryUnconfirmedTransactions(const httplib::Request &req, httplib::Response &res);
        void queryBlockByBlockHeight(const httplib::Request &req, httplib::Response &res);
        void queryBlockByBlockHash(const httplib::Request &req, httplib::Response &res);
        void queryLatest10Blocks(const httplib::Request &req, httplib::Response &res);
    };
}


#endif //HELLOWORLDCOIN_CPP_BLOCKCHAINBROWSERAPPLICATIONCONTROLLER_H
