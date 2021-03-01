#include<stdio.h>
#include<stdlib.h>
#include <time.h>

// Função para alocar dinamicamente o tamanho da matriz
long int **AlocaMatriz(long int size){
  long int **M;
  int i;

  M = (long int**)malloc(sizeof(long int*) * size);
  if(M == NULL){
    printf("Memoria insuficiente.\n");
    exit(1);
  }
  for(i = 0; i < size; i++){
    M[i] = (long int *)malloc(sizeof(long int) * size);
    if(M[i] == NULL){
      printf("Memoria insuficiente.\n");
      exit(1);
    }
  }
  return M;
}

// Função para liberar o espaço na memória que foi alocado dinâmicamente
void LiberaMatriz(long int **M, long int size){
  int i;
  for(i = 0; i < size; i++)
    free(M[i]);
  free(M);
}

// Função para a ler a quantidade de elementos das matrizes no arquivo
void LeTamanho(long int *size){
	FILE *fp;
  	long int sizef;
  	
  	fp = fopen("matrizes.txt", "r");
  	if(fp == NULL){
	    printf("Erro na leitura do arquivo.\n");
	    exit(1);
  	}
  
  	fscanf(fp,"%ld",&sizef);
  	*size = sizef;
  	
  fclose(fp);
}

// Função para ler o conteúdo das matrizes no arquivo
void LeMatriz(long int **matrizA, long int **matrizB,long int size){
  long int **M, **M2;
  FILE *fp;
  long int i,j;
 
  fp = fopen("matrizes.txt", "r");
  if(fp == NULL){
    printf("Erro na leitura do arquivo.\n");
    exit(1);
  }
  
  //Desloca o cursor à frente do arquivo de texto em número de bytes correspondente ao long int, partindo da posição atual.
  fseek(fp, +sizeof(long int), SEEK_CUR);
  
  M = AlocaMatriz(size);
  M2 = AlocaMatriz(size);
  for(i = 0; i < size; i++){
    for(j = 0; j < size; j++){
      fscanf(fp,"%ld",&M[i][j]);
      matrizA[i][j] = M[i][j];
    }
  }
  for(i = 0; i < size; i++){
    for(j = 0; j < size; j++){
      fscanf(fp,"%ld",&M2[i][j]);
      matrizB[i][j] = M2[i][j];
    }
  }
  fclose(fp);
}

int main()
{
	// Iniciando a contagem do tempo de execução
	clock_t begin = clock();
	
    // Declarando variáveis
    long int **matrizA, **matrizB, **matrizC;
    long int size;
    double timeSpent;
	int aux = 0, i, j, k;
	
	// Declarando as variáveis ponteiro para os arquivos
    FILE *file2;
	
	// Chamando a função para a ler a quantidade de elementos das matrizes no arquivo
	LeTamanho(&size);
	
	// Alocando dinamicamente o tamanho das matrizes
	matrizA = AlocaMatriz(size);
  	matrizB = AlocaMatriz(size);
  	
  	// Chamando a função para ler o conteúdo das matrizes no arquivo
	LeMatriz(matrizA,matrizB, size);
	
	// Alocando dinamicamente a matriz resultante
	matrizC = AlocaMatriz(size);
	
	// Multiplicando as matrizes
	for(i = 0; i < size; i++) {
		for(j = 0; j < size; j++) {
			matrizC[i][j] = 0;
			
			for(k = 0; k < size; k++) {
				aux +=  matrizA[i][k] * matrizB[k][j];
			}

			matrizC[i][j] = aux;
			aux = 0;
		}
	}
	
	// Abrindo o arquivo para as escrita da matriz resultante
	file2 = fopen("matriz-resultante.txt", "w");
	
	// Escrevendo no arquivo a matriz resultante
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {	
			fprintf(file2, "%ld ", matrizC[i][j]);
		}
		
		fprintf(file2, "\n");
	}
	
	// Finalizando a contagem do tempo de execução
	clock_t end = clock();
	
	// Calculando o tempo de execução
	timeSpent = (double) (end - begin) / CLOCKS_PER_SEC;
	
	// Exibindo o tempo de execução
	printf("Tempo de Execucao: %.3lf s\n\n", timeSpent);
	
	// Libera a memória da matriz
	LiberaMatriz(matrizA, size);
  	LiberaMatriz(matrizB, size);
  	LiberaMatriz(matrizC, size);
  	
  	// Fechando o arquivo de escrita
	fclose(file2);
	
    system ("pause");
    return 0;
}
