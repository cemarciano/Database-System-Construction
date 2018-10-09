#include "Record.h"

#include <fstream>
#include <stdint.h>

typedef uint32_t u_int32_t;

class Block {
private:
  std::fstream    file;
  const Record**  records;
  u_int32_t       n_r;

  void persist();
  void reset();

public:
  static const int64_t MAX_SIZE = 1024;

  u_int32_t blocks_used;

  Block(const char* filename, const char mode);
  ~Block();

  const Record* get(const int idx);

  void write(const Record* r);
  int read(const u_int64_t pos);
};
