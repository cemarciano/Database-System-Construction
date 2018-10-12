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
      if (toDelete)
      {
        // Replace the current register with 000's:
        this->blockg->nullify(i, this->pos);
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

const Record **Hash::selMultiple(const char **cpfs, const int quant)
{
  const Record *record;
  const Record **foundRecords;
  const Record **newFoundRecords;
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
        newFoundRecords = (const Record **)malloc((found + 1) * sizeof(Record)); //adds new record to found records
        for (int k = 0; k < found; k++)
        {
          newFoundRecords[k] = foundRecords[k];
        }
        newFoundRecords[found] = record;
        foundRecords = newFoundRecords;
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

const Record **Hash::selRange(const char *cpfBegin, const char *cpfEnd)
{
  this->pos = this->blockg->read(0);
  const Record *record;
  const Record **foundRecords;
  const Record **newFoundRecords;
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
          newFoundRecords = (const Record **)malloc((found + 1) * sizeof(Record)); //adds new record to found records
          for (int k = 0; k < found; k++)
          {
            newFoundRecords[k] = foundRecords[k];
          }
          newFoundRecords[found] = record;
          foundRecords = newFoundRecords;
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