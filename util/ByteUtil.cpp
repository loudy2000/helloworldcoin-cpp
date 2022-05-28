//
// author x.king xdotking@gmail.com
//

#include "ByteUtil.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <assert.h>
#include <openssl/bn.h>
#include <algorithm>
#include <cctype>

using namespace std;

int ByteUtil::BYTE8_BYTE_COUNT = 8;

string uchar2hex(unsigned char inchar)
{
    ostringstream oss (ostringstream::out);
    oss << setw(2) << setfill('0') << hex << (int)(inchar);
    return oss.str();
}
string uchars2hex(unsigned char* uchars,int length)
{
    string hexString = "";
    for (int i = 0; i < length; i++) {
        hexString += uchar2hex(uchars[i]);
    }
    return hexString;
}
string lowercase(string value) {
    string result(value);
    std::transform(value.begin(), value.end(), result.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return result;
}
vector<unsigned char> ByteUtil::hexStringToBytes(const string& hex) {
    vector<unsigned char> bytes;
    for (unsigned int i = 0; i < hex.length(); i += 2) {
        std::string byteString = hex.substr(i, 2);
        unsigned char byte = (unsigned char) strtol(byteString.c_str(), NULL, 16);
        bytes.push_back(byte);
    }
    return bytes;
}
string ByteUtil::bytesToHexString(vector<unsigned char> bytes) {
    return uchars2hex(&bytes[0],bytes.size());
}

vector<unsigned char> ByteUtil::uint64ToBytes(uint64_t number){
    vector<unsigned char> bytes;
    bytes.push_back((unsigned char)(number >> 8*7));
    bytes.push_back((unsigned char)(number >> 8*6));
    bytes.push_back((unsigned char)(number >> 8*5));
    bytes.push_back((unsigned char)(number >> 8*4));
    bytes.push_back((unsigned char)(number >> 8*3));
    bytes.push_back((unsigned char)(number >> 8*2));
    bytes.push_back((unsigned char)(number >> 8*1));
    bytes.push_back((unsigned char)(number >> 8*0));
    return bytes;
}
uint64_t ByteUtil::bytesToUint64(vector<unsigned char> bytes){
    unsigned long long result = strtoull(uchars2hex(&bytes[0],bytes.size()).c_str(), NULL, 16);
    return result;
}

vector<unsigned char> ByteUtil::copy(vector<unsigned char> sourceBytes, uint64_t startPosition, uint64_t length){
    vector<unsigned char> bytes;
    for(int i=startPosition;i<startPosition+length;i++){
        bytes.push_back(sourceBytes[i]);
    }
    return bytes;
}
void ByteUtil::copyTo(vector<unsigned char> sourceBytes, uint64_t sourceStartPosition, uint64_t length, vector<unsigned char> &destinationBytes, uint64_t destinationStartPosition){
    while (destinationBytes.size()<destinationStartPosition+length){
        destinationBytes.push_back(0x00);
    }
    for(int i=0;i<length;i++){
        destinationBytes[destinationStartPosition+i] = sourceBytes[sourceStartPosition+i];
    }
}
vector<unsigned char> ByteUtil::concatenate(vector<unsigned char> bytes1,vector<unsigned char> bytes2){
    vector<unsigned char> bytes;
    bytes.insert(bytes.end(), bytes1.begin(), bytes1.end());
    bytes.insert(bytes.end(), bytes2.begin(), bytes2.end());
    return bytes;
}
vector<unsigned char> ByteUtil::concatenate3(vector<unsigned char> bytes1,vector<unsigned char> bytes2,vector<unsigned char> bytes3){
    vector<unsigned char> bytes;
    bytes.insert(bytes.end(), bytes1.begin(), bytes1.end());
    bytes.insert(bytes.end(), bytes2.begin(), bytes2.end());
    bytes.insert(bytes.end(), bytes3.begin(), bytes3.end());
    return bytes;
}
vector<unsigned char> ByteUtil::concatenate4(vector<unsigned char> bytes1,vector<unsigned char> bytes2,vector<unsigned char> bytes3,vector<unsigned char> bytes4){
    vector<unsigned char> bytes;
    bytes.insert(bytes.end(), bytes1.begin(), bytes1.end());
    bytes.insert(bytes.end(), bytes2.begin(), bytes2.end());
    bytes.insert(bytes.end(), bytes3.begin(), bytes3.end());
    bytes.insert(bytes.end(), bytes4.begin(), bytes4.end());
    return bytes;
}

vector<unsigned char> ByteUtil::stringToUtf8Bytes(string stringValue){
    //TODO make sure really utf8 bytes?
    vector<unsigned char> bytes(stringValue.begin(), stringValue.end());
    return bytes;
}
string ByteUtil::utf8BytesToString(vector<unsigned char> bytesValue){
    string value(bytesValue.begin(), bytesValue.end());
    return value;
}
vector<unsigned char> ByteUtil::booleanToUtf8Bytes(bool booleanValue){
    return ByteUtil::stringToUtf8Bytes(booleanValue ? "t" : "f");
}
bool ByteUtil::utf8BytesToBoolean(vector<unsigned char> bytesValue){
    return ByteUtil::utf8BytesToString(bytesValue)=="t"?true:false;
}
vector<unsigned char> ByteUtil::random32Bytes(){
    vector<unsigned char> bytes;
    for(int i=0;i<32;i++){
        bytes.push_back((unsigned char)rand());
    }
    return bytes;
}

vector<unsigned char> ByteUtil::concatenateLength(vector<unsigned char> value){
    return ByteUtil::concatenate(ByteUtil::uint64ToBytes(value.size()),value);
}
vector<unsigned char> ByteUtil::flat(vector<vector<unsigned char>> values){
    vector<unsigned char> concatBytes;
    for(vector<unsigned char> value:values){
        concatBytes = ByteUtil::concatenate(concatBytes,value);
    }
    return concatBytes;
}
vector<unsigned char> ByteUtil::flatAndConcatenateLength(vector<vector<unsigned char>> values){
    vector<unsigned char> flatBytes = flat(values);
    return concatenateLength(flatBytes);
}
bool ByteUtil::equals(vector<unsigned char> bytes1, vector<unsigned char> bytes2){
    if(bytes1.size() != bytes2.size()){
        return false;
    }
    return std::equal(bytes1.begin(), bytes1.begin() + bytes1.size(), bytes2.begin());
}
bool ByteUtil::greatThan(string number1,string number2){
    BIGNUM *bignum1 = BN_new();
    BN_hex2bn(&bignum1,number1.c_str());
    BIGNUM *bignum2 = BN_new();
    BN_hex2bn(&bignum2,number2.c_str());

    int compareValue = BN_cmp(bignum1,bignum2);

    BN_free(bignum1);
    BN_free(bignum2);
    return compareValue>0;
}
string ByteUtil::multiply(string number1,string number2){
    BIGNUM *bignum1 = BN_new();
    BN_hex2bn(&bignum1,number1.c_str());
    BIGNUM *bignum2 = BN_new();
    BN_hex2bn(&bignum2,number2.c_str());
    BIGNUM *bignumResult = BN_new();
    BN_CTX *bnCtx = BN_CTX_new();
    BN_mul(bignumResult,bignum1,bignum2,bnCtx);
    char* stringResult = BN_bn2hex(bignumResult);

    BN_free(bignum1);
    BN_free(bignum2);
    BN_free(bignumResult);
    BN_CTX_free(bnCtx);
    return lowercase(stringResult);
}
string ByteUtil::divide(string number1,string number2){
    BIGNUM *bignum1 = BN_new();
    BN_hex2bn(&bignum1,number1.c_str());
    BIGNUM *bignum2 = BN_new();
    BN_hex2bn(&bignum2,number2.c_str());
    BIGNUM *bignumResult = BN_new();
    BIGNUM *rem = BN_new();
    BN_CTX *bnCtx = BN_CTX_new();


    BN_div(bignumResult,rem,bignum1,bignum2,bnCtx);
    char* stringResult = BN_bn2hex(bignumResult);

    BN_free(bignum1);
    BN_free(bignum2);
    BN_free(bignumResult);
    BN_free(rem);
    BN_CTX_free(bnCtx);

    return lowercase(stringResult);
}
#if 0
int main()
{
    uint64_t value = uint64_t(123456789);
    assert("00000000075bcd15" == ByteUtil::bytesToHexString(ByteUtil::uint64ToBytes(value)));
    assert(value == ByteUtil::bytesToUint64(ByteUtil::uint64ToBytes(value)));


    assert(ByteUtil::greatThan("13A59145513A591413A591445513A591","BA59145513A591413A591445513A5CC"));
    assert("e4d21ab54f24702a5177329a64542453672d4a2d7c48cd0a56bf3be421648c" == ByteUtil::multiply("13A59145513A591413A591445513A591","BA59145513A591413A591445513A5CC"));
    assert("1afd7d" == ByteUtil::divide("13A59145513A591413A591445513A591","BA59145513A591413A59144551"));
}
#endif
