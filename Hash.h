#include "Block.h"

class Hash
{
private:
  Block *blockp;
  Block *blockg;
  uint64_t pos;

public:
  Hash(const char *output);
  ~Hash();
  void ins(const char *record);
  const Record *sel(const char *cpf);
  void del(const char *cpf);
};
