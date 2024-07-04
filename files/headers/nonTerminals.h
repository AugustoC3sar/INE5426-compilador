#ifndef NON_TERMINALS_ANALYZER_H
#define NON_TERMINALS_ANALYZER_H

#include <parser.h>

class Program : public Item {
public:
  Program(NonTerminal *parent) {
    nonTerminal = new NonTerminal("PROGRAM", parent);
    type = NON_TERMINAL;
  }
};

class Statement : public Item {
public:
  Statement(NonTerminal *parent) {
    nonTerminal = new NonTerminal("STATEMENT", parent);
    type = NON_TERMINAL;
  }
};

class Funclist : public Item {
public:
  Funclist(NonTerminal *parent) {
    nonTerminal = new NonTerminal("FUNCLIST", parent);
    type = NON_TERMINAL;
  }
};

class Funcdef : public Item {
public:
  Funcdef(NonTerminal *parent) {
    nonTerminal = new NonTerminal("FUNCDEF", parent);
    type = NON_TERMINAL;
  }
};

class Type : public Item {
public:
  Type(NonTerminal *parent) {
    nonTerminal = new NonTerminal("TYPE", parent);
    type = NON_TERMINAL;
  }
};

class Paramlist : public Item {
public:
  Paramlist(NonTerminal *parent) {
    nonTerminal = new NonTerminal("PARAMLIST", parent);
    type = NON_TERMINAL;
  }
};

class Paramlista : public Item {
public:
  Paramlista(NonTerminal *parent) {
    nonTerminal = new NonTerminal("PARAMLIST'", parent);
    type = NON_TERMINAL;
  }
};

class Vardecl : public Item {
public:
  Vardecl(NonTerminal *parent) {
    nonTerminal = new NonTerminal("VARDECL", parent);
    type = NON_TERMINAL;
  }
};

class Arrayvardecl : public Item {
public:
  Arrayvardecl(NonTerminal *parent) {
    nonTerminal = new NonTerminal("ARRAYVARDECL", parent);
    type = NON_TERMINAL;
  }
};

class Atribstat : public Item {
public:
  Atribstat(NonTerminal *parent) {
    nonTerminal = new NonTerminal("ATRIBSTAT", parent);
    type = NON_TERMINAL;
  }
};

class Atribstata : public Item {
public:
  Atribstata(NonTerminal *parent) {
    nonTerminal = new NonTerminal("ATRIBSTAT'", parent);
    type = NON_TERMINAL;
  }
};

class Funccall : public Item {
public:
  Funccall(NonTerminal *parent) {
    nonTerminal = new NonTerminal("FUNCCALL", parent);
    type = NON_TERMINAL;
  }
};

class Paramlistcall : public Item {
public:
  Paramlistcall(NonTerminal *parent) {
    nonTerminal = new NonTerminal("PARAMLISTCALL", parent);
    type = NON_TERMINAL;
  }
};


class Paramlistcalla : public Item {
public:
  Paramlistcalla(NonTerminal *parent) {
    nonTerminal = new NonTerminal("PARAMLISTCALL'", parent);
    type = NON_TERMINAL;
  }
};

class Printstat : public Item {
public:
  Printstat(NonTerminal *parent) {
    nonTerminal = new NonTerminal("PRINTSTAT", parent);
    type = NON_TERMINAL;
  }
};

class ReadStat : public Item {
public:
  ReadStat(NonTerminal *parent) {
    nonTerminal = new NonTerminal("READSTAT", parent);
    type = NON_TERMINAL;
  }
};

class ReturnStat : public Item {
public:
  ReturnStat(NonTerminal *parent) {
    nonTerminal = new NonTerminal("RETURNSTAT", parent);
    type = NON_TERMINAL;
  }
};

class Ifstat : public Item {
public:
  Ifstat(NonTerminal *parent) {
    nonTerminal = new NonTerminal("IFSTAT", parent);
    type = NON_TERMINAL;
  }
};

class Elsestat : public Item {
public:
  Elsestat(NonTerminal *parent) {
    nonTerminal = new NonTerminal("ELSESTAT", parent);
    type = NON_TERMINAL;
  }
};

class Forstat : public Item {
public:
  Forstat(NonTerminal *parent) {
    nonTerminal = new NonTerminal("FORSTAT", parent);
    type = NON_TERMINAL;
  }
};

class Statelist : public Item {
public:
  Statelist(NonTerminal *parent) {
    nonTerminal = new NonTerminal("STATELIST", parent);
    type = NON_TERMINAL;
  }
};

class Statelista : public Item {
public:
  Statelista(NonTerminal *parent) {
    nonTerminal = new NonTerminal("STATELIST'", parent);
    type = NON_TERMINAL;
  }
};

class Allocexpression : public Item {
public:
  Allocexpression(NonTerminal *parent) {
    nonTerminal = new NonTerminal("ALLOCEXPRESION", parent);
    type = NON_TERMINAL;
  }
};

class Numlist : public Item {
public:
  Numlist(NonTerminal *parent) {
    nonTerminal = new NonTerminal("NUM_LIST", parent);
    type = NON_TERMINAL;
  }
};

class Numlista : public Item {
public:
  Numlista(NonTerminal *parent) {
    nonTerminal = new NonTerminal("NUM_LIST'", parent);
    type = NON_TERMINAL;
  }
};

class Relop : public Item {
public:
  Relop(NonTerminal *parent) {
    nonTerminal = new NonTerminal("RELOP", parent);
    type = NON_TERMINAL;
  }
};

class Expression : public Item {
public:
  Expression(NonTerminal *parent) {
    nonTerminal = new NonTerminal("EXPRESSION", parent);
    type = NON_TERMINAL;
  }
};

class Expressiona : public Item {
public:
  Expressiona(NonTerminal *parent) {
    nonTerminal = new NonTerminal("EXPRESSION'", parent);
    type = NON_TERMINAL;
  }
};

class Signal : public Item {
public:
  Signal(NonTerminal *parent) {
    nonTerminal = new NonTerminal("SIGNAL", parent);
    type = NON_TERMINAL;
  }
};

class Numexpression : public Item {
public:
  Numexpression(NonTerminal *parent) {
    nonTerminal = new NonTerminal("NUMEXPRESSION", parent);
    type = NON_TERMINAL;
  }
};

class Numexpressiona : public Item {
public:
  Numexpressiona(NonTerminal *parent) {
    nonTerminal = new NonTerminal("NUMEXPRESSION'", parent);
    type = NON_TERMINAL;
  }
};

class Termrec : public Item {
public:
  Termrec(NonTerminal *parent) {
    nonTerminal = new NonTerminal("TERM_REC", parent);
    type = NON_TERMINAL;
  }
};

class Termreca : public Item {
public:
  Termreca(NonTerminal *parent) {
    nonTerminal = new NonTerminal("TERM_REC'", parent);
    type = NON_TERMINAL;
  }
};

class Operator : public Item {
public:
  Operator(NonTerminal *parent) {
    nonTerminal = new NonTerminal("OPERATOR", parent);
    type = NON_TERMINAL;
  }
};

class Term : public Item {
public:
  Term(NonTerminal *parent) {
    nonTerminal = new NonTerminal("TERM", parent);
    type = NON_TERMINAL;
  }
};

class Terma : public Item {
public:
  Terma(NonTerminal *parent) {
    nonTerminal = new NonTerminal("TERM'", parent);
    type = NON_TERMINAL;
  }
};


class Unaryexprrec : public Item {
public:
  Unaryexprrec(NonTerminal *parent) {
    nonTerminal = new NonTerminal("UNARYEXPR_REC", parent);
    type = NON_TERMINAL;
  }
};

class Unaryexprreca : public Item {
public:
  Unaryexprreca(NonTerminal *parent) {
    nonTerminal = new NonTerminal("UNARYEXPR_REC'", parent);
    type = NON_TERMINAL;
  }
};

class Unaryexpr : public Item {
public:
  Unaryexpr(NonTerminal *parent) {
    nonTerminal = new NonTerminal("UNARYEXPR", parent);
    type = NON_TERMINAL;
  }
};

class Factor : public Item {
public:
  Factor(NonTerminal *parent) {
    nonTerminal = new NonTerminal("FACTOR", parent);
    type = NON_TERMINAL;
  }
};

class Lvalue : public Item {
public:
  Lvalue(NonTerminal *parent) {
    nonTerminal = new NonTerminal("LVALUE", parent);
    type = NON_TERMINAL;
  }
};

class Lvaluea : public Item {
public:
  Lvaluea(NonTerminal *parent) {
    nonTerminal = new NonTerminal("LVALUE'", parent);
    type = NON_TERMINAL;
  }
};

class Numexpressionrec : public Item {
public:
  Numexpressionrec(NonTerminal *parent) {
    nonTerminal = new NonTerminal("NUMEXPRESSION_REC", parent);
    type = NON_TERMINAL;
  }
};

class Numexpressionreca : public Item {
public:
  Numexpressionreca(NonTerminal *parent) {
    nonTerminal = new NonTerminal("NUMEXPRESSION_REC'", parent);
    type = NON_TERMINAL;
  }
};

class DollarSign : public Item {
public:
  DollarSign() : Item() {
    nonTerminal = new NonTerminal("$", NULL);
    type = NON_TERMINAL;
  }
};

#endif
