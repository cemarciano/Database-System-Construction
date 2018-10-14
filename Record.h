#ifndef RECORD_H
#define RECORD_H

#include <string>
#include <iostream>
#include <cstring>
#include <sstream>

class Record
{
private:
  size_t csvcpy(char *dst, const char *src, size_t start, size_t sz);
  std::string cpf, rg, email, dt_nasc, sexo, nome;
  float salario;

public:
  // char cpf[11], rg[12], email[40], dt_nasc[10], sexo[10], nome[40];
  // float salario;

  Record(const std::string r);
  bool cpfcmp(const char *cpf) const;
  bool cpfinrange(const char *cpf1, const char *cpf2) const;
  std::string split(std::string s);

  void setCpf(std::string cpf);
  void setRg(std::string rg);
  void setEmail(std::string email);
  void setDt_nasc(std::string dt_nasc);
  void setSexo(std::string sexo);
  void setNome(std::string nome);
  void setSalario(float salario);
  std::string getCpf();
  std::string getRg();
  std::string getEmail();
  std::string getDt_nasc();
  std::string getSexo();
  std::string getNome();
  float getSalario();

  friend std::ostream &operator<<(std::ostream &out, const Record &r);
  bool operator<(const Record &r) const;
};

#endif