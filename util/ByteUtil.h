//
// author x.king xdotking@gmail.com
//

#ifndef UNTITLED_BYTEUTIL_H
#define UNTITLED_BYTEUTIL_H

#include <string>
#include <vector>
using namespace std;

namespace ByteUtil {

    extern int BYTE8_BYTE_COUNT;

    string bytesToHexString(vector<unsigned char> bytes);
    vector<unsigned char> hexStringToBytes(const string& hex);

    vector<unsigned char> uint64ToBytes(uint64_t number);
    uint64_t bytesToUint64(vector<unsigned char> bytes);

    vector<unsigned char> stringToUtf8Bytes(string stringValue);
    string utf8BytesToString(vector<unsigned char> bytesValue);

    vector<unsigned char> booleanToUtf8Bytes(bool booleanValue);
    bool utf8BytesToBoolean(vector<unsigned char> bytesValue);

    vector<unsigned char> concatenate(vector<unsigned char> bytes1,vector<unsigned char> bytes2);
    vector<unsigned char> concatenate3(vector<unsigned char> bytes1,vector<unsigned char> bytes2,vector<unsigned char> bytes3);
    vector<unsigned char> concatenate4(vector<unsigned char> bytes1,vector<unsigned char> bytes2,vector<unsigned char> bytes3,vector<unsigned char> bytes4);

    vector<unsigned char> concatenateLength(vector<unsigned char> value);
    vector<unsigned char> flat(vector<vector<unsigned char>> values);
    vector<unsigned char> flatAndConcatenateLength(vector<vector<unsigned char>> values);

    vector<unsigned char> copy(vector<unsigned char> sourceBytes, uint64_t startPosition, uint64_t length);
    void copyTo(vector<unsigned char> sourceBytes, uint64_t sourceStartPosition, uint64_t length, vector<unsigned char> &destinationBytes, uint64_t destinationStartPosition);

    bool equals(vector<unsigned char> bytes1, vector<unsigned char> bytes2);
    vector<unsigned char> random32Bytes();

    //TODO java,go
    bool greatThan(string number1,string number2);
    string multiply(string number1,string number2);
    string divide(string number1,string number2);
};


#endif //UNTITLED_BYTEUTIL_H
