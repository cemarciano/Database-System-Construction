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
  const Record ** selMultiple(const char** cpfs, const int quant);
  const Record ** selRange(const char* cpfBegin, const char* cpfEnd);
  void del(const char* cpf);
};
