# Detalhes do Funcionamento

## Seleção dos ativos
O algoritmo de seleção, filtra os ativos onde
  "quantidade de ações" * "valor de 1 ação" é menor do que o somatorio de ("quantidade de ações" * "valor de 1 ação") * "percentual da carteira" / somatorio de ("percentual da carteira").
Se um ativo não passar pelo filtro (for maior ou igual), ele é removido da análise. O valor total investido e o percentual da carteira são ajustados, e a seleção começa novamente.  
**Filtro, em notação matematica**, seja:      
- q : quantidade de ações    
- v : valor de 1 ação    
- p : percentual do ativo na carteira    
- a : aporte     
então:     
$`q \cdot v \leq ((\sum\limits_{i=1}^n q_i \cdot v_i)+a) \cdot \frac{p} {\sum\limits_{i=1}^n p_i}`$

### Ordem de magnitude de execução do algoritmo
No pior caso, apenas o último ativo não receberia investimento, o que significaria ler todos os N ativos e reiniciar a análise, e se esse caso se repetir denovo e denovo, resultando é um total de N + (N-1) + (N-2) + ... + 3 + 2 + 1 = $`\frac{N^2 - N}{2}`$ operações, com uma complexidade de O($`N^2`$).

exemplo com ações e um aporte de 500.00:
| nome da ação | percentual da carteira | quantidade de ações | valor de 1 ação | valor total investido |
| ------------ | ---------------------- | ------------------- | --------------- | --------------------- |
| abce3        | 10%                    | 100                 | 9.50            | 950.00                |
| aeim3        | 40%                    | 250                 | 8.12            | 2030.00               |
| agmr3        | 30%                    | 125                 | 30              | 3750.00               |
| alwh3        | 20%                    | 800                 | 2.37            | 1896.00               |

| aporte | total investido + aporte |
| ------ | ------------------------ |
| 500.00 | 9126.00                  |

filtro de abce3 (1° iteração):  
$`100*9.50 < 9126*10/100 => 950 < 912.6`$, nao passou no filtro, entao o total investido é 9126 - 950 = 8176, e o total dos percentuais é 100-10 = 90.

filtro de aeim3 (2° iteração):  
$`250*8.12 < 8176*40/90 => 2030 < 3633.78`$, passou no filtro.

filtro de agmr3 (2° iteração):  
$`125*30 < 8176*30/90 => 3750 < 2725.34`$, nao passou no filtro, entao o total investido é 8176 - 3750 = 4426, e o total dos percentuais é 90-30 = 60.  

filtro de aeim3 (3° iteração):  
$`250*8.12 < 4426*40/60 => 2030 < 2.950`$, passou no filtro.  

filtro de alwh3 (3° iteração):  
$`800*2.37 < 4426*20/60 => 1896 < 1475.34`$, nao passou no filtro, entao o total investido é 4426 - 1896 = 2530, e o total dos percentuais é 60-20 = 40. 

filtro de aeim3 (4° iteração):  
250*8.12 < 2530*40/40 => 2030 < 2530, passou no filtro.  

### Resultado da seleção
Apenas aeim3 satisfaz a condicao do algoritmo após todos os ajustes.

## Cálculo da quantidade ótima para investir em cada ativo

Dado que todos os ativos listados devem receber investimento:
valor investido + delta x = (total investido nos ativos selecionados + aporte) * percentual,
onde delta x é uma "nova quantidade de ações" * "valor unitário da ação".

Portanto, a quantidade de novas ações para comprar é:  
Seja:  
- v: valor unitário  
- q: quantidade de ações  
- nq: quantidade de novas ações  
- a: aporte  
Então:  
$`Err(q) = \sum\limits_{i=1}^n (v_i*)\cdot\frac{(q_i* - q_i)^2}{q_i*}`$  

### Ordem de magnitude de execução do algoritmo

Como será feita uma operação por ativo selecionado, e são N ativos, então a complexidade do algoritmo é O(N).

## Arredondamento

Como não existe 1/2 ação, ou 15.333... ações, deve ser feito um arredondamento. Esse arredondamento será feito para tentar encontrar o menor erro, com as seguintes variáveis:  
- s* : total à investir ideal, em uma ação  
- s : o que será investido em uma ação  
- v : valor unitario  
- q* : quantidade de ações à comprar, ideal  
- q : quantidade de ações que será comprada  
A função de erro é definida como:  
$`Err(q) := \sum\limits_{i=1}^n \frac{(s_i* - s_i)^2}{s_i*} => \sum\limits_{i=1}^n \frac{(v_i*\cdot q_i*) - (v_i*q_i))^2}{v_i*\cdot q_i*}
=> \sum\limits_{i=1}^n (v_i*)\cdot\frac{(q_i* - q_i)^2}{q_i*}`$

### Funcao de Erro
Portanto, a funcao de erro é:  
$`Err(q) = \sum\limits_{i=1}^n (v_i*) \cdot \frac{(q_i* - q_i)^2}{q_i*}`$  

### Chute Inicial e Ajuste  
O chute inicial será arredondar cada $`q_i*`$ para cima e ir decrementando de cada ativo, de forma que a combinação de cortes gere o menor erro possivel e o total a gastar seja menor do que o aporte.
  
  #### diagrama de exemplo
  ```mermaid
graph TD;
  root-->n1(1);
  root-->n2(2);
  root-->ni(...);
  root-->nm(N);
  n1-->n11(11);
  n1-->n12(12);
  n1-->n1i(...);
  n1-->n1m(1N);
  n2-->n21(21);
  n2-->n22(22);
  n2-->n2m(2N);
  nm-->nm1(N1);
  nm-->nm2(N2);
  nm-->nmm(NN);
  n11-->n111(111);
  n11-->n112(112);
  n11-->n11i(...);
  n11-->n11m(11N);
```



Nesse caso, o nó root representa todos os $`q_i*`$ arredondados para cima, o nó 1, representa o root, mas com $`q_1 - 1`$, o nó 12 representa o root, mas com $`q_1 - 1`$ e o $`q_2 - 1`$, e assim por diante.
### Complexidade da Busca
Procurar pelo nó ideal via força bruta seria muito custoso, pois a ordem de complexidade seria O($`N^H`$), onde N é o número de ativos e H é a altura da árvore de nós.


Portanto, para encontrar a resposta mais rapidamente, será feita uma otimização que reduz a complexidade. A ideia é minimizar o erro sem explorar todas as combinações possíveis, aproveitando técnicas de otimização como busca heurística e algoritmos de aproximação.


**1° passo, calcular o gradiente da funcao erro:**  
  $`Err_i'(q) = \frac{d}{dq} (v*)*\frac{(q* - q)^2}{q*} => -2(v*)*\frac{(q*)-q}{q*} => (\frac{2v}{q*})*q - 2v `$  
  ∴ $`Err_i'(q) = (\frac{2v}{q*})*q - 2v`$  



**2° passo, calcular o vetor que sera usado para fazer os cortes na quantidade de ações:**  
  Como seguir o gradiente aumenta o erro muito, e nao podemos tomar o caminho contrario "- gradiente". Em vez disso, usaremos um vetor V para determinar a direção da otimização, calculado como, 1/[coeficiente angular(gradiente Err(q))]  
  $`V_i = 1/coefciente-angular(Err'_i(q)) = \frac{1}{\frac{2v_i}{q_i*}} = \frac{q_i*}{2v_i}`$  
∴ $`V_i = \frac{q_i*}{2v_i}`$  



**3° Encontrar o menor a, que faça com que o gasto extra seja menor ou igual a 0:**  
Gasto extra referente ao arredondamento para cima é dado por: 
  $`G = \sum\limits_{i=1}^N \lceil q_i* - q_i \rceil * v_i`$.  
Equação completa:  
$`(\sum\limits_{i=1}^N \lfloor a*\frac{q_i*}{2v_i} \rfloor * v_i) - (\sum\limits_{i=1}^N \lceil q_i* - q_i \rceil * v_i) \geq 0`$  

onde: $`\lfloor a*\frac{q_i*}{2v_i} \rfloor`$ significa descontar uma ação, e: $`v_i`$ o valor, portanto:  
$`(\sum\limits_{i=1}^N \lfloor a*\frac{q_i*}{2v_i} \rfloor * v_i)`$ significa a economia feita com os cortes de investimento.
E se essa economia for maior do que o gasto extra, então dá para comprar as ações sem precisar fazer outro aporte.
Quantidade de ações a comprar. Seja:  
- r : vetor de quantidade de ações a comprar, arredondada para cima.
- s : vetor de ações descontadas, obtidas atraves de $`\lfloor a*\frac{q_i*}{2v_i}\rfloor`$
**vetor das ações a comprar: $`r-s`$**




### Resolvendo a equação:
$`F(a) = (\sum\limits_{i=1}^N \lfloor a*\frac{q_i*}{2v_i} \rfloor * v_i) - (\sum\limits_{i=1}^N \lceil q_i* - q_i \rceil * v_i) \geq 0`$
Como para resolver essa equação, de forma precisa para obter o menor a possivel, seria necessario usar um sistema de N equações, seria relativamente custoso, em comparação com usar uma heuristica de busca binaria com um chute incial, pois, se o menor a possivel faz com que a equação F(a) = b, um F(a+ε) = b, pois tem uma floor function envolvendo a. E para usar a heuristica, vamos:  

  
1° encontrar um chte inicial:  
como $`(\sum\limits_{i=1}^N \lfloor a*\frac{q_i*}{2v_i} \rfloor * v_i) \approx (\sum\limits_{i=1}^N (a*\frac{q_i*}{2v_i}) * v_i) = (\sum\limits_{i=1}^N a*\frac{q_i*}{2})`$  
e $`(\sum\limits_{i=1}^N \lceil q_i* - q_i \rceil * v_i) \approx (\sum\limits_{i=1}^N \frac{1}{2} * v_i)`$
temos:  $`(\sum\limits_{i=1}^N a*\frac{q_i*}{2}) \approx (\sum\limits_{i=1}^N \frac{1}{2} * v_i)  
=> \frac{a}{2}*(\sum\limits_{i=1}^N q_i) \approx \frac{1}{2}*(\sum\limits_{i=1}^N v_i)  
=> a \approx \frac{\sum\limits_{i=1}^N v_i}{\sum\limits_{i=1}^N q_i}`$  <br><br>
∴ O chute inicial, $`a_0 = \frac{\sum\limits_{i=1}^N v_i}{\sum\limits_{i=1}^N q_i}`$  
2° se $`F(a_n) \leq 0`$, entao, ou tira a media com um $`a_{n-1}`$, ou caso não tenha um $`a_{n-1}`$ maior que $`a_n`$, dobre $`a_n`$.
3° se $`F(a_n) \geq 0`$, entao verifique se existe um $`R = F(a_n)`$, se sim, pare, se não, armazene esse resultado em R, e tire a media de $`a_n`$ com $`a_{n-1}`$.

### Ordem de magnitude de execução do algoritmo
Como para encontrar o menor a, são feitas log(N) operacoes na F(a), e para fazer uma operacao na F(a) são necessarias fazer N operácoes.  
No pior caso, o a encontrado faz com que seja necessário vender uma ou mais ações, então seria necessário, remover esse ativo, da lista de ativos para investir, e recalcular a quantidade ótima para investir em cada ativo. E se após esse processo, perceber que deve se remover outro ativo, de novo e de novo, até que reste apenas um ativo.  
Resultaria em um total de N*log(N) + (N-1)*log(N-1) + ... (2)*(log2) + (1*log(1)) = $`\frac{(N \cdot log(N))^2 - N \cdot log(N)}{2}`$ operações, com um O($`N^2 \cdot log(N)^2`$)
