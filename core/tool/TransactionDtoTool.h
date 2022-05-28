//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_TRANSACTIONDTOTOOL_H
#define HELLOWORLDCOIN_CPP_TRANSACTIONDTOTOOL_H

#include "../../netcoredto/netcoredto.h"

using namespace std;
using namespace dto;

namespace TransactionDtoTool {


    string calculateTransactionHash(TransactionDto &transactionDto);

    string getSignatureHashAllRawMaterial(TransactionDto &transactionDto);

    string signature(string &privateKey, TransactionDto &transactionDto);

    bool verifySignature(TransactionDto &transaction, string &publicKey, vector<unsigned char> &bytesSignature) ;


    //region Serialization and Deserialization
    /**
     * Serialization: Convert TransactionDto into byte array. Requires that the resulting byte array can Convert into the original transaction.
     */
    vector<unsigned char> bytesTransaction(TransactionDto &transactionDto, bool omitInputScript);
    TransactionDto transactionDto(vector<unsigned char> bytesTransaction, bool omitInputScript) ;
    //endregion
}

    



#endif //HELLOWORLDCOIN_CPP_TRANSACTIONDTOTOOL_H