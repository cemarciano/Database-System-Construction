#ifndef BLOCK_H
#define BLOCK_H

#include "Record.h"
#include <fstream>
#include <stdint.h>
#include <iostream>

class Block
{
private:
  // Variáveis membro. Arquivo de disco, lista de registros e número de registros
  std::FILE *pFile;
  const Record **records;
  int n_r;

  // Métodos
  void reset();

public:
  // Variáveis membro
  static const int MAX_SIZE = 1024;
  int blocks_used;

  // Construtor e destrutor
  Block(const char *filename);
  ~Block();

  // Métodos
  const Record *get(const int idx);
  int count();
  void write(const Record *r, const int pos = -1);
  int read(const int pos);
  void nullify(int reg, int pos);
  void persist(const int pos = -1);
};

#endif