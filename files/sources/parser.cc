#include "semantics.h"
#include "terminals.h"
#include "nonTerminals.h"
#include "parser.h"
#include "expa.h"
#include "scope.h"
#include "codeGen.h"

#include <iostream>
#include <stdexcept>

Parser::Parser(SymbolTable *table)
{
    _symbolTable = table;

    _stack = {DollarSign(), Program(NULL, table)};

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
        {"PARAMLIST", {{")", 11}, {"int", 10}, {"float", 10}, {"string", 10}}},
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
                               {")", 35},
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
        {"TERM", {{"(", 69}, {"ident", 69}, {"{", 69}, {"int_constant", 69}, {"+", 69}, {"-", 69}, {"float_constant", 69}, {"string_constant", 69}, {"null", 69}}},
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

std::vector<Item> Parser::generateNewTokens(int production, NonTerminal *parent)
{
    switch (production)
    {
    case 0:
        // PROGRAM -> STATEMENT
        return {Statement(parent)};
    case 1:
        // PROGRAM -> FUNCLIST
        return {Funclist(parent)};
    case 2:
        // PROGRAM -> &
        return {Epsilon(parent)};
    case 3:
        // FUNCLIST -> FUNCDEF FUNCLIST'
        return {NewScope(parent), Funcdef(parent), Funclist(parent)};
    case 4:
        // FUNCLIST' -> FUNCLIST
        return {Funclist(parent)};
    case 5:
        // FUNCLIST' -> &
        return {Epsilon(parent)};
    case 6:
        // FUNCDEF -> def ident(PARAMLIST) {STATELIST}
        return {Def(parent), Ident("", parent), OpenParentheses(parent), Paramlist(parent), CloseParentheses(parent), OpenBrackets(parent), Statelist(parent), CloseBrackets(parent)};
    case 7:
        // TYPE -> int { TYPE.type = int }
        return {Int(parent), SaveType("int", parent)};
    case 8:
        // TYPE -> float { TYPE.float = float }
        return {Float(parent), SaveType("float", parent)};
    case 9:
        // TYPE -> string { TYPE.string = string }
        return {String(parent), SaveType("string", parent)};
    case 10:
        // PARAMLIST -> TYPE ident { symbolTable->addType(ident.lexicalValue, TYPE.type) } PARAMLIST'
        return {Type(parent), Ident("", parent), AddType(parent), Paramlista(parent)};
    case 11:
        // PARAMLIST -> &
        return {Epsilon(parent)};
    case 12:
        // PARAMLIST' -> , PARAMLIST
        return {Comma(parent), Paramlist(parent)};
    case 13:
        // PARAMLIST' -> &
        return {Epsilon(parent)};
    case 14:
        // STATEMENT -> VARDECL;
        return {Vardecl(parent), Semicolon(parent)};
    case 15:
        // STATEMENT -> ATRIBSTAT;
        return {Atribstat(parent), Semicolon(parent)};
    case 16:
        // STATEMENT -> PRINTSTAT;
        return {Printstat(parent), Semicolon(parent)};
    case 17:
        // STATEMENT -> READSTAT;
        return {ReadStat(parent), Semicolon(parent)};
    case 18:
        // STATEMENT -> RETURNSTAT;
        return {ReturnStat(parent), Semicolon(parent)};
    case 19:
        // STATEMENT -> IFSTAT
        return {Ifstat(parent)};
    case 20:
        // STATEMENT -> FORSTAT
        return {NewScope(parent), Forstat(parent)};
    case 21:
        // STATEMENT -> {STATELIST}
        return {OpenBrackets(parent), Statelist(parent), CloseBrackets(parent)};
    case 22:
        // STATEMENT -> { checkBreakInScope } break;
        return {CheckBreakInScope(parent), Break(parent), Semicolon(parent)};
    case 23:
        // STATEMENT -> ;
        return {Semicolon(parent)};
    case 24:
        // VARDECL -> TYPE ident { ARRAYVARDECL.inhType = TYPE.type } ARRAYVARDECL { VARDECL.type = ARRAYVARDECL.type } { symbolTable->addType(ident.lexicalValue, VARDECL.type) }
        return {Type(parent), Ident("", parent), InheritedType(parent), Arrayvardecl(parent), SynthesizedType(parent), AddType(parent)};
    case 25:
        // ARRAYVARDECL ->[int_constant] ARRAYVARDECL
        return {OpenSquareBrackets(parent), IntConstant("", parent), CloseSquareBrackets(parent), ArrayInheritedType(parent), Arrayvardecl(parent), ArraySynthesizedType(parent)};
    case 26:
        // ARRAYVARDECL -> & { ARRAYVARDECL.type = ARRAYVARDECL.inhType }
        return {Epsilon(parent), ArraySynthesizeType(parent)};
    case 27:
        // ATRIBSTAT -> LVALUE = ATRIBSTAT'
        return {Lvalue(parent), Equal(parent), Atribstata(parent), GenerateAtribstatCode(parent)};
    case 28:
        // ATRIBSTAT' -> EXPRESSION { ATRIBSTAT'.node = EXPRESSION.node }
        return {Expression(parent), AssignTree(parent, t, &expressionTrees)};
    case 29:
        // ATRIBSTAT' -> ALLOCEXPRESSION
        return {Allocexpression(parent)};
    case 30:
        // ATRIBSTAT' -> FUNCCALL
        return {Funccall(parent)};
    case 31:
        // FUNCCALL -> call ident(PARAMLISTCALL)
        return {Call(parent), Ident("", parent), OpenParentheses(parent), Paramlistcall(parent), CloseParentheses(parent)};
    case 32:
        // PARAMLISTCALL -> ident PARAMLISTCALL'
        return {Ident("", parent), Paramlistcalla(parent)};
    case 33:
        // PARAMLISTCALL -> &
        return {Epsilon(parent)};
    case 34:
        // PARAMLISTCALL' -> , PARAMLISTCALL
        return {Comma(parent), Paramlistcall(parent)};
    case 35:
        // PARAMLISTCALL' -> &
        return {Epsilon(parent)};
    case 36:
        // PRINTSTAT -> print EXPRESSION
        return {Print(parent), Expression(parent)};
    case 37:
        // READSTAT -> read LVALUE
        return {Read(parent), Lvalue(parent)};
    case 38:
        // RETURNSTAT -> return
        return {Return(parent)};
    case 39:
        // IFSTAT -> if (EXPRESSION) { STATELIST } ELSESTAT
        return {If(parent), OpenParentheses(parent), Expression(parent), CloseParentheses(parent), OpenBrackets(parent), Statelist(parent), CloseBrackets(parent), Elsestat(parent)};
    case 40:
        // ELSESTAT -> else { STATELIST }
        return {Else(parent), OpenBrackets(parent), Statelist(parent), CloseBrackets(parent)};
    case 41:
        // ELSESTAT -> &
        return {Epsilon(parent)};
    case 42:
        // FORSTAT -> for(ATRIBSTAT; EXPRESSION; ATRIBSTAT) { STATELIST }
        return {For(parent), OpenParentheses(parent), Atribstat(parent), Semicolon(parent), Expression(parent), Semicolon(parent), Atribstat(parent), CloseParentheses(parent), OpenBrackets(parent), Statelist(parent), CloseBrackets(parent)};
    case 43:
        // STATELIST -> STATEMENT STATELIST'
        return {Statement(parent), Statelista(parent)};
    case 44:
        // STATELIST' -> STATELIST
        return {Statelist(parent)};
    case 45:
        // STATELIST' -> &
        return {Epsilon(parent)};
    case 46:
        // ALLOCEXPRESSION -> new TYPE NUM_LIST
        return {New(parent), Type(parent), Numlist(parent)};
    case 47:
        // NUM_LIST -> [NUMEXPRESSION] NUM_LIST'
        return {OpenSquareBrackets(parent), Numexpression(parent), CloseSquareBrackets(parent), Numlista(parent)};
    case 48:
        // NUM_LIST' -> NUM_LIST
        return {Numlist(parent)};
    case 49:
        // NUM_LIST' -> &
        return {Epsilon(parent)};
    case 50:
        // RELOP -> <
        return {LessThan(parent)};
    case 51:
        // RELOP -> >
        return {GreaterThan(parent)};
    case 52:
        // RELOP -> <=
        return {LessOrEquals(parent)};
    case 53:
        // RELOP -> >=
        return {GreaterOrEquals(parent)};
    case 54:
        // RELOP -> ==
        return {Equals(parent)};
    case 55:
        // RELOP -> !=
        return {Different(parent)};
    case 56:
        // EXPRESSION -> NUMEXPRESSION { EXPRESSION.leftNode = NUMEXPRESSION.node } EXPRESSION' { EXPRESSION.node = EXPRESSION'.node }
        return {Numexpression(parent), InheritNumexpressionNode(parent), Expressiona(parent), ReturnNode(parent)};
    case 57:
        // EXPRESSION' -> RELOP NUMEXPRESSION
        return {Relop(parent), Numexpression(parent)};
    case 58:
        // EXPRESSION' -> & { EXPRESSION'.node = EXPRESSION'.leftNode}
        return {Epsilon(parent), SyntehsizeNode(parent)};
    case 59:
        // SIGNAL -> + { SIGNAL.value = + }
        return {Positive(parent), ReturnOperationValue(parent)};
    case 60:
        // SIGNAL -> - { SIGNAL.value = - }
        return {Minus(parent), ReturnOperationValue(parent)};
    case 61:
        // NUMEXPRESSION -> TERM { NUMEXPRESSION'.leftNode = TERM.node } NUMEXPRESSION' { NUMEXPRESSION.node = NUMEXPRESSION'.node }
        return {Term(parent), InheritTermNode(parent), Numexpressiona(parent), ReturnNode(parent)};
    case 62:
        // NUMEXPRESSION' -> { TERM_REC.leftNode = NUMEXPRESSION'.leftNode } TERM_REC { NUMEXPRESSION'.node = TERM_REC.node }
        return {InheritLeftNodeToFirstChild(parent), Termrec(parent), ReturnNode(parent)};
    case 63:
        // TERM_REC -> SIGNAL TERM { TERM_REC'.leftNode = new Node(SIGNAL.value, TERM_REC.leftNode, TERM.node) } TERM_REC' { TERM_REC.node = TERM_REC'.node }
        return {Signal(parent), Term(parent), CreateInheritedSignalNode(parent), Termreca(parent), ReturnNode(parent)};
    case 64:
        // TERM_REC -> & { TERM_REC.node = TERM_REC.leftNode }
        return {Epsilon(parent), SyntehsizeNode(parent)};
    case 65:
        // TERM_REC' -> { TERM_REC.leftNode = TERM_REC'.leftNode } TERM_REC { TERM_REC'.node = TERM_REC.node }
        return { InheritLeftNodeToFirstChild(parent), Termrec(parent), ReturnNode(parent)};
    case 66:
        // OPERATOR -> * { OPERATOR.value = * }
        return {Times(parent), ReturnOperationValue(parent)};
    case 67:
        // OPERATOR -> / { OPERATOR.value = / }
        return {Divide(parent), ReturnOperationValue(parent)};
    case 68:
        // OPERATOR -> % { OPERATOR.value = % }
        return {Remainder(parent), ReturnOperationValue(parent)};
    case 69:
        // TERM -> UNARYEXPR { TERM'.leftNode = UNARYEXPR.node } TERM' { TERM.node = TERM'.node }
        return {Unaryexpr(parent),  InheritUnaryexprNode(parent), Terma(parent), ReturnNode(parent)};
    case 70:
        // TERM' -> { UNARYEXPR_REC.leftNode = TERM'.leftNode } UNARYEXPR_REC { TERM'.node = UNARYEXPR_REC.node }
        return {InheritLeftNodeToFirstChild(parent), Unaryexprrec(parent), ReturnNode(parent)};
    case 71:
        // UNARYEXPR_REC -> OPERATOR UNARYEXPR { UNARYEXPR_REC'.leftNode = new Node(OPERATOR.value, UNARYEXPR_REC.leftNode, UNARYEXPR.node) } UNARYEXPR_REC' { UNARYEXPR_REC.node = UNARYEXPR_REC'.node }
        return {Operator(parent),  Unaryexpr(parent), CreateUnaryexprRecInheritedNode(parent), Unaryexprreca(parent), ReturnNode(parent)};
    case 72:
        // UNARYEXPR_REC -> & { UNARYEXPR_REC.node = UNARYEXPR_REC.leftNode }
        return {Epsilon(parent), SyntehsizeNode(parent)};
    case 73:
        // UNARYEXPR_REC' -> { UNARYEXPR_REC.leftNode = UNARYEXPR_REC'.leftNode } UNARYEXPR_REC { UNARYEXPR_REC'.node = UNARYEXPR_REC.node }
        return {InheritLeftNodeToFirstChild(parent), Unaryexprrec(parent), ReturnNode(parent)};
    case 74:
        // UNARYEXPR -> SIGNAL FACTOR { UNARYEXPR.node = new Node(SIGNAL.operationValue, UNARYEXPR.leftNode, FACTOR.node) }
        return {Signal(parent), Factor(parent), CreateOperatorNode(parent)};
    case 75:
        // UNARYEXPR -> { FACTOR.leftNode = UNARYEXPR.leftNode } FACTOR { UNARYEXPR.node = FACTOR.node }
        return {InheritLeftNodeToFirstChild(parent), Factor(parent), ReturnNode(parent)};
    case 76:
        // FACTOR -> int_constant { FACTOR.node = new Node(int_constant, NULL, NULL) }
        return {IntConstant("", parent), CreateLeafNode(parent)};
    case 77:
        // FACTOR -> float_constant { FACTOR.node = new Node(float_constant, NULL, NULL) 
        return {FloatConstant("", parent), CreateLeafNode(parent)};
    case 78:
        // FACTOR -> string_constant { FACTOR.node = new Node(string_constant, NULL, NULL) }
        return {StringConstant("", parent), CreateLeafNode(parent)};
    case 79:
        // FACTOR -> null { FACTOR.node = new Node(null, NULL, NULL) }
        return {Null(parent), CreateLeafNode(parent)};
    case 80:
        // FACTOR -> { LVALUE.leftNode = FACTOR.leftNode } LVALUE { FACTOR.node = LVALUE.node }
        return {InheritLeftNodeToFirstChild(parent), Lvalue(parent), ReturnNode(parent)};
    case 81:
        // FACTOR -> (NUMEXPRESSION) { FACTOR.node = NUMEXPRESSION.node }
        return {OpenParentheses(parent), Numexpression(parent), CloseParentheses(parent), SynthesizeNumexpressionNode(parent)};
    case 82:
        // LVALUE -> ident LVALUE' { FACTOR.node = new Node(ident, NULL, NULL) }
        return {Ident("", parent),  InheritLvalueType(parent), Lvaluea(parent), CreateLeafNode(parent), SynthesizeLvalueType(parent), GenerateLvalueCode(parent, t)};
    case 83:
        // LVALUE' -> NUMEXPRESSION_REC
        return {InheritLvalueLinhaType(parent), Numexpressionrec(parent), SynthesizeLvalueLinhaType(parent)};
    case 84:
        // NUMEXPRESSION_REC -> [NUMEXPRESSION] NUMEXPRESSION_REC'
        return {OpenSquareBrackets(parent), Numexpression(parent), CloseSquareBrackets(parent), Numexpressionreca(parent)};
    case 85:
        // NUMEXPRESSION_REC -> &
        return {Epsilon(parent), SynthesizeNumexpressionRecType(parent)};
    case 86:
        // NUMEXPRESSION_REC' -> NUMEXPRESSION_REC
        return {Numexpressionrec(parent)};
    default:
        std::string error = "\033[31merror:\033[0m unrecognized production";
        throw std::logic_error(error);
    }
};

void Parser::parse(std::vector<Token *> tokens)
{
    long unsigned int i = 0;
    while (i < tokens.size())
    {
        Token *token = tokens.at(i);

        // Retrieve top of stack.
        Item topOfStack = _stack.at(_stack.size() - 1);

        // Converts enums to a string value to be used in lexical values cases.
        std::string tokenValue = token->value();
        if (token->type() == INT_CONSTANT)
        {
            tokenValue = "int_constant";
        }
        else if (token->type() == FLOAT_CONSTANT)
        {
            tokenValue = "float_constant";
        }
        else if (token->type() == STRING_CONSTANT)
        {
            tokenValue = "string_constant";
        }
        else if (token->type() == IDENT)
        {
            tokenValue = "ident";
        }

        // std::cout << "CURRENT TOKEN " << tokenValue << std::endl;
        // std::cout << "TOP OF STACK " << topOfStack.value() << std::endl;

        try {
            // Verifies if there is an entry in parse table for the top of stack as the head of production.
            bool containsEntryInParseTable = !(_parseTable.find(topOfStack.value()) == _parseTable.end());
            if (topOfStack.type == SEMANTIC_ACTION)
            {
                // Checks if the syntax item is a semantic action before executing the algorithm.
                topOfStack.semanticAction->execute();
                _stack.pop_back();
            }
            else if (tokenValue == topOfStack.value())
            {
                // If the value of the current token is equal to the value of the top of stack, we can remove the token from
                // the stack and retrieve the next token in the sequence. The next token advances in the for loop.
                topOfStack.terminal->lexicalValue = token->value();
                _stack.pop_back();
                i++;
            }
            else if (topOfStack.value() == "&")
            {
                // If the top of stack is epsilon we just pop the top and use the same token.
                _stack.pop_back();

            } else if (!containsEntryInParseTable) {
                std::string error = "\033[31merror:\033[0m stack top '" + topOfStack.value() + "' could not be found in parsing table";
                throw std::logic_error(error);
            } else {
                // Removes the current non terminal from the top of the stack.
                _stack.pop_back();

                // Retrieves the production we must apply next based on the current token and the current non terminal at
                // the top of the stack using the parse table.
                std::unordered_map<std::string, int> productionsParseRow = _parseTable.at(topOfStack.value());
                bool containsProductionForToken = !(productionsParseRow.find(tokenValue) == productionsParseRow.end());

                if (!containsProductionForToken) {
                    std::string error = "Token '" + tokenValue +  "' have no production for stack top '" + topOfStack.value() +"'";
                    throw std::logic_error(error);
                }

                // Generates the non terminals and terminals of the production to apply. We add to all terminals, non
                // terminals and semantic actions the reference for the head of the production and its siblings.
                int production = productionsParseRow.at(tokenValue);
                NonTerminal *head = topOfStack.nonTerminal;
                std::vector<Item> tail = generateNewTokens(production, head);
                head->children = tail;
                for (int i = tail.size() - 1; i >= 0; i--)
                {
                    // Add syntax items in reverse order into the stack
                    Item item = tail.at(i);
                    _stack.push_back(item);
                }
            }
        } catch (const std::exception& error) {
            std::cout << "At line " << token->line() << " and column " << token->column() << std::endl;
            std::cout << error.what() << std::endl;
            throw error;
        }
    }

    // Print all executed expression trees.
    i = 0;
    for (auto node : expressionTrees) {
        std::cout << "Computed expression tree " << i << std::endl;
        node->printLeftFromRight();
        std::cout << std::endl << std::endl;
        i++;
    }
}
