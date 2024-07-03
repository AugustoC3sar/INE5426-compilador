#include "parser.h"

#include <iostream>

Parser::Parser()
{

    _stack = {DollarSign(), Program(NULL)};

    _parseTable = {
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

std::vector<Item> Parser::generateNewTokens(int production, NonTerminal *parent) {
    switch (production) {
    case 0:
        return {Statement(parent)};
    case 1:
        return {Funclist(parent)};
    case 2:
        return {Epsilon(parent)};
    case 3:
        return {Funcdef(parent), Funclist(parent)};
    case 4:
        return {Funclist(parent)};
    case 5:
        return {Epsilon(parent)};
    case 6:
        return {Def(parent), Ident("", parent), OpenParentheses(parent), Paramlist(parent), CloseParentheses(parent), OpenBrackets(parent), Statelist(parent), CloseBrackets(parent)};
    case 7:
        return {Int(parent)};
    case 8:
        return {Float(parent)};
    case 9:
        return {String(parent)};
    case 10:
        return {Type(parent), Ident("", parent), Paramlist(parent)};
    case 11:
        return {Epsilon(parent)};
    case 12:
        return {Comma(parent), Paramlist(parent)};
    case 13:
        return {Epsilon(parent)};
    case 14:
        return {Vardecl(parent), Semicolon(parent)};
    case 15:
        return {Atribstat(parent), Semicolon(parent)};
    case 16:
        return {Printstat(parent), Semicolon(parent)};
    case 17:
        return {ReadStat(parent), Semicolon(parent)};
    case 18:
        return {ReturnStat(parent), Semicolon(parent)};
    case 19:
        return {Ifstat(parent)};
    case 20:
        return {Forstat(parent)};
    case 21:
        return {OpenBrackets(parent), Statelist(parent), CloseBrackets(parent)};
    case 22:
        return {Break(parent), Semicolon(parent)};
    case 23:
        return {Semicolon(parent)};
    case 24:
        return {Type(parent), Ident("", parent), Arrayvardecl(parent)};
    case 25:
        return {OpenSquareBrackets(parent), IntConstant("", parent), CloseSquareBrackets(parent), Arrayvardecl(parent)};
    case 26:
        return {Epsilon(parent)};
    case 27:
        return {Lvalue(parent), Equal(parent), Atribstata(parent)};
    case 28:
        return {Expression(parent)};
    case 29:
        return {Allocexpression(parent)};
    case 30:
        return {Funccall(parent)};
    case 31:
        return {Call(parent), Ident("", parent), OpenParentheses(parent), Paramlistcall(parent), CloseBrackets(parent)};
    case 32:
        return {Ident("", parent), Paramlistcalla(parent)};
    case 33:
        return {Epsilon(parent)};
    case 34:
        return {Comma(parent), Paramlistcall(parent)};
    case 35:
        return {Epsilon(parent)};
    case 36:
        return {Print(parent), Expression(parent)};
    case 37:
        return {Read(parent), Lvalue(parent)};
    case 38:
        return {Return(parent), Ident("", parent)};
    case 39:
        return {If(parent), OpenParentheses(parent), Expression(parent), CloseParentheses(parent), OpenBrackets(parent), Statement(parent), CloseBrackets(parent), Elsestat(parent)};
    case 40:
        return {Else(parent), OpenBrackets(parent), Statement(parent), CloseBrackets(parent)};
    case 41:
        return {Epsilon(parent)};
    case 42:
        return {For(parent), OpenParentheses(parent), Atribstat(parent), Semicolon(parent), Expression(parent), Semicolon(parent), Atribstat(parent), CloseParentheses(parent), Statement(parent)};
    case 43:
        return {Statement(parent), Statelista(parent)};
    case 44:
        return {Statelist(parent)};
    case 45:
        return {Epsilon(parent)};
    case 46:
        return {New(parent), Type(parent), Numlist(parent)};
    case 47:
        return {OpenSquareBrackets(parent), Numexpression(parent), CloseSquareBrackets(parent), Numlista(parent)};
    case 48:
        return {Numlist(parent)};
    case 49:
        return {Epsilon(parent)};
    case 50:
        return {LessThan(parent)};
    case 51:
        return {GreaterThan(parent)};
    case 52:
        return {LessOrEquals(parent)};
    case 53:
        return {GreaterOrEquals(parent)};
    case 54:
        return {Equals(parent)};
    case 55:
        return {Different(parent)};
    case 56:
        return {Numexpression(parent), Expressiona(parent)};
    case 57:
        return {Relop(parent), Numexpression(parent)};
    case 58:
        return {Epsilon(parent)};
    case 59:
        return {Positive(parent)};
    case 60:
        return {Minus(parent)};
    case 61:
        return {Term(parent), Numexpressiona(parent)};
    case 62:
        return {Termrec(parent)};
    case 63:
        return {Signal(parent), Term(parent), Termreca(parent)};
    case 64:
        return {Epsilon(parent)};
    case 65:
        return {Termrec(parent)};
    case 66:
        return {Times(parent)};
    case 67:
        return {Divide(parent)};
    case 68:
        return {Remainder(parent)};
    case 69:
        return {Unaryexpr(parent), Terma(parent)};
    case 70:
        return {Unaryexprrec(parent)};
    case 71:
        return {Operator(parent), Unaryexpr(parent), Unaryexprreca(parent)};
    case 72:
        return {Epsilon(parent)};
    case 73:
        return {Unaryexprrec(parent)};
    case 74:
        return {Signal(parent), Factor(parent)};
    case 75:
        return {Factor(parent)};
    case 76:
        return {IntConstant("", parent)};
    case 77:
        return {FloatConstant("", parent)};
    case 78:
        return {StringConstant("", parent)};
    case 79:
        return {Null(parent)};
    case 80:
        return {Lvalue(parent)};
    case 81:
        return {OpenParentheses(parent), Numexpression(parent), CloseParentheses(parent)};
    case 82:
        return {Ident("", parent), Lvaluea(parent)};
    case 83:
        return {Numexpressionrec(parent)};
    case 84:
        return {OpenSquareBrackets(parent), Numexpression(parent), CloseSquareBrackets(parent), Numexpressionreca(parent)};
    case 85:
        return {Epsilon(parent)};
    case 86:
        return {Numexpressionrec(parent)};
    default:
        std::cerr << "Produção não reconhecida" << std::endl;
        return {};
    }
};

void Parser::parse(std::vector<Token*> tokens) {
    for (auto token : tokens) {
        // Retrieve top of stack.
        Item topOfStack = _stack.at(_stack.size()-1);
        
        // Converts enums to a string value to be used in lexical values cases.
        std::string tokenValue = token->value();
        if (token->type() == INT_CONSTANT) {
            tokenValue = "int_constant";
        } else if (token->type() == FLOAT_CONSTANT) {
            tokenValue = "float_constant";
        } else if (token->type() == STRING_CONSTANT) {
            tokenValue = "string_constant";
        } else if (token->type() == IDENT) {
            tokenValue = "ident";
        }

        // Verifies if there is an entry in parse table for the top of stack as the head of production.
        bool containsEntryInParseTable = !(_parseTable.find(topOfStack.value()) == _parseTable.end());

        if (tokenValue == topOfStack.value()) {
            // If the value of the current token is equal to the value of the top of stack, we can remove the token from
            // the stack and retrieve the next token in the sequence. The next token advances in the for loop.
            topOfStack.terminal->lexicalValue = token->value(); 
            _stack.pop_back();
        } else if (topOfStack.value() == "&") {
            // If the top of stack is epsilon we just pop the top and retrieve the next token.
            _stack.pop_back();
        } else if (!containsEntryInParseTable) {
            std::cerr << "Topo da pilha não pode ser encontrado na tabela de parse " << topOfStack.value() << std::endl;
            return;
        } else {
            // Removes the current non terminal from the top of the stack.
            _stack.pop_back();

            // Retrieves the production we must apply next based on the current token and the current non terminal at
            // the top of the stack using the parse table.
            std::unordered_map<std::string, int> productionsParseRow = _parseTable.at(topOfStack.value());
            bool containsProductionForToken = !(productionsParseRow.find(tokenValue) == productionsParseRow.end());
            if (!containsProductionForToken) {
                std::cerr << "Token " << tokenValue <<  " não reconhecido para a produção " << topOfStack.value() << std::endl;
                return;
            }

            // Generates the non terminals and terminals of the production to apply. We add to all terminals, non
            // terminals and semantic actions the reference for the head of the production and its siblings.
            int production = productionsParseRow.at(tokenValue);
            NonTerminal *head = topOfStack.nonTerminal;
            std::vector<Item> tail = generateNewTokens(production, head);
            for (int i = tail.size() - 1; i >= 0; i--) {
                // Add syntax items in reverse order into the stack
                Item item = tail.at(i);
                _stack.push_back(item);
            }
        }
    }
}
