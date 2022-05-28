//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_TRANSACTIONTOOL_H
#define HELLOWORLDCOIN_CPP_TRANSACTIONTOOL_H


#include "../model/model.h"

using namespace model;

namespace TransactionTool {
    /**
     * Get Total Input Value Of Transaction
     */
    uint64_t getInputValue(Transaction *transaction) ;

    /**
     * Get Total Output Value Of Transaction
     */
    uint64_t getOutputValue(Transaction *transaction) ;

    /**
     * Get Total Fees Of Transaction
     */
    uint64_t getTransactionFee(Transaction *transaction) ;

    /**
     * Get Fee Rate Of Transaction
     */
    uint64_t getTransactionFeeRate(Transaction *transaction) ;





    string getSignatureHashAllRawMaterial(Transaction *transaction) ;

    string signature(string privateKey, Transaction *transaction) ;

    bool verifySignature(Transaction transaction, string publicKey, vector<unsigned char> *bytesSignature)  ;




    string calculateTransactionHash(Transaction *transaction) ;

    uint64_t getTransactionInputCount(Transaction *transaction) ;

    uint64_t getTransactionOutputCount(Transaction *transaction) ;

    string getTransactionOutputId(TransactionOutput *transactionOutput)  ;


    /**
     * Check Transaction Value
     */
    bool checkTransactionValue(Transaction *transaction) ;

    /**
     * Check whether the transaction value is legal: this is used to limit the maximum value, minimum value, decimal places, etc. of the transaction value
     */
    bool checkValue(uint64_t transactionAmount) ;

    /**
     * Check if the address in the transaction is a P2PKH address
     */
    bool checkPayToPublicKeyHashAddress(Transaction *transaction) ;

    /**
     * Check if the script in the transaction is a P2PKH script
     */
    bool checkPayToPublicKeyHashScript(Transaction *transaction)  ;

    /**
     * Is there a duplicate [unspent transaction output] in the transaction
     */
    bool isExistDuplicateUtxo(Transaction *transaction) ;

    /**
     * Whether the newly generated address of the block is duplicated
     */
    bool isExistDuplicateNewAddress(Transaction *transaction) ;

    /**
     * Sort transactions by rate (fee per character) from largest to smallest
     */
    void sortByTransactionFeeRateDescend(vector<Transaction> *transactions)  ;
};


#endif //HELLOWORLDCOIN_CPP_TRANSACTIONTOOL_H
