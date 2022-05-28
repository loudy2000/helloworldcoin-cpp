//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_BLOCKCHAINBROWSERAPPLICATIONSERVICE_H
#define HELLOWORLDCOIN_CPP_BLOCKCHAINBROWSERAPPLICATIONSERVICE_H

#include "../vo/transactionvo.h"
#include "../vo/walletvo.h"
#include "../../netcore/BlockchainNetCore.h"
#include "../vo/blockvo.h"

using namespace vo;

using namespace netcore;



namespace service {


    class BlockchainBrowserApplicationService {
    private:
        BlockchainNetCore *blockchainNetCore;
    public:
        BlockchainBrowserApplicationService(BlockchainNetCore *blockchainNetCore);
    public:
        unique_ptr<TransactionOutputVo3> queryTransactionOutputByTransactionOutputId(string transactionHash, uint64_t transactionOutputIndex);
        unique_ptr<TransactionOutputVo3> queryTransactionOutputByAddress(string address);
        unique_ptr<TransactionVo> queryTransactionByTransactionHash(string transactionHash);
        vector<TransactionVo> queryTransactionListByBlockHashTransactionHeight(string blockHash, uint64_t from, uint64_t size);
        unique_ptr<BlockVo> queryBlockViewByBlockHeight(uint64_t blockHeight);
        unique_ptr<UnconfirmedTransactionVo> queryUnconfirmedTransactionByTransactionHash(string transactionHash);
    };
};


#endif //HELLOWORLDCOIN_CPP_BLOCKCHAINBROWSERAPPLICATIONSERVICE_H
