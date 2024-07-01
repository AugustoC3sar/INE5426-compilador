#ifndef SYNTAX_ANALYZER_H
#define SYNTAX_ANALYZER_H

#include "LexicalAnalyzer.h"

#include <unordered_map>
#include <string>
#include <vector>

struct Production
{
  int id;
  std::string head;
  std::vector<std::string> tails;

  std::string type;
  std::string inh_type;
};

class SyntaxAnalyzer
{
private:
  std::vector<std::string> stack;
  std::vector<Production> productions;
  std::unordered_map<std::string, std::unordered_map<std::string, int>> parseTable;
  LexicalAnalyzer *lexicalAnalyzer;

public:
  SyntaxAnalyzer(LexicalAnalyzer *la);

  void parse();
};

#endif