# Prova de que a gramática está em LL1

Neste documento iremos descrever a nossa prova de que a gramática que possuímos está em LL1.

De forma a provar que uma gramática está em LL1 devemos ter as seguintes regras matemáticas cumpridas:

```math
FIRST(B) \cap FIRST(C) = \emptyset

se FIRST(B) \superset \epsilon, então FIRST(C) \cap LAST(A) = \emptyset

se FIRST(C) \superset \epsilon, então FIRST(B) \cap LAST(A) = \emptyset
```