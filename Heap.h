#include "Block.h"
#include "Header.h"

class Heap
{
private:
  uint64_t pos; // Reading block position in the file

public:
  Block *blockp;
  Block *blockg;
  Header* header;

  Heap(const std::string);
  ~Heap();

  void flush();

  void ins(const char *record);
  const Record *sel(const char *cpf, bool toDelete=false);
  const Record **selMultiple(const char **cpfs, const int quant);
  const Record **selRange(const char *cpfBegin, const char *cpfEnd);
  void del(const char *cpf);
};
