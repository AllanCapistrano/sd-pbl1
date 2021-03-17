/*********************************************************************************************
Autores: Allan Capistrano de Santana Santos e João Erick Barbosa Teixeira da Silva
Componente Curricular: MI - Sistemas Digitais
Concluido em: 10/03/2021
Declaramos que este código foi elaborado por nós de forma individual e não contém nenhum
trecho de código de outro colega ou de outro autor, tais como provindos de livros e
apostilas, e páginas ou documentos eletrônicos da Internet. Qualquer trecho de código
de outra autoria que não a nossa está destacado com uma citação para o autor e a fonte
do código, e estamos cientes que estes trechos não serão considerados para fins de avaliação.
***********************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include <time.h>

// Função para alocar dinamicamente o tamanho da matriz
int **allocateMatrix(int size){
	int **matrix;
	int i;

	matrix = (int**)malloc(sizeof(int*) * size);
	
	if(matrix == NULL){
		printf("Memoria insuficiente.\n");
		exit(1);
	}
	
	for(i = 0; i < size; i++){
		matrix[i] = (int *)malloc(sizeof(int) * size);
		if(matrix[i] == NULL){
			printf("Memoria insuficiente.\n");
			exit(1);
		}
	}
	
	return matrix;
}

// Função para liberar o espaço na memória que foi alocado dinamicamente
void freeMatrix(int **matrix, int size){
  int i;
  for(i = 0; i < size; i++)
    free(matrix[i]);
  free(matrix);
}

// Função para a ler a quantidade de elementos das matrizes no arquivo
void readFileToSize(int *size){
	FILE *file;
	int sizef;

	// Abrindo o arquivo para a leitura
	file = fopen("matrizes.txt", "r");

	if(file == NULL){
		printf("Erro na leitura do arquivo.\n");
	    exit(1);
	}
  
	// Salvando a dimensão das matrizes a partir do arquivo
	fscanf(file,"%ld",&sizef);
	*size = sizef;

	// Fechando o arquivo 
	fclose(file);
}

// Função para ler o conteúdo das matrizes no arquivo
void readFile(int **matrixA, int **matrixB, int size){
	int **matrixTemp, **matrixTemp2;
	int i,j;
	FILE *file;
 
	// Abrindo o arquivo para a leitura
	file = fopen("matrizes.txt", "r");
  
	if(file == NULL){
		printf("Erro na leitura do arquivo.\n");
		exit(1);
	}
  
	//Desloca o cursor à frente do arquivo de texto em número de bytes correspondente ao long int, partindo da posição atual.
	fseek(file, +sizeof(int), SEEK_CUR);
  
	// Alocando dinamicamente as matrizes temporárias
	matrixTemp = allocateMatrix(size);
	matrixTemp2 = allocateMatrix(size);
  
	// Salvando o conteúdo das matrizes a partir do arquivo
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
	
	// Liberando o espaço na memória que foi alocado dinamicamente
	freeMatrix(matrixTemp, size);
	freeMatrix(matrixTemp2, size);
}

// Função para realizar a multiplicação das matrizes
int **multMatrix(int **matrixA, int **matrixB, int **matrixC, int size) {
	int aux = 0;
	int i, j, k;
	
	// Multiplicando as matrizes
	for(i = 0; i < size; i++) {
		for(j = 0; j < size; j++) {
			matrixC[i][j] = 0;
			
			for(k = 0; k < size; k++) {
				aux +=  matrixA[i][k] * matrixB[k][j];
			}

			matrixC[i][j] = aux;
			aux = 0;
		}
	}
	
	return matrixC;
}

// Função para escrever no arquivo a matriz resultante
void writeFile(int **matrixC, int size) {
	int i, j;
	FILE *file2;
	
	// Abrindo o arquivo para as escrita da matriz resultante
	file2 = fopen("matriz-resultante.txt", "w");
	
	// Escrevendo no arquivo a matriz resultante
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {	
			fprintf(file2, "%ld ", matrixC[i][j]);
		}
		
		fprintf(file2, "\n");
	}
	
	// Fechando o arquivo de escrita
	fclose(file2);
}

int main()
{
	// Iniciando a contagem do tempo de execução
	clock_t begin = clock();
	
    // Declarando variáveis
    int **matrixA, **matrixB, **matrixC;
    int size;
    double timeSpent, timeSpentFunction;
	
	// Chamando a função para a ler a quantidade de elementos das matrizes no arquivo
	readFileToSize(&size);
	
	// Alocando dinamicamente o tamanho das matrizes
	matrixA = allocateMatrix(size);
	matrixB = allocateMatrix(size);
	
	// Chamando a função para ler o conteúdo das matrizes no arquivo
	readFile(matrixA,matrixB, size);
	
	// Alocando dinamicamente a matriz resultante
	matrixC = allocateMatrix(size);
	
	// Iniciando a contagem do tempo de execução da função de multiplicação
	clock_t beginFunction = clock();

	// Chamando a função para multiplicar as matrizes
	matrixC = multMatrix(matrixA, matrixB, matrixC, size);
	
	// Finalizando a contagem do tempo de execução da função de multiplicação
	clock_t endFunction = clock();
	
	// Calculando o tempo de execução
	timeSpentFunction = (double) (endFunction - beginFunction) / CLOCKS_PER_SEC;
	
	// Chamando a função para a escrita da matriz resultante no arquivo
	writeFile(matrixC, size);
	
	// Finalizando a contagem do tempo de execução
	clock_t end = clock();
	
	// Calculando o tempo de execução
	timeSpent = (double) (end - begin) / CLOCKS_PER_SEC;
	
	// Exibindo o tempo de execução
	printf("Tempo de Execucao da Multiplicacao: %.5lf s\n\n", timeSpentFunction);
	
	// Exibindo o tempo de execução
	printf("Tempo de Execucao do Programa: %.5lf s\n\n", timeSpent);
	
	// Libera a memória da matriz
	freeMatrix(matrixA, size);
	freeMatrix(matrixB, size);
	freeMatrix(matrixC, size);
	
    system ("pause");
    return 0;
}
