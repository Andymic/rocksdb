#include <cstdio>
#include <string>
#include <iostream>
#include "rocksdb/db.h"
#include "rocksdb/slice.h"
#include "rocksdb/options.h"

using namespace rocksdb;

std::string kDBPath = "/tmp/rocksdb_lsmtrie_example";

int main() {
  DB* db;
  Options options;

  options.IncreaseParallelism();
  options.OptimizeLevelStyleCompaction();

  options.create_if_missing = true;
  options.statistics = rocksdb::CreateDBStatistics();

  Status s = DB::Open(options, kDBPath, &db);
  assert(s.ok());

  s = db->Put(WriteOptions(), "lsm", "trie");
  assert(s.ok());
  std::string value;
  
  s = db->Get(ReadOptions(), "lsm", &value);
  assert(s.ok());
  assert(value == "trie");
	
  std::cout<<options.statistics.get()->ToString()<<std::endl;
  
  delete db;

  return 0;
}
