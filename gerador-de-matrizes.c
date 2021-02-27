#include<stdio.h>
#include<stdlib.h>
#include <locale.h>

int main() {
	setlocale(LC_ALL, "Portuguese");
	
	// Declarando variáveis
    long int **matrizA, **matrizB;
    long int size, limit;
    int i, j;
    
    // Declarando a variável ponteiro para o arquivo
    FILE *fp;
    
    // Abrindo o arquivo para escrita das matrizes randômicas
    fp= fopen("matrizes.txt","w");
    
    printf("Digite qual será o maior número gerado: ");
	scanf("%ld", &limit);
	
	printf("Digite a quantidade de elemento por linha: ");
	scanf("%ld", &size);
	printf("\n");
	
	// Alocando dinamicamente o tamanho das matrizes
	matrizA = malloc(size * sizeof(long int*));
	matrizB = malloc(size * sizeof(long int*));
	
	for(i = 0; i < size; i++) {
		matrizA[i] = malloc(size * sizeof(long int));
		matrizB[i] = malloc(size * sizeof(long int));
	}
	
	// Gerando os numéros aleatoriamente e salavndo nas matrizes
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++){
			matrizA[i][j] = 1 + (rand() % limit);
			matrizB[i][j] = 1 + (rand() % limit);
		}
	}
	
	// Salvando no arquivo a quantidade de elementos por linha
	fprintf(fp, "%ld\n\n", size);
	
	// Salvando a primeira matriz no arquivo
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			fprintf(fp, "%ld ", matrizA[i][j]);	
		}
		fprintf(fp, "\n");
	}
	
	fprintf(fp, "\n");
	
	// Salvando a segunda matriz no arquivo
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			fprintf(fp, "%ld ", matrizB[i][j]);	
		}
		fprintf(fp, "\n");
	}
	
	// Libera a memória da matriz
	for (i=0; i < size; i++){
		free (matrizA[i]);
		free (matrizB[i]);
	}
	
	free (matrizA);
	free (matrizB);
	
	// Fechando o arquivo de escrita
	fclose(fp);
	
	system ("pause");
    return 0;
}
