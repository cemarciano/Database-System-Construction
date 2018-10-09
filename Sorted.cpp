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

void ins(const char* record){

}

const Record * sel(const char* cpf){

}

void del(const char* cpf){
    
}