//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_NODECONSOLEAPPLICATIONCONTROLLER_H
#define HELLOWORLDCOIN_CPP_NODECONSOLEAPPLICATIONCONTROLLER_H

#include "../../thirdpart/httplib/httplib.h"
#include "../../netcore/BlockchainNetCore.h"

using namespace netcore;



namespace controller{



    class NodeConsoleApplicationController {
    private:
        BlockchainNetCore *blockchainNetCore;
    public:
        NodeConsoleApplicationController(BlockchainNetCore *blockchainNetCore);
    public:
        void IsMinerActive(const httplib::Request &req, httplib::Response &res);
        void ActiveMiner(const httplib::Request &req, httplib::Response &res);
        void DeactiveMiner(const httplib::Request &req, httplib::Response &res);
        void IsAutoSearchBlock(const httplib::Request &req, httplib::Response &res);
        void ActiveAutoSearchBlock(const httplib::Request &req, httplib::Response &res);
        void DeactiveAutoSearchBlock(const httplib::Request &req, httplib::Response &res);
        void AddNode(const httplib::Request &req, httplib::Response &res);
        void UpdateNode(const httplib::Request &req, httplib::Response &res);
        void DeleteNode(const httplib::Request &req, httplib::Response &res);
        void queryAllNodes(const httplib::Request &req, httplib::Response &res);
        void IsAutoSearchNode(const httplib::Request &req, httplib::Response &res);
        void ActiveAutoSearchNode(const httplib::Request &req, httplib::Response &res);
        void DeactiveAutoSearchNode(const httplib::Request &req, httplib::Response &res);
        void DeleteBlocks(const httplib::Request &req, httplib::Response &res);
        void GetMinerMineMaxBlockHeight(const httplib::Request &req, httplib::Response &res);
        void SetMinerMineMaxBlockHeight(const httplib::Request &req, httplib::Response &res);
    };
}


#endif //HELLOWORLDCOIN_CPP_NODECONSOLEAPPLICATIONCONTROLLER_H
