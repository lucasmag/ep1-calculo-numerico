# ep1-calculo-numerico
Exercício programa I - Cadeira de cálculo numérico, Engenharia da computação - 2018.1 | Instituto Federal do Ceará

## Descrição do projeto
O presente projeto é parte de uma das atividades da disciplina de cálculo numérico para fixação de conteúdos ensinados em aula. Conteúdos envolvidos no projeto: 
* Conversão de bases numéricas (decimal, binária, octal e hexadecimal);
* Método de Jordan;
* Método da pivotação completa;
* Substituição retroativa;
* Teorema de Bolzano;
* Teorema de Lagrange;
* Método da bisseção.

### Pré-requisitos

* Sistema operacional: Windows 7 ou superior

### Executando

- Baixe o arquivo *ep1.exe*
- Execute-o

## Testes

Ao executar o programa, o mesmo mostra-rá um menu principal com 4 opções: ‘C’ – Conversão, ‘S’ – Sistema Linear, ‘E’ – Equação Algébrica e ‘F’ – Finalizar.

Ao selecionar a opção ‘C’, o usuário deverá digitar um número decimal, eventualmente com parte fracionária, e o programa deverá exibir esse número no sistema numérico binário, octal e hexadecimal, com até 20 casas decimais. 

Ao selecionar a opção ‘S’, o programa deverá pedir o nome de um arquivo de texto contendo um sistema linear de n equações e n variáveis. O lay-out do arquivo deverá ser:
```
n
a1,1 a1,2 ... a1,n b1
a2,1 a2,2 ... a2,n b2
...
an,1 an,2 ... an,n bn
```
onde ai,j é o coeficiente da variável i na equação j e bj é o termo independente da equação j. Por exemplo, o arquivo correspondente ao sistema:
```
 x1 –  x2 + 3x3 =  8
2x1 – 2x2 +  x3 =  1
–x1 + 3x2 –  x3 =  2
```
seria
```
 3
 1 -1  3  8
 2 -2  1  1
-1  3 -1  2
```

O programa deverá então transformar a matriz de coeficientes numa matriz diagonal usando o Método de Jordan., Exiba a matriz diagonal e, se o sistema for compatível, uma solução do sistema.

Ao selecionar a opção ‘E’, o programa deverá ler uma equação algébrica da forma anxn + an-1xn-1 + ... + a1x + a0, com an > 0 e a0 ≠ 0. O programa deverá solicitar o grau da equação e os coeficientes an, an-1, ..., a0, nessa ordem. O programa deve certificar-se de que an > 0 e a0 ≠ 0. 

Utilizando o Teorema de Lagrange, o programa deverá calcular e exibir os intervalos onde se encontram as raízes reais negativas e as raízes reais positivas da equação. Em seguida, o programa deverá solicitar ao usuário que informe um intervalo. Usando a Teorema de Bolzano, o programa deverá verificar se esse intervalo contém uma quantidade ímpar de raízes. Em caso afirmativo, o programa deverá calcular e exibir uma aproximação para uma raiz contida nesse intervalo usando o Método da Bisseção (pare quando o erro for menor do que 10-8 ou após 1000 iterações). Caso contrário, o programa deverá informar que o número de raízes no intervalo é par.


## Feito com

* [DevC++](http://www.bloodshed.net/devcpp.html) 

## Autor

* **Lucas Magalhães** - [LucasMag](https://github.com/lucasmag)
