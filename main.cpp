#include <iostream>
#include <fstream>

#include "Heap.h"

using namespace std;

void insertHeap() {
  string line;
  ifstream infile("data-generation/data.csv");
  getline(infile, line);
  Heap h("out.txt");
  if (infile.is_open()) {
    while (getline(infile, line)) {
      h.ins(line.c_str());
    }
    infile.close();
  }
  std::cout << h.blockg->blocks_used << " read blocks used" << std::endl;
  std::cout << h.blockp->blocks_used << " write blocks used" << std::endl;
}

void selectHeap(const char* cpf) {
  // const char* cpf = "70009764623";
  Heap h("out.txt");
  h.sel(cpf);
  std::cout << h.blockg->blocks_used << " read blocks used" << std::endl;
  std::cout << h.blockp->blocks_used << " write blocks used" << std::endl;
}

int main(int argc, char** argv) {
  // insertHeap();
  selectHeap(argv[1]);
}
