/*********************************************************************************************
Autores: Allan Capistrano de Santana Santos e João Erick Barbosa Teixeira da Silva
Componente Curricular: MI - Sistemas Digitais
Concluido em: 17/03/2021
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

// Função para alocar dinamicamente o tamanho do vetor
int *allocateArray(int size){
	int *array;
	
	size *= size;

	array = (int *)malloc(sizeof(int) * size);
	
	return array;
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
int *multMatrix(int **matrixA, int **matrixB, int *arrayTemp, int size) {
	int i = -1, j = 0, k = 0; // Variáveis utilizadas nos loops
	int * inc1, *inc2, *inc3, *inc4; // Ponteiros utilizados nos acessos da memória
	int temp1M1, temp2M1, temp1M2, temp2M2; // Variáveis de uso geral
	int result = 0; // Varíavel acumuladora
	
	asm(
		"multMatrixAsm:\n"
			"mov %[inc1], -1\n" 									// inc1 = -1
			"mov %[inc4], 0\n"  									// inc4 = 0
			
			"jmp loop1\n" 											// Desvie para o loop1
		"loop1:\n"
			"inc %[i]\n"											// i = i + 1
			
			"cmp %[i], %[size]\n"									// i >= size
			"jge end\n"												// Em caso positivo, desvie para end, caso contrário, continue a execução
			"inc %[inc1]\n"											// inc1 = inc1 + 1
			
			"mov %[inc2], 0\n"										// inc2 = 0
			"mov %[j], 0\n"											// j = 0
			"loop2:\n"
				"cmp %[j], %[size]\n"								// j >= size
				"jge loop1\n"										// Em caso positivo, desvie para loop1, caso contrário, continue a execução
				
				"mov %[result], 0\n"								// result = 0
				"mov %[k], 0\n"										// k = 0
				"mov %[inc3], -1\n"									// inc3 = -1
				"loop3:\n"
					"cmp %[k], %[size]\n"							// k >= size
					"jge assignment\n"								// Em caso positivo, desvie para assignment, caso contrário, continue a execução
					
					"inc %[inc3]\n"									// inc3 = inc3 + 1
					
					"mov %[temp1M1], [%[matrixA] + %[inc1]*8]\n"	// Acessando as linhas da matrizA
					"mov %[temp2M1], [%[temp1M1] + %[k]*4]\n"   	// Acessando as colunas da matrizA, e guardando o valor em temp2M1
					
					"mov %[temp1M2], [%[matrixB] + %[inc3]*8]\n"	// Acessando as linhas da matrizB   
					"mov %[temp2M2], [%[temp1M2] + %[j]*4]\n"   	// Acessando as colunas da matrizB, e guardando o valor em temp2M2
					
					"imul %[temp2M2], %[temp2M1]\n"					// temp2M2 = temp2M2 * temp2M1
					"add %[result], %[temp2M2]\n"					// result = result + temp2M2
					
					"inc %[k]\n"									// k = k + 1
					"jmp loop3\n"									// Desvie para o loop3
				"assignment:\n"
					"mov %[temp1M2], %[result]\n"				   // Transferindo o valor de result para um registrador
					"mov [%[arrayTemp] + %[inc4]*4], %[temp1M2]\n" // Salvando o valor do registrador, em uma posição específica do vetor
					
					"inc %[inc4]\n"								   // inc4 = inc4 + 1

					"inc %[j]\n"								   // j = j + 1
					"inc %[inc2]\n"								   // inc2 = inc2 + 1
					
					"jmp loop2\n"								   // Desvie para o loop2
				
		"end:\n"
		: [arrayTemp] "+r" (arrayTemp) //Output
		: [matrixA] "r" (matrixA), [matrixB] "r" (matrixB), //Inputs
		  [inc1] "r" (inc1), [inc2] "r" (inc2), [inc3] "r" (inc3), [inc4] "r" (inc4),
		  [i] "r" (i), [j] "r" (j), [k] "r" (k), [size] "m" (size),
		  [temp1M1] "r" (temp1M1), [temp2M1] "r" (temp2M1), [temp1M2] "r" (temp1M2), [temp2M2] "r" (temp2M2),
		  [result] "m" (result)
	);
	
	return arrayTemp;
}

// Função para escrever no arquivo a matriz resultante
void writeFile(int **matrixC, int size) {
	int i, j;
	FILE *file2;
	
	// Abrindo o arquivo para as escrita da matriz resultante
	file2 = fopen("matriz-resultante-asm.txt", "w");
	
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
    int *arrayTemp;
    int size;
    int i = 0, j = 0, k = 0;
    double timeSpent, timeSpentFunction;
	
	// Chamando a função para a ler a quantidade de elementos das matrizes no arquivo
	readFileToSize(&size);
	
	// Alocando dinamicamente o tamanho das matrizes
	matrixA = allocateMatrix(size);
	matrixB = allocateMatrix(size);
	
	// Alocando dinamicamente o tamanho do vetor
	arrayTemp = allocateArray(size);
	
	// Chamando a função para ler o conteúdo das matrizes no arquivo
	readFile(matrixA,matrixB, size);
	
	// Alocando dinamicamente a matriz resultante
	matrixC = allocateMatrix(size);
	
	// Iniciando a contagem do tempo de execução da função de multiplicação
	clock_t beginFunction = clock();

	// Chamando a função para multiplicar as matrizes e salvar em um vetor temporário
	arrayTemp = multMatrix(matrixA, matrixB, arrayTemp, size);
	
	// Passando os valores que estavam no vetor temporário para a matriz resultante
	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			matrixC[i][j] = arrayTemp[k];
			k++;
		}
	}
	
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
	
	// Liberar a memória do vetor temporário
	free(arrayTemp);
	
    return 0;
}
