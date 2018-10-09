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
  // this->pos = 0;
  // const Record* record;
  // while (this->blockg->read(this->pos) > 0) {
  //   for(int i = 0; i < Block::MAX_SIZE / sizeof(Record); i += sizeof(Record)) {
  //     record = this->blockg->get(i);
  //     if(!strcmp(record->get_cpf(), cpf)) return record;
  //   }
  //   this->pos += Block::MAX_SIZE;
  // }
  // return nullptr;
}

void Heap::del(const char* cpf) {
  Heap::sel(cpf);
  this->blockp;
}
