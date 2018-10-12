#include "Hash.h"

#include <iostream>
#include <cstring>
#include <functional>

Hash::Hash(const char *output)
{
  this->blockp = new Block(output, 'o');
  this->blockg = new Block(output, 'r');
}

Hash::~Hash()
{
  delete this->blockp;
  delete this->blockg;
}

void Hash::ins(const char *string)
{
  const Record *record = new Record(string);
  char cpf[11];
  memcpy(cpf,record->cpf,11);
  cpf[11]='\0';
  std::string cpfString(cpf);
  this->blockp->write(record,hashFunction(cpfString)/1000000000000000);
  std::cout<<cpfString<<std::endl;
  std::cout<<hashFunction(cpfString)/1000000000000000<<std::endl;
}

void Hash::flush()
{
  this->blockp->persist();
}

const Record *Hash::sel(const char *cpf)
{
  std::cout<<1<<std::endl;
  std::string cpfString(cpf);
  this->pos = this->blockg->read(hashFunction(cpfString)/1000000000000000);
  std::cout<<cpfString<<std::endl<<hashFunction(cpfString)/1000000000000000<<std::endl;
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