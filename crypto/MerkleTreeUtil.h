//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_MERKLETREEUTIL_H
#define HELLOWORLDCOIN_CPP_MERKLETREEUTIL_H
#include <string>
#include <vector>
using namespace std;


namespace MerkleTreeUtil {

    vector<unsigned char> calculateMerkleTreeRoot(vector<vector<unsigned char>> datas);
};


#endif //HELLOWORLDCOIN_CPP_MERKLETREEUTIL_H
