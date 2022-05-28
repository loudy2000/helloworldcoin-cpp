//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_UNCONFIRMEDTRANSACTIONSSEARCHER_H
#define HELLOWORLDCOIN_CPP_UNCONFIRMEDTRANSACTIONSSEARCHER_H



#include "netcoreconfiguration/NetCoreConfiguration.h"
#include "netcoreserver/NodeServer.h"
#include "../netcoredto/netcoredto.h"

using namespace netcoreconfiguration;
using namespace dto;


namespace netcore{

    class UnconfirmedTransactionsSearcher {
    private:
        NetCoreConfiguration *netCoreConfiguration;
        BlockchainCore *blockchainCore;
        NodeService *nodeService;
    public:
        UnconfirmedTransactionsSearcher(NetCoreConfiguration *netCoreConfiguration, BlockchainCore *blockchainCore, NodeService *nodeService);
    public:
        void start();
    private:
        void searchUnconfirmedTransactions();
    };

}


#endif //HELLOWORLDCOIN_CPP_UNCONFIRMEDTRANSACTIONSSEARCHER_H
