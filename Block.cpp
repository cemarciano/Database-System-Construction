#include "Block.h"

#include <iostream>

Block::Block(const char* filename) {
  this->reset();
  this->file.open(filename, std::ios_base::app);
  this->write_blocks_used = 0;
}

Block::~Block() {
  this->persist();
  delete this->records;
  this->file.close();
}

void Block::write(const Record* r) {
  if (sizeof(Record) * (this->n_r + 1) > Block::MAX_SIZE) {
    this->persist();
  }
  this->records[this->n_r] = r;
  this->n_r++;
}

void Block::persist() {
  this->write_blocks_used++;
  for (u_int32_t i = 0; i < this->n_r; i++) {
    this->file << *(this->records[i]);
    delete this->records[i];
    this->records[i] = nullptr;
  }
  this->file.flush();
  this->reset();
}

void Block::reset() {
  delete this->records;
  this->records = (const Record**) malloc(Block::MAX_SIZE);
  this->n_r = 0;
}