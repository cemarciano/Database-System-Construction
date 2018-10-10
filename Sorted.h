#include "Block.h"

class Sorted {
private:
  Block *blockp;
  Block *blockg;
  uint64_t pos;
public:
  Sorted(const char* output);
  ~Sorted();
  void ins(const char* record);
  const Record * sel(const char* cpf);
  void del(const char* cpf);
};
