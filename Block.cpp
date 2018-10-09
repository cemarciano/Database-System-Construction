#include "Block.h"

#include <iostream>

Block::Block(const char* filename, const char mode) {
  /* mode = 'w' -> write
     mode = 'r' -> read
     default -> read */
  this->reset();                                    // Reset block
  if (mode == 'w') {                                // If mode write
    this->file.open(filename, std::ios_base::app);  // Open file in append mode
  } else {                                          // If mode read
    this->file.open(filename, std::ios_base::in);   // Open file in input mode
  }
  this->blocks_used = 0;                      // Set blocks_used to 0
}

Block::~Block() {
  this->persist();      // Persists block in disk
  delete this->records; // Delete record array
  this->file.close();   // Close opened file (disk)
}

const Record* Block::get(const int idx) {
  return this->records[idx];
}

void Block::write(const Record* r) {
  if (sizeof(Record) * (this->n_r + 1) > Block::MAX_SIZE) { // If block is full
    this->persist();                                        // Persists block in disk
  }
  this->records[this->n_r] = r;                             // Write record in records member
  this->n_r++;                                              // Increment number of records
}

int Block::read(const u_int64_t pos) {
  this->reset();
  this->file.seekg(pos);
  std::string line;
  for (u_int32_t i = 0; i < (Block::MAX_SIZE / sizeof(Record)); i++) {
    if (!getline(this->file, line)) {
      if (this->file.eof()) return 0;
      else return -1;
    }
    Record* record = new Record(line.c_str());
    this->records[i] = record;
  }
  return this->file.peek();
}

void Block::persist() {
  this->blocks_used++;                        // Increment number of write blocks used
  for (u_int32_t i = 0; i < this->n_r; i++) { // For each record
    this->file << *(this->records[i]);        // Write this in disk
    delete this->records[i];                  // Delete the block's record
    this->records[i] = nullptr;               // Set block's record pointer to null
  }
  this->file.flush();                         //
  this->reset();                              // Reset block
}

void Block::reset() {
  delete this->records;                                     // Delete all block's records
  this->records = (const Record**) malloc(Block::MAX_SIZE); // Alocate new block 
  this->n_r = 0;                                            // Reset number of records
}
