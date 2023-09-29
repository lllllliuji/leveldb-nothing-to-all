#include <iostream>
#include <leveldb/db.h>
#include <leveldb/options.h>
#include <leveldb/slice.h>
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

  // 创建 WriteBatch
  leveldb::WriteBatch batch;

  // 添加操作到 WriteBatch
  batch.Put("key1", "value1");
  batch.Put("key2", "value2");
  batch.Delete("key3");

  // 批量写入
  status = db->Write(leveldb::WriteOptions(), &batch);

  if (!status.ok()) {
    std::cerr << "WriteBatch failed: " << status.ToString() << std::endl;
    delete db;
    return 1;
  }
  std::string value;
  leveldb::Slice key{"key1"};
  status = db->Get(leveldb::ReadOptions(), key, &value);
  if (status.ok()) {
    std::cout << "Get: key = " << key.data() << ", value = " << value
              << std::endl;
  }

  std::cout << "WriteBatch completed successfully." << std::endl;

  // 关闭数据库
  delete db;

  return 0;
}
