#include <string>

class Record {
private:
  char cpf[11], rg[12], email[40], dt_nasc[10], sexo[10], nome[40];
  float salario;

  size_t csvcpy(char* dst, const char* src, size_t start, size_t sz);

public:
  Record(const char string[]);
  friend std::ostream& operator<< (std::ostream &out, const Record &r);
  char const * get_cpf();
  char *get_rg();
  char *get_email();
  char *get_dt_nasc();
  char *get_sexo();
  char *get_nome();
  float get_salario();
};
