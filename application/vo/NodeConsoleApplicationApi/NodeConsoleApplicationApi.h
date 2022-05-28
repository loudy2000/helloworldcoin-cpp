//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_NODECONSOLEAPPLICATIONAPI_H
#define HELLOWORLDCOIN_CPP_NODECONSOLEAPPLICATIONAPI_H

#include <string>
using namespace std;



namespace NodeConsoleApplicationApi {

    const string IS_MINER_ACTIVE = "/Api/NodeConsoleApplication/IsMinerActive";
    const string ACTIVE_MINER = "/Api/NodeConsoleApplication/ActiveMiner";
    const string DEACTIVE_MINER = "/Api/NodeConsoleApplication/DeactiveMiner";

    const string IS_AUTO_SEARCH_BLOCK = "/Api/NodeConsoleApplication/IsAutoSearchBlock";
    const string ACTIVE_AUTO_SEARCH_BLOCK = "/Api/NodeConsoleApplicationle/ActiveAutoSearchBlock";
    const string DEACTIVE_AUTO_SEARCH_BLOCK = "/Api/NodeConsoleApplication/DeactiveAutoSearchBlock";

    const string IS_AUTO_SEARCH_NODE = "/Api/NodeConsoleApplication/IsAutoSearchNode";
    const string ACTIVE_AUTO_SEARCH_NODE = "/Api/NodeConsoleApplication/ActiveAutoSearchNode";
    const string DEACTIVE_AUTO_SEARCH_NODE = "/Api/NodeConsoleApplication/DeactiveAutoSearchNode";

    const string SET_MINER_MINE_MAX_BLOCK_HEIGHT = "/Api/NodeConsoleApplication/SetMinerMineMaxBlockHeight";
    const string GET_MINER_MINE_MAX_BLOCK_HEIGHT = "/Api/NodeConsoleApplication/GetMinerMineMaxBlockHeight";

    const string ADD_NODE = "/Api/NodeConsoleApplication/AddNode";
    const string UPDATE_NODE = "/Api/NodeConsoleApplication/UpdateNode";
    const string DELETE_NODE = "/Api/NodeConsoleApplication/DeleteNode";
    const string QUERY_ALL_NODES = "/Api/NodeConsoleApplication/QueryAllNodes";
    const string DELETE_BLOCKS = "/Api/NodeConsoleApplication/DeleteBlocks";
};


#endif //HELLOWORLDCOIN_CPP_NODECONSOLEAPPLICATIONAPI_H
