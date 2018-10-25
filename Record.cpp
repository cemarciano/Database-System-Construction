#include "Record.h"

size_t Record::csvcpy(char *dst, const char *src, size_t start, size_t sz)
{
  size_t end = start;
  size_t idx = -1;
  for (; end < start + sz; end++)
  {
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

char *Record::rtoc()
{
  char *record = new char[133];
  strcpy(record, this->cpf);
  strcat(record, this->rg);
  strcat(record, this->email);
  strcat(record, this->dt_nasc);
  strcat(record, this->sexo);
  strcat(record, this->nome);
  char *salario = new char[6];
  sprintf(salario, "%.2f", this->salario);
  strcat(record, salario);
  return record;
}

Record::Record(const char *r)
{
  int idx = 0;
  idx = this->csvcpy(this->cpf, r, idx, sizeof(this->cpf)) + 1;
  idx = this->csvcpy(this->rg, r, idx, sizeof(this->rg)) + 1;
  idx = this->csvcpy(this->email, r, idx, sizeof(this->email)) + 1;
  idx = this->csvcpy(this->dt_nasc, r, idx, sizeof(this->dt_nasc)) + 1;
  idx = this->csvcpy(this->sexo, r, idx, sizeof(this->sexo)) + 1;
  idx = this->csvcpy(this->nome, r, idx, sizeof(this->nome)) + 1;
  this->salario = std::stof(r + idx);
}

char *Record::getCpf()
{
  return this->cpf;
}

char *Record::getRg()
{
  return this->rg;
}

char *Record::getEmail()
{
  return this->email;
}

char *Record::getDt_nasc()
{
  return this->dt_nasc;
}

char *Record::getSexo()
{
  return this->sexo;
}

char *Record::getNome()
{
  return this->nome;
}

float Record::getSalario()
{
  return this->salario;
}

void Record::setCpf(char *cpf)
{
  this->csvcpy(this->cpf, cpf, 0, sizeof(this->cpf));
}

void Record::setRg(char *rg)
{
  this->csvcpy(this->rg, rg, 0, sizeof(this->rg));
}

void Record::setEmail(char *email)
{
  this->csvcpy(this->email, email, 0, sizeof(this->email));
}

void Record::setDt_nasc(char *dt_nasc)
{
  this->csvcpy(this->dt_nasc, dt_nasc, 0, sizeof(this->dt_nasc));
}

void Record::setSexo(char *sexo)
{
  this->csvcpy(this->sexo, sexo, 0, sizeof(this->sexo));
}

void Record::setNome(char *nome)
{
  this->csvcpy(this->nome, nome, 0, sizeof(this->nome));
}

void Record::setSalario(float salario)
{
  this->salario = salario;
}