Algoritmo de Programação Dinâmica para Distância de Edição
======

O Problema
---------

Imagine que você, como engenheiro de computação de uma empresa, foi requisitado para desenvolver uma ferramenta de correção automática de palavras em um texto.

Nesse sentido a ideia seria que quando o usuário estivesse digitando no editor de ferramentas disponibilizado pela empresa, a ferramenta detectasse automaticamente que aquela palavra está ortograficamente errada, e, assim, sugerisse a forma correta:

![](Corretor_Automatico.gif)

Junto do seu time, vocês chegaram aos passos que teriam que ser executados em Sprints para o desenvolvimento de um MVP dessa ferramenta:



1. *Ter um dicionário de palavras nas linguas que a ferramenta teria suporte*

2. *Desensolver um modelo Bayesiano que identificasse qual a probabilidade de uma palavra aparecer próxima da outra*

3. *Desenvolver um algoritmo que entenda o quão parecida uma palavra é com a outra*

4. *Desenvolver um algoritmo que junta os passos anteriores, de modo a identificar uma palavra que não existe em uma lingua e devolver a mais próxima dela para o contexto das palavras próximas dela*

5. *Desenvolver uma interface gráfica*


Com isso o time decidiu que o Scrum Master da Sprint responsável pela *Passo* 3 seria você, ou seja, você tem o desafio de desenvolver um algoritmo capaz de entender a semelhança entre as palavras.

-----------------------------------------------------

Esse problema apresentado está inserido no escopo de *NLP* - **Natural Language Processing** -, ou em português, *PNL* - **Processamento de Linguagem Natural** -.

Visto a ascensão de tecnologias de automação e a grande necessidade de tecnologias com a sua interface mais humana, um caso como esse não seria algo distante de ocorrer contigo. Dessa forma, podemos considerar o NLP um **Hot Topic**, ou seja, algo relevante para o contexto atual de tecnologia (e muito utilizado).

Se você ficou preocupado de não saber como fazer isso, não se preocupe. Este Handout tem por objetivo te apresentar um modo de fazer isso.

O Problema de identificar palavras parecidas
--------------------------------------------

O problema de entender o nível de semelhança entres palavras, na verdade é um problema que transcende o escopo das palavras e o universo de **NLP** ( ou em português, **PNL** ).

A própria Google utiliza essa ferramenta no **Google Docs**:

![](google_docs.png)

Um ótimo ponto de partida para começar a pensar na ideia de solução do problema é entender sua natureza. Tendo em vista tal ponto, existe uma forma eficiente de se pensar na ótica desse problema.

??? Atividade 1

Reflita em um modo de pensar em quão parecidas são as palavras.

::: Gabarito
Uma solução é pensar em quanto passos teriamos que fazer de modo que uma palavra se torne a outra.
:::

???

Ora, se para saber o quão parecida uma palavra é da outra, basta saber quantos passos são necessários aplicar em uma de modo que ela se torne a outra palavra. Então, só precisamos definir o que é necessário para que uma palavra precisa seja igual a outra. Apesar de parecer uma solução muito simples, é muito importante entender essas definições para que se pense em um algoritmo posteriormente. 

??? Atividade 2

Quais são as condições para que uma palavra seja igual a outra?

::: Gabarito
É necessário que as palavras sejam somente formadas pelos `md mesmos caracteres` e que eles estejam `md ordenadas`
:::

???

A ótica do problema não é mais simplesmente do que olhar para palavras, mas sim para as suas **sequências de caracteres**. Por esse motivo o problema não se restringe ao universo de **NLP** ou **Palavras**, mas está também inserido em outros contextos, como a de **Biologia Computacional**, por exemplo, já que calcular o nível de semelhança entre os DNAs e os RNAs é necessário fazer comparações entre suas bases nitrogendas de modo ordenado, as quais são representadas pelos caracteres: `md A` `md T` `md C` `md G` e no caso de RNAs também tem o`md U`.



Tendo em vista que já definimos o que é necessário para que uma palavra seja igual à outra e que para que uma seja semelhante à outra é necessário contabilizar quantos passos são necessários para que ela se torna a outra palavra, precisamos definir quais poderiam ser esses passos.

Tente reflitir quais eles seriam.

??? Atividade 3

Utilizando o conhecimento adquirido até aqui e utilizando conhecimento próprio, ranqueie, em ordem crescente, o nível de semelhança que as palavras abaixo possuem com a palavra **Computação**  

 **Lembrete** : *Desconsidere a diferença entre entre caracteres masiúsculos e minúsculos.*

* `md Ação`
* `md Computar`
* `md Com`
* `md Açai`
* `md Comprar`
* `md Computação`

::: Gabarito
`md Açai` < `md Com` < `md Ação`< `md Comprar`< `md Computar` < `md Computação`
:::

???

A partir desse ponto, nós entramos no escopo do algoritmo principal desse Handout que é um algoritmo que calcula justamente o quão parecida uma palavra é da outra através da contabilização de passos para que uma palavra se torne outra palavra.

E esse algoritmo é o: **Algoritmo de Edição de Distância de Levenshtein**

--------------------------------------------------------------------------------

**Algoritmo de Edição de Distância de Levenshtein**
----------------

A ideia
---------

É possível dizer o quanto duas palavras são diferentes ao contabilizar o número de ações necessárias para tornar uma palavra igual à outra. Podemos considerar como ações:

* Substituir

* Adicionar

* Remover

O retorno da função deve ser a quantidade de ações que foram tomadas. Quanto maior o retorno da função, maior a diferença entre elas.

Veja abaixo um exemplo de comparação:


Vamos comparar as palavras `md kitten` e `md sitting`. 

![](exemplo-comparacao.png)

Veja que em laranja haveria uma inserção e em azul duas substituições. Para esse caso não haveria remoção.


??? Checkpoint

Qual deveria ser o número de ações para tornar a palavra `md casa` em `md capa`?.

::: Gabarito
Seria necessária uma ação, sendo ela de susbtituissão entre a letra `md s` e `md p`.
:::

???

??? Checkpoint

Qual deveria ser o número de ações para tornar a palavra `md ouro` em `md tesouro`?.

::: Gabarito
Seria necessário a inserção de `md tes` na palavra `md ouro`, ou seja, três ações. Perceba que não é apenas como um for em que você verifica letra a letra.
:::

???

Nesse caso, bastaria comparar individualmente os caracters e sua ordem para obter um resultado de quanto as palavras são diferentes. 

??? Checkpoint

Para uma primeira versão, sem rigor matemático, tente escrever um programa que retorne a semelhança entre duas palavras. 

Dica: lembre-se que o retorno da função deve ser um inteiro equivalente ao número de ações.

::: Gabarito

Abaixo está uma possível implementação. Ela possui muitos problemas, consegue identificar quais? Tire alguns minutos e tente pensar em quais são eles e converse com seus colegas.

Não se preocupe com a simplicidade, o objetivo era que você pudesse treinar o raciocínio do algoritmo (ou ao menos uma das suas ideias principais).

``` c

edit(char palavra_um[], int tamanho_um, char palavra_dois[], int tamanho_dois){
    int acoes = 0;

    for (int i = 0; i < tamanho_um; i++){
        
        if (i < tamanho_dois) {
            //uma forma de verificar a substituição
            if (palavra_um[i] != palavra_dois[i]) {
                acoes += 1;
            }
        } else {
            //significa que a palavra um é maior e será preciso remover para que fiquem iguais
            acoes += 1;
        }
    }

    if (tamanho_um < tamanho_dois) {
        //significa que a palavra um é menor e será preciso adicionar para que fiquem iguais
        acoes += 1;
    }

}

```


:::

???

O Construto Matemático do Algoritmo 
-----------

Nesse momento, uma vez compreendidos os passos do algoritmo, é importante metodotizar o modo que implementaremos essa ideia para dar espaço à minimização de passos.


Vamos começar a chamar cada passo - inserção, substituição ou remoção de caracter -  de **edição**. A partir daqui, a ideia é dar um custo para cada momento em que uma edição é feita.

Vamos exemplificar isso com as palavras abaixo:

* `md Palavra 1`: Cama.     
* `md n` = 4. Sendo m o tamanho da `md Palavra 1` e `md j` o índice dela. (vai fazer sentido daqui a pouco o uso índice)


![](Img_ex1.png)

* `md Palavra 2`: Caixa.     
* `md m` = 5. Sendo m o tamanho da `md Palavra 2` e `md i` o índice dela.

![](Img_ex2.png)

Vamos começar a pensar o modo de comparação, para isso vamos pegar a palavra caixa como base para comparar com a cama.

Vamos começar com o custo zero. E vamos comparar os primeiros caractéres.

* **Custo** : 0


![](Img_ex3.png)

Os caractéres de índice `md i = 0` e `md j = 0` são iguais, logo não há necessidade de fazer nenhuma **edição**. logo:

* **Custo** : 0

Bom, vamos continuar a nossa comparação. Mas quando formos comparar os índices `md i = 1` e `md j = 1` , não olharemos para somente para o carácter daquele índice mas de todos que vieram anteriormente. Isso quer dizer que comparar em um índice `md i = x` com `md j = y` é comparar o **"prefixo"** da palavra até o índice x e y das palavras respectivas.

* **Custo** : 0


![](Img_ex4.png)

Os prefixos de índice `md i = 1` e `md j = 1` são iguais, logo não há necessidade de fazer nenhuma **edição**. logo:

* **Custo** : 0

Agora vamos para os prefixos de índices `md i = 2` e `md j = 2`.


![](Img_ex5.png)

Os prefixos de índice `md i = 2` e `md j = 2`  não são iguais, logo há necessidade de fazer nenhuma **edição**. Como **M** é diferente de **I**, logo fazer uma **edição** de **substituição** de **I** por **M** é interessante. Ficando assim:

![](Img_ex6.png)

Logo:

* **Custo** : 1



![](Img_ex7.png)

Agora vamos para os prefixos de índices `md i = 3` e `md j = 3`.

??? Atividade 

Tente fazer você esse próxima passo. Haverá edição ou não? Se sim qual edição ? Responda também se o custo muda, e caso mude qual será o novo valor.  




::: Gabarito
Os prefixos de índice `md i = 3` e `md j = 3`  não são iguais, logo há necessidade de fazer nenhuma **edição**. Como **A** é diferente de **X**, logo fazer uma **edição** de **substituição** de **X** por **A** é interessante. Ficando assim:

![](Img_ex8.png)

Logo:

* **Custo** : 2
:::

???



Agora vamos para os prefixos de índices `md i = 4` e `md j = 3`. Mas antes, observe que o índice `md j` não acresceu mais uma unidade...

??? Checkpoint

Responda porque o índice `md j` não acresce mais unidade a partir deste passo.

::: Gabarito

Isso ocorre porque ele atingiu o valor máximo da `md Palavra 2` que está definida por `md n`. Logo o índice  não pode ultrapassar o tamanho da string (neste caso, como índice começou em `md 0` então o valor máximo que ele pode atingir é `md n-1`)

:::

???

![](Img_ex9.png)


Os prefixos de índice `md i = 4` e `md j = 3`  não são iguais, logo há necessidade de fazer nenhuma **edição**. Como **A** é diferente de **vazio**, logo fazer uma **edição** de **remoção** do **A** é interessante. Ficando assim:

![](Img_ex10.png)

Logo:

* **Custo** : 3


Agora os prefixos estão iguais. Então chegamos ao objetivo de tornar uma palavra igual a outra e a partir disso sabemos quanto custo foi necessário para isso acontecer.

Vamos refeltir sobre esse processo e pensar em alguns pontos.

Primeiro ponto é lembrar a cada passo que tinhamos estavamos avaliando qual edição iriamos fazer ou mesmo se não iriamos fazer. A razão disso está em uma ideia crucial para eficiência do problema.

??? Reflexão

Qual é essa ideia que é essencial para a eficiência do algoritmo ?

::: Gabarito

**Minimização** do custo de edições.

:::

???


Segundo ponto é que a cada passo que davamos sempre chegavamos de uma parte menos completa para uma mais completa do problema. Podemos dizer então que estavamos sempre pensando em uma versão "maior" do problema a cada passo. Mas e se pensassemos de trás para frente, vulgo, ao invés de pensar em um problema cada vez maior pensassemos em um problema cada vez menor ?

??? Reflexão

Pensar sempre em uma versão menor do problema traz uma ideia que já estamos acostumados. Qual você acha que é essa ideia ?

::: Gabarito 


**Recursão**.

:::

???

Então a partir dessa exercício com as palavras **cama** e **caixa**, fica mais fácil pensar em um modo algoritmíco de construir um porgrama que encontra a semelhança entre palavras objetificando a **minimização** do custo.

Como a recursividade é a ideia que parece ser a mais natural, então vamos tentar trilhar essa vereda.


--------------------------------------------------------------------------------

Recursividade
--------------

A ideia do modo recursivo é olhar para a palavras e pensar em uma versão do problema cada vez **menor**



Vamos utilizar os mesmos exemplos de **cama** e **caixa**

mas dessa vez vamos tentar tornar a palavra **cama** em **caixa** e não o contrário.


 Para o caso o caso recursivo, começamos olhando para a palavras inteiras e depois vamos pensando no prefixo de cada palavra.

??? Checkpoint

Quando pensamos em recursão, é necessário que haja uma condição raiz para que a recursão  encontre um ponto de término. Qual seria esse condição ?

::: Gabarito

Esse ponto seria o momento em que `md m = 0` ou `md n = 0`. Sendo n e m os tamanhos das palavras. 

:::

???

Como já sabemos a condição para a recursão, vamos montar um pseucódigo recursivo para esse algoritmo.

??? Pseudocódigo recursivo  

``` python

def levenshtein(palavra1, m, palavra2, n):
    

se (m == 0)
    
    retorna n

se (n == 0)

    retorna m


se ( palavra1[m-1] == palavra2[n-1] )

    retorna levenshtein(palavra1, m-1, palavra2, n-1)

retorna 1 + min(levenshtein(palavra1, m, palavra2, n-1),
                levenshtein(palavra1, m-1, palavra2, n-1),
                levenshtein(palavra1, m-1, palavra2, n-1))



```

???

Essa estrutura do pseucocódigo, consegue abarcar essa ideia de **recursividade** e e de **minimização de passos**.


![140x140](ja_acabou.jpg)

Brincadeiras a parte, ainda não acabou. Isso porque a forma recursiva não é a mais eficiente de se implementar um algoritmo para o Levehnstein.

Para entender isso vamos tentar gerar a árvore baseada na versão recursiva.

Vamos fazer isso olhando para o pseudocódigo já que na prática é o que ele pareceria no final.

se comerçamos com `md m = 5` e `md n = 4` e chamarmos a função passando a `md palavra1` e `md palavra2`, então teremos uma função que começará com uma estrutura de **f(5,4)**.

Na função do pseucódigo, há trẽs chamadas da própria função para visualizar a questão da **minimização**.( Vamos pensar no pior caso, o qual os caractéres não são iguais)

Por recursão serão chamados então:

* **f(5,3)**
* **f(4,4)**
* **f(4,3)**

Desse modo temos a árvore:

![140x140](arvore_building.png)

A partir daqui já dá para entender o porquê a vereda recursiva do algoritmo não parece ser uma ideia eficiente.

??? Checkpoint

Para que fique ainda mais claro, complete mais uma andar da árvore de recursão

::: Gabarito

Ele vai passar pelo mesmo caso de comparação mais de uma vez. Na verdade, isso faz com que a complexidade do algoritmo seja exponencial.


![140x140](arvore.drawio.png)

:::

???


Por essa razão, é interessante pensar em um algoritmo com menor nível de complexidade.

---------------------------------------------------------------------------------------------------------


Algoritmo Melhorado
------------------

Diferente do algoritmo anterior que não alocava memória, aqui nós vamos precisar fazer isso utilizando alocação dinâmica de matrizes.

Vamos utilizar, novamente, o mesmo exemplo de palavras anteriores: **caixa** e **cama**, com tamanhos `md m = 5` e `md n = 4`, respectivamente. sendo `md palavra1` caixa e `md palavra2` cama.

A ideia aqui é preencher uma matriz utilizando a mesma lógica de custo para as edições do algoritmo.

Vamos fazer um diagrama em formato de matriz para um melhor entendimento visual.*(Note que essa ainda não é a matriz que iremos preencher, mas sim uma maneira visual para facilitarmos a lógica)*:

![](matriz1.png)

Para preencher a primeira linha e primeira coluna é só lembrarmos que eles funcionam como string vazia.

Mas como vamos preencher eles numericamente ?

vamos olhar para o a posição do canto superior esquedo vazia:

Tanto na vertical e na horizontal dele temos `md #`, logo aquele prefixo já é igual. Então o valor daquela posição vai ser `md 0 `, já que para aquele prefixo até aquele ponto seja igual não foi necessário nenhuma modificação.

Já se olharmos para o valor seguinte na mesma linha, para que o prefixo `md #` se torne `md #c` é necessária uma **edição**. Logo o valor daquele posição será `md 1`.

Agora se pensarmos para os valores seguintes da mesma linha seguirão a mesma lógica.



??? Atividade

Preencha essa matriz para a primeira linha e coluna

**Dica** : *A mesma lógica para preenchimento de coluna é a mesma para a linha*

::: Gabarito

![](matriz2.png)

:::

???

Bom, continuemos a lógica de preenchimento.

Como queremos que o prefixo da linha até o quadrado do canto superior esquerdo vazio tanto da coluna tanto da sejam iguais então. Tanto na coluna e na linha encontramos `md #c` , logo não precisamos de edição. Então o custo naquela posição será zero.

![](matriz3_1.png)

Agora é só continuar com a mesma lógica

??? Preenchendo a matriz

:slides

???

Então, matriz preenchida. Legal né?! Será que não existe uma maneira mais *"robótica"* de fazer isso de modo que consigamos escrever isso.

??? Algoritmo de preenchimento de matriz

Se você percebeu existe uma regrinha a partir dessa matriz que nos ajuda **MUITO** a fazer isso mais rápido e que envolve a ideia de **minimização**

![](delicia.gif)

A ideia é a seguinte:

*Como queremos a minimização das edições, basta olharmos para três posições*:

* **Para a posição acima do quadrado ( Se existir)**
* **Para a posição a esquerda do quadrado**
* **Para a posição na diagonal esquerda para cima do quadrado ( Se existir)**

Basta repetir o menor desses valores. Caso os valores da a últimas caractéres da coluna e linha sejam diferentes você adiciona um a esse valor.

Vamos fazer um exemplo:

![](bb.png)

Para preencher o primeiro quadrado olhamos para os valores de:

* **cima** : `md 1`
* **esquerda** : `md 1`
* **esquerda-cima** : `md 0`

O menor valor é `md 0`

Pegamos esse valor e verificamos se os ultimos caractéres da linha e coluna são iguais ou não. Como são iguais, não adicionamos `md 1` ao menor valor.

Logo o quadrado fica com valor de `md 0`:

![](bb1.png)

Vamos para o próximo.

 **cima** : `md 2`
* **esquerda** : `md 0`
* **esquerda-cima** : `md 1`

O menor valor é `md 0`

Pegamos esse valor e verificamos se os ultimos caractéres da linha e coluna são iguais ou não. Como não são iguais, adicionamos `md 1` ao menor valor.

Logo o quadrado fica com valor de `md 1`:

![](bb2.png)

Vamos fazer só mais um para que fique bem claro.

 **cima** : `md 3`
* **esquerda** : `md 1`
* **esquerda-cima** : `md 2`

O menor valor é `md 1`

Pegamos esse valor e verificamos se os ultimos caractéres da linha e coluna são iguais ou não. Como não são iguais, adicionamos `md 1` ao menor valor.

Logo o quadrado fica com valor de `md 2`:

![](bb3.png)

???

??? Checkpoint

Ficou mais claro agora né?!

![](makes_sense.gif)

Bom, agora tente você terminar de completar as últimas 2 linhas da matriz

::: Gabarito

:slides2

:::

???

Se você entendeu bem a ideia, provavelmente deve ter pescado que o número de menor passo que você precisa tomar para tornar uma palavra em outra é o número do canto inferior direito.

Voltando ao exemlo da `md cama` e `md caixa` a distância de Levehnstein seria `md 2`

![](m20.png)


Ufa!!! Finalmente chegamos a entender a ideia do algoritmo de edição de distância de Levenshtein.

![](brabo.gif)

Parabéns!!! Você chegou ao final da Sprint, e, portanto, cumpriu sua tarefa. Mas para assegurar que você entendeu bem a ideia, pratique alguns exercícios a seguir.

-----------------------------------------------------------

Fake Quiz
---------


??? Fake Quiz 1

Preencha a matriz de Kitten e Sitting

::: Gabarito
![](kitten-sitting.drawio.svg)
:::

???

??? Fake Quiz 2

Preencha a matriz de Saturday e Sunday

::: Gabarito
![](saturday-sunday.drawio.svg)
:::

???


??? Desafio

Tente implementar o modelo recursivo do Edit Distance. 

Dica: Lembre-se de qual deve ser o passo para a recursão e os demais casos da chamada da recursão.

::: Gabarito

```c
int edit_distance(char str1[], int m, char str2[], int n){

    if (m == 0) {
        return n;
    } 
    
    if (n == 0) {
        return m;
    }

    if (str1[m - 1] == str2[n - 1]) {
        return edit_distance(str1, m - 1, str2, n - 1);
    }

    return 1 + min(edit_distance(str1, m, str2, n-1),
                    edit_distance(str1, m - 1, str2, n - 1), 
                    edit_distance(str1, m - 1, str2, n)
                );
}
```
:::
???
