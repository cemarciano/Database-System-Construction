#include "Block.h"


Block::Block(const char *filename, const char mode)
{
  /* mode = 'o' -> out
     mode = 'w' -> write
     mode = 'r' -> read
     default -> read */
  this->reset(); // Reset block
  if (mode == 'o') //use in Hash
  {
    std::fstream file;
    file.open(filename); // Open file in out mode
    for(int i = 0; i<12800000; i++){
      file.put(0x00);
    }
  }
  else
  {
    if (mode == 'w')
    {                                                // If mode write
      this->file.open(filename, std::ios_base::app); // Open file in append mode
    }
    else
    {                                               // If mode read
      this->file.open(filename, std::ios_base::in); // Open file in input mode
    }
  }
  this->blocks_used = 0; // Set blocks_used to 0
}

Block::~Block()
{
  this->persist();      // Persists block in disk
  delete this->records; // Delete record array
  this->file.close();   // Close opened file (disk)
}

const Record *Block::get(const int idx)
{
  return this->records[idx];
}

uint32_t Block::count()
{
  return this->n_r; // Return number of records in this
}

void Block::write(const Record *r, const int pos)
{
  if (sizeof(Record) * (this->n_r + 1) > Block::MAX_SIZE || pos >= 0)
  {                  // If block is full
    this->persist(pos); // Persists block in disk
  }
  this->records[this->n_r] = r; // Write record in records member
  this->n_r++;                  // Increment number of records
}

int Block::read(const uint64_t pos)
{
  this->blocks_used++;
  // std::cout << "Pos = " << pos << std::endl;
  this->reset();
  this->file.seekg(pos);
  std::string line;
  // std::cout << "for i to " << (Block::MAX_SIZE / sizeof(Record)) << std::endl;
  for (uint32_t i = 0; i < (Block::MAX_SIZE / sizeof(Record)); i++)
  {
    // std::cout << "i = " << i << std::endl;
    // std::getline(this->file, line, '5');
    // std::cout << "line = " << line.c_str() << std::endl;
    if (!std::getline(this->file, line))
    {
      // std::cout << "error" << std::endl;
      if (this->file.eof())
        return 0;
      else
        return -1;
    }
    Record *record = new Record(line.c_str());
    // std::cout << "record = " << *record << std::endl;
    this->records[i] = record;
    this->n_r++;
  }
  return this->file.tellg();
}

void Block::persist(const int pos)
{
  this->blocks_used++; // Increment number of write blocks used
  for (uint32_t i = 0; i < this->n_r; i++)
  {                                    // For each record
    if (pos>=0){
      this->file.seekp(pos);
    }
    this->file << *(this->records[i]);  // Write this in disk
    delete this->records[i];           // Delete the block's record
    this->records[i] = nullptr;        // Set block's record pointer to null
  }
  this->file.flush(); // Reload file with new records
  this->reset();    // Reset block
}

void Block::reset()
{
  delete this->records;                                     // Delete all block's records
  this->records = (const Record **)malloc(Block::MAX_SIZE); // Alocate new block
  this->n_r = 0;                                            // Reset number of records
}

// Replaces register in registers[reg] with a bunch of 000's. Then writes to file in pos +- offset:
void Block::nullify(int reg, int pos, const char* path){
    // This is the null register that will replace the one we will delete:
    const char allZeroChar[] = "00000000000;00.000.000-0;0000@000.com000;00/00/0000;00000;0000000;1111";
    Record *record = new Record(allZeroChar);
    delete (this->records[reg]);  // Frees space occupied by old record
    this->records[reg] = record;  // Replaces that specific record with all 0, essentially deleting it

    // Custom-persist block to file. We write the whole block, which includes the modified register:
    std::fstream zeroFile;
    zeroFile.open(path);
    zeroFile.seekp(pos - 1072);  // pos was passed to us by the Select function so we know where to write
    // Writes all records belonging to this block:
    for (int i = 0; i < this->count(); i++){
        zeroFile << records[i][0];
        zeroFile.flush();
    }
}
