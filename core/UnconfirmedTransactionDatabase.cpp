//
// author x.king xdotking@gmail.com
//

#include "UnconfirmedTransactionDatabase.h"
#include "tool/TransactionDtoTool.h"
#include "../util/FileUtil.h"
#include "../util/ByteUtil.h"
#include "../util/EncodeDecodeTool.h"
#include "../util/KvDbUtil.h"
#include "../util/LogUtil.h"

namespace core{

    const string UNCONFIRMED_TRANSACTION_DATABASE_NAME = "UnconfirmedTransactionDatabase";

    bool UnconfirmedTransactionDatabase::insertTransaction(TransactionDto transaction) {
        try {
            string transactionHash = TransactionDtoTool::calculateTransactionHash(transaction);
            KvDbUtil::put(getUnconfirmedTransactionDatabasePath(), getKey(transactionHash), EncodeDecodeTool::encode(transaction));
            return true;
        } catch (exception e) {
            LogUtil::error("'insert transaction to database' error. ["+ JsonUtil::toString(transaction)+"]",e);
            return false;
        }
    }
    vector<TransactionDto> UnconfirmedTransactionDatabase::selectTransactions(uint64_t from, uint64_t size) {
        vector<TransactionDto> transactionDtos;
        vector<vector<unsigned char>> bytesTransactionDtos = KvDbUtil::gets(getUnconfirmedTransactionDatabasePath(),from,size);
        if(!bytesTransactionDtos.empty()){
            for(vector<unsigned char> bytesTransactionDto:bytesTransactionDtos){
                TransactionDto transactionDto = EncodeDecodeTool::decode(bytesTransactionDto,TransactionDto{});
                transactionDtos.push_back(transactionDto);
            }
        }
        return transactionDtos;
    }
    void UnconfirmedTransactionDatabase::deleteByTransactionHash(string transactionHash) {
        KvDbUtil::delete0(getUnconfirmedTransactionDatabasePath(), getKey(transactionHash));
    }
    unique_ptr<TransactionDto> UnconfirmedTransactionDatabase::selectTransactionByTransactionHash(string transactionHash){
        vector<unsigned char> byteTransactionDto = KvDbUtil::get(getUnconfirmedTransactionDatabasePath(), getKey(transactionHash));
        if(byteTransactionDto.empty()){
            return unique_ptr<TransactionDto>(nullptr);
        }
        TransactionDto transactionDto = EncodeDecodeTool::decode(byteTransactionDto,TransactionDto{});
        return unique_ptr<TransactionDto>(new TransactionDto(transactionDto));
    }




    string UnconfirmedTransactionDatabase::getUnconfirmedTransactionDatabasePath() {
        return FileUtil::newPath(coreConfiguration->getCorePath(), UNCONFIRMED_TRANSACTION_DATABASE_NAME);
    }
    vector<unsigned char> UnconfirmedTransactionDatabase::getKey(string transactionHash){
        return ByteUtil::hexStringToBytes(transactionHash);
    }

    UnconfirmedTransactionDatabase::UnconfirmedTransactionDatabase(CoreConfiguration *coreConfiguration) {
        this->coreConfiguration = coreConfiguration;
    }
}