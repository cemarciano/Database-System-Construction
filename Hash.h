#include "Block.h"
#include "Header.h"

class Hash
{
private:
  Header* header;
  uint64_t pos;
  std::hash<std::string> hashFunction;

public:
  Block *blockp;
  Block *blockg;
  Hash();
  ~Hash();
  void ins(const char *string);
  void flush();
  const Record **selMultiple(const char **cpfs, const int quant);
  const Record **selRange(const char *cpfBegin, const char *cpfEnd);
  const Record *sel(const char *cpf, bool toDelete=false);
  void del(const char *cpf);
};
