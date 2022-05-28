//
// author x.king xdotking@gmail.com
//

#include "KvDbUtil.h"
#include <leveldb/db.h>
#include "leveldb/write_batch.h"
#include <iostream>


namespace KvDbUtil{
    void KvWriteBatch::delete0(vector<unsigned char> key) {
        KvWrite kvWrite;
        kvWrite.key = key;
        kvWrite.kvWriteAction = KvWriteAction::DELETE00;
        this->kvWrites.push_back(kvWrite);
    }

    void KvWriteBatch::put(vector<unsigned char> key, vector<unsigned char> value) {
        KvWrite kvWrite;
        kvWrite.key = key;
        kvWrite.value = value;
        kvWrite.kvWriteAction = KvWriteAction::ADD00;
        this->kvWrites.push_back(kvWrite);
    }


    leveldb::WriteBatch toLevelDbWriteBatch(KvWriteBatch &batch) {
        leveldb::WriteBatch writeBatch;
        vector<KvWrite> kvWrites = batch.kvWrites;
        vector<KvWrite>::iterator it = kvWrites.begin();
        for(; it != kvWrites.end(); ++it)
        {
            KvWrite kvWrite = *it;
            std::string key(kvWrite.key.begin(), kvWrite.key.end());
            std::string value(kvWrite.value.begin(), kvWrite.value.end());

            if(kvWrite.kvWriteAction == KvWriteAction::ADD00){
                writeBatch.Put(key,value);
            } else if(kvWrite.kvWriteAction == KvWriteAction::DELETE00){
                writeBatch.Delete(key);
            }
        }
        return writeBatch;
    }


    mutex mutex;
    void put(string dbPath, vector<unsigned char> bytesKey, vector<unsigned char> bytesValue){
        mutex.lock();
        std::string key(bytesKey.begin(), bytesKey.end());
        std::string value(bytesValue.begin(), bytesValue.end());

        leveldb::DB* db;
        leveldb::Options options;
        options.create_if_missing = true;
        leveldb::Status status = leveldb::DB::Open(options, dbPath, &db);
        db->Put(leveldb::WriteOptions(), key, value);
        delete db;
        mutex.unlock();
    }
    void delete0(string dbPath, vector<unsigned char> bytesKey){
        mutex.lock();
        std::string key(bytesKey.begin(), bytesKey.end());

        leveldb::DB* db;
        leveldb::Options options;
        options.create_if_missing = true;
        leveldb::Status status = leveldb::DB::Open(options, dbPath, &db);
        db->Delete(leveldb::WriteOptions(), key);
        delete db;
        mutex.unlock();
    }
    vector<unsigned char> get(string dbPath, vector<unsigned char> bytesKey){
        mutex.lock();
        std::string key(bytesKey.begin(), bytesKey.end());
        std::string value;

        leveldb::DB* db;
        leveldb::Options options;
        options.create_if_missing = true;
        leveldb::Status status = leveldb::DB::Open(options, dbPath, &db);
        db->Get(leveldb::ReadOptions(), key, &value);
        delete db;
        mutex.unlock();
        std::vector<unsigned char> bytesValue(value.begin(), value.end());
        return bytesValue;
    }
    vector<vector<unsigned char>> gets(string dbPath, uint64_t from, uint64_t size){
        mutex.lock();
        vector<vector<unsigned char>> resp;
        leveldb::DB* db;
        leveldb::Options options;
        options.create_if_missing = true;
        leveldb::Status status = leveldb::DB::Open(options, dbPath, &db);
        leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
        for (it->SeekToFirst(); it->Valid(); it->Next()) {
            string key = it->key().ToString();
            string value = it->value().ToString();
            std::vector<unsigned char> bytesValue(value.begin(), value.end());
            resp.push_back(bytesValue);
        }
        delete it;
        delete db;
        mutex.unlock();
        return resp;
    }
    void write(string dbPath, KvWriteBatch kvWriteBatch){
        mutex.lock();
        leveldb::WriteBatch batch = toLevelDbWriteBatch(kvWriteBatch);
        leveldb::DB* db;
        leveldb::Options options;
        options.create_if_missing = true;
        leveldb::Status status = leveldb::DB::Open(options, dbPath, &db);
        db->Write(leveldb::WriteOptions(), &batch);
        delete db;
        mutex.unlock();
    }
}

#if 0
int main()
{
    string key = "111";
    vector<unsigned char> bytesKey(key.begin(), key.end());
    std::vector<unsigned char> bytesValue = KvDbUtil::get("E:\\logs", bytesKey);
    cout << "value is : " << string(bytesValue.begin(),bytesValue.end())<< endl;

    string value = "111";
    std::vector<unsigned char> bytesValue2(value.begin(), value.end());
    KvDbUtil::put("E:\\logs", bytesKey,bytesValue2);

    bytesValue = KvDbUtil::get("E:\\logs", bytesKey);
    cout << "value is : " <<  string(bytesValue.begin(),bytesValue.end())<< endl;
}
#endif
