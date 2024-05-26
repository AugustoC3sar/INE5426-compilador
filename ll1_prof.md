# Prova de que a gramática está em LL1

Neste documento iremos descrever a nossa prova de que a gramática que possuímos está em LL1.

De forma a provar que uma gramática está em LL1 devemos ter as seguintes regras matemáticas cumpridas:

```math
FIRST(B) \cap FIRST(C) = \emptyset
```

```math
se FIRST(B) \superset \epsilon, então FIRST(C) \cap LAST(A) = \emptyset
```

```math
se FIRST(C) \superset \epsilon, então FIRST(B) \cap LAST(A) = \emptyset
```

Dessa forma, asseguramos que a gramática está em LL1 para a construção do nosso compilador.

## Construção dos FIRST das produções

FIRST(PROGRAM) = {{, break, ;, int, float, string, bool, print, read, return, if, for, def, ident, &}

FIRST(FUNCLIST) = {def}

FIRST(FUNCLIST') = {def, &}

FIRST(FUNCDEF) = {def}

FIRST(TYPE) = {int, float, string, bool}

FIRST(PARAMLIST) = {int, float, string, bool, &}

FIRST(PARAMLIST') = {,, &}

FIRST(STATEMENT) = {{, break, ;, int, float, string, bool, print, read, return, if, for, ident}

FIRST(VARDECL) = {int, float, string, bool}

FIRST(VARDECL') = {[, &}

FIRST(INT_LIST) = {[, &}

FIRST(INT_LIST') = {[, &}

FIRST(ATRIBSTAT) = {ident}

FIRST(ATRIBSTAT') = {new, ident, (, not, +, -, int_constant, float_constant, string_constant, null}

FIRST(FUNCCALL) = {ident}

FIRST(PARAMLISTCALL) = {ident, &}

FIRST(PARAMLISTCALL') = {,, &}

FIRST(PRINTSTAT) = {print}

FIRST(READSTAT) = {read}

FIRST(RETURNSTAT) = {return}

FIRST(IFSTAT) = {if}

FIRST(ELSESTAT) = {else}

FIRST(FORSTAT) = {for}

FIRST(STATELIST) = {{, break, ;, int, float, string, bool, print, read, return, if, for, ident}

FIRST(STATELIST') = {{, break, ;, int, float, string, bool, print, read, return, if, for, ident, &}

FIRST(ALLOCEXPRESSION) = {new}

FIRST(NUM_LIST) = {[}

FIRST(NUM_LIST') = {[, &}

FIRST(RELOP) = {<, >, <=, >=, ==, !=}

FIRST(EXPRESSION) = {(, not, +, -, int_constant, float_constant, string_constant, null, ident, &}

FIRST(EXPRESSION') = {<, >, <=, >=, ==, !=, &}

FIRST(SIGNAL) = {+, -}

FIRST(NUMEXPRESSION) = {+, -, int_constant, float_constant, string_constant, null, (, ident}

FIRST(NUMEXPRESSION') = {+, -, &&}

FIRST(TERM_REC) = {+, -, &}

FIRST(TERM_REC') = {+, -, &}

FIRST(OPERATOR) = {*, /, %}

FIRST(TERM) = {+, -, int_constant, float_constant, string_constant, null, (, ident}

FIRST(TERM') = {*, /, %, &}

FIRST(UNARYEXPR_REC) = {*, /, %, &}

FIRST(UNARYEXPR_REC') = {*, /, %, &}

FIRST(UNARYEXPR) = {+, -, int_constant, float_constant, string_constant, null, (, ident}

FIRST(FACTOR) = {int_constant, float_constant, string_constant, null, (, ident}

FIRST(LVALUE) = {ident}

FIRST(LVALUE') = {[, &}

FIRST(NUMEXPRESSION_REC) = {[, &}

FIRST(NUMEXPRESSION_REC') = {[, &}

FIRST(BOOLEXPRESSION) = {(, not, +, -, int_constant, float_constant, string_constant, null, ident}

FIRST(BOOLEXPRESSION') = {and, or, &}

FIRST(BOOLEXPRESSION_OP) = {and, or, &}

## Construção dos FOLLOW das produções

FOLLOW(PROGRAM) = {$}

FOLLOW(FUNCLIST) = {$}

FOLLOW(FUNCLIST') = {$}

FOLLOW(FUNCDEF) = {def, $}

FOLLOW(TYPE) = {ident, [}

FOLLOW(PARAMLIST) = {)}

FOLLOW(PARAMLIST') = {)}

FOLLOW(STATEMENT) = {else, }, {, break, ;, int, float, string, bool, print, read,return, if, for, ident, $}

FOLLOW(VARDECL) = {;}

FOLLOW(VARDECL') = {;}

FOLLOW(INT_LIST) = {;}

FOLLOW(INT_LIST') = {;}

FOLLOW(ATRIBSTAT) = {;, )}

FOLLOW(ATRIBSTAT') = {;, )}

FOLLOW(FUNCCALL) = {;, )}

FOLLOW(PARAMLISTCALL) = {)}

FOLLOW(PARAMLISTCALL') = {)}

FOLLOW(PRINTSTAT) = {;}

FOLLOW(READSTAT) = {;}

FOLLOW(RETURNSTAT) = {;}

FOLLOW(IFSTAT) = {else, }, {, break, ;, int, float, string, bool, print, read, return, if, for, ident, $}

FOLLOW(ELSESTAT) = {else, }, {, break, ;, int, float, string, bool, print, read, return, if, for, ident, $}

FOLLOW(FORSTAT) = {else, }, {, break, ;, int, float, string, bool, print, read, return, if, for, ident, $}

FOLLOW(STATELIST) = {}}

FOLLOW(STATELIST') = {}}

FOLLOW(ALLOCEXPRESSION) = {;, )}

FOLLOW(NUM_LIST) = {;, )}

FOLLOW(NUM_LIST') = {;, )}

FOLLOW(RELOP) = {+, -, int_constant, float_constant, string_constant, null, (, ident}

FOLLOW(EXPRESSION) = {;, )}

FOLLOW(EXPRESSION') = {;, )}

FOLLOW(SIGNAL) = {+, -, int_constant, float_constant, string_constant, null, (, ident}

FOLLOW(NUMEXPRESSION) = {], ;, ), <, >, <=, >=, ==, !=, and, or}

FOLLOW(NUMEXPRESSION') = {], ;, ), <, >, <=, >=, ==, !=, and, or}

FOLLOW(TERM_REC) = {], ;, ), <, >, <=, >=, ==, !=, and, or}

FOLLOW(TERM_REC') = {], ;, ), <, >, <=, >=, ==, !=, and, or}

FOLLOW(OPERATOR) = {+, -, int_constant, float_constant, string_constant, null, (, ident}

FOLLOW(TERM) = {], ;, ), <, >, <=, >=, ==, !=, +, -, and, or}

FOLLOW(TERM') = {], ;, ), <, >, <=, >=, ==, !=, +, -, and, or}

FOLLOW(UNARYEXPR_REC) = {], ;, ), <, >, <=, >=, ==, !=, +, -, and, or}

FOLLOW(UNARYEXPR_REC') = {], ;, ), <, >, <=, >=, ==, !=, +, -, and, or}

FOLLOW(UNARYEXPR) = {], ;, ), <, >, <=, >=, ==, !=, +, -, *, /, %, and, or}

FOLLOW(FACTOR) = {], ;, ), <, >, <=, >=, ==, !=, +, -, *, /, %, and, or}

FOLLOW(LVALUE) = {=, ;, ], ), <, >, <=, >=, ==, !=, +, -, *, /, %, and, or}

FOLLOW(LVALUE') = {=, ;, ], ), <, >, <=, >=, ==, !=, +, -, *, /, %, and, or}

FOLLOW(NUMEXPRESSION_REC) = {=, ;, ], ), <, >, <=, >=, ==, !=, +, -, *, /, %, and, or}

FOLLOW(NUMEXPRESSION_REC') = {=, ;, ], ), <, >, <=, >=, ==, !=, +, -, *, /, %, and, or}

FOLLOW(BOOLEXPRESSION) = {;, ), and, or}

FOLLOW(BOOLEXPRESSION') = {;, ), and, or}

FOLLOW(BOOLEXPRESSION_OP) = {;, ), and, or}

## Corpos das produções

### PROGRAM

FIRST(STATEMENT) = {{, break, ;, int, float, string, bool, print, read, return, if, for, ident}

FIRST(FUNCLIST) = {def}

FIRST(&) = {&}

Para o par PROGRAM -> STATEMENT e PROGRAM -> FUNCLIST:

```math
FIRST(STATEMENT) \cap FIRST(FUNCLIST) = \emptyset
```

Nenhum das produções tem & no FIRST, logo, não precisamos verificar mais nada.

Para o par PROGRAM -> STATEMENT e PROGRAM -> &:

```math
FIRST(STATEMENT) \cap FIRST(&) = \emptyset
```

e

```
FIRST(STATEMENT) \cap FOLLOW(PROGRAM) = \emptyset
```

Verificado para as produções do não terminal PROGRAM.

### FUNCLIST

FIRST(FUNCDEF FUNCLIST') = {def}

Só possui uma produção, não precisamos verificar.

### FUNCLIST'

FIRST(FUNCLIST) = {def}

FIRST(&) = {&}

Temos que:

```math
FIRST(FUNCLIST) \cap FIRST(&) = \emptyset
```

e

```math
FIRST(FUNCLIST) \cap FOLLOW(FUNCLIST') = \emptyset
```

Verificado para as produções do não terminal FUNCLIST'.

### FUNCDEF

FIRST(def ident(PARAMLIST){STATELIST}) = {def}

Só possui uma produção, não precisamos verificar.

### TYPE

FIRST(int) = {int}

FIRST(float) = {float}

FIRST(string) = {string}

FIRST(bool) = {bool}

Todas as produções não possuem intersecção e também não há & em nenhum FIRST.

### PARAMLIST

FIRST(TYPE ident PARAMLIST') = {int, float, string, bool}

FIRST(&) = {&}

Temos que:

```math
FIRST(TYPE ident PARAMLIST') \cap FIRST(&) = \emptyset
```

e

```math
FIRST(TYPE ident PARAMLIST') \cap FOLLOW(PARAMLIST) = \emptyset
```

### PARAMLIST'

FIRST(, PARAMLIST) = {,}

FIRST(&) = {&}

Temos que:

```math
FIRST(, PARAMLIST) \cap FIRST(&) = \emptyset
```

e

```math
FIRST(, PARAMLIST) \cap FOLLOW(PARAMLIST') =  \emptyset
```

### STATEMENT

FIRST(VARDECL;) = {int, float, string, bool}

FIRST(ATRIBSTAT;) = {ident}

FIRST(PRINTSTAT;) = {print}

FIRST(READSTAT;) = {read}

FIRST(RETURNSTAT;) = {return}

FIRST(IFSTAT) = {if}

FIRST(FORSTAT) = {for}

FIRST({STATELIST}) = {{}

FIRST(break;) = {break}

FIRST(;) = {;}

Nenhum FIRST tem intersecção como podemos ver e nenhum possui &.

### VARDECL

FIRST(TYPE ident VARDECL') = {int, float, string, bool}

Só possui uma produção, não precisamos verificar.

### VARDECL'

FIRST(INT_LIST) = {[, &}

FIRST(&) = {&}

Temos que:

```math
FIRST(INT_LIST) \cap FIRST(&) = {&}
```

> Sugestão: remover o & deste não terminal deve ser o suficiente. (FEITO)

### INT_LIST

FIRST([int_constant]INT_LIST') = {[}

FIRST(&) = {&}

Temos que:

```math
FIRST([int_constant]INT_LIST') \cap FIRST(&) = \emptyset
```

e

```math
FIRST([int_constant]INT_LIST') \cap FOLLOW(INT_LIST) = \emptyset
```

Verificado para as produções do não terminal INT_LIST.

### INT_LIST'

FIRST(INT_LIST) = {[, &}

FIRST(&) = {&}

Temos que:

```math
FIRST(INT_LIST) \cap FIRST(&) = {&}
```

> Sugestão: remover o & deste não terminal deve ser o suficiente. (FEITO)

### ATRIBSTAT

FIRST(LVALUE = ATRIBSTAT') = {ident}

Só possui uma produção, não precisamos verificar.

### ATRIBSTAT'

FIRST(EXPRESSION) = {(, not, +, -, int_constant, float_constant, string_constant, null, ident, &}

FIRST(ALLOCEXPRESSION) = {new}

FIRST(FUNCCALL) = {ident}

Temos entre os FIRST:

```math
FIRST(EXPRESSION) \cap FIRST(FUNCCALL) = {ident}
```

> Sugestão: (TODO)

### FUNCCALL

FIRST(ident(PARAMLISTCALL)) = {ident}

Só possui uma produção, não precisamos verificar.

### PARAMLISTCALL

FIRST(ident PARAMLISTCALL') = {ident}

FIRST(&) = {&}

Temos que:

```math
FIRST(ident PARAMLISTCALL') \cap FIRST(&) = \emptyset
```

e

```math
FIRST(ident PARAMLISTCALL') \capt FOLLOW(PARAMLISTCALL) = \emptyset 
```

Verificado para as produções do não terminal PARAMLISTCALL.

### PARAMLISTCALL'

FIRST(, PARAMLISTCALL) = {,}

FIRST(&) = {&}

Temos que:

```math
FIRST(, PARAMLISTCALL) \cap FIRST(&) = \emptyset
```

e

```math
FIRST(, PARAMLISTCALL) \cap FOLLOW(PARAMLISTCALL') = \emptyset 
```

Verificado para as produções do não terminal PARAMLISTCALL'.

### PRINTSTAT

FIRST(print EXPRESSION) = {print}

Só possui uma produção, não precisamos verificar.

### READSTAT

FIRST(read LVALUE) = {read}

Só possui uma produção, não precisamos verificar.

### RETURNSTAT

FIRST(return ident) = {return}

Só possui uma produção, não precisamos verificar.

### IFSTAT

FIRST(if (EXPRESSION) STATEMENT ELSESTAT) = {if}

Só possui uma produção, não precisamos verificar.

### ELSESTAT

FIRST(else STATEMENT) = {else}

FIRST(&) = {&}

Temos que:

```math
FIRST(else STATEMENT) \cap FIRST(&) = \emptyset
```

e

```math
FIRST(else STATEMENT) \cap FOLLOW(ELSESTAT) = {else}
```

> Sugestão: (TODO)

### FORSTAT

FIRST(for (ATRIBSTAT; EXPRESSION; ATRBISTAT) STATEMENT) = {for}

Só possui uma produção, não precisamos verificar.

### STATELIST

FIRST(STATEMENT STATELIST') = {{, break, ;, int, float, string, bool, print, read, return, if, for, ident}

Só possui uma produção, não precisamos verificar.

### STATELIST'

FIRST(STATELIST) = {{, break, ;, int, float, string, bool, print, read, return, if, for, ident}

FIRST(&) = {&}

Temos que:

```math
FIRST(STATELIST) \cap FIRST(&) = \emptyset
```

e

```math
FIRST(STATELIST) \cap FOLLOW(STATELIST') = \emptyset
```

Verificado para as produções do não terminal STATELIST'.

### ALLOCEXPRESSION

FIRST(new TYPE NUM_LIST) = {new}

Só possui uma produção, não precisamos verificar.

### NUM_LIST

FIRST([NUMEXPRESSION]NUM_LIST') = {[}

Só possui uma produção, não precisamos verificar.

### NUM_LIST'

FIRST(NUM_LIST) = {[}

FIRST(&) = {&}

Temos que:

```math
FIRST(NUM_LIST) \cap FIRST(&) = \emptyset
```

e

```math
FIRST(NUM_LIST) \cap FOLLOW(NUM_LIST') = \emptyset
```

Verificado para as produções do não terminal NUM_LIST'.

### RELOP

FIRST(<) = {<}

FIRST(>) = {>}

FIRST(<=) = {<=}

FIRST(>=) = {>=}

FIRST(==) = {==}

FIRST(!=) = {!=}

Como podemos ver nenhum dos FIRST possuem intersecção nem mesmo &.

### EXPRESSION

FIRST(NUMEXPRESSION EXPRESSION') = {[, &}

FIRST(BOOLEXPRESSION) = {(, not, +, -, int_constant, float_constant, string_constant, null, ident}

Temos que:

```math
FIRST(NUMEXPRESSION EXPRESSION') \cap FIRST(BOOLEXPRESSION) = \emptyset
```

e

```math
FIRST(BOOLEXPRESSION) \cap FOLLOW(EXPRESSION) = \emptyset 
```


Verificado para as produções do não terminal EXPRESSION.

### EXPRESSION'

FIRST(RELOP NUMEXPRESSION) = {<, >, <=, >=, ==, !=}

FIRST(&) = {&}

Temos que:

```math
FIRST(RELOP NUMEXPRESSION) \cap FIRST(&) = \emptyset
```

e

```math
FIRST(RELOP NUMEXPRESSION) \cap FOLLOW(EXPRESSION') = \emptyset
```

Verificado para as produções do não terminal EXPRESSION'.

### SIGNAL

FIRST(+) = {+}

FIRST(-) = {-}

Podemos ver que não há intersecção entre FIRST e nem &.

### NUMEXPRESSION

FIRST(TERM NUMEXPRESSION') = {+, -, int_constant, float_constant, string_constant, null, (, ident}

Só possui uma produção, não precisamos verificar.

### NUMEXPRESSION'

FIRST(TERM_REC) = {+, -, &}

FIRST(&) = {&}

Temos que:

```math
FIRST(TERM_REC) \cap FIRST(&) = {&}
```

> Sugestão: Remover o & e verificar se conseguimos chegar no mesmo resultado por TERM_REC, provavelmente sim. (FEITO)

### TERM_REC

FIRST(SIGNAL TERM TERM_REC') = {+, -}

FIRST(&) = {&}

Temos que:

```math
FIRST(SIGNAL TERM TERM_REC') \cap FIRST(&) = \emptyset
```

e

```math
FIRST(SIGNAL TERM TERM_REC') \cap FOLLOW(TERM_REC) = \emptyset
```

Verificado para as produções do não terminal TERM_REC.

### TERM_REC'

FIRST(TERM_REC) = {+, -, &}

FIRST(&) = {&}

Temos que:

```math
FIRST(TERM_REC) \cap TERM(&) = {&}
```

> Sugestão: Remover o & das produções e confiar na produção de & em TERM_REC. (FEITO)

### OPERATOR

FIRST(*) = {*}

FIRST(/) = {/}

FIRST(%) = {%}

Como podemos ver, nenhum FIRST pososui intersecção e nem &.

### TERM

FIRST(UNARYEXPR TERM') = {+, -, int_constant, float_constant, string_constant, null, (, ident}

Só possui uma produção, não precisamos verificar.

### TERM'

FIRST(UNARYEXPR_REC) = {*, /, %, &}

FIRST(&) = {&}

Temos que:

```math
FIRST(UNARYEXPR_REC) \cap FIRST(&) = {&}
```

> Sugestão: remover a produção & e confiar na de UNARYEXPR_REC. (FEITO)

### UNARYEXPR_REC

FIRST(OPERATOR UNARYEXPR UNARYEXPR_REC') = {*, /, %}

FIRST(&) = {&}

Temos que:

```math
FIRST(OPERATOR UNARYEXPR UNARYEXPR_REC') \cap FIRST(&) = \emptyset
```

e

```math
FIRST(OPERATOR UNARYEXPR UNARYEXPR_REC') \cap FOLLOW(UNARYEXPR_REC) = \emptyset
```

Verificado para as produções do não terminal UNARYEXPR_REC.

### UNARYEXPR_REC'

FIRST(UNARYEXPR_REC) = {*, /, %, &}

FIRST(&) = {&}

Temos que:

```math
FIRST(UNARYEXPR_REC) \cap FIRST(&) = {&}
```

> Sugestão: remover a produção & e confiar em UNARYEXPR_REC para esse resultado. (FEITO)

### FACTOR

FIRST(SIGNAL FACTOR) = {+, -}

FIRST(int_constant) = {int_constant}

FIRST(float_constant) = {float_constant}

FIRST(string_constant) = {string_constant}

FIRST(null) = {null}

FIRST(LVALUE) = {ident}

FIRST((NUMEXPRESSION)) = {(}

Como podemos ver, nenhum dos FIRST possui intersecção e nem &.

### LVALUE

FIRST(ident LVALUE') = {ident}

Só possui uma produção, não precisamos verificar.

### LVALUE'

FIRST(NUMEXPRESSION_REC) = {[, &}

FIRST(&) = {&}

Temos que:

```math
FIRST(NUMEXPRESSION_REC) \cap FIRST(&) = {&}
```

> Sugestão: remover a produção & e confiar em NUMEXPRESSION_REC para produzir &. (FEITO)

### NUMEXPRESSION_REC

FIRST([NUMEXPRESSION]NUMEXPRESSION_REC') = {[}

FIRST(&) = {&}

Temos que:

```math
FIRST([NUMEXPRESSION]NUMEXPRESSION_REC') \cap FIRST(&) = \emptyset
```

e

```math
FIRST([NUMEXPRESSION]NUMEXPRESSION_REC') \cap FOLLOW(NUMEXPRESSION_REC) = \emptyset
```

Verificado para as produções do não terminal NUMEXPRESSION_REC'.

### NUMEXPRESSION_REC'

FIRST(NUMEXPRESSION_REC) = {[, &}

FIRST(&) = {&}

Temos que:

```math
FIRST(NUMEXPRESSION_REC) \cap FIRST(&) = {&}
```

> Sugestão: Remover a & produção e produzir ela por NUMEXPRESSION_REC. (FEITO)

### BOOLEXPRESSION

FIRST((BOLLEXPRESSION) BOOLEXPRESSION_OP BOOLEXPRESSION') = {(}

FIRST(not (BOOLEXPRESSION) BOOLEXPRESSION') = {not}

FIRST(NUMEXPRESSION BOOLEXPRESSION') = {+, -, int_constant, float_constant, string_constant, null, (, ident}

Temos que:

```math
FIRST((BOLLEXPRESSION) BOOLEXPRESSION_OP BOOLEXPRESSION') \cap FIRST(NUMEXPRESSION BOOLEXPRESSION') = {(}
```

> Sugestão: não tenho sugestão.

### BOOLEXPRESSION'

FIRST(BOLLEXPRESSION_OP BOOLEXPRESSION') = {and, or, &}

FIRST(&) = {&}

Temos que:

```math
FIRST(BOLLEXPRESSION_OP BOOLEXPRESSION') \cap FIRST(&) = {&}
```

> Sugestão: possivelmente remover a & produção em BOOLEXPRESSION_OP já deve ser o suficiente.

### BOOLEXPRESSION_OP

FIRST(and BOOLEXPRESSION) = {and}

FIRST(or BOOLEXPRESSION) = {or}

FIRST(&) = {&}

Temos que nenhum FIRST tem intersecção e com FOLLOW(BOOLEXPRESSION_OP) = {;, ), and, or}, temos uma intersecção entre tanto FIRST(and BOOLEXPRESSION) e FIRST(or BOOLEXPRESSION).

> Sugestão: talvez unir as produções em BOOLEXPRESSION' e BOOLEXPRESSION_OP para formar apenas uma classe.
