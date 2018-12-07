#include "Header.h"

#include <iostream>

#include "Record.h"

Header::Header(std::string headerFilename)
{
  this->headerFilename = headerFilename;
  std::string line;
  this->headerFile.open(this->headerFilename, std::ios_base::in);
  if (headerFile.good()) {
    std::getline(headerFile, line);
    std::list<std::string> columns = this->split(line, ";");
    for (std::list<std::string>::iterator it = columns.begin(); it != columns.end(); it++) {
      std::list<std::string> tokens = this->split(*it, "\xff");
      std::string columnName = tokens.front();
      tokens.pop_front();
      std::string columnTypeAndSz = tokens.front();
      tokens.pop_front();
      tokens = this->split(columnTypeAndSz, "(");
      std::string columnType = tokens.front();
      tokens.pop_front();
      int columnSz = -1;
      if (tokens.begin() != tokens.end()) {
        std::string columnSzStr = tokens.front();
        tokens.pop_front();
        columnSz = std::atoi(columnSzStr.substr(0, -1).c_str());
      }
      this->schema.addColumn(Column(columnName, columnType, columnSz));
    }
    std::getline(headerFile, line);
    this->n_r = std::atoi(line.c_str());
    std::getline(headerFile, line);
    this->record_sz = std::atoi(line.c_str());
  } else {
    this->schema.addColumn(Column("cpf",      "CHAR",   11));
    this->schema.addColumn(Column("rg",       "CHAR",   12));
    this->schema.addColumn(Column("email",    "CHAR",   40));
    this->schema.addColumn(Column("dt_nasc",  "CHAR",   10));
    this->schema.addColumn(Column("sexo",     "CHAR",   10));
    this->schema.addColumn(Column("nome",     "CHAR",   40));
    this->schema.addColumn(Column("salario",  "FLOAT"));
    this->n_r = 0;
    this->record_sz = sizeof(Record);
  }
  this->headerFile.close();
}

Header::~Header()
{

}

void Header::addRecord() {
  this->n_r++;
}

void Header::delRecord() {
  this->n_r--;
}

void Header::write() {
  this->headerFile.open(this->headerFilename, std::ios_base::out);

  this->headerFile << this->schema << std::endl;
  this->headerFile << this->n_r << std::endl;
  this->headerFile << this->record_sz << std::endl;
}

std::list<std::string> Header::split(std::string s, std::string delim) {
  std::list<std::string> tokens;
  size_t pos = 0;
  std::string token;
  while ((pos = s.find(delim)) != std::string::npos) {
    tokens.push_back(s.substr(0, pos));
    s.erase(0, pos + delim.length());
  }
  tokens.push_back(s);
  return tokens;
}
