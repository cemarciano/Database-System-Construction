#include <iostream>
#include <fstream>
#include <list>

#include "Heap.h"
// #include "Sorted.h"

using namespace std;

/* Insert records from csv in disk using heap */
void insertHeap()
{
  string line;
  ifstream infile("data-generation/test.csv");
  getline(infile, line);
  Heap h("out.txt");
  if (infile.is_open())
  {
    while (getline(infile, line))
    {
      h.ins(line.c_str());
    }
    infile.close();
    h.flush();
  }
  std::cout << h.blockg->blocks_used << " read blocks used" << std::endl;
  std::cout << h.blockp->blocks_used << " write blocks used" << std::endl;
}

/* Test select a record using heap */
void selectHeap(const char *cpf)
{
  // const char* cpf = "70009764623";
  Heap h("out.txt");
  h.sel(cpf);
  std::cout << h.blockg->blocks_used << " read blocks used" << std::endl;
  std::cout << h.blockp->blocks_used << " write blocks used" << std::endl;
}

/* Test select multiple records using heap */
void selectMultipleHeap()
{
  Heap h("out.txt");
  const char **cpfs = (const char **)malloc(22);
  cpfs[0] = "11111111111";
  cpfs[1] = "22222222222";
  const Record **records = h.selMultiple(cpfs, 2);
  for (int i = 0; i < 2; i++)
  {
    std::cout << "Registro " << i << ": " << records[i][0] << endl;
  }
  std::cout << h.blockg->blocks_used << " read blocks used" << std::endl;
  std::cout << h.blockp->blocks_used << " write blocks used" << std::endl;
}

/* Test select range records using heap */
void selectRangeHeap()
{
  Heap h("out.txt");
  const char *cpfBegin = "11111111111";
  const char *cpfEnd = "33333333333";
  const Record **records = h.selRange(cpfBegin, cpfEnd);
  for (int i = 0; i < sizeof(records); i++)
  {
    std::cout << "Registro " << i << ": " << records[i][0] << endl;
  }
  std::cout << h.blockg->blocks_used << " read blocks used" << std::endl;
  std::cout << h.blockp->blocks_used << " write blocks used" << std::endl;
}

/* Test select a record using heap */
void deleteHeap(const char *cpf)
{
  // const char* cpf = "70009764623";
  Heap h("out.txt");
  h.del(cpf);
  std::cout << h.blockg->blocks_used << " read blocks used" << std::endl;
  std::cout << h.blockp->blocks_used << " write blocks used" << std::endl;
}

int main(int argc, char **argv)
{
  // insertHeap();
  deleteHeap(argv[1]);
  // selectMultipleHeap();
  // selectRangeHeap();
}
