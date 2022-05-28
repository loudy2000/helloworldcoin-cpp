//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_UNCONFIRMEDTRANSACTIONDATABASE_H
#define HELLOWORLDCOIN_CPP_UNCONFIRMEDTRANSACTIONDATABASE_H


#include "../netcoredto/netcoredto.h"
#include "CoreConfiguration.h"

using namespace dto;

namespace core{
    class UnconfirmedTransactionDatabase {
    private:
        CoreConfiguration *coreConfiguration;
    public:
        UnconfirmedTransactionDatabase(CoreConfiguration *coreConfiguration);

    public:
        bool insertTransaction(TransactionDto transaction) ;
        vector<TransactionDto> selectTransactions(uint64_t from, uint64_t size) ;
        void deleteByTransactionHash(string transactionHash) ;
        unique_ptr<TransactionDto> selectTransactionByTransactionHash(string transactionHash);

    private:
        string getUnconfirmedTransactionDatabasePath() ;
        vector<unsigned char> getKey(string transactionHash);
    };
}



#endif //HELLOWORLDCOIN_CPP_UNCONFIRMEDTRANSACTIONDATABASE_H
