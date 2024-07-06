# Geração de código intermediário

Teremos que criar uma SDD para a geração de código de todas as nossas produções de acordo com o que elas fazem.

| Produção                                                      | Definições|
|---------------------------------------------------------------|-----------|
| PROGRAM -> STATEMENT                                          | PROGRAM.code = STATEMENT.code |
| PROGRAM -> FUNCLIST                                           | PROGRAM.code = FUNCLIST.code |
| PROGRAM -> &                                                  | PROGRAM.code = '' |
| FUNCLIST -> FUNCDEF FUNCLIST'                                 | FUNCLIST.code = FUNCDEF.code || FUNCLIST'.code |
| FUNCLIST' -> &                                                | FUNCLIST'.code = '' |
| FUNCDEF -> def ident(PARAMLIST) { STATELIST }                 | |
| TYPE -> int                                                   | TYPE.code = '' |
| VARDECL -> TYPE ident ARRAYVARDECL                            | VARDECL.code = '' |
| ATRIBSTAT -> LVALUE = ATRIBSTAT'                              | ATRIBSTAT.code = LVALUE.code || ATRIBSTAT'.code' || LVALUE.return = ATRIBSTAT'.return |
| LVALUE -> ident LVALUE'                                       | LVALUE'.inhType = LVALUE.type |
|                                                               | LVALUE.type = LVALUE'.type |
|                                                               | { t = newT() } |
|                                                               | LVALUE.code = "t = ident" |
|                                                               | LVALUE.return = t |
| LVALUE' -> NUMEXPRESSION_REC                                  | NUMEXPRESSION_REC.inhType = LVALUE'.inhType |
|                                                               | LVALUE'.type = NUMEXPRESSION_REC.type |
| NUMEXPRESSION_REC -> &                                        | NUMEXPRESSION_REC.type = NUMEXPRESSION_REC.inhType |
| ATRIBSTAT' -> EXPRESSION                                      | ATRIBSTAT'.code = ATRIBSTAT'.node.code |
|                                                               | ATRIBSTAT'.return = ATRIBSTAT'.node.return |
| EXPRESSION -> NUMEXPRESSION EXPRESSION'                       | |
| EXPRESSION' -> RELOP NUMEXPRESSION                            | |
| EXPRESSION' -> &                                              | |
| NUMEXPRESSION ->  TERM NUMEXPRESSION'                         | |
| NUMEXPRESSION' -> TERM_REC                                    | |
| TERM_REC -> SIGNAL TERM TERM_REC'                             | |
| TERM_REC -> &                                                 | |
| TERM_REC' -> TERM_REC                                         | |
| TERM -> UNARYEXPR TERM'                                       | |
| TERM' -> UNARYEXPR_REC                                        | |
| UNARYEXPR_REC -> OPERATOR UNARYEXPR UNARYEXPR_REC'            | |
| UNARYEXPR_REC -> &                                            | |
| UNARYEXPR_REC' -> UNARYEXPR_REC                               | |
| UNARYEXPR -> SIGNAL FACTOR                                    | |
| UNARYEXPR -> FACTOR                                           | |
















| FUNCLIST' -> FUNCLIST                                         | FUNCLIST'.code = FUNCLIST.code |
| TYPE -> float                                                 | |
| TYPE -> string                                                | |
| PARAMLIST -> TYPE ident PARAMLIST'                            | |
| PARAMLIST -> &                                                | |
| PARAMLIST' -> , PARAMLIST                                     | |
| PARAMLIST' -> &                                               | |
| STATEMENT -> VARDECL;                                         | STATEMENT.code = VARDECL.code |
| STATEMENT -> ATRIBSTAT;                                       | STATEMENT.code = ATRIBSTAT.code |
| STATEMENT -> PRINTSTAT;                                       | STATEMENT.code = PRINTSTAT.code |
| STATEMENT -> READSTAT;                                        | STATEMENT.code = READSTAT.code |
| STATEMENT -> RETURNSTAT;                                      | STATEMENT.code = RETURNSTAT.code |
| STATEMENT -> IFSTAT                                           | |
| STATEMENT -> FORSTAT                                          | |
| STATEMENT -> {STATELIST}                                      | |
| STATEMENT -> break;                                           | |
| STATEMENT -> ;                                                | |
| VARDECL -> TYPE ident ARRAYVARDECL                            | |
| ARRAYVARDECL -> [int_constant] ARRAYVARDECL                   | |
| ARRAYVARDECL -> &                                             | |
| ATRIBSTAT -> LVALUE = ATRIBSTAT'                              | ATRIBSTAT.code = LVALUE.code || ATRIBSTAT'.code || LVALUE.return = ATRIBSTAT'.return |
| ATRIBSTAT' -> EXPRESSION                                      | ATRIBSTAT'.code = ATRIBSTAT'.node.code |
|                                                               | ATRIBSTAT'.return = ATRIBSTAT'.node.return |
| ATRIBSTAT' -> ALLOCEXPRESSION                                 | |
| ATRIBSTAT' -> FUNCCALL                                        | ATRIBSTAT'.code = FUNCCALL.code |
|                                                               |
| FUNCCALL -> call ident(PARAMLISTCALL)                         | |
| PARAMLISTCALL -> identPARAMLISTCALL'                          | |
| PARAMLISTCALL -> &                                            | |
| PARAMLISTCALL' -> , PARAMLISTCALL                             | |
| PARAMLISTCALL' -> &                                           | |
| PRINTSTAT -> print EXPRESSION                                 | |
| READSTAT -> read LVALUE                                       | |
| RETURNSTAT -> return                                          | |
| IFSTAT -> if ( EXPRESSION ) { STATELIST } ELSESTAT            | |
| ELSESTAT -> else { STATEMENT }                                | |
| ELSESTAT -> &                                                 | |
| FORSTAT -> for(ATRIBSTAT; EXPRESSION; ATRIBSTAT) STATEMENT    | |
| STATELIST -> STATEMENT STATELIST'                             | |
| STATELIST' -> STATELIST                                       | |
| STATELIST' -> &                                               | |
| ALLOCEXPRESSION -> new TYPE NUM_LIST                          | |
| NUM_LIST -> [NUMEXPRESSION]NUM_LIST'                          | |
| NUM_LIST' -> NUM_LIST                                         | |
| NUM_LIST' -> &                                                | |
| RELOP -> <                                                    | RELOP.operationValue = <  |
| RELOP -> >                                                    | RELOP.operationValue = >  |
| RELOP -> <=                                                   | RELOP.operationValue = <= |
| RELOP -> >=                                                   | RELOP.operationValue = >= |
| RELOP -> == UNARYEXPR                                                  | RELOP.operationValue = == |
| RELOP -> !=                                                   | RELOP.operationValue = != |
| EXPRESSION -> NUMEXPRESSION EXPRESSION'                       | |
| EXPRESSION' -> RELOP NUMEXPRESSION                            | |
| EXPRESSION' -> &                                              | |
| SIGNAL -> +                                                   | SIGNAL.operationValue = + |
| SIGNAL -> -                                                   | SIGNAL.operationValue = - |
| NUMEXPRESSION ->  TERM NUMEXPRESSION'                         | |
| NUMEXPRESSION' -> TERM_REC                                    | |
| TERM_REC -> SIGNAL TERM TERM_REC'                             | |
| TERM_REC -> &                                                 | |
| TERM_REC' -> TERM_REC                                         | |
| OPERATOR -> *                                                 | OPERATOR.operationValue = * |
| OPERATOR -> /                                                 | OPERATOR.operationValue = / |
| OPERATOR -> %                                                 | OPERATOR.operationValue = % |
| TERM -> UNARYEXPR TERM'                                       | |
| TERM' -> UNARYEXPR_REC                                        | |
| UNARYEXPR_REC -> OPERATOR UNARYEXPR UNARYEXPR_REC'            | |
| UNARYEXPR_REC -> &                                            | |
| UNARYEXPR_REC' -> UNARYEXPR_REC                               | |
| UNARYEXPR -> SIGNAL FACTOR                                    | |
| UNARYEXPR -> FACTOR                                           | |
| FACTOR -> int_constant                                        | |
| FACTOR -> float_constant                                      | |
| FACTOR -> string_constant                                     | |
| FACTOR -> null                                                | |
| FACTOR -> LVALUE                                              | |
| FACTOR -> (NUMEXPRESSION)                                     | |
| LVALUE -> ident LVALUE'                                       | LVALUE'.inhType = ident.type |
|                                                               | LVALUE.type = LVALUE.type |
|                                                               | LVALUE.return = ident[LVALUE'.return]
|                                                               | LVALUE.code = LVALUE'.code |
| LVALUE' -> NUMEXPRESSION_REC                                  | NUMEXPRESSION_REC.inhType = LVALUE'.type |
|                                                               | LVALUE'.code = NUMEXPRESSION_REC.code |
|                                                               | LVALUE'.return = NUMEXPRESSION_REC.return |
| NUMEXPRESSION_REC -> [NUMEXPRESSION] NUMEXPRESSION_REC'       | NUMEXPRESSION_REC'.inhType = Array(NUMEXPRESSION_REC.type) |
|                                                               | NUMEXPRESSION_REC.type = NUMEXPRESSION_REC'.type |
|                                                               | { t = generateT() } |
|                                                               | NUMEXPRESSION_REC.return = t |
|                                                               | NUMEXPRESSION_REC.code = NUMEXPRESSION.code || t = NUMEXPRESSION.return * NUMEXPRESSION_REC.type.arraySize() |
| NUMEXPRESSION_REC -> &                                        | NUMEXPRESSION_REC.type = NUMEXPRESSION_REC.inhType  |
| NUMEXPRESSION_REC' -> NUMEXPRESSION_REC                       | NUMEXPRESSION_REC.inhType = NUMEXPRESSION_REC'.type |
|                                                               | NUMEXPRESSION_REC'.type = NUMEXPRESSION_REC.type |

Estou assumindo que todos os 
