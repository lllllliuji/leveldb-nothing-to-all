#include <iostream>
#include <leveldb/cache.h>
#include <leveldb/db.h>
#include <leveldb/filter_policy.h>

int main() {

  // 设置数据库选项，包括 Cache 和 FilterPolicy
  leveldb::Options options;
  options.create_if_missing = true;

  // 创建 Cache，用于缓存数据块
  const size_t cache_size = 1024 * 1024; // 1 MB
  options.block_cache = leveldb::NewLRUCache(cache_size);

  // 创建 FilterPolicy，用于过滤不匹配的键
  options.filter_policy = leveldb::NewBloomFilterPolicy(10); // 10 bits per key

  // 打开 LevelDB 数据库
  leveldb::DB *db;
  leveldb::Status status = leveldb::DB::Open(options, "/tmp/testdb", &db);

  if (!status.ok()) {
    std::cerr << "Unable to open database: " << status.ToString() << std::endl;
    return 1;
  }

  // 向数据库中插入一些数据
  leveldb::WriteOptions write_options;
  db->Put(write_options, "key1", "value1");
  db->Put(write_options, "key2", "value2");
  db->Put(write_options, "key3", "value3");
  db->Put(write_options, "key4", "value4");

  // 查询数据库
  leveldb::ReadOptions read_options;

  leveldb::Iterator *it = db->NewIterator(read_options);
  for (it->SeekToFirst(); it->Valid(); it->Next()) {
    std::cout << "Key: " << it->key().ToString()
              << ", Value: " << it->value().ToString() << std::endl;
  }

  // 释放资源
  delete it;
  delete db;

  return 0;
}
