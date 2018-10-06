#include "Record.h"

#include <iostream>
#include <cstring>

std::ostream& print(std::ostream& out, const char* str, size_t sz) {
  for (size_t i = 0; i < sz; i++) {
    out << str[i];
    // printf("%c", str[i]);
  }
  out << ';';
  return out;
  // printf("\n");
}

Record::Record(const char* string) {
  int8_t idx = 0;
  memcpy(this->cpf, string, sizeof(this->cpf));
  idx += sizeof(this->cpf) + 1;
  memcpy(this->rg, string + idx, sizeof(this->rg));
  idx += sizeof(this->rg) + 1;
  idx = this->csvcpy(this->email, string, idx, sizeof(this->email)) + 1;
  memcpy(this->dt_nasc, string + idx, sizeof(this->dt_nasc));
  idx += sizeof(this->dt_nasc) + 1;
  idx = this->csvcpy(this->sexo, string, idx, sizeof(this->sexo)) + 1;
  idx = this->csvcpy(this->nome, string, idx, sizeof(this->nome)) + 1;
  this->salary = std::stof(string + idx);
}

std::ostream& operator<<(std::ostream& out, const Record& r) {
  print(out, r.cpf, sizeof(r.cpf));
  print(out, r.rg, sizeof(r.rg));
  print(out, r.email, sizeof(r.email));
  print(out, r.dt_nasc, sizeof(r.dt_nasc));
  print(out, r.sexo, sizeof(r.sexo));
  print(out, r.nome, sizeof(r.nome));
  return out << r.salary << std::endl;
}

size_t Record::csvcpy(char* dst, const char* src, size_t start, size_t sz) {
  size_t end = start;
  size_t idx;
  for (; end < start + sz; end++) {
    if (src[end] == ';') {
      idx = end - start;
      memcpy(dst, src + start, idx);
      break;
    }
  }
  memset(dst + idx, '\0', sz - idx);
  return end;
}