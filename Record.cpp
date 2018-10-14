#include "Record.h"


std::string Record::split(std::string s)
{
  std::istringstream iss(s);
  std::string token;
  std::getline(iss, token, ';');
  return token;
}

Record::Record(const std::string r)
{
  std::string fields(r);
  this->setCpf(Record::split(fields));
  fields = fields.substr((size_t) Record::split(fields).length() + 1);
  this->setRg(Record::split(fields));
  fields = fields.substr((size_t) Record::split(fields).length() + 1);
  this->setEmail(Record::split(fields));
  fields = fields.substr((size_t) Record::split(fields).length() + 1);
  this->setDt_nasc(Record::split(fields));
  fields = fields.substr((size_t) Record::split(fields).length() + 1);
  this->setSexo(Record::split(fields));
  fields = fields.substr((size_t) Record::split(fields).length() + 1);
  this->setNome(Record::split(fields));
  fields = fields.substr((size_t) Record::split(fields).length() + 1);
  this->setSalario(std::stof(Record::split(fields)));
}

std::ostream &operator<<(std::ostream &out, const Record &r)
{
  return out << r.cpf << r.rg << r.email << r.dt_nasc << r.sexo << r.nome << r.salario << std::endl;
}

// bool Record::operator<(const Record &r) const
// {
//   // std::cout << this->cpf << " " << r.cpf << std::endl;
//   for (int i = 0; i < sizeof(this->cpf); i++)
//   {
//     if (this->cpf[i] < r.cpf[i])
//     {
//       return true;
//     }
//   }
//   return false;
//   // return (this->cpf < r.cpf);
// }

// bool Record::cpfcmp(const char *cpf) const
// {
//   for (int j = 0; j < 11; j++)
//   {
//     if (this->cpf[j] != cpf[j])
//     {
//       return false;
//     }
//   }
//   return true;
// }

// bool Record::cpfinrange(const char *cpfBegin, const char *cpfEnd) const
// {
//   char cpf[12];
//   memcpy(cpf,this->cpf,11);
//   cpf[11]='\0';
//   if (strcmp(cpf,cpfBegin)>0 && strcmp(cpf,cpfEnd)<0)
//   {
//     return true;
//   }
//   return false;
// }

std::string Record::getCpf()
{
  return this->cpf;
}

std::string Record::getRg()
{
  return this->rg;
}

std::string Record::getEmail()
{
  return this->email;
}

std::string Record::getDt_nasc()
{
  return this->dt_nasc;
}

std::string Record::getSexo()
{
  return this->sexo;
}

std::string Record::getNome()
{
  return this->nome;
}

float Record::getSalario()
{
  return this->salario;
}

void Record::setCpf(std::string cpf)
{
  if (cpf.length() == 11)
    this->cpf = cpf;
  else
    std::cout << "O campo CPF precisa de exatamente 11 dígitos." << std::endl;
}

void Record::setRg(std::string rg)
{
  if (rg.length() == 12)
    this->rg = rg;
  else
    std::cout << "O campo RG precisa de exatamente 12 dígitos." << std::endl;
}

void Record::setEmail(std::string email)
{
  if (email.length() <= 40)
  {
    this->email = email;
    for (int i = 0; i < 40 - email.length(); i++)
      this->email += " ";
  }
  else
    std::cout << "O campo EMAIL só pode ter 40 caracteres ou menos.";
}

void Record::setDt_nasc(std::string dt_nasc)
{
  if (dt_nasc.length() == 10)
    this->dt_nasc = dt_nasc;
  else
    std::cout << "O campo DT_NASC deve ser inserido no seguinte formato: dd/mm/aaaa.";
}

void Record::setSexo(std::string sexo)
{
  if (sexo.length() <= 9)
  {
    this->sexo = sexo;
    for (int i = 0; i < 9 - sexo.length(); i++)
      this->sexo += " ";
  }
  else
    std::cout << "O campo SEXO deve ter menos de 10 caracteres." << std::endl;
}

void Record::setNome(std::string nome)
{
  if (nome.length() <= 40)
  {
    this->nome = nome;
    for (int i = 0; i < 40 - nome.length(); i++)
      this->nome += " ";
  }
  else
    std::cout << "O campo NOME deve ter menos de 41 caracteres." << std::endl;
}

void Record::setSalario(float salario)
{
  this->salario = salario;
}