# Verificação de declaração para escopos

Para lidar com a declaração das variáveis a estratégia adotada seŕa:

1. Sempre que iniciarmos um novo escopo, seja ele uma função ou um for loop, iremos copiar a tabela de símbolos principal para a função.
2. Quando tentarmos redefinir um tipo já atribuído a um identificador na mesma tabela de símbolos iremos emitir um erro.

## SDD

Desta forma, teremos a seguinte SDD com as seguintes produções:

| Produção                                                                | Definições                        |
|-------------------------------------------------------------------------|-----------------------------------|
| FUNCLIST -> FUNCDEF FUNCLIST'                                           | { newScope }                      |
| FORSTAT -> for(ATRIBSTAT; EXPRESSION; ATRIBSTAT) STATEMENT              | { newScope }                      |

## SDT

Gerando a seguinte SDT:

FUNCLIST -> { newScope } FUNCDEF FUNCLIST'
STATEMENT -> FORSTAT -> for(ATRIBSTAT; EXPRESSION; ATRIBSTAT) { newScope } STATEMENT 

A função `newScope` irá copiar o conteúdo da tabela de símbolos em FUNCLIST e STATEMENT, para FUNCDEF e FORSTAT respectivamente.

Desta forma, evitamos que identificadores se repitam dentro dos escopos, podendo ser definidos apenas uma vez.
