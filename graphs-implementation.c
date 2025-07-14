#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#define ARQUIVO1 "arquivoGrafos-Teste1.txt"
#define ARQUIVO2 "arquivoGrafos-Teste2.txt"
#define ARQUIVO3 "arquivoGrafos-Teste3.txt"
#define ARQUIVO4 "arquivoGrafos-Teste4.txt"
#define ARQUIVO5 "arquivoGrafos-Teste5.txt"
#define MAX 100
#define INF INT_MAX


void lerArquivo (int *numV, int *numA, int matriz[][3], int *flagValorado, char *tipo, char arq[])
{
  FILE *arquivo = fopen(arq, "r");
  int vi, vj, peso;

  if (arquivo == NULL) 
  {
    perror("Erro ao abrir o arquivo");
    return;
  }

  // LEITURA DOS DADOS, LINHA POR LINHA

  fscanf(arquivo, "%d %d %c %d", numV, numA, tipo, flagValorado); // 1ª LINHA

  for (int i = 0; i < *numA; i++)  // DEMAIS LINHAS (ARESTAS E PESOS)
  {
    if (*flagValorado == 1) 
    {
      fscanf(arquivo, "%d %d %d", &vi, &vj, &peso);
      matriz[i][0] = vi;
      matriz[i][1] = vj;
      matriz[i][2] = peso;
    } 
    else 
    {
      fscanf(arquivo, "%d %d", &vi, &vj);
      matriz[i][0] = vi;
      matriz[i][1] = vj;
      matriz[i][2] = 1;
    }
  }

  // PRINTA AS INFORMAÇÕES COLETADAS

  printf("\nLEITURA DO GRAFO:\n");
  printf("\nVertices: %d\nArestas: %d\nTipo: %c\nValorado: %d\n\n", *numV, *numA, *tipo, *flagValorado);

  if (*flagValorado == 1)
  {
    for(int i=0; i < *numA; i++)
    {
      if (*tipo == 'G') printf("Aresta: %d <-> %d / Peso: %d\n", matriz[i][0], matriz[i][1], matriz[i][2]);
      else printf("Aresta: %d -> %d / Peso: %d\n", matriz[i][0], matriz[i][1], matriz[i][2]);
    }
  }
  else
  {
    for(int i=0; i < *numA; i++)
    {
      if (*tipo == 'G') printf("Aresta: %d <-> %d\n", matriz[i][0], matriz[i][1]);
      else printf("Aresta: %d -> %d\n", matriz[i][0], matriz[i][1]);
    }
  }

  fclose(arquivo);
}


void criarGrafo(char arq[])
{
  FILE *arquivo = fopen(arq, "w");
  int numV, numA, flagValorado, matriz[MAX][3];
  char tipo;

  // DIGITAÇÃO DO USUÁRIO E LEITURA DOS DADOS

  printf("CRIAR GRAFO/DIGRAFO:\n");

  printf("\nQual o tipo do grafo?\n");
  printf("  G - Grafo Nao Dirigido;\n  D - Grafo Dirigido\nTipo escolhido: ");
  scanf("%c", &tipo);

  printf("\nValorado ou Nao Valorado?\n");
  printf("  1 - Valorado;\n  0 - Nao Valorado\nOpcao escolhida: ");
  scanf("%d", &flagValorado);

  printf("\nQuantos Vertices?\n");
  printf("Quantidade escolhida: ");
  scanf("%d", &numV);

  printf("\nQuantas Arestas?\n");
  printf("Quantidade escolhida: ");
  scanf("%d", &numA);

  if(flagValorado) printf("\nInforme as arestas e os pesos (vi vj peso):\n");
  else printf("\nInforme as arestas (vi vj):\n");

  for(int i=0; i < numA; i++)
  {
    scanf("%d %d", &matriz[i][0], &matriz[i][1]);
    if(flagValorado) scanf(" %d", &matriz[i][2]);
  }

  // ADICIONA AO ARQUIVO

  fprintf(arquivo, "%d %d %c %d\n", numV, numA, tipo, flagValorado);

  for (int i = 0; i < numA; i++) 
  {
    if (flagValorado) fprintf(arquivo, "%d %d %d\n", matriz[i][0], matriz[i][1], matriz[i][2]);    
    else fprintf(arquivo, "%d %d\n", matriz[i][0], matriz[i][1]);  
  }

  fclose(arquivo);
}

int existeVerticeZero(int matAr[][3], int numA)
{
  int flagVerticeZero=0;

  // VERIFICA SE ALGUM VÉRTICE FOI NOMEADO COM 0 
  // FAZ FUNCIONAR PARA QUAISQUER NOMEAÇÕES DE VÉRTICES (NÚMEROS INTEIROS)

  for(int i=0; i < numA; i++)
  {
    if(matAr[i][0] == 0 || matAr[i][1] == 0) 
    {
      flagVerticeZero=1;
    }
  }
  return flagVerticeZero;
}


void geraMatrizAdjacencias(int matAr[][3], int matAdj[][MAX], int numV, int numA, char tipo)
{
  int x, y, peso;

  // INICIALIZA A MATRIZ COM 0

  for(int i=0; i < numV; i++)
  {
    for(int j=0; j < numV; j++)
    {
      matAdj[i][j] = 0;
    }
  }

  // ADICIONA OS PESOS NAS POSIÇÕES

  for(int i=0; i < numA; i++)
  {
    if(existeVerticeZero(matAr, numA))
    {
      x = matAr[i][0]; 
      y = matAr[i][1];
    }   
    else
    {
      x = matAr[i][0]-1; 
      y = matAr[i][1]-1;
    }    
    peso = matAr[i][2];
 
    if (matAdj[x][y] == 0)
    {
      if (tipo == 'G')
      { 
        matAdj[x][y] = peso;
        matAdj[y][x] = peso;
      }
      else
      {
        matAdj[x][y] = peso;
      }
    }
    else if (matAdj[x][y] != 0 && peso <= matAdj[x][y]) // VERIFICA SE 
    {
      if (tipo == 'G')
      { 
        matAdj[x][y] += peso;
        matAdj[y][x] += peso;
      }
      else
      {
        matAdj[x][y] += peso;
      }
    }
  }

  // IMPRIME A MATRIZ DE ADJACÊNCIAS

  printf("\nMATRIZ DE ADJACENCIAS:\n\n");
  for(int i=0; i < numV; i++)
  {
    for(int j=0; j < numV; j++)
    {
      printf("%d ", matAdj[i][j]);
    }
    printf("\n");
  }
}


void calculaGrauVertices(int matAr[][3], int numA, int numV, char tipo)
{
  int grauEntrada[MAX] = {0}, grauSaida[MAX] = {0}, grau[MAX] = {0};
  int temZero = existeVerticeZero(matAr, numA);

  printf("\nCALCULO DOS GRAUS DE CADA VERTICE:\n");

  for (int i = 0; i < numA; i++)
  {
    int origem = matAr[i][0];
    int destino = matAr[i][1];

    if (!temZero) {
      origem--;
      destino--;
    }

    if (tipo == 'D')
    {
      grauSaida[origem]++;
      grauEntrada[destino]++;
    }
    else
    {
      if (origem == destino)
        grau[origem] += 2;
      else {
        grau[origem]++;
        grau[destino]++;
      }
    }
  }

  for (int i = 0; i < numV; i++)
  {
    if (tipo == 'D')
    {
      if (temZero)
      {
        printf("\nGrau de Saida do Vertice %d: %d", i, grauSaida[i]);
        printf("\nGrau de Entrada do Vertice %d: %d\n", i, grauEntrada[i]);
      }
      else
      {
        printf("\nGrau de Saida do Vertice %d: %d", i+1, grauSaida[i]);
        printf("\nGrau de Entrada do Vertice %d: %d\n", i+1, grauEntrada[i]);
      }
    }
    else
    {
      if (temZero)
        printf("\nGrau do Vertice %d: %d", i, grau[i]);
      else
        printf("\nGrau do Vertice %d: %d", i+1, grau[i]);
    }
  }
}

int arestaValida(int v1, int v2, int verticesArvore[])
{
  // VALIDAÇÃO DE ARESTAS:
  // CONECTA UM VÉRTICE QUE JÁ ESTÁ NA ÁRVORE COM OUTRO QUE AINDA NÃO ESTÁ

  if (v1 == v2) return 0; // Impede laços (mesmo vértice)
  if (verticesArvore[v1] == 0 && verticesArvore[v2] == 0) return 0; // Nenhum dos dois vértices está na árvore
  if (verticesArvore[v1] == 1 && verticesArvore[v2] == 1) return 0; // Os dois vértices já estão na árvore

  return 1;
}


void arvoreGeradoraMinimaPrim(int matAdj[][MAX], int matAr[][3], int numA, int numV, int flagValorado, char tipo)
{
  printf("\n\nARVORE GERADORA MINIMA (PRIM):\n");

  if(flagValorado)
  {
    if (tipo == 'G')
    {
      int pesoMinimo=0, contaV=0, verticesArvore[numV], copiaMatAdjINF[numV][numV];

      // GUARDA OS VÉRTICES DA ÁRVORE
      // (0: AINDA NÃO ESTÁ NA ÁRVORE, 1: JÁ ESTÁ NA ÁRVORE)

      for(int i=0; i < numV; i++) verticesArvore[i] = 0;
      verticesArvore[0] = 1;

      for(int i=0; i < numV; i++)
      {
        for(int j=0; j < numV; j++)
        {
          copiaMatAdjINF[i][j] = matAdj[i][j];
          if(copiaMatAdjINF[i][j] == 0) copiaMatAdjINF[i][j] = INF;
        }
      }

      while (contaV < numV - 1)
      {
        int x = -1, y = -1, menor = INF;

        for (int i = 0; i < numV; i++)
        {
          for (int j = 0; j < numV; j++)
          {
            if (copiaMatAdjINF[i][j] < menor)
            {
              if (arestaValida(i, j, verticesArvore))
              {
                menor = copiaMatAdjINF[i][j];
                x = i;
                y = j;
              }
            }
          }
        }

        if (x == -1 || y == -1)
        {
          break;
        }

        if (existeVerticeZero(matAr, numA))
            printf("\nAresta: %d <-> %d / Peso: %d", y, x, menor);
        else
            printf("\nAresta: %d <-> %d / Peso: %d", y + 1, x + 1, menor);

        contaV++;
        pesoMinimo += menor;
        verticesArvore[x] = 1;
        verticesArvore[y] = 1;
      }

      printf("\n\nPeso minimo: %d\n", pesoMinimo);
    }
    else printf("\nO grafo deve ser do tipo 'G'\n");
  }
  else printf("\nO grafo deve ser Valorado\n");
}


void caminhoMaisCurtoDijkstra(int matAdj[][MAX], int numV, int matAr[][3], int numA, int flagValorado)
{
  printf("\nCAMINHOS MINIMOS (DIJKSTRA):\n");

  if (flagValorado)
  {
    int distancias[numV], visitados[numV], contaV=0, copiaMatAdjINF[numV][numV];

    // UTILIZA-SE UM VETOR DE DISTÂNCIAS PARA GUARDAR O MENOR CAMINHO ENTRE OS VÉRTICES
    // E UM VETOR DE VISITADOS, PARA GUARDAR OS VÉRTICES QUE JÁ FORAM ANALISADOS

    for(int i=0; i < numV; i++)
    {
      distancias[i] = INF; visitados[i] = 0;

      for(int j=0; j < numV; j++)
      {
        copiaMatAdjINF[i][j] = matAdj[i][j];
        if(copiaMatAdjINF[i][j] == 0) copiaMatAdjINF[i][j] = INF;
      }
    }
    distancias[0] = 0;

    while (contaV < numV - 1)
    {
      int menor=INF, indMenor=-1;

      for(int i=0; i < numV; i++)
      {
        // PEGA O VÉRTICE DE MENOR DISTÂNCIA E QUE AINDA NÃO FOI VISITADO

        if (visitados[i] == 0 && distancias[i] < menor) 
        {
          menor = distancias[i]; indMenor = i; 
        }
      }

      if (indMenor == -1) break;

      visitados[indMenor] = 1;

      for (int j=0; j < numV; j++)
      {
        if 
        (visitados[j] == 0 && 
        copiaMatAdjINF[indMenor][j] != INF && 
        distancias[indMenor] != INF && 
        distancias[j] > distancias[indMenor] + copiaMatAdjINF[indMenor][j])
        {
          distancias[j] = distancias[indMenor] + copiaMatAdjINF[indMenor][j];
        }
      }
      contaV++;
    }

    for(int i=0; i < numV; i++)
    {
      if(visitados[i] == 0 || distancias[i] > MAX) distancias[i] = -1;
    }

    // IMPRIME TABELA DE VÉRTICES E SUAS RESPECTIVAS DISTÂNCIAS

    printf("\nVERTICES          DISTANCIAS\n");

    for(int i=0; i < numV; i++)
    {
      if(existeVerticeZero(matAr, numA)) printf("\n    %d                  %d  ", i, distancias[i]);
      else printf("\n    %d                  %d  ", i+1, distancias[i]);
    }
    printf("\n");
  }
  else printf("\nO grafo deve ser Valorado\n");
}

// FUNÇÕES AUXILIARES PARA A BUSCA EM LARGURA
// UTILIZA UMA FILA PARA GUARDAR OS VÉRTICES DESCOBERTOS

void inserirFila (int fila[], int x, int *inicio, int *fim)
{
  if ((*fim + 1) % MAX == *inicio)
  {
    printf("Overflow\n\n");
  }
  else
  {
    (*fim) = (*fim + 1) % MAX;
    fila[*fim] = x;
  }
}

void eliminarFila (int fila[], int *inicio, int *fim, int *elem)
{
  if (*inicio == *fim)
  {
    printf("Underflow\n\n");
  }
  else
  {
    (*inicio) = (*inicio + 1) % MAX;
    *elem = fila[*inicio];
  }
}


void buscaEmLargura(int matAdj[][MAX], int matAr[][3], int numA, int numV)
{
  int fila[MAX], inicioFila = 0, fimFila = 0, elim = 0;
  int visitadosBFS[numV], sequencia[numV], distancias[numV], inicial, seq=0;
  
  for (int i=0; i < numV; i++) 
  {
    visitadosBFS[i] = 0;
    distancias[i] = -1;
  }

  printf("\nBUSCA EM LARGURA:\n\nEscolha o vertice inicial: ");
  scanf("%d", &inicial); 

  if(!existeVerticeZero(matAr, numA)) inicial--;

  visitadosBFS[inicial] = 1;
  distancias[inicial] = 0;
  inserirFila(fila, inicial, &inicioFila, &fimFila);
  
  while (inicioFila != fimFila)
  {
    eliminarFila(fila, &inicioFila, &fimFila, &elim);
    sequencia[seq] = elim; seq++;

    for (int j=0; j < numV; j++)
    {
      if(matAdj[elim][j] != 0 && visitadosBFS[j] == 0)
      {
        inserirFila(fila, j, &inicioFila, &fimFila);
        visitadosBFS[j] = 1;
        distancias[j] = distancias[elim] + 1; 
        // A DISTÂNCIA DE UM VÉRTICE É 1 MAIS A DISTÂNCIA DO VÉRTICE QUE O DESCOBRIU
      }
    }
  }

  printf("\nSequencia: ");
  for(int i=0; i < seq; i++)
  {
    if(!existeVerticeZero(matAr, numA)) printf("%d ", sequencia[i]+1);
    else printf("%d ", sequencia[i]);
  } 
  printf("\nDistancias: ");
  for(int i=0; i < numV; i++) printf("%d ", distancias[i]);
}

int visitadosDFS[MAX], sequenciaDFS[MAX], indSeqDFS=0;

void DFS(int matAdj[][MAX], int matAr[][3], int numA, int numV, int vertice)
{
  visitadosDFS[vertice] = 1;
  sequenciaDFS[indSeqDFS] = vertice;
  indSeqDFS++;

  for(int j=0; j < numV; j++)
  {
    if(matAdj[vertice][j] != 0 && visitadosDFS[j] == 0)
    {
      DFS(matAdj, matAr, numA, numV, j); 
      // UTILIZA RECURSÃO, APLICANDO A DFS PARA O PRÓXIMO VÉRTICE
      // CONDIÇÃO DE PARADA: PERCORRE A MATRIZ E NÃO ENCONTRA UM VÉRTICE AINDA NÃO VISITADO, OU NÃO ENCONTRA UM VÉRTICE
    }
  }
}


void buscaEmProfundidade(int matAdj[][MAX], int matAr[][3], int numA, int numV)
{
  int verticeInicial;
  printf("\n\nBUSCA EM PROFUNDIDADE\n\nEscola o vertice inicial: ");
  scanf("%d", &verticeInicial);
 
  if(!existeVerticeZero(matAr, numA)) verticeInicial--;
  for (int i=0; i < numV; i++) visitadosDFS[i] = 0;

  // PRIMEIRAMENTE: APLICA A DFS PARA O COMPONENTE CONEXO PARTINDO DO VÉRTICE INICIAL
  DFS(matAdj, matAr, numA, numV, verticeInicial);

  // POSTERIORMENTE: VERIFICA SE HÁ COMPONENTES NÃO CONEXOS E VÉRTICES NÃO VISITADOS, APLICANDO A DFS A ELES
  for (int i = 0; i < numV; i++)
  {
    if (!visitadosDFS[i])
    {
      DFS(matAdj, matAr, numA, numV, i);
    }
  }

  printf("\nSequencia de visitacao: ");
  for (int i=0; i < indSeqDFS; i++) 
  {
    if(existeVerticeZero(matAr, numA)) printf("%d ", sequenciaDFS[i]);
    else printf("%d ", sequenciaDFS[i]+1);
  }
  printf("\n");
}

int main()
{
  int numVertices, numArestas, matrizArestas[MAX][3], flagValorado=-1, matrizAdjacencias[MAX][MAX];
  char tipo;

  criarGrafo(ARQUIVO4);
  lerArquivo(&numVertices, &numArestas, matrizArestas, &flagValorado, &tipo, ARQUIVO5); 
  geraMatrizAdjacencias(matrizArestas, matrizAdjacencias, numVertices, numArestas, tipo); 
  calculaGrauVertices(matrizArestas, numArestas, numVertices, tipo); 
  arvoreGeradoraMinimaPrim(matrizAdjacencias, matrizArestas, numArestas, numVertices, flagValorado, tipo); 
  caminhoMaisCurtoDijkstra(matrizAdjacencias, numVertices, matrizArestas, numArestas, flagValorado); 
  buscaEmLargura(matrizAdjacencias, matrizArestas, numArestas, numVertices); 
  buscaEmProfundidade(matrizAdjacencias, matrizArestas, numArestas, numVertices); 

  return 0;
}