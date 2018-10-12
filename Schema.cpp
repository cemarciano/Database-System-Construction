#include "Schema.h"


Schema::Schema()
{
}

Schema::~Schema()
{
}

void Schema::addColumn(Column column) {
  this->columns.push_back(column);
}

std::ostream& operator<<(std::ostream &out, const Schema& s) {
  for (std::list<Column>::const_iterator it = s.columns.begin(); it != s.columns.end(); it++) {
    out << *it;
    if (std::next(it) != s.columns.cend()) out << ';';
  }
  return out;
}