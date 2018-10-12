#ifndef COLUMN_H
#define COLUMN_H

#include <string>
#include <iostream>

class Column
{
private:
  std::string columnName;
  std::string columnType;
  int columnSz;

public:
  Column(std::string columnName, std::string columnType) : Column(columnName, columnType, -1) {}
  Column(std::string columnName, std::string columnType, int columnSz);
  ~Column();

  friend std::ostream &operator<<(std::ostream &out, const Column &c);
};

#endif