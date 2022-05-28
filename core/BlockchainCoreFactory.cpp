//
// author x.king xdotking@gmail.com
//

#include "BlockchainCoreFactory.h"
#include "tool/ResourceTool.h"
using namespace core;

namespace core{
    namespace BlockchainCoreFactory {
        BlockchainCore* createDefaultBlockchainCore(){
            return createBlockchainCore(ResourceTool::getDataRootPath());
        }
        BlockchainCore* createBlockchainCore(string corePath){
            CoreConfiguration *coreConfiguration = new CoreConfiguration(corePath);
            Incentive *incentive = new Incentive();
            Consensus *consensus = new Consensus();
            VirtualMachine *virtualMachine = new VirtualMachine();
            BlockchainDatabase *blockchainDatabase = new BlockchainDatabase(coreConfiguration,incentive,consensus,virtualMachine);


            UnconfirmedTransactionDatabase *unconfirmedTransactionDatabase = new UnconfirmedTransactionDatabase(coreConfiguration);
            Wallet *wallet = new Wallet(coreConfiguration,blockchainDatabase);
            Miner *miner = new Miner(coreConfiguration,wallet,blockchainDatabase,unconfirmedTransactionDatabase);
            BlockchainCore *blockchainCore = new BlockchainCore(coreConfiguration,blockchainDatabase,unconfirmedTransactionDatabase,wallet,miner);
            return blockchainCore;
        }
    };
}
