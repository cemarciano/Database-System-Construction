#include "Block.h"

class Sorted
{
private:
  uint64_t pos;
  const char* output;
  bool sorted;

public:
  Block *blockp;
  Block *blockg;

  Sorted(const char *output);
  ~Sorted();

  void ins(const char *string);
  const Record *sel(const char *cpf);
  void del(const char *cpf);

  void sort();
};
