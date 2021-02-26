#include<stdio.h>
#include<stdlib.h>

int main()
{
    // Declarando variáveis
    int size;
    int **matrizA, **matrizB, **matrizC;
    int i, j, k, aux = 0;
	
	// Declarando a variável ponteiro para o arquivo
    FILE *fp;
    
    // Abrindo o arquivo para leitura
    fp= fopen("matrizes.txt","r");
    
    // Lendo a quantidade de elementos por linha
    fscanf(fp,"%d",&size);
    printf("Matriz %dx%d\n\n", size, size);

	// Alocando dinamicamente o tamanho das matrizes
	matrizA = malloc(size * sizeof(int*));
	matrizB = malloc(size * sizeof(int*));
	matrizC = malloc(size * sizeof(int*));
	
	for(i = 0; i < size; i++) {
		matrizA[i] = malloc(size * sizeof(int));
		matrizB[i] = malloc(size * sizeof(int));
		matrizC[i] = malloc(size * sizeof(int));
	}
	
	// Lendo o arquivo e salvando os valores nas matrizes
	while(!feof(fp)) {
		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++){
				fscanf(fp, "%d", &matrizA[i][j]);
			}
		}
	
		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++){
				fscanf(fp, "%d", &matrizB[i][j]);
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
	
	// Exibição das matrizes
//	for (i = 0; i < size; i++) {
//		for (j = 0; j < size; j++) {
//			printf("\t%d", matrizA[i][j]);
//		}
//		printf("\n\n");
//	}
//	
//	printf("\n\n");
//	
//	for (i = 0; i < size; i++) {
//		for (j = 0; j < size; j++) {
//			printf("\t%d", matrizB[i][j]);
//		}
//		printf("\n\n");
//	}

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			printf("\t%d", matrizC[i][j]);
		}
		printf("\n\n");
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
	
	// Fechando o arquivo
    fclose(fp);
    system ("pause");
    return 0;
}
