#include "Block.h"

class Hash
{
private:
  uint64_t pos;
  std::hash<std::string> hashFunction;

public:
  Block *blockp;
  Block *blockg;
  Hash(const char *output);
  ~Hash();
  void ins(const char *string);
  void flush();
  const Record *sel(const char *cpf);
  void del(const char *cpf);
};
