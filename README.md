# Arv_SistemaControleVoos

![C](https://img.shields.io/badge/Language-C-blue)
![License](https://img.shields.io/badge/License-MIT-green)
![Version](https://img.shields.io/badge/Version-1.0-orange)

## Alunos
| Matrícula | Nome |
|-----------|------|
| 21/1031593 | Andre Lopes de Sousa |
| 23/1012129 | Gabriel Lopes de Amorim |

## Descrição do Projeto

Este projeto implementa um sistema de Controle de Voos de Aeroporto, que demonstra a aplicação prática das três árvores balanceadas que vimos em sala de aula: Heap, Árvore AVL e Árvore Rubro-Negra. O projeto vai alem de uma implementação basica das estruturas, ele oferece funcionalidades completas de gerenciamento de aeroporto.
## Guia de instalação

### Dependências do Projeto

- Compilador: GCC 7.0 ou superior
- Make: GNU Make 4.0 ou superior
- Sistema Operacional: Linux,ou Windows (com o WSL)
- Terminal: Com suporte a cores ANSI

### Como Executar o Projeto

1. Clone ou baixe o repositório:
```bash
https://github.com/EDAII/ArvoresBalanceadas_SistemaControleVoos
```

2. Entre na pasta do projeto:
```bash
cd ArvoresBalanceadas_SistemaControleVoos/
```

3. Compile o projeto:
```bash
make
```

3. Execute o sistema:
```bash
./aeroporto
```

Ou compile e execute em um único comando:
```bash
make run
```

4. Limpar arquivos compilados:
```bash
make clean
```

5. Ver ajuda do Makefile:
```bash
make help
```
## Capturas de tela
### Menu Principal
![Menu Principal](/assets/imagens/imagem_1.png)

O menu principal apresenta todas as funcionalidades do sistema organizadas por estrutura de dados utilizada.

### Cadastro de Voo
![Cadastro de Voo](/assets/imagens/imagem_2.png)

Interface de cadastro com validação de dados e impacto climático automático na prioridade.

### Fila de Prioridade (Heap)
![Fila de Prioridade](/assets/imagens/imagem_3.png)

Visualização da fila de prioridade mostrando voos ordenados do mais urgente ao menos urgente.

### Fila de Prioridade (Heap)
![Fila de Prioridade](/assets/imagens/imagem_3.png)

Visualização da fila de prioridade mostrando voos ordenados do mais urgente ao menos urgente.

### Listando todos os voos (AVL)
![Fila de Prioridade](/assets/imagens/imagem_6.png)

Resultado em ordem alfabetica, isso prova que a AVL mantém os dados ordenados.


### Listando todos os voos (Rubro negra)
![Fila de Prioridade](/assets/imagens/imagem_7.png)

Resultado em ordem cronologica, independente da ordem de inserção, saem em ordem de tempo, isso prova como a rubro-negra mantem os dados ordenados.


### Status das Pistas
![Status das Pistas](/assets/imagens/imagem_4.png)

Painel em tempo real mostrando ocupação das pistas, voos alocados e tempo restante.

### Estatísticas do Aeroporto
![Estatísticas](/assets/imagens/imagem_5.png)


## Vídeo de Apresentação

Aqui está o vídeo de apresentação do projeto:

[Link para o vídeo](https://youtu.be/gPSf7B3i32s)

## Resultados Alcançados

O projeto demonstrou com sucesso a aplicação prática de três importantes estruturas de dados balanceadas em um cenário real de gerenciamento de aeroporto. As conclusões principais são:

#### Heap (Min-Heap)
- Vantagens:
  - Extremamente eficiente para operações de prioridade
  - Inserção e remoção em O(log n)
  - Ideal para fila de processamento sequencial
- Limitações:
  - Não permite busca eficiente por elementos específicos
  - Não mantém ordenação completa dos elementos
- Aplicação: Perfeito para gerenciar a fila de decolagens/pousos por prioridade

#### Árvore AVL
- Vantagens:
  - Busca extremamente rápida: O(log n) garantido
  - Balanceamento rígido garante melhor desempenho em buscas
  - Ideal para operações com muitas consultas
- Limitações:
  - Requer mais rotações que Rubro-Negra em inserções
  - Overhead de manutenção do fator de balanceamento
- Aplicação: Excelente para busca rápida de voos por número ou destino

#### Árvore Rubro-Negra
- Vantagens:
  - Balanceamento mais relaxado que AVL
  - Menos rotações em inserções/remoções
  - Ótima para cronogramas com muitas inserções
- Limitações:
  - Implementação mais complexa
  - Busca ligeiramente mais lenta que AVL (na prática, diferença desprezível)
- Aplicação: Ideal para manter cronograma ordenado por timestamp

### Lições Aprendidas

1. Escolha da Estrutura: A escolha da estrutura de dados correta depende do padrão de uso:
   - Heap para processamento por prioridade
   - AVL para buscas frequentes
   - Rubro-Negra para inserções frequentes com ordenação

2. Complexidade na Prática: Embora as três estruturas tenham complexidade teórica O(log n), os fatores constantes e o número de rotações fazem diferença em aplicações reais.

3. Complementaridade: Usar múltiplas estruturas para diferentes aspectos do mesmo sistema maximiza a eficiência geral.

## Referências

### Referência da literatura para as Àrvores

1. **CORMEN, Thomas H. et al.** *Introduction to Algorithms*, 3rd Edition. MIT Press, 2009.
   - Capítulo 12-13: Árvores Binárias de Busca e Árvores Rubro-Negras

2. **DROZDEK, Adam.** *Data Structures and Algorithms in C++*, 4th Edition. Cengage Learning, 2012.
   - Capítulo 6: Binary Trees (AVL Trees)

3. **Também foram utilizados os materiais didáticos da disciplina: Slides/Materias sobre as Àrvores**

### Implementações de Referência

4. **GeeksforGeeks** - AVL Tree Implementation
   - https://www.geeksforgeeks.org/avl-tree-set-1-insertion/

5. **GeeksforGeeks** - Red-Black Tree Implementation
   - https://www.geeksforgeeks.org/red-black-tree-set-1-introduction-2/

6. **Programiz** - Heap Data Structure
   - https://www.programiz.com/dsa/heap-data-structure

**Nota**: Nenhum código foi copiado diretamente. As implementações seguem os pseudocódigos clássicos apresentados em Cormen et al, adaptados para as necessidades específicas do projeto.
