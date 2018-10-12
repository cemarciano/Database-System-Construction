#include "Block.h"
#include "Header.h"

class Hash
{
private:
  Block *blockp;
  Block *blockg;
  Header* header;
  uint64_t pos;
  std::hash<std::string> hashFunction;
  

public:
  Hash(const std::string output);
  ~Hash();
  void ins(const char *record);
  const Record *sel(const char *cpf, bool toDelete=false);
  const Record **selMultiple(const char **cpfs, const int quant);
  const Record **selRange(const char *cpfBegin, const char *cpfEnd);
  void del(const char *cpf);
};
