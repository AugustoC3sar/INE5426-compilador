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