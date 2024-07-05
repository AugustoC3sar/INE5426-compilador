# Gramática EXPA

ATRIBSTAT' -> EXPRESSION
EXPRESSION -> NUMEXPRESSION  EXPRESSION'
EXPRESSION' -> &
SIGNAL -> +
SIGNAL -> -
NUMEXPRESSION -> TERM NUMEXPRESSION'
NUMEXPRESSION' -> TERM_REC
TERM_REC -> SIGNAL TERM TERM_REC'
TERM_REC -> &
TERM_REC' -> TERM_REC
TERM -> UNARYEXPR TERM'
TERM' -> UNARYEXPR_REC
UNARYEXPR_REC -> OPERATOR UNARYEXPR UNARYEXPR_REC'                           
UNARYEXPR_REC -> &
UNARYEXPR_REC' -> UNARYEXPR_REC
UNARYEXPR -> SIGNAL FACTOR
UNARYEXPR -> FACTOR
FACTOR -> int_constant
FACTOR -> float_constant
OPERATOR -> *
OPERATOR -> /
OPERATOR -> %
FACTOR -> string_constant
FACTOR -> null
FACTOR -> LVALUE
FACTOR -> (NUMEXPRESSION)
LVALUE -> ident LVALUE'

## SDD L-Atribuída

| Produção                                           | Definições                                                                                     |
|----------------------------------------------------|------------------------------------------------------------------------------------------------|
| ATRIBSTAT' -> EXPRESSION                           | ATRIBSTAT'.tree = EXPRESSION.node                                                              |
| EXPRESSION -> NUMEXPRESSION  EXPRESSION'           | EXPRESSION'.leftNode = NUMEXPRESSION.node                                                      |
|                                                    | EXPRESSION.node = EXPRESSION'.node                                                             |
| EXPRESSION' -> &                                   | EXPRESSION'.node = EXPRESSION'.leftNode                                                        |
| SIGNAL -> +                                        | SIGNAL.value = +                                                                               |
| SIGNAL -> -                                        | SIGNAL.value = -                                                                               |
| NUMEXPRESSION -> TERM NUMEXPRESSION'               | NUMEXPRESSION'.leftNode = TERM.node                                                            |
|                                                    | NUMEXPRESSION.node = NUMEXPRESSION'.node                                                       |
| NUMEXPRESSION' -> TERM_REC                         | NUMEXPRESSION'.node = TERM_REC.node                                                            |
| TERM_REC -> SIGNAL TERM TERM_REC'                  | TERM_REC.node = TERM_REC'.node                                                                 |
|                                                    | TERM_REC'.leftNode = new Node(SIGNAL.value, TERM_REC.leftNode, TERM.node)                      |
| TERM_REC -> &                                      | TERM_REC.node = TERM_REC.leftNode                                                              |
| TERM_REC' -> TERM_REC                              | TERM_REC'.node = TERM_REC.node                                                                 |
| TERM -> UNARYEXPR TERM'                            | TERM'.leftNode = UNARYEXPR.node                                                                |
|                                                    | TERM.node = TERM'.node                                                                         |
| TERM' -> UNARYEXPR_REC                             | TERM'.node = UNARYEXPR_REC.node                                                                |
| UNARYEXPR_REC -> OPERATOR UNARYEXPR UNARYEXPR_REC' | UNARYEXPR_REC.node = UNARYEXPR_REC'.node                                                       |
|                                                    | UNARYEXPR_REC'.leftNode = new Node(OPERATOR.value, UNARYEXPR.leftNode, UNARYEXPR_REC.leftNode) |
| UNARYEXPR_REC -> &                                 | UNARYEXPR_REC.node = UNARYEXPR_REC.leftNode                                                    |
| UNARYEXPR_REC' -> UNARYEXPR_REC                    | UNARYEXPR_REC'.node = UNARYEXPR_REC.node                                                       |
| UNARYEXPR -> SIGNAL FACTOR                         | UNARYEXPR.node = new Node(SIGNAL.value, UNARYEXPR.leftNode, FACTOR.node)                       |
| UNARYEXPR -> FACTOR                                | UNARYEXPR.node = FACTOR.node                                                                   |
| FACTOR -> int_constant                             | FACTOR.node = new Node(int_constant.lexValue, NULL, NULL)                                      |
| FACTOR -> float_constant                           | FACTOR.node = new Node(float_constant.lexValue, NULL, NULL)                                    |
| OPERATOR -> *                                      | OPERATOR.value = *                                                                             |
| OPERATOR -> /                                      | OPERATOR.value = /                                                                             |
| OPERATOR -> %                                      | OPERATOR.value = %                                                                             |
| FACTOR -> string_constant                          | FACTOR.node = new Node(string_constant.lexValue, NULL, NULL)                                   |
| FACTOR -> null                                     | FACTOR.node = new Node(null, NULL, NULL)                                                       |
| FACTOR -> LVALUE                                   | FACTOR.node = LVALUE.node                                                                      |
| FACTOR -> (NUMEXPRESSION)                          | FACTOR.node = NUMEXPRESSION.node                                                               |
| LVALUE -> ident LVALUE'                            | FACTOR.node = new Node(ident, NULL, NULL)                                                      |

## SDT

ATRIBSTAT' -> EXPRESSION { ATRIBSTAT'.tree = EXPRESSION.node }
EXPRESSION -> NUMEXPRESSION { EXPRESSION.leftNode = NUMEXPRESSION.node } EXPRESSION' { EXPRESSION.node = EXPRESSION'.node }
EXPRESSION' -> & { EXPRESSION'.node = EXPRESSION'.leftNode}
SIGNAL -> + { SIGNAL.value = + }
SIGNAL -> - { SIGNAL.value = - }
NUMEXPRESSION -> TERM { NUMEXPRESSION'.leftNode = TERM.node } NUMEXPRESSION' { NUMEXPRESSION.node = NUMEXPRESSION'.node }
NUMEXPRESSION' -> TERM_REC { NUMEXPRESSION'.node = TERM_REC.node }
TERM_REC -> SIGNAL TERM { TERM_REC'.leftNode = new Node(SIGNAL.value, TERM_REC.leftNode, TERM.node) } TERM_REC' { TERM_REC.node = TERM_REC'.node }
TERM_REC -> & { TERM_REC.node = TERM_REC.leftNode }
TERM_REC' -> TERM_REC { TERM_REC'.node = TERM_REC.node }
TERM -> UNARYEXPR { TERM.leftNode = UNARYEXPR.node } TERM' { TERM.node = TERM'.node }
TERM' -> UNARYEXPR_REC { TERM'.node = UNARYEXPR_REC.node }
UNARYEXPR_REC -> OPERATOR UNARYEXPR { UNARYEXPR_REC'.leftNode = new Node(OPERATOR.value, UNARYEXPR_REC.leftNode, UNARYEXPR.node) } UNARYEXPR_REC' { UNARYEXPR_REC.node = UNARYEXPR_REC'.node }                    
UNARYEXPR_REC -> & { UNARYEXPR_REC.node = UNARYEXPR_REC.leftNode }
UNARYEXPR_REC' -> UNARYEXPR_REC { UNARYEXPR_REC'.node = UNARYEXPR_REC.node }
UNARYEXPR -> SIGNAL FACTOR { UNARYEXPR.node = new Node(SIGNAL.value, UNARYEXPR.leftNode, FACTOR.node) }
UNARYEXPR -> FACTOR { UNARYEXPR.node = FACTOR.node }
FACTOR -> int_constant { FACTOR.node = new Node(int_constant, NULL, NULL) }
FACTOR -> float_constant { FACTOR.node = new Node(float_constant, NULL, NULL) }
OPERATOR -> * { OPERATOR.value = * }
OPERATOR -> / { OPERATOR.value = / }
OPERATOR -> % { OPERATOR.value = % }
FACTOR -> string_constant { FACTOR.node = new Node(string_constant, NULL, NULL) }
FACTOR -> null { FACTOR.node = new Node(null, NULL, NULL) }
FACTOR -> LVALUE { FACTOR.node = LVALUE.node }
FACTOR -> (NUMEXPRESSION) { FACTOR.node = NUMEXPRESSION.node }
LVALUE -> ident LVALUE' { FACTOR.node = new Node(ident, NULL, NULL) }

## Ações semânticas

Vamos separar as ações semânticas em algumas que são comuns a todos. Primeiro iremos enumerá-las:

1 - { ATRIBSTAT'.tree = EXPRESSION.node }
2 - { EXPRESSION.leftNode = NUMEXPRESSION.node }
3 - { EXPRESSION.node = EXPRESSION'.node }
4 - { EXPRESSION'.node = EXPRESSION'.leftNode}
5 - { SIGNAL.value = + }
6 - { SIGNAL.value = - }
7 - { NUMEXPRESSION'.leftNode = TERM.node }
8 - { NUMEXPRESSION.node = NUMEXPRESSION'.node }
9 - { NUMEXPRESSION'.node = TERM_REC.node }
10 - { TERM_REC'.leftNode = new Node(SIGNAL.value, TERM_REC.leftNode, TERM.node) }
11 - { TERM_REC.node = TERM_REC'.node }
12 - { TERM_REC.node = TERM_REC.leftNode }
13 - { TERM_REC'.node = TERM_REC.node }
14 - { TERM.leftNode = UNARYEXPR.node }
15 - { TERM.node = TERM'.node }
16 - { TERM'.node = UNARYEXPR_REC.node }
17 - { UNARYEXPR_REC'.leftNode = new Node(OPERATOR.value, UNARYEXPR_REC.leftNode, UNARYEXPR.node) }
18 - { UNARYEXPR_REC.node = UNARYEXPR_REC'.node }                    
19 - { UNARYEXPR_REC.node = UNARYEXPR_REC.leftNode }
20 - { UNARYEXPR_REC'.node = UNARYEXPR_REC.node }
21 - { UNARYEXPR.node = new Node(SIGNAL.value, UNARYEXPR.leftNode, FACTOR.node) }
22 - { UNARYEXPR.node = FACTOR.node }
23 - { FACTOR.node = new Node(int_constant, NULL, NULL) }
24 - { FACTOR.node = new Node(float_constant, NULL, NULL) }
25 - { OPERATOR.value = * }
26 - { OPERATOR.value = / }
27 - { OPERATOR.value = % }
28 - { FACTOR.node = new Node(string_constant, NULL, NULL) }
29 - { FACTOR.node = new Node(null, NULL, NULL) }
30 - { FACTOR.node = LVALUE.node }
31 - { FACTOR.node = NUMEXPRESSION.node }
32 - { FACTOR.node = new Node(ident, NULL, NULL) }

                 
21 - { UNARYEXPR.node = new Node(SIGNAL.value, UNARYEXPR.leftNode, FACTOR.node) }
17 - { UNARYEXPR_REC'.leftNode = new Node(OPERATOR.value, UNARYEXPR_REC.leftNode, UNARYEXPR.node) }
14 - { TERM.leftNode = UNARYEXPR.node }
10 - { TERM_REC'.leftNode = new Node(SIGNAL.value, TERM_REC.leftNode, TERM.node) }
7 - { NUMEXPRESSION'.leftNode = TERM.node }
2 - { EXPRESSION.leftNode = NUMEXPRESSION.node }

Primeiro trataremos de todas as ações semânticas que criam nós folhas em uma ação semântica "createLeafNode"

createLeafNode = new Node(TERMINAL, NULL, NULL)

Agora todas as operações que realizam este padrão:

PARENT_NON_TERMINAL.node = LAST_CHILD.node

Serão a ação semântica "returnNode".

Agora todas as ações semânticas que passam um valor ao nó pai do tipo de operação sendo feita será o "returnOperationValue":

OPERATION.value = TERMINAL.lexicalValue

Quanto as ações 19, 12 e 4 elas se tornarão a ação semântica "synthesizeNode":

NONTERMINAL.node = NONTERMINAL.leftNode

Por fim, teremos as ações seguintes para os números:

21: createSignalNode
17: createOperatorNode
14: inheritUnaryexprNode
10: createTermSignalNode
7: inheritTermNode
2: inheritNumexpressionNode
