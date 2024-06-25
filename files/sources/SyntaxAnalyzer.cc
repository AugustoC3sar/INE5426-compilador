#include "SyntaxAnalyzer.h"

#include <iostream>

SyntaxAnalyzer::SyntaxAnalyzer(LexicalAnalyzer *la)
{
    lexicalAnalyzer = la;

    stack = {"$", "PROGRAM"};

    productions = {
        {0, "PROGRAM", {"STATEMENT"}},
        {1, "PROGRAM", {"FUNCLIST"}},
        {2, "PROGRAM", {"&"}},
        {3, "FUNCLIST", {"FUNCDEF", "FUNCLIST'"}},
        {4, "FUNCLIST'", {"FUNCLIST"}},
        {5, "FUNCLIST'", {"&"}},
        {6, "FUNCDEF", {"def", "ident", "(", "PARAMLIST", ")", "{", "STATELIST", "}"}},
        {7, "TYPE", {"int"}},
        {8, "TYPE", {"float"}},
        {9, "TYPE", {"string"}},
        {10, "PARAMLIST", {"TYPE", "ident", "PARAMLIST'"}},
        {11, "PARAMLIST", {"&"}},
        {12, "PARAMLIST'", {",", "PARAMLIST"}},
        {13, "PARAMLIST'", {"&"}},
        {14, "STATEMENT", {"VARDECL", ";"}},
        {15, "STATEMENT", {"ATRIBSTAT", ";"}},
        {16, "STATEMENT", {"PRINTSTAT", ";"}},
        {17, "STATEMENT", {"READSTAT", ";"}},
        {18, "STATEMENT", {"RETURNSTAT", ";"}},
        {19, "STATEMENT", {"IFSTAT"}},
        {20, "STATEMENT", {"FORSTAT"}},
        {21, "STATEMENT", {"{", "STATELIST", "}"}},
        {22, "STATEMENT", {"break", ";"}},
        {23, "STATEMENT", {";"}},
        {24, "VARDECL", {"TYPE", "ident", "ARRAYVARDECL"}},
        {25, "ARRAYVARDECL", {"[", "int_constant", "]", "ARRAYVARDECL"}},
        {26, "ARRAYVARDECL", {"&"}},
        {27, "ATRIBSTAT", {"LVALUE", "=", "ATRIBSTAT'"}},
        {28, "ATRIBSTAT'", {"EXPRESSION"}},
        {29, "ATRIBSTAT'", {"ALLOCEXPRESSION"}},
        {30, "ATRIBSTAT'", {"FUNCCALL"}},
        {31, "FUNCCALL", {"call", "ident", "(", "PARAMLISTCALL", ")"}},
        {32, "PARAMLISTCALL", {"ident", "PARAMLISTCALL'"}},
        {33, "PARAMLISTCALL", {"&"}},
        {34, "PARAMLISTCALL'", {",", "PARAMLISTCALL"}},
        {35, "PARAMLISTCALL'", {"&"}},
        {36, "PRINTSTAT", {"print", "EXPRESSION"}},
        {37, "READSTAT", {"read", "LVALUE"}},
        {38, "RETURNSTAT", {"return", "ident"}},
        {39, "IFSTAT", {"if", "(", "EXPRESSION", ")", "{", "STATEMENT", "}", "ELSESTAT"}},
        {40, "ELSESTAT", {"else", "{", "STATEMENT", "}"}},
        {41, "ELSESTAT", {"&"}},
        {42, "FORSTAT", {"for", "(", "ATRIBSTAT", ";", "EXPRESSION", ";", "ATRIBSTAT", ")", "STATEMENT"}},
        {43, "STATELIST", {"STATEMENT", "STATELIST'"}},
        {44, "STATELIST'", {"STATELIST"}},
        {45, "STATELIST'", {"&"}},
        {46, "ALLOCEXPRESSION", {"new", "TYPE", "NUM_LIST"}},
        {47, "NUM_LIST", {"[", "NUMEXPRESSION", "]", "NUM_LIST'"}},
        {48, "NUM_LIST'", {"NUM_LIST"}},
        {49, "NUM_LIST'", {"&"}},
        {50, "RELOP", {"<"}},
        {51, "RELOP", {">"}},
        {52, "RELOP", {"<="}},
        {53, "RELOP", {">="}},
        {54, "RELOP", {"=="}},
        {55, "RELOP", {"!="}},
        {56, "EXPRESSION", {"NUMEXPRESSION", "EXPRESSION'"}},
        {57, "EXPRESSION'", {"RELOP", "NUMEXPRESSION"}},
        {58, "EXPRESSION'", {"&"}},
        {59, "SIGNAL", {"+"}},
        {60, "SIGNAL", {"-"}},
        {61, "NUMEXPRESSION", {"TERM", "NUMEXPRESSION'"}},
        {62, "NUMEXPRESSION'", {"TERM_REC"}},
        {63, "TERM_REC", {"SIGNAL", "TERM", "TERM_REC'"}},
        {64, "TERM_REC", {"&"}},
        {65, "TERM_REC'", {"TERM_REC"}},
        {66, "OPERATOR", {"*"}},
        {67, "OPERATOR", {"/"}},
        {68, "OPERATOR", {"%"}},
        {69, "TERM", {"UNARYEXPR", "TERM'"}},
        {70, "TERM'", {"UNARYEXPR_REC"}},
        {71, "UNARYEXPR_REC", {"OPERATOR", "UNARYEXPR", "UNARYEXPR_REC'"}},
        {72, "UNARYEXPR_REC", {"&"}},
        {73, "UNARYEXPR_REC'", {"UNARYEXPR_REC"}},
        {74, "UNARYEXPR", {"SIGNAL", "FACTOR"}},
        {75, "UNARYEXPR", {"FACTOR"}},
        {76, "FACTOR", {"int_constant"}},
        {77, "FACTOR", {"float_constant"}},
        {78, "FACTOR", {"string_constant"}},
        {79, "FACTOR", {"null"}},
        {80, "FACTOR", {"LVALUE"}},
        {81, "FACTOR", {"(", "NUMEXPRESSION", ")"}},
        {82, "LVALUE", {"ident", "LVALUE'"}},
        {83, "LVALUE'", {"NUMEXPRESSION_REC"}},
        {84, "NUMEXPRESSION_REC", {"[", "NUMEXPRESSION", "]", "NUMEXPRESSION_REC'"}},
        {85, "NUMEXPRESSION_REC", {"&"}},
        {86, "NUMEXPRESSION_REC'", {"NUMEXPRESSION_REC"}},
    };

    parseTable = {
        {"PROGRAM", {
                        {"$", 2},
                        {"def", 1},
                        {"ident", 0},
                        {"{", 0},
                        {"int", 0},
                        {"float", 0},
                        {"string", 0},
                        {";", 0},
                        {"break", 0},
                        {"print", 0},
                        {"read", 0},
                        {"return", 0},
                        {"if", 0},
                        {"for", 0},
                    }},
        {"FUNCLIST", {
                         {"def", 3},
                     }},
        {"FUNCLIST'", {
                          {"$", 5},
                          {"def", 4},
                      }},
        {"FUNCDEF", {
                        {"def", 6},
                    }},
        {"TYPE", {
                     {"int", 7},
                     {"float", 8},
                     {"string", 9},
                 }},
        {"PARAMLIST", {{")", 11}, {"int", 10}, {"int", 10}, {"string", 10}}},
        {"PARAMLIST'", {
                           {")", 13},
                           {",", 12},
                       }},
        {"STATEMENT", {
                          {"ident", 15},
                          {"{", 21},
                          {"int", 14},
                          {"float", 14},
                          {"string", 14},
                          {";", 23},
                          {"break", 22},
                          {"print", 16},
                          {"read", 17},
                          {"return", 18},
                          {"if", 19},
                          {"for", 20},
                      }},
        {"VARDECL", {
                        {"int", 24},
                        {"float", 24},
                        {"string", 24},
                    }},
        {"ARRAYVARDECL", {
                             {";", 26},
                             {"[", 25},
                         }},
        {"ATRIBSTAT", {
                          {"ident", 27},
                      }},
        {"ATRIBSTAT'", {{"ident", 28}, {"(", 28}, {"int_constant", 28}, {"call", 30}, {"new", 29}, {"+", 28}, {"-", 28}, {"float_constant", 28}, {"string_constant", 28}, {"null", 28}}},
        {"FUNCCALL", {{"call", 31}}},
        {"PARAMLISTCALL", {
                              {"ident", 32},
                              {"(", 33},
                          }},
        {"PARAMLISTCALL'", {
                               {"(", 35},
                               {",", 34},
                           }},
        {"PRINTSTAT", {{"print", 36}}},
        {"READSTAT", {{"read", 37}}},
        {"RETURNSTAT", {{"return", 38}}},
        {"IFSTAT", {{"if", 39}}},
        {"ELSESTAT", {{"$", 41}, {"ident", 41}, {"{", 41}, {"}", 41}, {"int", 41}, {"float", 41}, {"string", 41}, {";", 41}, {"break", 41}, {"print", 41}, {"read", 41}, {"return", 41}, {"if", 41}, {"for", 41}, {"else", 40}}},
        {"FORSTAT", {{"for", 42}}},
        {"STATELIST", {{"ident", 43}, {"{", 43}, {"int", 43}, {"float", 43}, {"string", 43}, {";", 43}, {"break", 43}, {"print", 43}, {"read", 43}, {"return", 43}, {"if", 43}, {"for", 43}}},
        {"STATELIST'", {{"ident", 44}, {"{", 44}, {"int", 44}, {"float", 44}, {"string", 44}, {";", 44}, {"break", 44}, {"print", 44}, {"read", 44}, {"return", 44}, {"if", 44}, {"for", 44}, {"}", 45}}},
        {"ALLOCEXPRESSION", {
                                {"new", 46},
                            }},
        {"NUM_LIST", {{"[", 47}}},
        {"NUM_LIST'", {{")", 49}, {";", 49}, {"[", 48}}},
        {"RELOP", {{"<", 50}, {">", 51}, {"<=", 52}, {">=", 53}, {"==", 54}, {"!=", 55}}},
        {"EXPRESSION", {{"ident", 56}, {"(", 56}, {"int_constant", 56}, {"+", 56}, {"-", 56}, {"float_constant", 56}, {"string_constant", 56}, {"null", 56}}},
        {"EXPRESSION'", {{")", 58}, {";", 58}, {"<", 57}, {">", 57}, {"<=", 57}, {">=", 57}, {"==", 57}, {"!=", 57}}},
        {"SIGNAL", {{"+", 59}, {"-", 60}}},
        {"NUMEXPRESSION", {{"ident", 61}, {"(", 61}, {"int_constant", 61}, {"+", 61}, {"-", 61}, {"float_constant", 61}, {"string_constant", 61}, {"null", 61}}},
        {"NUMEXPRESSION'", {{")", 62}, {";", 62}, {"]", 62}, {"<", 62}, {">", 62}, {"<=", 62}, {">=", 62}, {"==", 62}, {"!=", 62}, {"+", 62}, {"-", 62}}},
        {"TERM_REC", {{")", 64}, {"]", 64}, {";", 64}, {"<", 64}, {">", 64}, {"<=", 64}, {">=", 64}, {"==", 64}, {"!=", 64}, {"+", 63}, {"-", 63}}},
        {"TERM_REC'", {{")", 65}, {"]", 65}, {";", 65}, {"<", 65}, {">", 65}, {"<=", 65}, {">=", 65}, {"==", 65}, {"!=", 65}, {"+", 65}, {"-", 65}}},
        {"OPERATOR", {{"*", 66}, {"/", 67}, {"%", 68}}},
        {"TERM", {{"ident", 69}, {"{", 69}, {"int_constant", 69}, {"+", 69}, {"-", 69}, {"int_constant", 69}, {"string_constant", 69}, {"null", 69}}},
        {"TERM'", {{")", 70}, {";", 70}, {"]", 70}, {"<", 70}, {">", 70}, {"<=", 70}, {">=", 70}, {"==", 70}, {"!=", 70}, {"+", 70}, {"-", 70}, {"*", 70}, {"/", 70}, {"%", 70}}},
        {"UNARYEXPR_REC", {{")", 72}, {";", 72}, {"]", 72}, {"<", 72}, {">", 72}, {"<=", 72}, {">=", 72}, {"==", 72}, {"!=", 72}, {"+", 72}, {"-", 72}, {"*", 71}, {"/", 71}, {"%", 71}}},
        {"UNARYEXPR_REC'", {{")", 73}, {";", 73}, {"]", 73}, {"<", 73}, {">", 73}, {"<=", 73}, {">=", 73}, {"==", 73}, {"!=", 73}, {"+", 73}, {"-", 73}, {"*", 73}, {"/", 73}, {"%", 73}}},
        {"UNARYEXPR", {{"ident", 75}, {"(", 75}, {"int_constant", 75}, {"+", 74}, {"-", 74}, {"float_constant", 75}, {"string_constant", 75}, {"null", 75}}},
        {"FACTOR", {{"ident", 80}, {"(", 81}, {"int_constant", 76}, {"float_constant", 77}, {"string_constant", 78}, {"null", 79}}},
        {"LVALUE", {{"ident", 82}}},
        {"LVALUE'", {{")", 83}, {";", 83}, {"[", 83}, {"]", 83}, {"=", 83}, {"<", 83}, {">", 83}, {"<=", 83}, {">=", 83}, {"==", 83}, {"!=", 83}, {"+", 83}, {"-", 83}, {"*", 83}, {"/", 83}, {"%", 83}}},
        {"NUMEXPRESSION_REC", {{")", 85}, {";", 85}, {"[", 84}, {"]", 85}, {"=", 85}, {"<", 85}, {">", 85}, {"<=", 85}, {">=", 85}, {"==", 85}, {"!=", 85}, {"+", 85}, {"-", 85}, {"*", 85}, {"/", 85}, {"%", 85}}},
        {"NUMEXPRESSION_REC'", {{")", 86}, {";", 86}, {"[", 84}, {"]", 86}, {"=", 86}, {"<", 86}, {">", 86}, {"<=", 86}, {">=", 86}, {"==", 86}, {"!=", 86}, {"+", 86}, {"-", 86}, {"*", 86}, {"/", 86}, {"%", 86}}},
    };
}

void SyntaxAnalyzer::parse() {
    Token token = lexicalAnalyzer->getNextToken();
    while (token.type != END_OF_FILE)
    {
        if (token.type == WAITING) continue;

        std::string A = stack.at(stack.size()-1);
        std::string tokenValue = token.value;
        if (token.type == INT_CONSTANT) {
            tokenValue = "int_constant";
        } else if (token.type == FLOAT_CONSTANT) {
            tokenValue = "float_constant";
        } else if (token.type == STRING_CONSTANT) {
            tokenValue = "string_constant";
        } else if (token.type == IDENT) {
            tokenValue = "ident";
        }

        bool containsEntryInParseTable = !(parseTable.find(A) == parseTable.end());
        if (tokenValue == A) {
            stack.pop_back();
            token = lexicalAnalyzer->getNextToken();
        } else if (A == "&") {
            stack.pop_back();
        } else if (!containsEntryInParseTable) {
            std::cerr << "Topo da pilha não pode ser encontrado na tabela de parse " << A << std::endl;
            return;
        } else {
            stack.pop_back();
            std::unordered_map<std::string, int> productionsParseRow = parseTable.at(A);
            bool containsProductionForToken = !(productionsParseRow.find(tokenValue) == productionsParseRow.end());
            if (!containsProductionForToken) {
                std::cerr << "Token " << tokenValue <<  " não reconhecido para a produção " << A << std::endl;
                return;
            }

            Production production = productions.at(productionsParseRow.at(tokenValue));
            for (int i = production.tails.size() - 1; i >= 0; i--) {
                std::string tokenToAdd = production.tails.at(i);
                stack.push_back(tokenToAdd);
            }
        }
    }
}
