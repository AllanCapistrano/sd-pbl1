#include<stdio.h>
#include<stdlib.h>
#include <time.h>

// Fun��o para alocar dinamicamente o tamanho da matriz
long int **allocateMatrix(long int size){
  long int **matrix;
  int i;

  matrix = (long int**)malloc(sizeof(long int*) * size);
  
  if(matrix == NULL){
    printf("Memoria insuficiente.\n");
    exit(1);
  }
  
  for(i = 0; i < size; i++){
    matrix[i] = (long int *)malloc(sizeof(long int) * size);
    if(matrix[i] == NULL){
      printf("Memoria insuficiente.\n");
      exit(1);
    }
  }
  
  return matrix;
}

// Fun��o para liberar o espa�o na mem�ria que foi alocado dinamicamente
void freeMatrix(long int **matrix, long int size){
  int i;
  for(i = 0; i < size; i++)
    free(matrix[i]);
  free(matrix);
}

// Fun��o para a ler a quantidade de elementos das matrizes no arquivo
void readFileToSize(long int *size){
	FILE *file;
	long int sizef;

	// Abrindo o arquivo para a leitura
	file = fopen("matrizes.txt", "r");

	if(file == NULL){
		printf("Erro na leitura do arquivo.\n");
	    exit(1);
	}
  
	// Salvando a dimens�o das matrizes a partir do arquivo
	fscanf(file,"%ld",&sizef);
	*size = sizef;

	// Fechando o arquivo 
	fclose(file);
}

// Fun��o para ler o conte�do das matrizes no arquivo
void readFile(long int **matrixA, long int **matrixB, long int size){
	long int **matrixTemp, **matrixTemp2;
	long int i,j;
	FILE *file;
 
	// Abrindo o arquivo para a leitura
	file = fopen("matrizes.txt", "r");
  
	if(file == NULL){
		printf("Erro na leitura do arquivo.\n");
		exit(1);
	}
  
	//Desloca o cursor � frente do arquivo de texto em n�mero de bytes correspondente ao long int, partindo da posi��o atual.
	fseek(file, +sizeof(long int), SEEK_CUR);
  
	// Alocando dinamicamente as matrizes tempor�rias
	matrixTemp = allocateMatrix(size);
	matrixTemp2 = allocateMatrix(size);
  
	// Salvando o conte�do das matrizes a partir do arquivo
	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
		  fscanf(file,"%ld",&matrixTemp[i][j]);
		  matrixA[i][j] = matrixTemp[i][j];
		}
	}
	
	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
		  fscanf(file,"%ld",&matrixTemp2[i][j]);
		  matrixB[i][j] = matrixTemp2[i][j];
		}
	}
	
	// Fechando o arquivo
	fclose(file);
	
	// Liberando o espa�o na mem�ria que foi alocado dinamicamente
	freeMatrix(matrixTemp, size);
	freeMatrix(matrixTemp2, size);
}

// Fun��o para realizar a multiplica��o das matrizes
void multMatrix(long int **matrixA, long int **matrixB, long int **matrizC, long int size) {
	long int **matrixTemp;
	long int aux = 0;
	int i, j, k;
	
	// Alocando dinamicamente a matriz tempor�ria
	matrixTemp = allocateMatrix(size);
	
	// Multiplicando as matrizes
	for(i = 0; i < size; i++) {
		for(j = 0; j < size; j++) {
			matrixTemp[i][j] = 0;
			
			for(k = 0; k < size; k++) {
				aux +=  matrixA[i][k] * matrixB[k][j];
			}

			matrixTemp[i][j] = aux;
			matrizC[i][j] = matrixTemp[i][j];
			aux = 0;
		}
	}
	
	// Liberando o espa�o na mem�ria que foi alocado dinamicamente
	freeMatrix(matrixTemp, size);
}

// Fun��o para escrever no arquivo a matriz resultante
void writeFile(long int **matrizC, long int size) {
	int i, j;
	FILE *file2;
	
	// Abrindo o arquivo para as escrita da matriz resultante
	file2 = fopen("matriz-resultante.txt", "w");
	
	// Escrevendo no arquivo a matriz resultante
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {	
			fprintf(file2, "%ld ", matrizC[i][j]);
		}
		
		fprintf(file2, "\n");
	}
	
	// Fechando o arquivo de escrita
	fclose(file2);
}

int main()
{
	// Iniciando a contagem do tempo de execu��o
	clock_t begin = clock();
	
    // Declarando vari�veis
    long int **matrixA, **matrixB, **matrizC;
    long int size;
    double timeSpent;
	
	// Chamando a fun��o para a ler a quantidade de elementos das matrizes no arquivo
	readFileToSize(&size);
	
	// Alocando dinamicamente o tamanho das matrizes
	matrixA = allocateMatrix(size);
	matrixB = allocateMatrix(size);
	matrizC = allocateMatrix(size);
	
	// Chamando a fun��o para ler o conte�do das matrizes no arquivo
	readFile(matrixA,matrixB, size);

	// Chamando a fun��o para multiplicar as matrizes
	multMatrix(matrixA, matrixB, matrizC, size);
	
	// Chamando a fun��o para a escrita da matriz resultante no arquivo
	writeFile(matrizC, size);
	
	// Finalizando a contagem do tempo de execu��o
	clock_t end = clock();
	
	// Calculando o tempo de execu��o
	timeSpent = (double) (end - begin) / CLOCKS_PER_SEC;
	
	// Exibindo o tempo de execu��o
	printf("Tempo de Execucao: %.3lf s\n\n", timeSpent);
	
	// Libera a mem�ria das matrizes
	freeMatrix(matrixA, size);
	freeMatrix(matrixB, size);
	freeMatrix(matrizC, size);
	
    system ("pause");
    return 0;
}
