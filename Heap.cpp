#include "Heap.h"

#include <iostream>
#include <cstring>

Heap::Heap(const char* output) {
  this->blockp = new Block(output, 'w');
  this->blockg = new Block(output, 'r');
}

Heap::~Heap() {
  delete this->blockp;
  delete this->blockg;
}

void Heap::ins(const char* string) {
  const Record* record = new Record(string);
  this->blockp->write(record);
}

const Record* Heap::sel(const char* cpf) {
  this->pos = this->blockg->read(0);
  const Record* record;
  do {
    for(int i = 0; i < this->blockg->count(); i++) {
      record = this->blockg->get(i);
      bool found = 1;
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
  } while ((this->pos = this->blockg->read(this->pos)) > 0);
  std::cout << "No record with CPF = " << cpf << std::endl;
  return nullptr;
}

void Heap::del(const char* cpf) {
  Heap::sel(cpf);
  this->blockp;
}
