//
// author x.king xdotking@gmail.com
//

#include "BlockDtoTool.h"
#include "../../util/ByteUtil.h"
#include "../../crypto/Sha256Util.h"
#include "TransactionDtoTool.h"
#include "../../crypto/MerkleTreeUtil.h"
#include "../../util/StringUtil.h"

using namespace std;

string BlockDtoTool::calculateBlockHash(dto::BlockDto *blockDto){
    vector<unsigned char> bytesTimestamp = ByteUtil::uint64ToBytes(blockDto->timestamp);
    vector<unsigned char> bytesPreviousBlockHash = ByteUtil::hexStringToBytes(blockDto->previousHash);
    vector<unsigned char> bytesMerkleTreeRoot = ByteUtil::hexStringToBytes(calculateBlockMerkleTreeRoot(blockDto));
    vector<unsigned char> bytesNonce = ByteUtil::hexStringToBytes(blockDto->nonce);

    vector<unsigned char> bytesBlockHeader = ByteUtil::concatenate4(bytesTimestamp,bytesPreviousBlockHash,bytesMerkleTreeRoot,bytesNonce);
    vector<unsigned char> bytesBlockHash = Sha256Util::doubleDigest(bytesBlockHeader);
    return ByteUtil::bytesToHexString(bytesBlockHash);
}
string BlockDtoTool::calculateBlockMerkleTreeRoot(dto::BlockDto *blockDto){
    vector<dto::TransactionDto> transactions = blockDto->transactions;
    vector<vector<unsigned char>> bytesTransactionHashs;
    if(!transactions.empty()){
        for(dto::TransactionDto &transactionDto : transactions) {
            string transactionHash = TransactionDtoTool::calculateTransactionHash(transactionDto);
            vector<unsigned char> bytesTransactionHash = ByteUtil::hexStringToBytes(transactionHash);
            bytesTransactionHashs.push_back(bytesTransactionHash);
        }
    }
    return ByteUtil::bytesToHexString(MerkleTreeUtil::calculateMerkleTreeRoot(bytesTransactionHashs));
}
bool BlockDtoTool::isBlockEquals(dto::BlockDto *block1, dto::BlockDto *block2){
    string block1Hash = calculateBlockHash(block1);
    string block2Hash = calculateBlockHash(block2);
    return StringUtil::equals(block1Hash, block2Hash);
}
