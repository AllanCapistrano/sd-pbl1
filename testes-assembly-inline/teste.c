/*---------------------------------------------*/
/* No terminal:                                */
/* $ gcc teste.c -o teste.exe -masm=intel      */
/* $ ./teste.exe                               */
/*---------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

int sumLeaExtAsm(int x, int y);
int mult(int x, int y, int z);
int somaVetor(int *x, int *y);
int acessandoMatriz(int **x, int **y);
int loop();
int nestedLoop();
int threeLoop();

int main() {
	
//	int *x;
//	int *y;
//	int **a, **b;
//	int z, c;
//	int i;
//	
//	x = (int*)malloc(sizeof(int) * 2);
//	y = (int*)malloc(sizeof(int) * 2);
//	
//	a = (int**)malloc(sizeof(int*) * 3);
//	b = (int**)malloc(sizeof(int*) * 2);
//
//	for(i = 0; i < 3; i++){
//	    a[i] = (int *)malloc(sizeof(int) * 3);
//	    
//	    if(a[i] == NULL || b[i] == NULL){
//	      printf("Memoria insuficiente.\n");
//	      exit(1);
//	    }
//	  }
//	  
//	for(i = 0; i < 2; i++){
//	    b[i] = (int *)malloc(sizeof(int) * 2);
//	    
//	    if(a[i] == NULL || b[i] == NULL){
//	      printf("Memoria insuficiente.\n");
//	      exit(1);
//	    }
//	  }
//	
//	x[0] = 80;
//	x[1] = 5;
//	
//	y[0] = 10;
//	y[1] = 9;
//	
//	a[0][0] = 100;
//	a[0][1] = 25;
//	a[0][2] = 5;
//	a[1][0] = 3;
//	a[1][1] = 22;
//	a[1][2] = 59;
//	a[2][0] = 20;
//	a[2][1] = 39;
//	a[2][2] = 60;
//	
//	
//	b[0][0] = 5;
//	b[0][1] = 6;
//	b[1][0] = 7;
//	b[1][1] = 8;
//	
//	
//	z = somaVetor(x, y);
//	
//	c = acessandoMatriz(a, b);

//	printf("\nSoma (lea) - Extended Asm: %d\n", sumLeaExtAsm(15, 2));
//	printf("Multiplicacao - Extended Asm: %d\n\n", mult(5, 10, 2));
	
//	printf("\n%d\n", z);

//	printf("\n%d\n", c);
	
//	printf("\nLopp: %d\n", loop());

//	printf("\nNested Lopp: %d\n", nestedLoop());
	
	printf("\nTres Loops: %d\n", threeLoop());
	
//	free(x);
//	free(y);
//	
//	for(i = 0; i < 2; i++){
//		free(a[i]);
//		free(b[i]);
//	}
//		
//	free(a);
//	free(b);
	
//	system("pause");
	return 0;
}

/* Soma (lea) utilizando Extended Asm */
int sumLeaExtAsm(int x, int y) {
	int r;
	
	asm(
		"lea %[saida], [%1 + %2]"
		: [saida] "=r" (r)  // Output
		: "r" (x), "r" (y) // Input
	);

	return r;
}

/* Multiplica??o utilizando Extended Asm */
int mult(int x, int y, int z) {
	int r;
	
	asm(
		"imul %1, %2\n"
		"imul %1, %3\n"
		"mov %[saida], %1"
		: [saida] "=r" (r)  // Output
		: "r" (x), "r" (y), "r" (z) // Input
	);

	return r;
}

/* utilizando vetores */
/* as posi??es do vetor s?o acessadas em 4 em 4, come?ando do 0*/
int somaVetor(int *x, int *y) {
	int r, teste;
	
	asm(
		"mov %3, [%1 + 0]\n"
		"add %3, [%2 + 8]\n"
		"mov %[saida], %3\n"
		: [saida] "=r" (r)  // Output
		: "r" (x), "r" (y), "r" (teste) // Input
	);

	return r;
}

/* Para acessar a matriz voc? primeiro move a linha para um registrador (multiplos de 8), 
e depois no mesmo registrador voc? acessa as colunas (multiplos de 4)
*/
/* Exemplo Matriz 2x2, acessando a linha 1 coluna 2:
	"mov %3, [%1 + 0]\n"
	"mov %[saida], [%3 + 4]\n"
*/
int acessandoMatriz(int **x, int **y){
	int r, teste;
	int **tempMatrix;
	
	asm(
		"mov %4, %1\n"     // Move o cont?udo da matriz x para tempMatrix
		"mov %1, 1\n"     // Atribui 1 para x
		"mov %3, [%4 + %1*8]\n"  // Acessa a segunda linha da primeira matriz
		"mov %[saida], [%3 + 4]\n" //Acessa a segunda coluna da primeira matriz
		: [saida] "=r" (r)  // Output
		: "r" (x), "r" (y), "r" (teste), "r" (tempMatrix) // Input
	);

	return r;
}

/*Loop for, utiliza o %[saida] (eax/rax)*/
int loop(){
	int r;
	
	asm(
		"mov %[saida], 0\n" // eax = 0
		"cmp %[saida], 10\n" // comparar eax com 10
		"jge Finished\n" // Se eax >= 10 -> Finished
		"LoopHead:\n"
			"inc %[saida]\n" // eax++
			"cmp %[saida], 10\n" // comparar eax com 10
			"jl LoopHead\n" // Se eax < 10 -> Loop
		"Finished:\n"
		:[saida] "=r" (r)
	);
	
	return r;
}

int nestedLoop(){
	int r;
	int i = -1, j = 0, increment = 0, size = 10;
	
	asm(
		"loop1:\n"
			"inc %1\n"
			"cmp %1, %4\n"
			"jge end\n"
			"mov %2, 0\n"
			"loop2:\n"
				"cmp %2, %4\n"
				"jge loop1\n"
				"inc %3\n"
				"inc %2\n"
				"jmp loop2\n"
		"end:\n"
		"mov %[saida], %3\n"
		:[saida] "=r" (r)
		: "r" (i), "r" (j), "r" (increment), "r" (size)
	);
	
	return r;
}

int threeLoop(){
	int r;
	int i = -1, j = 0, k = 0, increment = 0, size = 5;
	
	asm(
		"loop11:\n"
			"inc %1\n"
			"cmp %1, %5\n"
			"jge end1\n"
			"mov %2, 0\n"
			"loop21:\n"
				"cmp %2, %5\n"
				"jge loop11\n"
				"mov %3, 0\n"
				"inc %2\n"
				"loop31:\n"
					"cmp %3, %5\n"
					"jge loop21\n"
					"inc %4\n"
					"inc %3\n"
					"jmp loop31\n"
		"end1:\n"
		"mov %[saida], %4\n"
		:[saida] "=r" (r)
		: "r" (i), "r" (j), "r" (k), "r" (increment), "r" (size)
	);
	
	return r;
}

