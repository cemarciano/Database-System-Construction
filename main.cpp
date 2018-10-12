#include <iostream>
#include <fstream>
#include <list>

#include "Heap.h"
#include "Sorted.h"
#include "Hash.h"

#define DATA_STRUCT Hash

using namespace std;

void printBlocks(DATA_STRUCT* db)
{
  cout << db->blockg->blocks_used << " read blocks used" << endl;
  cout << db->blockp->blocks_used << " write blocks used" << endl;
}

void initDb(DATA_STRUCT* db)
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

void testInsert(DATA_STRUCT* db)
{
  db->ins("44444444444;54.037.661-5;estermoro@gmail.com;06/01/1952;Feminino;Yuri Matheus Antonia;5942.00");
  db->flush();
  printBlocks(db);
}

void testSelect(DATA_STRUCT* db)
{
  const char *cpf = "48112098182";
  db->sel(cpf);
  printBlocks(db);
}

void testSelectMultiple(DATA_STRUCT* db)
{
  const char **cpfs = (const char **)malloc(55);
  cpfs[0] = "48112098182";
  cpfs[1] = "12612266402";
  cpfs[2] = "16992486136";
  cpfs[3] = "08576967421";
  cpfs[4] = "03108358286";
  const std::vector<const Record *> records = db->selMultiple(cpfs, 5);
  for (int i = 0; i < records.size(); i++)
  {
    cout << "Registro " << i << ": " << records[i][0] << endl;
  }
  printBlocks(db);
}

void testSelectRange(DATA_STRUCT *db)
{
  const char *cpfBegin = "03108358286";
  const char *cpfEnd = "08576967421";
  const std::vector<const Record *> records = db->selRange(cpfBegin, cpfEnd);
  for (int i = 0; i < records.size(); i++)
  {
    cout << "Registro " << i << ": " << records[i][0] << endl;
  }
  printBlocks(db);
}

void testDelete(DATA_STRUCT *db)
{
  const char *cpf = "48112098182";
  db->del(cpf);
  printBlocks(db);
}

int main(int argc, char **argv)
{
  DATA_STRUCT db;

  // Init database
  initDb(&db);

  // Insert
  // testInsert(&db);

  // Select
  // testSelect(&db);

  // Select multiple
  // testSelectMultiple(&db);

  // Select range
  // testSelectRange(&db);

  // Delete
  // testDelete(&db);
  
}