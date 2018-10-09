#include "Hash.h"

#include <iostream>
#include <cstring>

Hash::Hash(const char* output) {
  this->blockp = new Block(output, 'w');
  this->blockg = new Block(output, 'r');
}

Hash::~Hash() {
  delete this->blockp;
  delete this->blockg;
}

void ins(const char* record){
    
}

const Record * sel(const char* cpf){
    
}

void del(const char* cpf){
    
}