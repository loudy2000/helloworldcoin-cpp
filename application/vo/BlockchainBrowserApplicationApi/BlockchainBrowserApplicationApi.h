//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_BLOCKCHAINBROWSERAPPLICATIONAPI_H
#define HELLOWORLDCOIN_CPP_BLOCKCHAINBROWSERAPPLICATIONAPI_H

#include <string>
using namespace std;


namespace BlockchainBrowserApplicationApi {


    const string QUERY_BLOCKCHAIN_HEIGHT = "/Api/BlockchainBrowserApplication/QueryBlockchainHeight";

    const string QUERY_TRANSACTION_BY_TRANSACTION_HASH = "/Api/BlockchainBrowserApplication/QueryTransactionByTransactionHash";
    const string QUERY_TRANSACTIONS_BY_BLOCK_HASH_TRANSACTION_HEIGHT = "/Api/BlockchainBrowserApplication/QueryTransactionsByBlockHashTransactionHeight";
    const string QUERY_TRANSACTION_OUTPUT_BY_ADDRESS = "/Api/BlockchainBrowserApplication/QueryTransactionOutputByAddress";
    const string QUERY_TRANSACTION_OUTPUT_BY_TRANSACTION_OUTPUT_ID = "/Api/BlockchainBrowserApplication/QueryTransactionOutputByTransactionOutputId";

    const string QUERY_UNCONFIRMED_TRANSACTIONS = "/Api/BlockchainBrowserApplication/QueryUnconfirmedTransactions";
    const string QUERY_UNCONFIRMED_TRANSACTION_BY_TRANSACTION_HASH = "/Api/BlockchainBrowserApplication/QueryUnconfirmedTransactionByTransactionHash";

    const string QUERY_BLOCK_BY_BLOCK_HEIGHT = "/Api/BlockchainBrowserApplication/QueryBlockByBlockHeight";
    const string QUERY_BLOCK_BY_BLOCK_HASH = "/Api/BlockchainBrowserApplication/QueryBlockByBlockHash";
    const string QUERY_LATEST_10_BLOCKS = "/Api/BlockchainBrowserApplication/QueryLatest10Blocks";

};


#endif //HELLOWORLDCOIN_CPP_BLOCKCHAINBROWSERAPPLICATIONAPI_H
