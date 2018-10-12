#include "Sorted.h"

#include <iostream>
#include <cstring>
#include <list>

#define SORTED_DISK "Sorted.cbd"

Sorted::Sorted()
{
  const std::string dataFilename = SORTED_DISK;
  const std::string headerFilename = SORTED_DISK"h";
  this->blockp = new Block(dataFilename.c_str(), 'w');
  this->blockg = new Block(dataFilename.c_str(), 'r');
  this->header = new Header(headerFilename);
  this->sort();
  this->sorted = true;
}

Sorted::~Sorted()
{
  delete this->blockp;
  delete this->blockg;
}

void Sorted::flush()
{
  this->blockp->persist();
  this->header->write();
  if (this->sorted == false){
    this->sort();
    this->sorted = true;
  }
}



void Sorted::ins(const char *string)
{
  const Record *record = new Record(string); // Initialize record to be inserted
  this->blockp->write(record);               // Write record in writing block
  this->sorted = false;
}

const Record *Sorted::sel(const char *cpf, bool toDelete)
{
  if (!this->sorted) {
    this->sort();
    this->sorted = true;
  }
  int64_t start = 0;
  int64_t end = this->blockg->blocks_used * Block::MAX_SIZE;
  const Record *record;
  do
  {
    this->pos = this->blockg->read((start + end) / 2);
    record = this->blockg->get(0); //checks if first record is larger
    bool found = 1;
    bool searchAgain = 0;
    for (int j = 0; j < sizeof(record->cpf); j++)
    {
      if (record->cpf[j] != cpf[j])
      {
        found = 0;
        break;
      }
      if (record->cpf[j] > cpf[j])
      {
        end = this->pos;
        searchAgain = 1;
        break;
      }
    }
    if (found)
    {
      if (toDelete){
        // Replace the current register with 000's:
        this->blockg->nullify(0, this->pos, SORTED_DISK);
        std::cout << "Deleted";
      }
      else{
        std::cout<<"Found";
      }
      // Finishes printing:
      std::cout << " record " << *record << " in block position " << 0 << std::endl;
      return record;
    }
    else
    {
      if (searchAgain)
      {
        continue;
      }
    }
    record = this->blockg->get(this->blockg->count() - 1); // Checks if last record is smaller
    found = 1;
    searchAgain = 0;
    for (int j = 0; j < sizeof(record->cpf); j++)
    {
      if (record->cpf[j] != cpf[j])
      {
        found = 0;
        break;
      }
      if (record->cpf[j] < cpf[j])
      {
        start = this->pos;
        searchAgain = 1;
        break;
      }
    }
    if (found)
    {
      if (toDelete){
        // Replace the current register with 000's:
        this->blockg->nullify(this->blockg->count() - 1, this->pos, SORTED_DISK);
        std::cout << "Deleted";
      }
      else{
        std::cout<<"Found";
      }
      // Finishes printing:
      std::cout << " record " << *record << " in block position " << this->blockg->count() - 1 << std::endl;
      return record;
    }
    else
    {
      if (searchAgain)
      {
        continue;
      }
    }
    for (int i = 1; i < this->blockg->count() - 1; i++)
    { //check other records
      record = this->blockg->get(i);
      found = 1;
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
        this->blockg->nullify(i, this->pos, SORTED_DISK);
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
  } while ((start + end) / 2 != this->pos);
  std::cout << "No record with CPF = " << cpf << std::endl;
  return nullptr;
}

std::vector<const Record *>Sorted::selMultiple(const char **cpfs, const int quant)
{
  std::vector<const Record*>foundRecords;
  for (int i = 0; i < quant; i++)
  {
    foundRecords.push_back(Sorted::sel(cpfs[i]));        
  }
  return foundRecords;
}

std::vector<const Record *>Sorted::selRange(const char *cpfBegin, const char *cpfEnd)
{
  this->pos = this->blockg->read(0);
  const Record *record;
  std::vector<const Record*>foundRecords;
  int found = 0;
  
  // do
  // {
  //   for (int i = 0; i < this->blockg->count(); i++)
  //   {
  //     record = this->blockg->get(i);
  //     for (int j = 0; j < sizeof(record->cpf); j++)
  //     {
  //       if (record->cpfinrange(cpfBegin, cpfEnd))
  //       {
  //         foundRecords.push_back(record);  
  //         found++;
  //         break;
  //       }
  //     }
  //   }
  // } while ((this->pos = this->blockg->read(this->pos)) > 0);
  // return foundRecords;
}

void Sorted::del(const char *cpf)
{
  // Seek and destroy:
  Sorted::sel(cpf, true);
}

void Sorted::sort() {
  std::string line;
  std::ifstream outputFile(SORTED_DISK, std::ios_base::in);
  std::list<Record> records;
  if (outputFile.is_open()) {
    while (std::getline(outputFile, line)){
      Record r(line.c_str());
      records.push_back(r);
    }
    outputFile.close();
  }
  records.sort();
  std::ofstream sortedOutputFile(SORTED_DISK, std::ios_base::out);
  for (std::list<Record>::iterator it = records.begin(); it != records.end(); it++) {
    sortedOutputFile << *it;
  }
}