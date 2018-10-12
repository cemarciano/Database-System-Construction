#include "Hash.h"

#include <iostream>
#include <cstring>
#include <functional>

Hash::Hash(const std::string output)
{
  const std::string dataFilename = output + ".cbd";
  const std::string headerFilename = output + ".cbdh";
  this->blockp = new Block(dataFilename.c_str(), 'w'); // Initialize writing block
  this->blockg = new Block(dataFilename.c_str(), 'r'); // Initialize reading block
  this->header = new Header(headerFilename);
}

Hash::~Hash()
{
  delete this->blockp;
  delete this->blockg;
}

void Hash::ins(const char *record)
{
}

const Record *Hash::sel(const char *cpf, bool toDelete)
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
      if (toDelete){
        // Replace the current register with 000's:
        this->blockg->nullify(i, this->pos);
        std::cout << "Deleted";
      }
      else{
        std::cout<<"Found";
      }
      // Finishes printing:
      std::cout << " record " << *record << " in block position " << i << std::endl;
      return record;
    }
  }
  std::cout << "No record with CPF = " << cpf << std::endl;
  return nullptr;
}

void Hash::del(const char *cpf)
{
  // Seek and destroy:
  Hash::sel(cpf, true);
}