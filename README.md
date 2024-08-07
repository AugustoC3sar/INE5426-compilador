# Compilador CONVCC

Alunos:
- César Augusto Pereira de Souza
- Gian Ortiz

Para compilar o compilador, basta executar `make`, isto irá gerar um binário que pode ser executado da seguinte maneira:

```
./convcc -f filename.convcc
```

A partir deste comando aplicamos a análise léxica, a análise sintática e as funções semânticas da Tarefa ASem.

Disponibilizamos quatro exemplos de códigos na linguagem para testes:

* `examples/quadraticRoots.convcc`: Cálculo de raízes quadradas de equações de segundo grau.
* `examples/fib.convcc`: Cálculo de sequência de fibonnaci.
* `examples/geometry.convcc`: Alguns exemplos de cálculos de geometria com cosseno e seno.
* `examples/sqrt.convcc`: Implementação do cálculo da raiz quadrada usando o método de Newton.

Para rodar cada um, respectivamente, execute os comandos:

```
./convcc -f examples/quadraticRoots.convcc
```

```
./convcc -f examples/fib.convcc
```

```
./convcc -f examples/geometry.convcc
```

```
./convcc -f examples/sqrt.convcc
```

A parte de geração de código foi inicializada, porém não foi finalizada.
