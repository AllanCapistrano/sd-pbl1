/*********************************************************************************************
Autores: Allan Capistrano de Santana Santos e Jo�o Erick Barbosa Teixeira da Silva
Componente Curricular: MI - Sistemas Digitais
Concluido em: 02/03/2021
Declaramos que este c�digo foi elaborado por n�s de forma individual e n�o cont�m nenhum
trecho de c�digo de outro colega ou de outro autor, tais como provindos de livros e
apostilas, e p�ginas ou documentos eletr�nicos da Internet. Qualquer trecho de c�digo
de outra autoria que n�o a nossa est� destacado com uma cita��o para o autor e a fonte
do c�digo, e estamos cientes que estes trechos n�o ser�o considerados para fins de avalia��o.
***********************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include <locale.h>
#include<time.h>

int main() {
	setlocale(LC_ALL, "Portuguese");
	
	// Declarando vari�veis
    long int **matrizA, **matrizB;
    long int size, limit;
    int i, j;
    
    // Declarando a vari�vel ponteiro para o arquivo
    FILE *fp;
    
    // Abrindo o arquivo para escrita das matrizes rand�micas
    fp= fopen("matrizes.txt","w");
    
    printf("Digite qual ser� o maior n�mero gerado: ");
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
	
	// Fun��o para fazer com que os valores gerados n�o se repitam
	srand(time(NULL));
	
	// Gerando os num�ros aleatoriamente e salavndo nas matrizes
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
	
	// Libera a mem�ria da matriz
	for (i=0; i < size; i++){
		free (matrizA[i]);
		free (matrizB[i]);
	}
	
	free (matrizA);
	free (matrizB);
	
	// Fechando o arquivo de escrita
	fclose(fp);
	
    return 0;
}
