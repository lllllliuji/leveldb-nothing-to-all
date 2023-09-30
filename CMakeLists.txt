cmake_minimum_required(VERSION 3.10)
project(leveldb_playground)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)

# 寻找 LevelDB 库
find_package(leveldb REQUIRED)

# 添加可执行文件
add_executable(basic_operation basic_operation.cpp)

# 链接 LevelDB 库
target_link_libraries(basic_operation PRIVATE leveldb)

# 添加可执行文件
add_executable(write_batch write_batch.cpp)

# 链接 LevelDB 库
target_link_libraries(write_batch PRIVATE leveldb)

# 添加可执行文件
add_executable(db_iterator db_iterator.cpp)

# 链接 LevelDB 库
target_link_libraries(db_iterator PRIVATE leveldb)

# 添加可执行文件
add_executable(cache_and_filter cache_and_filter.cpp)

# 链接 LevelDB 库
target_link_libraries(cache_and_filter PRIVATE leveldb)

