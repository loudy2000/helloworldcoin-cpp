//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_NETCOREMODEL_H
#define HELLOWORLDCOIN_CPP_NETCOREMODEL_H

#include <string>
#include <cstdint>
using namespace std;

namespace netcoremodel {
    struct Node {
        string ip;
        uint64_t blockchainHeight;
    };
};


#endif //HELLOWORLDCOIN_CPP_NETCOREMODEL_H
