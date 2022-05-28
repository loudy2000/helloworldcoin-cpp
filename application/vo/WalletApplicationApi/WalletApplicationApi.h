//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_WALLETAPPLICATIONAPI_H
#define HELLOWORLDCOIN_CPP_WALLETAPPLICATIONAPI_H

#include <string>
using namespace std;



namespace WalletApplicationApi {

    const string CREATE_ACCOUNT = "/Api/WalletApplication/CreateAccount";
    const string CREATE_AND_SAVE_ACCOUNT = "/Api/WalletApplication/CreateAndSaveAccount";
    const string SAVE_ACCOUNT = "/Api/WalletApplication/SaveAccount";
    const string DELETE_ACCOUNT = "/Api/WalletApplication/DeleteAccount";
    const string QUERY_ALL_ACCOUNTS = "/Api/WalletApplication/QueryAllAccounts";

    const string AUTOMATIC_BUILD_TRANSACTION = "/Api/WalletApplication/AutomaticBuildTransaction";
    const string SUBMIT_TRANSACTION_TO_BLOCKCHIAIN_NEWWORK = "/Api/WalletApplication/SubmitTransactionToBlockchainNetwork";
};


#endif //HELLOWORLDCOIN_CPP_WALLETAPPLICATIONAPI_H
