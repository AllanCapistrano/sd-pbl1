#include<stdio.h>
#include<stdlib.h>
#include <string.h> //Apagar

int main()
{
    // Declarando variáveis
    int size;
    int **matrizA, **matrizB, **matrizC;
//    char *temp, *temp2; //Apagar
	char temp[500] = "", temp2[500] =""; //Apagar
    int i, j, k, aux = 0;
	
	// Declarando as variáveis ponteiro para os arquivos
    FILE *fp, *fp2;
    
    // Abrindo o arquivo para leitura
    fp = fopen("matrizes.txt","r");
    
    // Lendo a quantidade de elementos por linha
    fscanf(fp,"%d",&size);
    printf("Matriz %dx%d\n\n", size, size);

	// Alocando dinamicamente o tamanho das matrizes
	matrizA = malloc(size * sizeof(int*));
	matrizB = malloc(size * sizeof(int*));
	matrizC = malloc(size * sizeof(int*));
	
//	temp = malloc(size * sizeof(char*)); //Apagar
//	temp2 = malloc(size * sizeof(char*)); //Apagar
	
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

	// Fechando o arquivo de leitura
	fclose(fp);

	// Abrindo o arquivo para as escrita da matriz resultante
	fp2 = fopen("matriz-resultante.txt", "w");
	
	// Escrevendo no arquivo a matriz resultante
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {	
//			fprintf(fp2, "%d ", matrizC[i][j]);	
			
			sprintf(temp, "%d ", matrizC[i][j]); //Apagar
//			printf("\nTemp: %s\n", temp); //Apagar
			strcat(temp2, temp); // Apagar
			
		}
//		printf("\nTemp2: %s\n", temp2); // Apagar
		fprintf(fp2, "%s", temp2); //Apagar
		
		fprintf(fp2, "\n");
		
		sprintf(temp2, ""); //Apgar
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
//	free (temp); //Apagar
//	free (temp2); //Apagar
	
	// Fechando o arquivo de escrita
	fclose(fp2);
	
    system ("pause");
    return 0;
}
