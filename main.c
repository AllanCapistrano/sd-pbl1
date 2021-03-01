#include<stdio.h>
#include<stdlib.h>
#include <time.h>

// Função que realiza a leitura do arquivo
long int readArq(long int **matrizA, long int **matrizB) {
	// Declarando variáveis
	int i, j;
	long int size = 0;
	
	// Declarando as variáveis ponteiro para os arquivos
	FILE *file;
	
	// Abrindo o arquivo para leitura
	file = fopen("matrizes.txt","r");
	// Lendo a quantidade de elementos por linha
	fscanf(file,"%ld",&size);
    
    // Realocando o tamanho das matrizes
    matrizA = (long int**) realloc(matrizA, (size - 1) * sizeof(long int*));
	matrizB = (long int**) realloc(matrizB, (size - 1) * sizeof(long int*));
	
	for (i = 0; i < size; i++) {
		matrizA[i] = malloc(size * sizeof(long int));
		matrizB[i] = malloc(size * sizeof(long int));	
	}

	// Lendo o arquivo e salvando os valores nas matrizes
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++){
			fscanf(file, "%ld", &matrizA[i][j]);
			printf("\nmatrizA[%d][%d]: %ld\n", i, j, matrizA[i][j]);
		}
	}
	
	printf("\n---\n");

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++){
			fscanf(file, "%ld", &matrizB[i][j]);
			printf("\nmatrizB[%d][%d]: %ld\n", i, j, matrizB[i][j]);
		}
	}
	
	// Fechando o arquivo de leitura
	fclose(file);
	
	return size;
}

int main()
{
	// Iniciando a contagem do tempo de execução
	clock_t begin = clock();
	
    // Declarando variáveis
    long int **matrizA, **matrizB, **matrizC;
    long int size, aux = 0;
    double timeSpent;
	int i, j, k;
	
	// Declarando as variáveis ponteiro para os arquivos
    FILE *file2;

	// Alocando dinamicamente o tamanho das matrizes
	matrizA = malloc(1 * sizeof(long int*));
	matrizB = malloc(1 * sizeof(long int*));
	
//	for(i = 0; i < 1; i++) {
		matrizA[0] = malloc(1 * sizeof(long int));
		matrizB[0] = malloc(1 * sizeof(long int));
//	}

	// Chamando a função para a leitura do arquivo
	size = readArq(matrizA, matrizB);
	
	// Alocando dinamicamente a matriz resultante
	matrizC = malloc(size * sizeof(long int*));
	
	for(i = 0; i < size; i++) {
		matrizC[i] = malloc(size * sizeof(long int));
	}
	
	printf("\nMatrizA: %ld\n", matrizB[0][8]);
	
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
	
	printf("\nc\n", size);
	
	// Abrindo o arquivo para as escrita da matriz resultante
	file2 = fopen("matriz-resultante.txt", "w");
	
	// Escrevendo no arquivo a matriz resultante
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {	
			fprintf(file2, "%ld ", matrizC[i][j]);
		}
		
		fprintf(file2, "\n");
	}
	
	// Libera a memória da matriz
	free (matrizA);
	free (matrizB);
	free (matrizC);
	
	// Finalizando a contagem do tempo de execução
	clock_t end = clock();
	
	// Calculando o tempo de execução
	timeSpent = (double) (end - begin) / CLOCKS_PER_SEC;
	
	// Exibindo o tempo de execução
	printf("Tempo de Execucao: %.3lf s\n\n", timeSpent);
	
	// Fechando o arquivo de escrita
	fclose(file2);
	
    system ("pause");
    return 0;
}
