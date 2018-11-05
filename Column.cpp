#include "Column.h"


Column::Column(std::string columnName, std::string columnType, int columnSz)
{
  this->columnName = columnName;
  this->columnType = columnType;
  this->columnSz = columnSz;
}

Column::~Column()
{
}

std::ostream& operator<<(std::ostream &out, const Column& c)
{
  if (c.columnSz == -1) return out << c.columnName << '\xff' << c.columnType;
  return out << c.columnName << '\xff' << c.columnType << '(' << c.columnSz << ')';
}