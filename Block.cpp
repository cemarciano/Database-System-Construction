#include "Block.h"

Block::Block(const char *filename)
{
    this->reset();
    if (this->pFile = fopen(filename, "r+"))
        ;
    else
        this->pFile = fopen(filename, "w");
    this->blocks_used = 0;
}

// Block::~Block()
// {
//     this->persist();
//     delete this->records;
//     this->file.close();
// }

// const Record *Block::get(const int idx)
// {
//     return this->records[idx];
// }

int Block::count()
{
    return this->n_r;
}

// void Block::write(const Record *r, const int pos)
// {
//     if (sizeof(Record) * (this->n_r + 1) > Block::MAX_SIZE || pos >= 0)
//     {
//         this->persist(pos);
//     }
//     this->records[this->n_r] = r;
//     this->n_r++;
// }

// int Block::read(const int pos)
// {
//     this->blocks_used++;
//     this->reset();
//     this->file.seekg(pos);
//     std::string line;
//     for (int i = 0; i < (Block::MAX_SIZE / sizeof(Record)); i++)
//     {
//         if (!std::getline(this->file, line))
//         {
//             if (this->file.eof())
//                 return 0;
//             else
//                 return -1;
//         }
//         Record *record = new Record(line.c_str());
//         this->records[i] = record;
//         this->n_r++;
//     }
//     return this->file.tellg();
// }

void Block::persist(const int pos)
{
    this->blocks_used++;
    for (int i = 0; i < this->n_r; i++)
    {
        fseek(this->pFile, pos, SEEK_SET);
        // fputs(this->records[i]->rtoc(), this->pFile);   PQ NAO FUNCIONA?
        // this->file << *(this->records[i]);
        // delete this->records[i];
        this->records[i] = nullptr;
    }
    fflush(this->pFile);
    // this->file.flush();
    this->reset();
}

void Block::reset()
{
    delete this->records;
    this->records = (const Record **)malloc(Block::MAX_SIZE);
    this->n_r = 0;
}

// Replaces register in registers[reg] with a bunch of 000's. Then writes to file in pos +- offset:
// void Block::nullify(int reg, int pos)
// {
//     // This is the null register that will replace the one we will delete:
//     const std::string allZeroChar = "00000000000;00.000.000-0;0000@000.com000;00/00/0000;00000;0000000;1111";
//     Record *record = new Record(allZeroChar);
//     delete (this->records[reg]); // Frees space occupied by old record
//     this->records[reg] = record; // Replaces that specific record with all 0, essentially deleting it

//     // Custom-persist block to file. We write the whole block, which includes the modified register:
//     this->file.seekp(pos - 1072); // pos was passed to us by the Select function so we know where to write
//     // Writes all records belonging to this block:
//     for (int i = 0; i < this->count(); i++)
//     {
//         this->file << records[i][0];
//         this->file.flush();
//     }
// }
