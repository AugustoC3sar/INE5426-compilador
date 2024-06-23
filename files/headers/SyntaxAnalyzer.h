#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <unordered_map>
#include <string>
#include <vector>

struct Terminal
{
  std::string name;
};

struct Variable
{
  std::string name;
};

struct Production
{
  int id;
  std::string head;
  std::vector<std::string> tails;
};

class SyntaxAnalyzer
{
private:
  std::vector<std::string> stack;
  std::vector<Production> productions;
  std::unordered_map<std::string, std::unordered_map<std::string, int>> parseTable;
};

#endif