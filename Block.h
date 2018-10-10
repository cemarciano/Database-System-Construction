#include "Record.h"

#include <fstream>
#include <stdint.h>

typedef uint32_t uint32_t;

class Block {
private:
  std::fstream    file;
  const Record**  records;
  uint32_t       n_r;

  void persist();
  void reset();

public:
  static const int64_t MAX_SIZE = 1024;

  uint32_t blocks_used;

  Block(const char* filename, const char mode);
  ~Block();

  const Record* get(const int idx);
  uint32_t count();

  void write(const Record* r);
  int read(const uint64_t offset);
};
