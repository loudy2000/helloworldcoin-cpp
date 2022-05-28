//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_WALLET_H
#define HELLOWORLDCOIN_CPP_WALLET_H

#include "../crypto/AccountUtil.h"
#include "BlockchainDatabase.h"
#include "CoreConfiguration.h"


namespace core{
    class Wallet {
    private:
        CoreConfiguration *coreConfiguration;
        BlockchainDatabase *blockchainDatabase;
    public:
        Wallet(CoreConfiguration *coreConfiguration, BlockchainDatabase *blockchainDatabase);

    public:
        vector<Account> getAllAccounts();
        vector<Account> getNonZeroBalanceAccounts();
        Account createAccount();
        Account createAndSaveAccount();
        void saveAccount(Account account);
        void deleteAccountByAddress(string address);
        uint64_t getBalanceByAddress(string address);
        AutoBuildTransactionResponse autoBuildTransaction(AutoBuildTransactionRequest request) ;
    private:
        string getWalletDatabasePath();
        vector<unsigned char> getKeyByAddress(string address);
        vector<unsigned char> getKeyByAccount(Account account);
        bool haveEnoughMoneyToPay(vector<Payer> payers, vector<Payee> payees, uint64_t fee);
        unique_ptr<Payee> createChangePayee(vector<Payer> payers, vector<Payee> payees, string changeAddress, uint64_t fee);
        uint64_t changeValue(vector<Payer> payers, vector<Payee> payees, uint64_t fee);
        TransactionDto buildTransaction(vector<Payer> payers, vector<Payee> payees);
    };
}



#endif //HELLOWORLDCOIN_CPP_WALLET_H