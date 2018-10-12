#include "Block.h"
#include "Header.h"

class Sorted
{
private:
  uint64_t pos;
  const char* output;
  bool sorted;

public:
  Block *blockp;
  Block *blockg;
  Header* header;

  Sorted(const std::string output);
  ~Sorted();

  void ins(const char *string);
  const Record *sel(const char *cpf, bool toDelete=false);
  const Record **selMultiple(const char **cpfs, const int quant);
  const Record **selRange(const char *cpfBegin, const char *cpfEnd);
  void del(const char *cpf);

  void sort();
};
