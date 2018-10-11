#include "Hash.h"

#include <iostream>
#include <cstring>
#include <functional>

Hash::Hash(const char *output)
{
  this->blockp = new Block(output, 'w');
  this->blockg = new Block(output, 'r');
}

Hash::~Hash()
{
  delete this->blockp;
  delete this->blockg;
}

void Hash::ins(const char *record)
{
}

const Record *Hash::sel(const char *cpf)
{
  std::hash<std::string> hashFunction;
  std::string cpfString(cpf);
  this->pos = this->blockg->read(hashFunction(cpfString));
  const Record *record;
  for (int i = 0; i < this->blockg->count(); i++)
  {
    record = this->blockg->get(i);
    bool found = 1;
    for (int j = 0; j < sizeof(record->cpf); j++)
    {
      if (record->cpf[j] != cpf[j])
      {
        found = 0;
        break;
      }
    }
    if (found)
    {
      std::cout << "Found record " << *record << std::endl;
      return record;
    }
  }
  std::cout << "No record with CPF = " << cpf << std::endl;
  return nullptr;
}

void Hash::del(const char *cpf)
{
}