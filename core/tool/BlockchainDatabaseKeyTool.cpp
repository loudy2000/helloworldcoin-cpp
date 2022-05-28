//
// author x.king xdotking@gmail.com
//

#include "BlockchainDatabaseKeyTool.h"
#include "../../util/ByteUtil.h"
#include "../../util/StringUtil.h"


namespace BlockchainDatabaseKeyTool{

    //BLOCKCHAIN HEIGHT KEY => blockchain height value
    string BLOCKCHAIN_HEIGHT_KEY = "A";
    //BLOCKCHAIN TRANSACTION HEIGHT KEY => blockchain transaction height value
    string BLOCKCHAIN_TRANSACTION_HEIGHT_KEY = "B";
    //BLOCKCHAIN TRANSACTION OUTPUT HEIGHT KEY => blockchain transaction output height value
    string BLOCKCHAIN_TRANSACTION_OUTPUT_HEIGHT_KEY = "C";

    //HASH FLAG: hash prefix flag
    string HASH_PREFIX_FLAG = "D";


    //BLOCK FLAG: block height => block
    string BLOCK_HEIGHT_TO_BLOCK_PREFIX_FLAG = "E";
    //BLOCK FLAG: block hash => block
    string BLOCK_HASH_TO_BLOCK_HEIGHT_PREFIX_FLAG = "F";


    //TRANSACTION FLAG: transaction height => transaction
    string TRANSACTION_HEIGHT_TO_TRANSACTION_PREFIX_FLAG = "G";
    //TRANSACTION FLAG: transaction hash => transaction height
    string TRANSACTION_HASH_TO_TRANSACTION_HEIGHT_PREFIX_FLAG = "H";


    //TRANSACTION OUTPUT FLAG: transaction output height => transaction output
    string TRANSACTION_OUTPUT_HEIGHT_TO_TRANSACTION_OUTPUT_PREFIX_FLAG = "I";
    //TRANSACTION OUTPUT FLAG: transaction output id => transaction output height
    string TRANSACTION_OUTPUT_ID_TO_TRANSACTION_OUTPUT_HEIGHT_PREFIX_FLAG = "J";
    //TRANSACTION OUTPUT FLAG: transaction output id => unspent transaction output height
    string TRANSACTION_OUTPUT_ID_TO_UNSPENT_TRANSACTION_OUTPUT_HEIGHT_PREFIX_FLAG = "K";
    //TRANSACTION OUTPUT FLAG: transaction output id => spent transaction output height
    string TRANSACTION_OUTPUT_ID_TO_SPENT_TRANSACTION_OUTPUT_HEIGHT_PREFIX_FLAG = "L";
    //TRANSACTION OUTPUT FLAG: transaction output id => source transaction output height
    string TRANSACTION_OUTPUT_ID_TO_SOURCE_TRANSACTION_HEIGHT_PREFIX_FLAG = "M";
    //TRANSACTION OUTPUT FLAG: transaction output id => to transaction output height
    string TRANSACTION_OUTPUT_ID_TO_DESTINATION_TRANSACTION_HEIGHT_PREFIX_FLAG = "N";


    //ADDRESS FLAG: address prefix flag
    string ADDRESS_PREFIX_FLAG = "O";
    //ADDRESS FLAG: address => transaction output height
    string ADDRESS_TO_TRANSACTION_OUTPUT_HEIGHT_PREFIX_FLAG = "P";
    //ADDRESS FLAG: address => unspent transaction output height
    string ADDRESS_TO_UNSPENT_TRANSACTION_OUTPUT_HEIGHT_PREFIX_FLAG = "Q";
    //ADDRESS FLAG: address => spent transaction output height
    string ADDRESS_TO_SPENT_TRANSACTION_OUTPUT_HEIGHT_PREFIX_FLAG = "R";


    string END_FLAG = "#" ;
    string VERTICAL_LINE_FLAG = "|" ;



    //region Build Key
    vector<unsigned char> buildBlockchainHeightKey() {
        string stringKey = BLOCKCHAIN_HEIGHT_KEY + END_FLAG;
        return ByteUtil::stringToUtf8Bytes(stringKey);
    }
    vector<unsigned char> buildHashKey(string hash) {
        string stringKey = HASH_PREFIX_FLAG + hash + END_FLAG;
        return ByteUtil::stringToUtf8Bytes(stringKey);
    }
    vector<unsigned char> buildAddressKey(string address) {
        string stringKey = ADDRESS_PREFIX_FLAG + address + END_FLAG;
        return ByteUtil::stringToUtf8Bytes(stringKey);
    }
    vector<unsigned char> buildBlockHeightToBlockKey(uint64_t blockHeight) {
        string stringKey = BLOCK_HEIGHT_TO_BLOCK_PREFIX_FLAG + StringUtil::valueOfUint64(blockHeight) + END_FLAG;
        return ByteUtil::stringToUtf8Bytes(stringKey);
    }
    vector<unsigned char> buildBlockHashToBlockHeightKey(string blockHash) {
        string stringKey = BLOCK_HASH_TO_BLOCK_HEIGHT_PREFIX_FLAG + blockHash + END_FLAG;
        return ByteUtil::stringToUtf8Bytes(stringKey);
    }
    vector<unsigned char> buildTransactionHashToTransactionHeightKey(string transactionHash) {
        string stringKey = TRANSACTION_HASH_TO_TRANSACTION_HEIGHT_PREFIX_FLAG + transactionHash + END_FLAG;
        return ByteUtil::stringToUtf8Bytes(stringKey);
    }
    vector<unsigned char> buildTransactionOutputHeightToTransactionOutputKey(uint64_t transactionOutputHeight) {
        string stringKey = TRANSACTION_OUTPUT_HEIGHT_TO_TRANSACTION_OUTPUT_PREFIX_FLAG + StringUtil::valueOfUint64(transactionOutputHeight) + END_FLAG;
        return ByteUtil::stringToUtf8Bytes(stringKey);
    }
    vector<unsigned char> buildTransactionOutputIdToTransactionOutputHeightKey(string transactionHash,uint64_t transactionOutputIndex) {
        string transactionOutputId = buildTransactionOutputId(transactionHash, transactionOutputIndex);
        string stringKey = TRANSACTION_OUTPUT_ID_TO_TRANSACTION_OUTPUT_HEIGHT_PREFIX_FLAG + transactionOutputId + END_FLAG;
        return ByteUtil::stringToUtf8Bytes(stringKey);
    }
    vector<unsigned char> buildTransactionOutputIdToUnspentTransactionOutputHeightKey(string transactionHash,uint64_t transactionOutputIndex) {
        string transactionOutputId = buildTransactionOutputId(transactionHash, transactionOutputIndex);
        string stringKey = TRANSACTION_OUTPUT_ID_TO_UNSPENT_TRANSACTION_OUTPUT_HEIGHT_PREFIX_FLAG + transactionOutputId + END_FLAG;
        return ByteUtil::stringToUtf8Bytes(stringKey);
    }
    vector<unsigned char> buildTransactionOutputIdToSourceTransactionHeightKey(string transactionHash,uint64_t transactionOutputIndex) {
        string transactionOutputId = buildTransactionOutputId(transactionHash, transactionOutputIndex);
        string stringKey = TRANSACTION_OUTPUT_ID_TO_SOURCE_TRANSACTION_HEIGHT_PREFIX_FLAG + transactionOutputId + END_FLAG;
        return ByteUtil::stringToUtf8Bytes(stringKey);
    }
    vector<unsigned char> buildTransactionOutputIdToDestinationTransactionHeightKey(string transactionHash,uint64_t transactionOutputIndex) {
        string transactionOutputId = buildTransactionOutputId(transactionHash, transactionOutputIndex);
        string stringKey = TRANSACTION_OUTPUT_ID_TO_DESTINATION_TRANSACTION_HEIGHT_PREFIX_FLAG + transactionOutputId + END_FLAG;
        return ByteUtil::stringToUtf8Bytes(stringKey);
    }
    vector<unsigned char> buildAddressToTransactionOutputHeightKey(string address) {
        string stringKey = ADDRESS_TO_TRANSACTION_OUTPUT_HEIGHT_PREFIX_FLAG + address + END_FLAG;
        return ByteUtil::stringToUtf8Bytes(stringKey);
    }
    vector<unsigned char> buildAddressToUnspentTransactionOutputHeightKey(string address) {
        string stringKey = ADDRESS_TO_UNSPENT_TRANSACTION_OUTPUT_HEIGHT_PREFIX_FLAG + address + END_FLAG;
        return ByteUtil::stringToUtf8Bytes(stringKey);
    }
    vector<unsigned char> buildAddressToSpentTransactionOutputHeightKey(string address) {
        string stringKey = ADDRESS_TO_SPENT_TRANSACTION_OUTPUT_HEIGHT_PREFIX_FLAG + address + END_FLAG;
        return ByteUtil::stringToUtf8Bytes(stringKey);
    }
    vector<unsigned char> buildBlockchainTransactionHeightKey() {
        string stringKey = BLOCKCHAIN_TRANSACTION_HEIGHT_KEY + END_FLAG;
        return ByteUtil::stringToUtf8Bytes(stringKey);
    }
    vector<unsigned char> buildBlockchainTransactionOutputHeightKey() {
        string stringKey = BLOCKCHAIN_TRANSACTION_OUTPUT_HEIGHT_KEY + END_FLAG;
        return ByteUtil::stringToUtf8Bytes(stringKey);
    }
    vector<unsigned char> buildTransactionHeightToTransactionKey(uint64_t transactionHeight) {
        string stringKey = TRANSACTION_HEIGHT_TO_TRANSACTION_PREFIX_FLAG + StringUtil::valueOfUint64(transactionHeight) + END_FLAG;
        return ByteUtil::stringToUtf8Bytes(stringKey);
    }

    vector<unsigned char> buildTransactionOutputIdToSpentTransactionOutputHeightKey(string transactionHash,uint64_t transactionOutputIndex) {
        string transactionOutputId = buildTransactionOutputId(transactionHash, transactionOutputIndex);
        string stringKey = TRANSACTION_OUTPUT_ID_TO_SPENT_TRANSACTION_OUTPUT_HEIGHT_PREFIX_FLAG + transactionOutputId + END_FLAG;
        return ByteUtil::stringToUtf8Bytes(stringKey);
    }
    //endregion


    string buildTransactionOutputId(string transactionHash,uint64_t transactionOutputIndex) {
        string transactionOutputId = StringUtil::concatenate3(transactionHash, VERTICAL_LINE_FLAG, StringUtil::valueOfUint64(transactionOutputIndex));
        return transactionOutputId;
    }


}