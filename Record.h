#include<string>

class Record { 
  char cpf[11], rg[12], email[40], dt_nasc[10], sexo[10], nome[40];
  float salary;

  size_t csvcpy(char* dst, const char* src, size_t start, size_t sz);

public:
  Record(const char string[]);
  friend std::ostream& operator<< (std::ostream &out, const Record &r);
};
