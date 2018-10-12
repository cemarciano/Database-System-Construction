#include "Hash.h"

#include <iostream>
#include <cstring>
#include <functional>

#define HASH_DISK "Hash.cbd"

Hash::Hash()
{
  const std::string dataFilename = HASH_DISK;
  const std::string headerFilename = HASH_DISK"h";
  this->blockp = new Block(dataFilename.c_str(), 'o'); // Initialize writing block
  this->blockg = new Block(dataFilename.c_str(), 'r'); // Initialize reading block
  this->header = new Header(headerFilename);
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

const Record *Hash::sel(const char *cpf, bool toDelete)
{
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
      if (toDelete)
      {
        // Replace the current register with 000's:
        this->blockg->nullify(i, this->pos, HASH_DISK);
        std::cout << "Deleted";
      }
      else
      {
        std::cout << "Found";
      }
      // Finishes printing:
      std::cout << " record " << *record << " in block position " << i << std::endl;
      return record;
    }
  }
  std::cout << "No record with CPF = " << cpf << std::endl;
  return nullptr;
}

std::vector<const Record *>Hash::selMultiple(const char **cpfs, const int quant)
{
  const Record *record;
  std::vector<const Record *>foundRecords;
  int found = 0;
  for (int n = 0; n < quant; n++)
  {
    std::string cpfString(cpfs[n]);
    this->pos = this->blockg->read(hashFunction(cpfString));
    for (int i = 0; i < this->blockg->count(); i++)
    {
      record = this->blockg->get(i);
      if (record->cpfcmp(cpfs[n]))
      {
        foundRecords.push_back(record);
        found++;
        break;
      }
      if (found == quant)
      {
        std::cout << "All records found " << std::endl;
        return foundRecords;
      }
    }
    std::cout << "Not all records found " << std::endl;
    return foundRecords;
  }
}

std::vector<const Record *>Hash::selRange(const char *cpfBegin, const char *cpfEnd)
{
  this->pos = this->blockg->read(0);
  const Record *record;
  std::vector<const Record *>foundRecords;
  int found = 0;
  do
  {
    for (int i = 0; i < this->blockg->count(); i++)
    {
      record = this->blockg->get(i);
      for (int j = 0; j < sizeof(record->cpf); j++)
      {
        if (record->cpfinrange(cpfBegin, cpfEnd))
        {
          foundRecords.push_back(record);
          found++;
          break;
        }
      }
    }
  } while ((this->pos = this->blockg->read(this->pos)) > 0);
  return foundRecords;
}

void Hash::del(const char *cpf)
{
  // Seek and destroy:
  Hash::sel(cpf, true);
}