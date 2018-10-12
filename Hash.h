#include "Block.h"
#include "Header.h"

class Hash
{
private:
  Block *blockp;
  Block *blockg;
  Header* header;
  uint64_t pos;
  

public:
  Hash(const std::string output);
  ~Hash();
  void ins(const char *record);
  const Record *sel(const char *cpf, bool toDelete=false);
  void del(const char *cpf);
};
