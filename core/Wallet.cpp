//
// author x.king xdotking@gmail.com
//

#include "Wallet.h"
#include "tool/ScriptDtoTool.h"
#include "tool/TransactionDtoTool.h"
#include "../util/ByteUtil.h"
#include "../util/FileUtil.h"
#include "../util/EncodeDecodeTool.h"

namespace core{

    const string WALLET_DATABASE_NAME = "WalletDatabase";


    Wallet::Wallet(core::CoreConfiguration *coreConfiguration, core::BlockchainDatabase *blockchainDatabase) {
        this->coreConfiguration = coreConfiguration;
        this->blockchainDatabase = blockchainDatabase;
    }


    vector<Account> Wallet::getAllAccounts() {
        vector<Account> accounts;
        vector<vector<unsigned char>> bytesAccounts = KvDbUtil::gets(getWalletDatabasePath(),1,100000000);
        if(!bytesAccounts.empty()){
            for(vector<unsigned char> &bytesAccount:bytesAccounts){
                Account account = EncodeDecodeTool::decode(bytesAccount,Account{});
                accounts.push_back(account);
            }
        }
        return accounts;
    }


    vector<Account> Wallet::getNonZeroBalanceAccounts() {
        vector<Account> accounts;
        vector<vector<unsigned char>> bytesAccounts = KvDbUtil::gets(getWalletDatabasePath(),1,100000000);
        if(!bytesAccounts.empty()){
            for(vector<unsigned char> &bytesAccount:bytesAccounts){
                Account account = EncodeDecodeTool::decode(bytesAccount,Account{});
                unique_ptr<TransactionOutput> utxo = blockchainDatabase->queryUnspentTransactionOutputByAddress(account.address);
                if(utxo.get() && utxo->value > 0){
                    accounts.push_back(account);
                }
            }
        }
        return accounts;
    }


    Account Wallet::createAccount() {
        return AccountUtil::randomAccount();
    }


    Account Wallet::createAndSaveAccount() {
        Account account = createAccount();
        saveAccount(account);
        return account;
    }


    void Wallet::saveAccount(Account account) {
        KvDbUtil::put(getWalletDatabasePath(),getKeyByAccount(account), EncodeDecodeTool::encode(account));
    }


    void Wallet::deleteAccountByAddress(string address) {
        KvDbUtil::delete0(getWalletDatabasePath(),getKeyByAddress(address));
    }


    uint64_t Wallet::getBalanceByAddress(string address) {
        unique_ptr<TransactionOutput> utxo = blockchainDatabase->queryUnspentTransactionOutputByAddress(address);
        if(utxo.get()){
            return utxo->value;
        }
        return 0L;
    }


    AutoBuildTransactionResponse Wallet::autoBuildTransaction(AutoBuildTransactionRequest request) {
        vector<Payee> nonChangePayees = request.nonChangePayees;
        vector<Payer> payers;
        vector<Account> allAccounts = getNonZeroBalanceAccounts();
        if(!allAccounts.empty()){
            for(Account account:allAccounts){
                unique_ptr<TransactionOutput> utxo = blockchainDatabase->queryUnspentTransactionOutputByAddress(account.address);
                Payer payer;
                payer.privateKey=account.privateKey;
                payer.address=account.address;
                payer.transactionHash=utxo->transactionHash;
                payer.transactionOutputIndex=utxo->transactionOutputIndex;
                payer.value=utxo->value;
                payers.push_back(payer);
                uint64_t fee = 0L;
                bool haveEnoughMoneyToPay0 = haveEnoughMoneyToPay(payers,nonChangePayees,fee);
                if(haveEnoughMoneyToPay0){
                    Account changeAccount = createAndSaveAccount();
                    unique_ptr<Payee> changePayee = createChangePayee(payers,nonChangePayees,changeAccount.address,fee);
                    vector<Payee> payees(nonChangePayees);
                    if(changePayee.get()){
                        payees.push_back(*changePayee);
                    }
                    TransactionDto transactionDto = buildTransaction(payers,payees);
                    AutoBuildTransactionResponse response;
                    response.buildTransactionSuccess=true;
                    response.transaction=transactionDto;
                    response.transactionHash=TransactionDtoTool::calculateTransactionHash(transactionDto);
                    response.fee=fee;
                    response.payers=payers;
                    response.nonChangePayees=nonChangePayees;
                    if(changePayee.get()){
                        response.changePayee=*changePayee;
                    }
                    response.payees=payees;
                    return response;
                }
            }
        }
        AutoBuildTransactionResponse response;
        response.buildTransactionSuccess=false;
        return response;
    }





    string Wallet::getWalletDatabasePath() {
        return FileUtil::newPath(coreConfiguration->getCorePath(), WALLET_DATABASE_NAME);
    }
    vector<unsigned char> Wallet::getKeyByAddress(string address){
        return ByteUtil::stringToUtf8Bytes(address);
    }
    vector<unsigned char> Wallet::getKeyByAccount(Account account){
        return getKeyByAddress(account.address);
    }


    bool Wallet::haveEnoughMoneyToPay(vector<Payer> payers, vector<Payee> payees, uint64_t fee) {
        uint64_t changeValue0 = changeValue(payers,payees,fee);
        bool haveEnoughMoneyToPay = changeValue0>=0;
        return haveEnoughMoneyToPay;
    }
    unique_ptr<Payee> Wallet::createChangePayee(vector<Payer> payers, vector<Payee> payees, string changeAddress, uint64_t fee) {
        uint64_t changeValue0 = changeValue(payers,payees,fee);
        if(changeValue0 <= 0){
            return unique_ptr<Payee>(nullptr);
        }
        Payee changePayee;
        changePayee.address=changeAddress;
        changePayee.value=changeValue0;
        return unique_ptr<Payee>(new Payee(changePayee));
    }
    uint64_t Wallet::changeValue(vector<Payer> payers, vector<Payee> payees, uint64_t fee) {
        uint64_t transactionInputValues = 0;
        for(Payer payer: payers){
            transactionInputValues += payer.value;
        }
        uint64_t payeeValues = 0;
        if(!payees.empty()){
            for(Payee payee : payees){
                payeeValues += payee.value;
            }
        }
        uint64_t changeValue = transactionInputValues -  payeeValues - fee;
        return changeValue;
    }
    TransactionDto Wallet::buildTransaction(vector<Payer> payers, vector<Payee> payees) {
        vector<TransactionInputDto> transactionInputs;
        for(Payer payer: payers){
            TransactionInputDto transactionInput;
            transactionInput.transactionHash=payer.transactionHash;
            transactionInput.transactionOutputIndex=payer.transactionOutputIndex;
            transactionInputs.push_back(transactionInput);
        }
        vector<TransactionOutputDto> transactionOutputs;
        if(!payees.empty()){
            for(Payee payee : payees){
                TransactionOutputDto transactionOutput;
                OutputScriptDto outputScript = ScriptDtoTool::createPayToPublicKeyHashOutputScript(payee.address);
                transactionOutput.value=payee.value;
                transactionOutput.outputScript=outputScript;
                transactionOutputs.push_back(transactionOutput);
            }
        }
        TransactionDto transaction;
        transaction.inputs=transactionInputs;
        transaction.outputs=transactionOutputs;
        for(int i=0; i<transaction.inputs.size(); i++){
            TransactionInputDto &transactionInput = transaction.inputs[i];
            Account account = AccountUtil::accountFromPrivateKey(payers[i].privateKey);
            string signature = TransactionDtoTool::signature(account.privateKey,transaction);
            InputScriptDto inputScript = ScriptDtoTool::createPayToPublicKeyHashInputScript(signature, account.publicKey);
            transactionInput.inputScript=inputScript;
        }
        return transaction;
    }
}
