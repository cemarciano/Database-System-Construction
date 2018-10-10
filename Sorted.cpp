#include "Sorted.h"

#include <iostream>
#include <cstring>

Sorted::Sorted(const char* output) {
  this->blockp = new Block(output, 'w');
  this->blockg = new Block(output, 'r');
}

Sorted::~Sorted() {
  delete this->blockp;
  delete this->blockg;
}

void Sorted::ins(const char* record){

}

const Record* Sorted::sel(const char* cpf){
  int64_t start=0, end=blockg.blocks_used*Block::MAX_SIZE;
  const Record* record;
  do {
    this->pos = this->blockg->read((start+end)/2);
    record = this->blockg->get(0); //checks if first record is larger
    bool found = 1;
    bool searchAgain = 0;
    for (int j = 0; j < sizeof(record->cpf); j++) {
      if (record->cpf[j] != cpf[j]) {
        found = 0;
        break;
      }
      if (record->cpf[j] > cpf[j]) {
        end = this->pos;
        searchAgain = 1;
        break;
      }
    }
    if (found) {
      std::cout << "Found record " << *record << std::endl;
      return record;
    }
    else{
      if (searchAgain){
        continue;
      }
    }
    record = this->blockg->get(this->blockg->count()-1); //checks if last record is smaller
    found = 1;
    searchAgain=0;
    for (int j = 0; j < sizeof(record->cpf); j++) {
      if (record->cpf[j] != cpf[j]) {
        found = 0;
        break;
      }
      if (record->cpf[j] < cpf[j]) {
        start = this->pos;
        searchAgain=1;
        break;
      }
    }
    if (found) {
      std::cout << "Found record " << *record << std::endl;
      return record;
    }
    else{
      if (searchAgain){
        continue;
      }
    }
    for(int i = 1; i < this->blockg->count()-1; i++) { //check other records
      record = this->blockg->get(i);
      found = 1;
      for (int j = 0; j < sizeof(record->cpf); j++) {
        if (record->cpf[j] != cpf[j]) {
          found = 0;
          break;
        }
      }
      if (found) {
        std::cout << "Found record " << *record << std::endl;
        return record;
      }
    }
  } while ((start+end)/2!=this->pos);
  std::cout << "No record with CPF = " << cpf << std::endl;
  return nullptr;
}

void Sorted::del(const char* cpf){
    
}