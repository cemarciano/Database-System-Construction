#include "Record.h"

#include <iostream>
#include <cstring>

std::ostream &print(std::ostream &out, const char *str, size_t sz)
{
  for (size_t i = 0; i < sz; i++)
  {
    out << str[i];
    // printf("%c", str[i]);
  }
  out << ';';
  return out;
  // printf("\n");
}

Record::Record(const char *string)
{
  int idx = 0;
  // std::cout << "cpf\t";
  memcpy(this->cpf, string, sizeof(this->cpf));
  // print(std::cout, this->cpf, sizeof(this->cpf));
  // std::cout << std::endl;
  idx += sizeof(this->cpf) + 1;
  // std::cout << "rg\t";
  memcpy(this->rg, string + idx, sizeof(this->rg));
  // print(std::cout, this->rg, sizeof(this->rg));
  // std::cout << std::endl;
  idx += sizeof(this->rg) + 1;
  // std::cout << "email\t";
  idx = this->csvcpy(this->email, string, idx, sizeof(this->email)) + 1;
  // print(std::cout, this->email, sizeof(this->email));
  // std::cout << std::endl;
  // std::cout << "dt_nasc\t";
  memcpy(this->dt_nasc, string + idx, sizeof(this->dt_nasc));
  // print(std::cout, this->dt_nasc, sizeof(this->dt_nasc));
  // std::cout << std::endl;
  idx += sizeof(this->dt_nasc) + 1;
  // std::cout << "sexo\t";
  idx = this->csvcpy(this->sexo, string, idx, sizeof(this->sexo)) + 1;
  // print(std::cout, this->sexo, sizeof(this->sexo));
  // std::cout << std::endl;
  // std::cout << "nome\t";
  idx = this->csvcpy(this->nome, string, idx, sizeof(this->nome)) + 1;
  // print(std::cout, this->nome, sizeof(this->nome));
  // std::cout << std::endl;
  this->salario = std::stof(string + idx);
  // std::cout << "salario\t" << this->salario << std::endl;
}

std::ostream &operator<<(std::ostream &out, const Record &r)
{
  print(out, r.cpf, sizeof(r.cpf));
  print(out, r.rg, sizeof(r.rg));
  print(out, r.email, sizeof(r.email));
  print(out, r.dt_nasc, sizeof(r.dt_nasc));
  print(out, r.sexo, sizeof(r.sexo));
  print(out, r.nome, sizeof(r.nome));
  return out << r.salario << std::endl;
}

bool Record::operator<(const Record& r) const
{
  // std::cout << this->cpf << " " << r.cpf << std::endl;
  for (int i = 0; i < sizeof(this->cpf); i++) {
    if (this->cpf[i] < r.cpf[i]) {
      return true;
    }
  }
  return false;
  // return (this->cpf < r.cpf);
}

size_t Record::csvcpy(char *dst, const char *src, size_t start, size_t sz)
{
  size_t end = start;
  size_t idx = -1;
  for (; end < start + sz; end++)
  {
    // std::cout << end << "/" << src[end] << std::endl;
    if (src[end] == ';')
    {
      idx = end - start;
      memcpy(dst, src + start, idx);
      break;
    }
  }
  if (idx == -1)
    memcpy(dst, src + start, end - start);
  else
    memset(dst + idx, 0x00, sz - idx);
  return end;
}