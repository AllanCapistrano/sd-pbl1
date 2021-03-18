#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <time.h>

int main()
{
	// Iniciando a contagem do tempo de execução
	clock_t begin = clock();
	
    // Declarando variáveis
    long int **matrizA, **matrizB, **matrizC;
    long int size, aux = 0;
    char *temp, *temp2;
    double time_spent;
    int i, j, k;
	
	// Declarando as variáveis ponteiro para os arquivos
    FILE *fp, *fp2;
    
    // Abrindo o arquivo para leitura
    fp = fopen("matrizes.txt","r");
    
    // Lendo a quantidade de elementos por linha
    fscanf(fp,"%ld",&size);
    printf("Matriz %ldx%ld\n\n", size, size);

	// Alocando dinamicamente o tamanho das matrizes
	matrizA = malloc(size * sizeof(long int*));
	matrizB = malloc(size * sizeof(long int*));
	matrizC = malloc(size * sizeof(long int*));
	
	temp = malloc(size * sizeof(long int*));
	temp2 = malloc(size * sizeof(long int*));
	
	for(i = 0; i < size; i++) {
		matrizA[i] = malloc(size * sizeof(long int));
		matrizB[i] = malloc(size * sizeof(long int));
		matrizC[i] = malloc(size * sizeof(long int));
	}
	
	// Lendo o arquivo e salvando os valores nas matrizes
	while(!feof(fp)) {
		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++){
				fscanf(fp, "%ld", &matrizA[i][j]);
			}
		}
	
		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++){
				fscanf(fp, "%ld", &matrizB[i][j]);
			}
		}
	}
	
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

	// Fechando o arquivo de leitura
	fclose(fp);

	// Abrindo o arquivo para as escrita da matriz resultante
	fp2 = fopen("matriz-resultante.txt", "w");
	
	sprintf(temp, "");
	sprintf(temp2, "");
	
	// Escrevendo no arquivo a matriz resultante
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			
			sprintf(temp, "%ld ", matrizC[i][j]);
			strcat(temp2, temp);
			
		}
		
		fprintf(fp2, "%s", temp2);
		fprintf(fp2, "\n");
		sprintf(temp2, "");
	}
	
	// Libera a memória da matriz
	for (i=0; i < size; i++){
		free (matrizA[i]);
		free (matrizB[i]);
		free (matrizC[i]);
	}
	
	free (matrizA);
	free (matrizB);
	free (matrizC);
	free (temp);
	free (temp2);
	
	// Fechando o arquivo de escrita
	fclose(fp2);
	
	// Finalizando a contagem do tempo de execução
	clock_t end = clock();
	
	// Calculando o tempo de execução
	time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
	
	// Exibindo o tempo de execução
	printf("\n%lf\n", time_spent);
	
    system ("pause");
    return 0;
}
