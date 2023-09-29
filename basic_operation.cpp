#include "leveldb/db.h"
#include "leveldb/options.h"
#include <iostream>
#include <leveldb/slice.h>

int main() {
  leveldb::DB *db;
  leveldb::Options options;
  options.create_if_missing = true;

  leveldb::Status status = leveldb::DB::Open(options, "/tmp/testdb", &db);

  if (status.ok()) {
    std::cout << "LevelDB opened successfully." << std::endl;
    // delete db;
  } else {
    std::cerr << "Unable to open LevelDB: " << status.ToString() << std::endl;
  }
  auto readoptions = leveldb::ReadOptions();
  auto writeoptions = leveldb::WriteOptions();
  leveldb::Slice key{"hello"};
  std::string value;
  status = db->Get(readoptions, key, &value);
  if (!status.ok()) {
    std::cout << key.data() << ": " << status.ToString() << std::endl;
  }
  status = db->Put(writeoptions, key, "world");
  if (status.ok()) {
    std::cout << key.data() << ": write successfully" << std::endl;
    status = db->Get(readoptions, key, &value);
    if (status.ok()) {
      std::cout << "Get: "
                << "Key = " << key.data() << ", "
                << "value = " << value << std::endl;
    }
  }
  status = db->Delete(writeoptions, key);
  if (status.ok()) {
    std::cout << key.data() << ": deleted" << std::endl;
  }
  status = db->Get(readoptions, key, &value);
  if (!status.ok()) {
    std::cout << key.data() << ": " << status.ToString() << std::endl;
  }
  delete db;
  return 0;
}
