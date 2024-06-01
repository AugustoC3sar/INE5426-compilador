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

FIRST(PROGRAM) = {{, break, ;, int, float, string, print, read, return, if, for, def, ident, &}

FIRST(FUNCLIST) = {def}

FIRST(FUNCLIST') = {def, &}

FIRST(FUNCDEF) = {def}

FIRST(TYPE) = {int, float, string}

FIRST(PARAMLIST) = {int, float, string, &}

FIRST(PARAMLIST') = {,, &}

FIRST(STATEMENT) = {{, break, ;, int, float, string, print, read, return, if, for, ident}

FIRST(VARDECL) = {int, float, string}

FIRST(ARRAY_VARDECL) = {int, float, string}

FIRST(INT_LIST) = {[, &}

FIRST(INT_LIST') = {[, &}

FIRST(ATRIBSTAT) = {ident}

FIRST(ATRIBSTAT') = {new, call, +, -, int_constant, float_constant, string_constant, null, (, ident}

FIRST(FUNCCALL) = {call}

FIRST(PARAMLISTCALL) = {ident, &}

FIRST(PARAMLISTCALL') = {,, &}

FIRST(PRINTSTAT) = {print}

FIRST(READSTAT) = {read}

FIRST(RETURNSTAT) = {return}

FIRST(IFSTAT) = {if}

FIRST(ELSESTAT) = {else}

FIRST(FORSTAT) = {for}

FIRST(STATELIST) = {{, break, ;, int, float, string, print, read, return, if, for, ident}

FIRST(STATELIST') = {{, break, ;, int, float, string, print, read, return, if, for, ident, &}

FIRST(ALLOCEXPRESSION) = {new}

FIRST(NUM_LIST) = {[}

FIRST(NUM_LIST') = {[, &}

FIRST(RELOP) = {<, >, <=, >=, ==, !=}

FIRST(EXPRESSION) = {(, not, +, -, int_constant, float_constant, string_constant, null, ident, &}

FIRST(EXPRESSION') = {<, >, <=, >=, ==, !=, &}

FIRST(SIGNAL) = {+, -}

FIRST(NUMEXPRESSION) = {+, -, int_constant, float_constant, string_constant, null, (, ident}

FIRST(NUMEXPRESSION') = {+, -, &}

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

## Construção dos FOLLOW das produções

FOLLOW(PROGRAM) = {$}

FOLLOW(FUNCLIST) = {$}

FOLLOW(FUNCLIST') = {$}

FOLLOW(FUNCDEF) = {def, $}

FOLLOW(TYPE) = {ident, [}

FOLLOW(PARAMLIST) = {)}

FOLLOW(PARAMLIST') = {)}

FOLLOW(STATEMENT) = {}, {, break, ;, int, float, string, print, read,return, if, for, ident, $}

FOLLOW(VARDECL) = {;}

FOLLOW(ARRAYVARDECL) = {;}

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

FOLLOW(IFSTAT) = {}, {, break, ;, int, float, string, print, read, return, if, for, ident, $}

FOLLOW(ELSESTAT) = {}, {, break, ;, int, float, string, print, read, return, if, for, ident, $}

FOLLOW(FORSTAT) = {}, {, break, ;, int, float, string, print, read, return, if, for, ident, $}

FOLLOW(STATELIST) = {}}

FOLLOW(STATELIST') = {}}

FOLLOW(ALLOCEXPRESSION) = {;, )}

FOLLOW(NUM_LIST) = {;, )}

FOLLOW(NUM_LIST') = {;, )}

FOLLOW(RELOP) = {+, -, int_constant, float_constant, string_constant, null, (, ident}

FOLLOW(EXPRESSION) = {;, )}

FOLLOW(EXPRESSION') = {;, )}

FOLLOW(SIGNAL) = {+, -, int_constant, float_constant, string_constant, null, (, ident}

FOLLOW(NUMEXPRESSION) = {], ;, ), <, >, <=, >=, ==, !=}

FOLLOW(NUMEXPRESSION') = {], ;, ), <, >, <=, >=, ==, !=}

FOLLOW(TERM_REC) = {], ;, ), <, >, <=, >=, ==, !=}

FOLLOW(TERM_REC') = {], ;, ), <, >, <=, >=, ==, !=}

FOLLOW(OPERATOR) = {+, -, int_constant, float_constant, string_constant, null, (, ident}

FOLLOW(TERM) = {], ;, ), <, >, <=, >=, ==, !=, +, -}

FOLLOW(TERM') = {], ;, ), <, >, <=, >=, ==, !=, +, -}

FOLLOW(UNARYEXPR_REC) = {], ;, ), <, >, <=, >=, ==, !=, +, -}

FOLLOW(UNARYEXPR_REC') = {], ;, ), <, >, <=, >=, ==, !=, +, -}

FOLLOW(UNARYEXPR) = {], ;, ), <, >, <=, >=, ==, !=, +, -, *, /, %}

FOLLOW(FACTOR) = {], ;, ), <, >, <=, >=, ==, !=, +, -, *, /, %}

FOLLOW(LVALUE) = {=, ;, ], ), <, >, <=, >=, ==, !=, +, -, *, /, %}

FOLLOW(LVALUE') = {=, ;, ], ), <, >, <=, >=, ==, !=, +, -, *, /, %}

FOLLOW(NUMEXPRESSION_REC) = {=, ;, ], ), <, >, <=, >=, ==, !=, +, -, *, /, %}

FOLLOW(NUMEXPRESSION_REC') = {=, ;, ], ), <, >, <=, >=, ==, !=, +, -, *, /, %}

## Corpos das produções

### PROGRAM

FOLLOW(PROGRAM) = {$}

PROGRAM -> STATEMENT
PROGRAM -> FUNCLIST
PROGRAM -> &

FIRST(STATEMENT) = {{, break, ;, int, float, string, print, read, return, if, for, ident}
FIRST(FUNCLIST) = {def}
FIRST(&) = {&}

Vamos tomar PROGRAM -> STATEMENT e PROGRAM -> FUNCLIST:

Não temos intersecção entre FIRST e nenhum FIRST possui &.

Agora PROGRAM -> STATEMENT e PROGRAM -> &:

```math
FIRST(STATEMENT) \cap FIRST(&) = \emptyset
```

e

```math
FIRST(STATEMENT) \cap FOLLOW(PROGRAM) = \emptyset
```

Agora, finalmente, tomamos PROGRAM -> FUNCLIST e PROGRAM -> &:

```math
FIRST(FUNCLIST) \cap FIRST(&) = \emptyset
```

e

```math
FIRST(FUNCLIST) \cap FIRST(&) = \emptylist
```

Verificado para o não terminal PROGRAM.

### FUNCLIST

FOLLOW(FUNCLIST) = {$}

FUNCLIST -> FUNCDEF FUNCLIST'

Só possui uma produção, não precisamos verificar.

### FUNCLIST'

FOLLOW(FUNCLIST') = {$}

FUNCLIST' -> FUNCLIST
FUNCLIST' -> &

FIRST(FUNCLIST) = {def}
FIRST(&) = {&}

Podemos ver que não possui intersecção entre os FIRST e nem entre FIRST(FUNCLIST) e FOLLOW(FUNCLIST'), logo está verificado.

### FUNCDEF

FOLLOW(FUNCDEF) = {def, $}

FUNCDEF -> def ident(PARAMLIST){STATELIST}

Só possui uma produção, não precisamos verificar.

### TYPE

FOLLOW(TYPE) = {ident, [}

TYPE -> int
TYPE -> float
TYPE -> string

FIRST(int) = {int}
FIRST(float) = {float}
FIRST(string) = {string}

Podemos ver que não possui intersecção entre FIRST e nem um FIRST possui &, logo está verificado.

### PARAMLIST

FOLLOW(PARAMLIST) = {)}

PARAMLIST -> TYPE identPARAMLIST'
PARAMLIST -> &

FIRST(TYPE identPARAMLIST') = {int, float, string}
FIRST(&)

Temos:

```math
FIRST(TYPE identPARAMLIST') \cap FIRST(&) = \emptyset
```

e

```math
FIRST(TYPE identPARAMLIST') \cap FOLLOW(PARAMLIST) = \emptyset
```

Verificado para o não terminal PARAMLIST.

### PARAMLIST'

FOLLOW(PARAMLIST') = {)}

PARAMLIST' -> , PARAMLIST
PARAMLIST' -> &

FIRST(, PARAMLIST) = {,}
FIRST(&) = {&}

Temos:

```math
FIRST(, PARAMLIST) \cap FIRST(&) = \emptyset
```

e

```math
FIRST(, PARAMLIST) \cap FOLLOW(PARAMLIST') = \emptyset
```

Verificado para o não terminal PARAMLIST.

### STATEMENT

FOLLOW(STATEMENT) = {}, {, break, ;, int, float, string, print, read,return, if, for, ident, $}

STATEMENT -> VARDECL;
STATEMENT -> ATRIBSTAT;
STATEMENT -> PRINTSTAT;
STATEMENT -> READSTAT;
STATEMENT -> RETURNSTAT;
STATEMENT -> IFSTAT
STATEMENT -> FORSTAT
STATEMENT -> {STATELIST}
STATEMENT -> break;
STATEMENT -> ;

FIRST(VARDECL;) = {int, float, string}
FIRST(ATRIBSTAT;) = {ident}
FIRST(PRINTSTAT;) = {print}
FIRST(READSTAT;) = {read}
FIRST(RETURNSTAT;) = {return}
FIRST(IFSTAT) = {if}
FIRST(FORSTAT) = {for}
FIRST({STATELIST}) = {{}
FIRST(break;) = {break}
FIRST(;) = {;}

Como podemos ver não possui nenhuma intersecção entre os FIRST e nenhum FIRST possui &, logo, está verificado.

### VARDECL

FOLLOW(VARDECL) = {;}

VARDECL -> TYPE ident
VARDECL -> ARRAYVARDECL

FIRST(TYPE ident) = {int, float, string}
FIRST(ARRAYVARDECL) = {[, &}

Temos:

```math
FIRST(TYPE ident) \cap FIRST(ARRAYVARDECL) = \emptyset
```

e

```math
FIRST(TYPE ident) \cap FOLLOW(VARDECL) = \emptyset
```

Verificado para o não terminal VARDECL.

### ARRAYVARDECL

FOLLOW(ARRAYVARDECL) = {;}

ARRAYVARDECL -> [int_constant] ARRAYVARDECL
ARRAYVARDECL -> &

FIRST([int_constant] ARRAYVARDECL) = {[}
FIRST(&) = {&}

Temos:

```math
FIRST([int_constant] ARRAYVARDECL) \cap FIRST(&) = \emptyset
```

e

```math
FIRST([int_constant] ARRAYVARDECL) \cap FOLLOW(ARRAYVARDECL) = \emptyset
```

Verificado para o não terminal ARRAYVARDECL.

### ATRIBSTAT

FOLLOW(ATRIBSTAT) = {;, )}

ATRIBSTAT -> LVALUE = ATRIBSTAT'

Só possui uma produção, não precisamos verificar.

### ATRIBSTAT'

FOLLOW(ATRIBSTAT') = {;, )}

ATRIBSTAT' -> EXPRESSION
ATRIBSTAT' -> ALLOCEXPRESSION
ATRIBSTAT' -> FUNCCALL

FIRST(EXPRESSION) =  {(, not, +, -, int_constant, float_constant, string_constant, null, ident, &}
FIRST(ALLOCEXPRESSION) = {new}
FIRST(FUNCCALL) = {call}

Claramente não há nenhum problema entre FIRST(ALLOCEXPRESSION) e FIRST(FUNCCALL).

Para ATRIBSTAT' -> EXPRESSION e ATRIBSTAT' -> FUNCCALL, temos:

```math
FIRST(EXPRESSION) \cap FIRST(FUNCCALL) = \emptyset
```

e

```math
FIRST(FUNCCALL) \cap FOLLOW(ATRIBSTAT') = \emptyset
```

Agora, para ATRIBSTAT' -> EXPRESSION e ATRIBSTAT' -> ALLOCEXPRESSION, temos:

```math
FIRST(EXPRESSION) \cap FIRST(ALLOCEXPRESSION) = \emptyset
```

e

```math
FIRST(ALLOCEXPRESSOIN) \cap FOLLOW(ATRIBSTAT') = \emptyset
```

Verificado para o não terminal ATRIBSTAT';

### FUNCCALL

FOLLOW(FUNCCALL) = {;, )}

FUNCCALL -> call ident(PARAMLISTCALL)

Só possui uma produção, não precisamos verificar.

### PARAMLISTCALL

FOLLOW(PARAMLISTCALL) = {)}

PARAMLISTCALL -> identPARAMLISTCALL'
PARAMLISTCALL -> &

FIRST(identPARAMLISTCALL') = {ident}
FIRST(&) = &

Temos:

```math
FIRST(identPARAMLISTCALL') \cap FIRST(&) = \emptyset
```

e

```math
FIRST(identPARAMLISTCALL') \cap FOLLOW(PARAMLISTCALL) = \emptyset.
```

Verificado para o não terminal PARAMLISTCALL.

### PARAMLISTCALL'

FOLLOW(PARAMLISTCALL') = {)}

PARAMLISTCALL' -> , PARAMLISTCALL
PARAMLISTCALL' -> &

FIRST(, PARAMLISTCALL) = {,}
FIRST(&)

Não realizaremos o processo, pois claramente não há intersecção entre FIRSTs e nem entre FIRST(, PARAMLISTCALL) e FOLLOW(PARAMLISTCALL').

### PRINTSTAT

PRINTSTAT -> print EXPRESSION

Só possui uma produção, não precisamos verificar.

### READSTAT

READSTAT -> read LVALUE

Só possui uma produção, não precisamos verificar.

### RETURNSTAT

RETURNSTAT -> return ident

Só possui uma produção, não precisamos verificar.

### IFSTAT

IFSTAT -> if ( EXPRESSION ) { STATEMENT } ELSESTAT

Só possui uma produção, não precisamos verificar.

### ELSESTAT

FOLLOW(ELSESTAT) = {}, {, break, ;, int, float, string, print, read, return, if, for, ident, $}

ELSESTAT -> else { STATEMENT }
ELSESTAT -> &

FIRST(else { STATEMENT }) = {else}
FIRST(&) = {&}

Não há intersecção entre os FIRST e também entre FIRST(else { STATEMENT }) e FOLLOW(ELSESTAT)

### FORSTAT

FORSTAT -> for(ATRIBSTAT; EXPRESSION; ATRIBSTAT) STATEMENT

Só possui uma produção, não precisamos verificar.

### STATELIST

STATELIST -> STATEMENT STATELIST'

Só possui uma produção, não precisamos verificar.

### STATELIST'

FOLLOW(STATELIST') = {}}

STATELIST' -> STATELIST
STATELIST' -> &

FIRST(STATELIST) = {{, break, ;, int, float, string, print, read, return, if, for, ident}
FIRST(&) = {&}

Não há intersecção entre os FIRST e também entre FIRST(STATELIST) e FOLLOW(STATELIST').

### ALLOCEXPRESSION

ALLOCEXPRESSION -> new TYPE NUM_LIST

Só possui uma produção, não precisamos verificar.

### NUM_LIST

NUM_LIST -> [NUMEXPRESSION]NUM_LIST'

Só possui uma produção, não precisamos verificar.

### NUM_LIST'

FOLLOW(NUM_LIST') = {;, )}

NUM_LIST' -> NUM_LIST
NUM_LIST' -> &

FIRST(NUM_LIST) = {[}
FIRST(&) = {&}

Não há intersecção entre os FIRST e também entre FIRST(NUM_LIST) e FOLLOW(NUM_LIST').

### RELOP

FOLLOW(RELOP) = {+, -, int_constant, float_constant, string_constant, null, (, ident}

RELOP -> <
RELOP -> >
RELOP -> <=
RELOP -> >=
RELOP -> ==
RELOP -> !=

FIRST(<) = {<}
FIRST(>) = {>}
FIRST(<=) = {<=}
FIRST(>=) = {>=}
FIRST(==) = {==}
FIRST(!=) = {!=}

Não há intersecção entre os FIRST nem & entre eles.

### EXPRESSION

EXPRESSION -> NUMEXPRESSION EXPRESSION'

Só possui uma produção, não precisamos verificar.

### EXPRESSION'

FOLLOW(EXPRESSION') = {;, )}

EXPRESSION' -> RELOP NUMEXPRESSION
EXPRESSION' -> &

FIRST(RELOP NUMEXPRESSION) = {<, >, <=, >=, ==, !=}
FIRST(&)

Não há intersecção entre FIRST(RELOP NUMEXPRESSION) e FIRST(&), nem entre FIRST(RELOP NUMEXPRESSION) e FOLLOW(EXPRESSION').

### SIGNAL

SIGNAL -> +
SIGNAL -> -

FIRST(+) = {+}
FIRST(-) = {-}

Não há intersecção entre os FIRST nem & entre eles.

### NUMEXPRESSION

NUMEXPRESSION ->  TERM NUMEXPRESSION' 

Só possui uma produção, não precisamos verificar.

### NUMEXPRESSION'

NUMEXPRESSION' -> TERM_REC

Só possui uma produção, não precisamos verificar.

### TERM_REC

FOLLOW(TERM_REC) = {], ;, ), <, >, <=, >=, ==, !=} 

TERM_REC -> SIGNAL TERM TERM_REC'
TERM_REC -> &

FIRST(SIGNAL TERM TERM_REC') = {+, -}
FIRST(&)

Não há intersecção entre FIRST(SIGNAL TERM TERM_REC') e FIRST(&), nem entre FIRST(SIGNAL TERM TERM_REC') e FOLLOW(TERM_REC).

### TERM_REC'

TERM_REC' -> TERM_REC

Só possui uma produção, não precisamos verificar.

### OPERATOR

OPERATOR -> *
OPERATOR -> /
OPERATOR -> %

FIRST(*) = {\*}
FIRST(/) = {/}
FIRST(%) = {%}

Não há intersecção entre os FIRST nem & neles.

### TERM

TERM -> UNARYEXPR TERM'

Só possui uma produção, não precisamos verificar.

### TERM'

TERM' -> UNARYEXPR_REC

Só possui uma produção, não precisamos verificar.

### UNARYEXPR_REC

FOLLOW(UNARYEXPR_REC) = {], ;, ), <, >, <=, >=, ==, !=, +, -}

UNARYEXPR_REC -> OPERATOR UNARYEXPR UNARYEXPR_REC'
UNARYEXPR_REC -> &

FIRST(OPERATOR UNARYEXPR UNARYEXPR_REC') = {*, /, %}
FIRST(&)

Não há intersecção entre FIRST(OPERATOR UNARYEXPR UNARYEXPR_REC') e FIRST(&), nem entre FIRST(OPERATOR UNARYEXPR UNARYEXPR_REC') e FOLLOW(UNARYEXPR_REC).

### UNARYEXPR_REC'

UNARYEXPR_REC' -> UNARYEXPR_REC

Só possui uma produção, não precisamos verificar.

### UNARYEXPR

UNARYEXPR -> SIGNAL FACTOR
UNARYEXPR -> FACTOR

FIRST(SIGNAL FACTOR) = {+, -}
FIRST(FACTOR) = {int_constant, float_constant, string_constant, null, (, ident}

Não há intersecção entre os FIRST nem & neles.

### FACTOR

FACTOR -> int_constant
FACTOR -> float_constant
FACTOR -> string_constant
FACTOR -> null
FACTOR -> LVALUE
FACTOR -> (NUMEXPRESSION)

FIRST(int_constant) = {int_constant}
FIRST(float_constant) = {float_constant}
FIRST(string_constant) = {string_constant}
FIRST(null) = {null}
FIRST(LVALUE) = {ident}
FIRST((NUMEXPRESSION)) = {(}

Não há intersecção entre os FIRST nem & neles.

### LVALUE

LVALUE -> ident LVALUE'

Só possui uma produção, não precisamos verificar.

### LVALUE'

LVALUE' -> NUMEXPRESSION_REC

Só possui uma produção, não precisamos verificar.

### NUMEXPRESSION_REC

FOLLOW(NUMEXPRESSION_REC) = {=, ;, ], ), <, >, <=, >=, ==, !=, +, -, *, /, %}

NUMEXPRESSION_REC -> [NUMEXPRESSION] NUMEXPRESSION_REC'
NUMEXPRESSION_REC -> &

FIRST([NUMEXPRESSION] NUMEXPRESSION_REC') = {[}
FIRST(&) = {&}

Não há intersecção entre FIRST([NUMEXPRESSION] NUMEXPRESSION_REC') e FIRST(&), nem entre FIRST([NUMEXPRESSION] NUMEXPRESSION_REC') e FOLLOW(NUMEXPRESSION_REC).

### NUMEXPRESSION_REC'

NUMEXPRESSION_REC' -> NUMEXPRESSION_REC

Só possui uma produção, não precisamos verificar.

## Conclusão

Como pudemos ver, para cada par de produções de um não terminal as regras são respeitadas para classificar a gramática como sendo LL1.
