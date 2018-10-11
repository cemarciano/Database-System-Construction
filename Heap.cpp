#include "Heap.h"

#include <iostream>
#include <cstring>

Heap::Heap(const char *output)
{
  this->blockp = new Block(output, 'w'); // Initialize writing block
  this->blockg = new Block(output, 'r'); // Initialize reading block
}

Heap::~Heap()
{
  delete this->blockp; // Delete writing block
  delete this->blockg; // Delete reading block
}

void Heap::flush() {
  this->blockp->persist();
}

void Heap::ins(const char *string)
{
  const Record *record = new Record(string); // Initialize record to be inserted
  this->blockp->write(record);               // Write record in writing block
}

const Record *Heap::sel(const char *cpf)
{
  this->pos = this->blockg->read(0); // Use reading block to read the disk
  const Record *record;              // Initialize a empty record
  do
  {
    for (int i = 0; i < this->blockg->count(); i++)
    {                                // For i = 0 to i = number of reading block's records
      record = this->blockg->get(i); // Put idx record from block into record variable
      bool found = 1;                // Initialize boolean found as true
      for (int j = 0; j < sizeof(record->cpf); j++)
      {
        if (record->cpf[j] != cpf[j])
        { // Verify if record's cpf is different from query's cpf
          found = 0;
          break;
        }
      }
      if (found)
      { // If found record with query's cpf return the record
        std::cout << "Found record " << *record << std::endl;
        return record;
      }
    }
  } while ((this->pos = this->blockg->read(this->pos)) > 0); // While have records in block
  std::cout << "No record with CPF = " << cpf << std::endl;
  return nullptr;
}

const Record **Heap::selMultiple(const char **cpfs, const int quant)
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
      for (int j = 0; j < quant; j++)
      {
        if (!strcmp(record->cpf, cpfs[j]))
        {
          /* TO CORRECT */
          // newFoundRecords=(const Record**) malloc((found+1)*sizeof(Record)); //adds new record to found records
          // for (int k = 0; k < found; k++){
          //   newFoundRecords[k]=&foundRecords[k];
          // }
          // newFoundRecords[found]=&record;
          // record=newFoundRecords;
          // found ++;
          // break;
        }
      }
      if (found == quant)
      {
        std::cout << "All records found " << std::endl;
        return foundRecords;
      }
    }
  } while ((this->pos = this->blockg->read(this->pos)) > 0);
  std::cout << "Not all records found " << std::endl;
  return foundRecords;
}

const Record **Heap::selRange(const char *cpfBegin, const char *cpfEnd)
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
        if (strcmp(record->cpf, cpfBegin) > 0 && strcmp(record->cpf, cpfEnd) < 0)
        {
          /* TO CORRECT */
          // newFoundRecords=(const Record**) malloc((found+1)*sizeof(Record)); //adds new record to found records
          // for (int k = 0; k < found; k++){
          //   newFoundRecords[k]=&foundRecords[k];
          // }
          // newFoundRecords[found]=&record;
          // record=newFoundRecords;
          // found ++;
          // break;
        }
      }
    }
  } while ((this->pos = this->blockg->read(this->pos)) > 0);
  return foundRecords;
}

void Heap::del(const char *cpf)
{
  Heap::sel(cpf);
  // this->blockp;
}
