#include <iostream>
#include <fstream>

#include "Heap.h"

using namespace std;

int main(int argc, char** argv) {
  string line;
  ifstream infile("data-generation/test.csv");
  getline(infile, line);
  Heap h("out.txt");
  // Block b("out.txt");
  if (infile.is_open()) {
    while (getline(infile, line)) {
      // const Record* r = new Record(line.c_str());
      // b.write(r);
      h.ins(line.c_str());
    }
    infile.close();
  }
  //std::cout << b.write_blocks_used << " write blocks used" << std::endl;
}
