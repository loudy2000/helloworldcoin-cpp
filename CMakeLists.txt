cmake_minimum_required(VERSION 3.0)
project(helloworldcoin_cpp)

set(CMAKE_CXX_STANDARD 14)
set(project_name "helloworldcoin_cpp")


add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_executable(
        ${project_name}
        crypto/Sha256Util.cpp crypto/Sha256Util.h crypto/Ripemd160Util.cpp crypto/Ripemd160Util.h crypto/Base58Util.cpp crypto/Base58Util.h crypto/AccountUtil.cpp crypto/AccountUtil.h crypto/MerkleTreeUtil.cpp crypto/MerkleTreeUtil.h
        util/ByteUtil.cpp util/ByteUtil.h  util/MathUtil.cpp util/MathUtil.h util/FileUtil.cpp util/FileUtil.h util/NetUtil.cpp util/NetUtil.h util/SystemUtil.cpp util/SystemUtil.h util/ThreadUtil.cpp util/ThreadUtil.h util/TimeUtil.cpp util/TimeUtil.h util/StringUtil.cpp util/StringUtil.h util/LogUtil.cpp util/LogUtil.h util/JsonUtil.cpp util/JsonUtil.h util/KvDbUtil.cpp util/KvDbUtil.h util/EncodeDecodeTool.cpp util/EncodeDecodeTool.h util/StringsUtil.cpp util/StringsUtil.h
        core/model/model.cpp core/model/model.h
        setting/BlockSetting.cpp setting/BlockSetting.h setting/GenesisBlockSetting.cpp setting/GenesisBlockSetting.h setting/IncentiveSetting.cpp setting/IncentiveSetting.h setting/NetworkSetting.cpp setting/NetworkSetting.h setting/ScriptSetting.cpp setting/ScriptSetting.h setting/TransactionSetting.cpp setting/TransactionSetting.h
        netcoredto/netcoredto.cpp netcoredto/netcoredto.h
        core/tool/BlockTool.cpp core/tool/BlockTool.h core/tool/BlockDtoTool.cpp core/tool/BlockDtoTool.h core/tool/TransactionDtoTool.cpp core/tool/TransactionDtoTool.h core/tool/ScriptDtoTool.cpp core/tool/ScriptDtoTool.h core/tool/BlockchainDatabaseKeyTool.cpp core/tool/BlockchainDatabaseKeyTool.h core/tool/Model2DtoTool.cpp core/tool/Model2DtoTool.h core/tool/DtoSizeTool.cpp core/tool/DtoSizeTool.h core/tool/ResourceTool.cpp core/tool/ResourceTool.h core/tool/SizeTool.cpp core/tool/SizeTool.h core/tool/ScriptTool.cpp core/tool/ScriptTool.h core/tool/StructureTool.cpp core/tool/StructureTool.h core/tool/TransactionTool.cpp core/tool/TransactionTool.h
        core/VirtualMachine.cpp core/VirtualMachine.h core/Wallet.cpp core/Wallet.h core/UnconfirmedTransactionDatabase.cpp core/UnconfirmedTransactionDatabase.h core/Miner.cpp core/Miner.h core/Incentive.cpp core/Incentive.h core/CoreConfiguration.cpp core/CoreConfiguration.h core/Consensus.cpp core/Consensus.h core/BlockchainDatabase.cpp core/BlockchainDatabase.h core/BlockchainCore.cpp core/BlockchainCore.h core/BlockchainCoreFactory.cpp core/BlockchainCoreFactory.h
        netcore/netcorepo/netcorepo.cpp netcore/netcorepo/netcorepo.h
        netcore/netcoremodel/netcoremodel.cpp netcore/netcoremodel/netcoremodel.h
        netcore/netcoreconfiguration/NetCoreConfiguration.cpp netcore/netcoreconfiguration/NetCoreConfiguration.h
        netcore/netcoredao/NodeDao.cpp netcore/netcoredao/NodeDao.h
        netcore/netcoreservice/NodeService.cpp netcore/netcoreservice/NodeService.h
        netcore/netcoreserver/NodeServer.cpp netcore/netcoreserver/NodeServer.h netcore/BlockBroadcaster.cpp netcore/BlockBroadcaster.h
        netcoreclient/NodeClient.cpp netcoreclient/NodeClient.h netcore/NodeCleaner.cpp netcore/NodeCleaner.h netcore/NodeSearcher.cpp netcore/NodeSearcher.h netcore/SeedNodeInitializer.cpp netcore/SeedNodeInitializer.h netcore/UnconfirmedTransactionsSearcher.cpp netcore/UnconfirmedTransactionsSearcher.h netcore/NodeBroadcaster.cpp netcore/NodeBroadcaster.h netcore/BlockchainHeightBroadcaster.cpp netcore/BlockchainHeightBroadcaster.h netcore/BlockchainHeightSearcher.cpp netcore/BlockchainHeightSearcher.h netcore/BlockSearcher.cpp netcore/BlockSearcher.h netcore/BlockchainNetCore.cpp netcore/BlockchainNetCore.h netcore/BlockchainNetCoreFactory.cpp netcore/BlockchainNetCoreFactory.h
        application/main.cpp application/test.cpp
        application/vo/accountvo.cpp application/vo/accountvo.h application/vo/blockvo.cpp application/vo/blockvo.h application/vo/frameworkvo.cpp application/vo/frameworkvo.h application/vo/nodevo.cpp application/vo/nodevo.h application/vo/synchronizervo.cpp application/vo/synchronizervo.h application/vo/transactionvo.cpp application/vo/transactionvo.h application/vo/walletvo.cpp application/vo/walletvo.h application/vo/minervo.cpp application/vo/minervo.h
        application/vo/WalletApplicationApi/WalletApplicationApi.cpp application/vo/WalletApplicationApi/WalletApplicationApi.h application/vo/NodeConsoleApplicationApi/NodeConsoleApplicationApi.cpp application/vo/NodeConsoleApplicationApi/NodeConsoleApplicationApi.h application/vo/BlockchainBrowserApplicationApi/BlockchainBrowserApplicationApi.cpp application/vo/BlockchainBrowserApplicationApi/BlockchainBrowserApplicationApi.h
        application/controller/CommonController.cpp application/controller/CommonController.h application/controller/NodeConsoleApplicationController.cpp application/controller/NodeConsoleApplicationController.h application/controller/WalletApplicationController.cpp application/controller/WalletApplicationController.h application/controller/BlockchainBrowserApplicationController.cpp application/controller/BlockchainBrowserApplicationController.h
        application/service/WalletApplicationService.cpp application/service/WalletApplicationService.h application/service/BlockchainBrowserApplicationService.cpp application/service/BlockchainBrowserApplicationService.h
)




include_directories(thirdpart/openssl/include thirdpart/leveldb/include)

if(WIN32)
    target_link_libraries(
            ${project_name}
            ${CMAKE_SOURCE_DIR}/thirdpart/openssl/lib/windows/x86/libcrypto.lib ${CMAKE_SOURCE_DIR}/thirdpart/openssl/lib/windows/x86/libssl.lib
            ${CMAKE_SOURCE_DIR}/thirdpart/leveldb/lib/windows/x86/leveldb.lib
    )
    file(COPY ${CMAKE_SOURCE_DIR}/thirdpart/openssl/lib/windows/x86/libcrypto-1_1.dll DESTINATION ${CMAKE_BUILD_DIRECTORY}/)
    file(COPY ${CMAKE_SOURCE_DIR}/thirdpart/openssl/lib/windows/x86/libssl-1_1.dll DESTINATION ${CMAKE_BUILD_DIRECTORY}/)
endif()

if(APPLE)
    target_link_libraries(${project_name} ${CMAKE_SOURCE_DIR}/thirdpart/openssl/lib/mac/libcrypto.1.1.dylib ${CMAKE_SOURCE_DIR}/thirdpart/openssl/lib/mac/libssl.1.1.dylib)
endif()
