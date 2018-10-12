#include <iostream>
#include <fstream>
#include <list>

// #include "Heap.h"
// #include "Sorted.h"
#include "Hash.h"

using namespace std;

/* Insert records from csv in disk using heap */
// void insertHeap()
// {
//   string line;
//   ifstream infile("data-generation/test.csv");
//   getline(infile, line);
//   Heap h("out.txt");
//   if (infile.is_open())
//   {
//     while (getline(infile, line))
//     {
//       h.ins(line.c_str());
//     }
//     infile.close();
//     h.flush();
//   }
//   std::cout << h.blockg->blocks_used << " read blocks used" << std::endl;
//   std::cout << h.blockp->blocks_used << " write blocks used" << std::endl;
// }

/* Test select a record using heap */
// void selectHeap(const char *cpf)
// {
//   // const char* cpf = "70009764623";
//   Heap h("out.txt");
//   h.sel(cpf);
//   std::cout << h.blockg->blocks_used << " read blocks used" << std::endl;
//   std::cout << h.blockp->blocks_used << " write blocks used" << std::endl;
// }

/* Test select multiple records using heap */
// void selectMultipleHeap()
// {
//   Heap h("out.txt");
//   const char **cpfs = (const char **)malloc(22);
//   cpfs[0] = "11111111111";
//   cpfs[1] = "22222222222";
//   const Record **records = h.selMultiple(cpfs, 2);
//   for (int i = 0; i < 2; i++)
//   {
//     std::cout << "Registro " << i << ": " << records[i][0] << endl;
//   }
//   std::cout << h.blockg->blocks_used << " read blocks used" << std::endl;
//   std::cout << h.blockp->blocks_used << " write blocks used" << std::endl;
// }

/* Test select range records using heap */
// void selectRangeHeap()
// {
//   Heap h("out.txt");
//   const char *cpfBegin = "11111111111";
//   const char *cpfEnd = "33333333333";
//   const Record **records = h.selRange(cpfBegin, cpfEnd);
//   for (int i = 0; i < sizeof(records); i++)
//   {
//     std::cout << "Registro " << i << ": " << records[i][0] << endl;
//   }
//   std::cout << h.blockg->blocks_used << " read blocks used" << std::endl;
//   std::cout << h.blockp->blocks_used << " write blocks used" << std::endl;
// }

/* Insert records from csv in disk using hash */
void insertHash()
{
  string line;
  ifstream infile("data-generation/test.csv");
  getline(infile, line);
  Hash ha("out.txt");
  if (infile.is_open())
  {
    while (getline(infile, line))
    {
      ha.ins(line.c_str());
    }
    infile.close();
    ha.flush();
  }
  std::cout << ha.blockg->blocks_used << " read blocks used" << std::endl;
  std::cout << ha.blockp->blocks_used << " write blocks used" << std::endl;
}

/* Test select a record using hash */
void selectHash(const char *cpf)
{
  // const char* cpf = "70009764623";
  Hash h("out.txt");
  h.sel(cpf);
  std::cout << h.blockg->blocks_used << " read blocks used" << std::endl;
  std::cout << h.blockp->blocks_used << " write blocks used" << std::endl;
}

int main(int argc, char **argv)
{
  // insertHeap();
  // selectHeap(argv[1]);
  // selectMultipleHeap();
  // selectRangeHeap();
  insertHash();
  selectHash("11111111111");
}
