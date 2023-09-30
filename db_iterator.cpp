#include <iostream>
#include <leveldb/db.h>
#include <leveldb/options.h>
#include <leveldb/write_batch.h>

int main() {
  // 打开或者创建 LevelDB 数据库
  leveldb::DB *db;
  leveldb::Options options;
  options.create_if_missing = true;
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

  // 创建向前遍历的迭代器
  leveldb::Iterator *forward_it = db->NewIterator(leveldb::ReadOptions());

  std::cout << "Forward Iteration:" << std::endl;
  for (forward_it->SeekToFirst(); forward_it->Valid(); forward_it->Next()) {
    std::cout << "Key: " << forward_it->key().ToString()
              << ", Value: " << forward_it->value().ToString() << std::endl;
  }

  delete forward_it;

  // 创建向后遍历的迭代器
  leveldb::ReadOptions read_options;
  read_options.fill_cache = false; // 关闭缓存以便支持向后遍历
  leveldb::Iterator *backward_it = db->NewIterator(read_options);

  std::cout << "Backward Iteration:" << std::endl;
  for (backward_it->SeekToLast(); backward_it->Valid(); backward_it->Prev()) {
    std::cout << "Key: " << backward_it->key().ToString()
              << ", Value: " << backward_it->value().ToString() << std::endl;
  }

  delete backward_it;

  // 范围遍历
  leveldb::Range range("key2", "key4");
  leveldb::Iterator *range_it = db->NewIterator(leveldb::ReadOptions());

  std::cout << "Range Iteration:" << std::endl;
  for (range_it->Seek(range.start);
       range_it->Valid() &&
       range_it->key().ToString() <= range.limit.ToString();
       range_it->Next()) {
    std::cout << "Key: " << range_it->key().ToString()
              << ", Value: " << range_it->value().ToString() << std::endl;
  }

  delete range_it;

  // 关闭数据库
  delete db;

  return 0;
}
