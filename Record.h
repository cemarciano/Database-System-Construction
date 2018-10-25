#ifndef RECORD_H
#define RECORD_H

#include <string>
#include <iostream>
#include <cstring>

class Record
{
private:
  // Variáveis membro. cpf é chave primária.
  char cpf[12], rg[13], email[41], dt_nasc[11], sexo[11], nome[41];
  float salario;

public:
  // Construtor e destrutor
  Record(const char *r);

  // Métodos
  size_t csvcpy(char *dst, const char *src, size_t start, size_t sz);
  char *rtoc();

  // Getters e Setters
  void setCpf(char *cpf);
  void setRg(char *rg);
  void setEmail(char *email);
  void setDt_nasc(char *dt_nasc);
  void setSexo(char *sexo);
  void setNome(char *nome);
  void setSalario(float salario);
  char *getCpf();
  char *getRg();
  char *getEmail();
  char *getDt_nasc();
  char *getSexo();
  char *getNome();
  float getSalario();
};

#endif