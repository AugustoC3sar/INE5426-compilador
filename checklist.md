## Analisador Léxico

- [X] Ler caracter por caracter da entrada
- [ ] Baseado em diagramas de transição

## Tabela de símbolos

- [X] Uma entrada por token Identificador
- [X] Manter uma lista de ocorrências do identificador
- [X] Tabela preparada para novas inserções de propriedades de Identificadores

## Analisador Sintático

- [X] Gramática em LL(1)
- [X] Deve construir uma tabela de reconhecimento sintático uma única vez
- [X] Utilizar a tabela para verificar a pertinência ou não da entrada na linguagem gerada pela gramática

## Analisador Semântico

- [X] Construção de uma árvore de expressão (nós da árvore somente com operadores e operandos)
    - [X] Efetivada através de uma SDD L-atribuída
        - [X] separe as produções da gramática que derivam expressões aritméticas (EXPA)
        - [X] construa uma SDD L-atribuída para EXPA
        - [ ] mostre que a SDD é realmente L-atribuída
        - [X]  construa uma SDT para SDD de EXPA
        - [X] construa uma árvore de expressão T para expressões derivadas de EXPA
- [X] Inserção do tipo de variáveis na tabela de símbolos
    - [X] separe as produções da gramática que derivam em declarações de variáveis (DEC)
    - [X] construa uma SDD L-atribuida para DEC
    - [ ] mostre que a SDD é realmente L-atribuída
    - [X] construa uma SDT para SDD de DEC
- [X] Verificação de tipos em expressões aritméticas
    - [X] definir se é possível realizar as operações da expressão considerando os tipos de cada operando
- [X] Verificação de identificadores por escopo
    - [X] Permitir a declaração de variáveis de mesmo nome em diferentes escopos
    - [X] Não permitir a declaração de variáveis de mesmo nome no mesmo escopo
- [X] Verificação de que um comando break está no escopo de um comando de repetição
    - [X] Não permitir breaks fora do escopo de repetição

## Gerador de código intermediário

- [ ] Construir uma SDD L-atribuída para a gramática com regras semânticas que gerem código intermediário
- [ ] Construir uma SDT para a SDD
- [ ] Usar a SDT para gerar código intermediário para os comandos

## Sobre entrada e saída dos dados

- [ ] Saída em caso de sucesso da compilação
    - [ ] uma árvore de expressão para cada expressão aritmética do programa dado (raiz-esquerda-direita)
    - [ ] tabela de símbolos com atributo do tipo para cada identificador
    - [ ] mensagem de sucesso dizendo que as expressões aritméticas são válidas
    - [ ] mensagem de sucesso dizendo que as declarações das variáveis por escopo são válidas
    - [ ] mensagem de sucesso dizendo que todo break está num escopo de um for
    - [ ] código intermediário para a entrada
- [ ] Saída em caso de insucesso da compilação
    - [ ] mensagem de insucesso, esclarecendo ao usuário o que ocorreu de errado, indicando linha e coluna no arquivo de entrada onde ocorreu o erro;
        - [ ] parar no primeiro erro encontrado
