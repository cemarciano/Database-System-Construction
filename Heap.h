#include "Block.h"

class Heap {
private:
  uint64_t pos;

public:
  Block *blockp;
  Block *blockg;

  Heap(const char* output);
  ~Heap();
  
  void ins(const char* record);
  const Record * sel(const char* cpf);
  void del(const char* cpf);
};
