Algoritmo de Programação Dinâmica para Distância de Edição
======
O Problema de identificar palavras parecidas
--------------------------------------------

O problema de entender o nível de semelhança entres palavras é comum e precisa ser enfrentado diariamente nas mais diversas ferramentas. A própria Google utiliza essa ferramenta no **Google Docs**:

![](google_docs.png)

Um ótimo ponto de partida para começar a pensar na ideia de solução do problema é entender sua natureza. Tendo em vista tal ponto, existe uma forma eficiente de se pensar na ótica desse problema.

??? Atividade 1

Dado os dois grupos de palavras abaixo, qual dos grupos possui palavras mais semelhantes? É importante tentar listar os motivos.

`md Estacionar` e `md Encaixar`

`md Pão` e `md Chão`

::: Gabarito
Pão e Chão são palavras mais semelhantes pois o número de caracteres é mais próximo e possui maior quantidade de letras iguais em ambas as palavras.

:::

???

Então, para sabermos o quanto duas palavras são parecidas, podemos primeiro identificar as fazem parecidas. Além 
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


Vamos começar a chamar cada passo - inserção, substituição ou remoção de caracter -  de **edição**. Também vamos chamar `md str1` e `md str2` as palavras que vamos usar e m e n seus tamanhos, respectivamente.

* `md str1`: Caixa, sendo  m = 5
* `md str2`: Cama, sendo   n = 4

Aqui nós temos duas palavras representadas por `md str1` e `md str2` e precisamos pensar em quantidade mínimas de edições que tornem `md str1` e `md str2` iguais.

Vamos pensar que, para olhar cada caracter, teremos um iterador para cada palavra:

* `md i` itera na `md str1` = caixa
* `md j` itera na `md str2` = cama

E que na comparação, decidiremos que tipo (ou se precisaremos de edição) e o **custo** que cada edição trará. No caso desse algoritmo todas as edições possuem os mesmo custo, que é unitário:

* caso os caracteres sejam iguais( `md i`=`md j`), não haverá nenhuma **edição** e e o `md custo` = 0

* caso os caracteres sejam diferentes( `md i`$\ne$`md j`), haverá **edição** e o `md custo` = 1

Porém, dependendo de qual **edição** utilizarmos, haverá a necessidade de utilizar mais ou menos **edições**, e como buscamos a minimização desse número precisamos sempre olhar para os caracteres buscando aquela edição que trará esse número mínimo.

Então resumindo essa ideia em uma função matemática temos:

$$ lev_{str1,str2}(i,j) = \begin{cases} 
lev(i,j)& se&min(i,j) = 0,\\
\\
min\begin{cases}
{lev_{str1,str2}(i-1,j)+1} \\  
{lev_{str1,str2}(i,j-1)+1} \\      
{lev_{str1,str2}(i-1,j-1)+1_{(str1_i \ne str2_j)}}
\end{cases}\\
   \end{cases}$$

Modo Recursivo
--------------

A ideia do modo recursivo é aplicar essas edições utilizando passos prévios, sem alocar um espaço de memória a longo prazo.



Então utilizando o exemplo de palavras anteriores, *caixa* e *cama*, com tamanhos m = 5 e n = 4, respectivamente.

Queremos achar o mínimo de edições necessárias para converter `md str1` em `md str2`.

Utilizando a mesma idea apresentada, vamos assumir que todas as edições possuem o mesmo custo de uma unidade e que elas serão contabilizadas quando os caracteres correspondentes forem iguais, caso contrário o custo será zero.

 Para o caso o caso recursivo, começamos olhando os caracteres de cada palavra de trás para frente.

 E as condições para os caracteres são:

*  *Se eles forem iguais, custo é 0 e retornamos m-1 e n-1 na recursão*

* *Se eles forem diferentes e a edição for **inserção**, o custo é 1 e retornamos m e n-1 na recursão*

* *Se eles forem diferentes e a edição for **remoção**, o custo é 1 e retornamos m-1 e n na recursão*

* *Se eles forem diferentes e a edição for **substituição**, o custo é 1 e retornamos m-1 e n-1 na recursão*


 Então temos:

 `md caixa[m] = a` e `md cama[n] = a`. Nesse caso, como são iguais, o custo é zero, e o retorno na recursão é m-1 e n-1. 

Quando ela chega no passo (isso quando m ou n é igual a 0), ela retorna n, caso m seja 0; ou retorna m, caso n seja 0;

Esse método funciona, porém ele não é muito eficiente devido a um problema.

Tente reflitir sobre esse problema.

??? Checkpoint

Qual o problema com o modo recursivo? 

**Dica**: `md tente desenhar a árvore do algoritmo`

::: Gabarito

Ele vai passar pelo mesmo caso de comparação mais de uma vez. Na verdade, isso faz com que a complexidade do algoritmo seja exponencial.

Basta olhar para a árvore desse algoritmo na sua forma recursiva:

![](arvore.drawio.svg)

:::

???

Por essa razão, é interessante pensar em um algoritmo com menor nível de complexidade.

Algoritmo Melhorado
------------------

Diferente do algoritmo anterior que não alocava memória, aqui nós vamos precisar fazer isso utilizando alocação dinâmica de matrizes.

Vamos utilizar, novamente, o mesmo exemplo de palavras anteriores: *caixa* e *cama*, com tamanhos m = 5 e n = 4, respectivamente. sendo `md str1` caixa e `md str2` cama.

A ideia aqui é preencher uma matriz utilizando a mesma lógica de custo para as edições do algoritmo, só que, ao preencher a matriz, haverá o incremento com os valores já adicionados. Isso ficará mais claro em sua demonstração.

* `md str1` = caixa
* `md str2` = cama

 Vamos fazer um diagrama em formato de matriz para um melhor entendimento visual.*(Note que essa ainda não é a matriz que iremos preencher, mas sim uma maneira visual para facilitarmos a lógica)*:

![](matriz1.png)

E então preenchemos o array subsequente a palavra com uma númeração de 1 a m, para a `md str1` e 1 a n, para a `md str2`.

![](matriz2.png)

Uma vez apresentado esse diagrama , a lógica para preencher essa matriz que efetivamente utilizaremos é a seguinte:

* i itera nas linhas
* j itera nas colunas

$$ lev_{str1,str2}(i,j) = \begin{cases} 
lev(i,j)& & & &se&       min(i,j) = 0,\\
\\
min\begin{cases}
{lev(i-1,j)+1} \\  
{lev(i,j-1)+1} \\      
{lev(i-1,j-1)+1_{(str1_i \ne str2_j)}}
\end{cases}\\
   \end{cases}$$

Com isso, queremos preencher o espaço em vermelho destacado no diagrama que é a matriz onde efetivamente vamos preencher. Como queremos preenchê-la do canto superior esquerdo até o canto inferior esquerdo então `md i` e `md j` começam ambos em 1. Já que consideramos os valores dos índices das palavras como espaço da matriz também.

![](matriz3.png)

A partir disso, ele vai usar a lógica matemática do algortimo que foi apresentada, só que aqui na matriz.

Um exemplo para os casos em que `md i` = 1 e `md j` = 1:

![](matriz4.png)

$$ lev_{str1,str2}(1,1) = \begin{cases} 
min\begin{cases}
{lev(0,1)+1 = 1 + 1 = 2} \\  
{lev(1,0)+1 = 1 + 1 = 2} \\      
{lev(0,0)+1_{(str1_i \ne str2_j)} = 0 + 1 =1}
\end{cases}\\
   \end{cases}$$

$$ lev_{str1,str2}(1,1) = \begin{cases} 
min\begin{cases}
{2} \\  
{2} & & = 1\\      
{1}
\end{cases}\\
   \end{cases}$$

Como neste caso, ${ min(1,1) = 0}$, então temos que ${lev_{str1,str2}(1,1) = 1}$, e assim a matriz é preenchida:

![](matriz5.png)

Vamos fazer outro exemplo para os casos em que `md i` = 1 e `md j` = 2:
Como neste caso, ${ min(1,2) \ne 0}$, então temos:

$$ lev_{str1,str2}(1,2) = \begin{cases} 
min\begin{cases}
{lev(0,2)+1 = 2 + 1 = 3} \\  
{lev(1,1)+1 = 1 + 1 = 2} \\      
{lev(0,1)+1_{(str1_i \ne str2_j)} = 1 + 1 =2}
\end{cases}\\
   \end{cases}$$

$$ lev_{str1,str2}(1,2) = \begin{cases} 
min\begin{cases}
{3} \\  
{2} & & = 2\\      
{2}
\end{cases}\\
   \end{cases}$$

Portanto, ${lev_{str1,str2}(1,2) = 2}$, e assim a matriz é preenchida:

![](matriz6.png)


Depois de repetimos o processo até a matriz ser preenchida, temos a seguinte matriz:

![](matriz7.png)

Uma vez que a matriz está completa, basta olharmos para o valor do canto inferior direito. Ele é a distância de **edição de levenshtein entre as palavras caixa e cama**: *2*.



Ufa!!! Finalmente chegamos a entender a ideia do algoritmo de edição de distância de Levenshtein. Agora só falta uma coisa: escrever efetivamente um código desse algoritmo em C.

Mas essa tarefa eu vou deixar você tentar fazer.


??? Atividade 4

Escreva um programa em **C** que implemente a versão que utiliza alocação de **matriz dinâmica** do **algoritmo de edição de distância de levenshtein**

::: Gabarito

``` c
int edit_distance_dinamic(char str1[], int m, char str2[], int n) {
    
    int length [n+1][m+1];

    for (int i = 0; i <= m; i++){
        for (int j = 0; j <= n; j++){

            if (i == 0){
                length[i][j] = j;
            } else if (j == 0) {
                length[i][j] = i;
            } else if (str1[i-1] == str2[j-2]) {
                length[i][j] = length[i-1][j-1];
            } else {
                length[i][j] = 1 + min(lengh[i-1][j],
                                        length[i][j-1],
                                        lenght[i-1][j-1]
                                    );
            }
        }
    }

    return length[m][n];
    
}
```

:::

???

??? CheckPoint

Olhando para a sua implementação da distância de edição utilizando matriz dinâmica, qual seria a complexidade do algoritmo?

::: Gabarito
Na impementação do algoritmo, de forma geral, há apenas a necessidade de preencher uma matriz `md m` por `md n`. Portanto:
$$O(mn)$$

:::

???

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
