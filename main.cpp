#include <iostream>
#include <fstream>
#include <list>

#include "Heap.h"
#include "Sorted.h"
#include "Hash.h"

#define DATA_STRUCT Sorted

using namespace std;

void printBlocks(DATA_STRUCT* db)
{
  cout << db->blockg->blocks_used << " read blocks used" << endl;
  cout << db->blockp->blocks_used << " write blocks used" << endl;
}

void testInsert(DATA_STRUCT* db)
{
  string line;
  ifstream infile("data-generation/test.csv");
  getline(infile, line);
  if (infile.is_open())
  {
    while (getline(infile, line))
    {
      db->ins(line.c_str());
    }
    infile.close();
    db->flush();
  }
  printBlocks(db);
}

void testSelect(DATA_STRUCT* db)
{
  const char *cpf = "55555555555";
  db->sel(cpf);
  printBlocks(db);
}

void testSelectMultiple(DATA_STRUCT* db)
{
  const char **cpfs = (const char **)malloc(22);
  cpfs[0] = "11111111111";
  cpfs[1] = "55555555555";
  const std::vector<const Record *> records = db->selMultiple(cpfs, 2);
  for (int i = 0; i < records.size(); i++)
  {
    cout << "Registro " << i << ": " << records[i][0] << endl;
  }
  printBlocks(db);
}

// void testSelectRange(DATA_STRUCT *db)
// {
//   const char *cpfBegin = "11111111111";
//   const char *cpfEnd = "33333333333";
//   const std::vector<const Record *> records = db->selRange(cpfBegin, cpfEnd);
//   for (int i = 0; i < records.size(); i++)
//   {
//     cout << "Registro " << i << ": " << records[i][0] << endl;
//   }
//   printBlocks(db);
// }

void testDelete(DATA_STRUCT *db)
{
  const char *cpf = "88888888888";
  db->del(cpf);
  printBlocks(db);
}

int main(int argc, char **argv)
{
  DATA_STRUCT db;

  // Insert
  // testInsert(&db);

  // Select
  // testSelect(&db);

  // Select multiple
  testSelectMultiple(&db);

  // Select range
  // testSelectRange(&db);

  // Delete
  // testDelete(&db);
  
}