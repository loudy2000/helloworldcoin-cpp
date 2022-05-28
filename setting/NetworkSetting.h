//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_NETWORKSETTING_H
#define HELLOWORLDCOIN_CPP_NETWORKSETTING_H


#include <cstdint>
#include <string>
#include <vector>

using namespace std;

namespace NetworkSetting {

    //network port
    extern uint64_t PORT;
    //seed nodes
    extern vector<string> SEED_NODES;
};


#endif //HELLOWORLDCOIN_CPP_NETWORKSETTING_H
