#include "Block.h"

class Heap {
private:
  Block *blockp;
  Block *blockg;
  u_int64_t pos;
public:
  Heap(const char* output);
  ~Heap();
  void ins(const char* record);
  const Record * sel(const char* cpf);
  void del(const char* cpf);
};
