//
// author x.king xdotking@gmail.com
//

#ifndef HELLOWORLDCOIN_CPP_ENCODEDECODETOOL_H
#define HELLOWORLDCOIN_CPP_ENCODEDECODETOOL_H

#include <vector>
#include "JsonUtil.h"
#include "ByteUtil.h"

using namespace std;

namespace EncodeDecodeTool {

    template <typename T>
    inline vector<unsigned char> const encode (T const object)
    {
        return ByteUtil::stringToUtf8Bytes(JsonUtil::toString(object));
    }

    template <typename T>
    inline T const decode (vector<unsigned char> bytesObject, T const& object)
    {
        return JsonUtil::toObject(ByteUtil::utf8BytesToString(bytesObject),object);
    }

};


#endif //HELLOWORLDCOIN_CPP_ENCODEDECODETOOL_H
