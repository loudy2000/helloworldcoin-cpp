//
// author x.king xdotking@gmail.com
//

#include "WalletApplicationController.h"
#include "CommonController.h"
#include "../vo/accountvo.h"
#include "../../util/LogUtil.h"

using namespace vo;



namespace controller{


        WalletApplicationController::WalletApplicationController(BlockchainNetCore *blockchainNetCore,WalletApplicationService *walletApplicationService){
            this->blockchainNetCore = blockchainNetCore;
            this->walletApplicationService = walletApplicationService;
        }
        void WalletApplicationController::createAccount(const httplib::Request &req, httplib::Response &res){
            try {
                Account account = AccountUtil::randomAccount();
                AccountVo accountVo;
                accountVo.privateKey = account.privateKey;
                accountVo.publicKey = account.publicKey;
                accountVo.publicKeyHash = account.publicKeyHash;
                accountVo.address = account.address;
                CreateAccountResponse response;
                response.account=accountVo;
                success(res,response);
            } catch (exception e){
                string message = "'create account' error.";
                LogUtil::error(message,e);
                return serviceUnavailable(res);
            }
        }
        void WalletApplicationController::createAndSaveAccount(const httplib::Request &req, httplib::Response &res){
            try {
                Account account = blockchainNetCore->getBlockchainCore()->getWallet()->createAndSaveAccount();
                AccountVo accountVo;
                accountVo.privateKey = account.privateKey;
                accountVo.publicKey = account.publicKey;
                accountVo.publicKeyHash = account.publicKeyHash;
                accountVo.address = account.address;
                
                CreateAndSaveAccountResponse response;
                response.account=accountVo;
                success(res,response);
            } catch (exception e){
                string message = "'create and save account' error.";
                LogUtil::error(message,e);
                serviceUnavailable(res);
            }
        }
        void WalletApplicationController::saveAccount(const httplib::Request &req, httplib::Response &res){
            try {
                SaveAccountRequest request = JsonUtil::toObject(req.body, SaveAccountRequest{});

                string privateKey = request.privateKey;
                Account account = AccountUtil::accountFromPrivateKey(privateKey);
                blockchainNetCore->getBlockchainCore()->getWallet()->saveAccount(account);
                SaveAccountResponse response;
                success(res,response);
            } catch (exception e){
                string message = "'save account' error.";
                LogUtil::error(message,e);
                serviceUnavailable(res);
            }
        }
        void WalletApplicationController::deleteAccount(const httplib::Request &req, httplib::Response &res){
            try {
                DeleteAccountRequest request = JsonUtil::toObject(req.body, DeleteAccountRequest{});

                string address = request.address;
                blockchainNetCore->getBlockchainCore()->getWallet()->deleteAccountByAddress(address);
                DeleteAccountResponse response;
                success(res,response);
            } catch (exception e){
                string message = "'delete account' error.";
                LogUtil::error(message,e);
                serviceUnavailable(res);
            }
        }
        void WalletApplicationController::queryAllAccounts(const httplib::Request &req, httplib::Response &res){
            try {
                Wallet *wallet = blockchainNetCore->getBlockchainCore()->getWallet();
                vector<Account> allAccounts = wallet->getAllAccounts();

                vector<AccountVo2> accountVos;
                if(!allAccounts.empty()){
                    for(Account account:allAccounts){
                        AccountVo2 accountVo;
                        accountVo.address=account.address;
                        accountVo.privateKey=account.privateKey;
                        accountVo.value=wallet->getBalanceByAddress(account.address);
                        accountVos.push_back(accountVo);
                    }
                }

                uint64_t balance = 0;
                for(AccountVo2 accountVo : accountVos){
                    balance += accountVo.value;
                }

                QueryAllAccountsResponse response;
                response.accounts=accountVos;
                response.balance=balance;
                success(res,response);
            } catch (exception e){
                string message = "'query all accounts' error.";
                LogUtil::error(message,e);
                serviceUnavailable(res);
            }
        }
        void WalletApplicationController::automaticBuildTransaction(const httplib::Request &req, httplib::Response &res){
            try {
                AutomaticBuildTransactionRequest request = JsonUtil::toObject(req.body, AutomaticBuildTransactionRequest{});

                AutomaticBuildTransactionResponse autoBuildTransactionResponse = walletApplicationService->automaticBuildTransaction(request);
                if(autoBuildTransactionResponse.buildTransactionSuccess){
                    success(res,autoBuildTransactionResponse);
                }else {
                    serviceUnavailable(res);
                }
            } catch (exception e){
                string message = "'automatic build transaction' error.";
                LogUtil::error(message,e);
                serviceUnavailable(res);
            }
        }
        void WalletApplicationController::submitTransactionToBlockchainNetwork(const httplib::Request &req, httplib::Response &res){
            try {
                SubmitTransactionToBlockchainNetworkRequest request = JsonUtil::toObject(req.body, SubmitTransactionToBlockchainNetworkRequest{});

                SubmitTransactionToBlockchainNetworkResponse response = walletApplicationService->submitTransactionToBlockchainNetwork(request);
                success(res,response);
            } catch (exception e){
                string message = "'submit transaction to blockchain network' error.";
                LogUtil::error(message,e);
                serviceUnavailable(res);
            }
        }
}
