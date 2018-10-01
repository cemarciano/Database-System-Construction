#include "Record.h"

#include <fstream>

class Block {
  static const int64_t MAX_SIZE = 1024;
  
  std::ofstream   file;
  const Record**  records;
  u_int32_t       n_r;

  void persist();
  void reset();

public:
  u_int32_t write_blocks_used;

  Block(const char* filename);
  ~Block();

  void write(const Record* r);
};
