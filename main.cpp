#include <iostream>
#include <fstream>

#include "Block.h"

using namespace std;

int main(int argc, char** argv) {
  string line;
  ifstream infile("data-generation/data.csv");
  getline(infile, line);
  Block b("out.txt");
  if (infile.is_open()) {
    while (getline(infile, line)) {
      const Record* r = new Record(line.c_str());
      b.write(r);
    }
    infile.close();
  }
  std::cout << b.write_blocks_used << " write blocks used" << std::endl;
}
