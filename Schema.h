#ifndef SCHEMA_H
#define SCHEMA_H

#include <list>
#include <iostream>
#include "Column.h"

class Schema
{
private:
  std::list<Column> columns;

public:
  Schema();
  ~Schema();

  friend std::ostream &operator<<(std::ostream &out, const Schema& s);

  void addColumn(Column column);
};

#endif