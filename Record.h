#include <string>

class Record {
private:
  size_t csvcpy(char* dst, const char* src, size_t start, size_t sz);

public:
  char cpf[11], rg[12], email[40], dt_nasc[10], sexo[10], nome[40];
  float salario;
  
  Record(const char string[]);

  friend std::ostream& operator<< (std::ostream &out, const Record &r);
};
