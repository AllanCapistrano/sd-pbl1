/*---------------------------------------------*/
/* No terminal:                                */
/* $ gcc teste.c -o teste.exe -masm=intel      */
/* $ ./teste.exe                               */
/*---------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>


int **threeLoopArray(int ** x, int ** y, int ** z, int size);

int main() {
	int **a, **b;
	int **c;
	int i;
	int size = 2;

	a = (int**)malloc(sizeof(int*) * size);
	b = (int**)malloc(sizeof(int*) * size);
 
	for(i = 0; i < size; i++){
		a[i] = (int *)malloc(sizeof(int) * size);
	    b[i] = (int *)malloc(sizeof(int) * size);
	    
	}
	
	a[0][0] = 1;
	a[0][1] = 2;
	a[1][0] = 3;
	a[1][1] = 4;

	b[0][0] = 1;
	b[0][1] = 2;
	b[1][0] = 3;
	b[1][1] = 4;


	c = threeLoopArray(a, b, c, size);
	
	printf("\nc[0][0] = %d\n", c[0][0]);

	for(i = 0; i < size; i++){
		free(a[i]);
		free(b[i]);
	}
		
	free(a);
	free(b);
	
	return 0;
}

int **threeLoopArray(int ** x, int ** y, int ** z, int size){
	int r;
	int i = -1, j = 0, k = 0, result = 0, test=0;
	int temp1M1, temp2M1, temp1M2, temp2M2, temp1M3;
	int * inc1, *inc2, *inc3;
	int **matrixTemp;
	
	asm(
		"multplex:\n"
			"mov %[inc1], -1\n"
			"jmp laco1\n"
		"laco1:\n"
			"inc %[i]\n"
			"cmp %[i], %[size]\n"
			"jge final\n"
			"inc %[inc1]\n"
			"mov %[inc2], 0\n"
			"mov %[j], 0\n"
			"laco2:\n"
				"cmp %[j], %[size]\n"
				"jge laco1\n"
				//result = 0
				"mov %[result], 0\n"
				"mov %[k], 0\n"
				"mov %[inc3], -1\n"
				"laco3:\n"
					"cmp %[k], %[size]\n"
				
					//"jge laco2\n" //atribuicao
					"jge atribuicao\n"
					
					"inc %[inc3]\n"
					
					"mov %[temp1M1], 0\n"
					"mov %[temp1M2], 0\n"
					
					"mov %[temp1M1], [%[x] + %[inc1]*8]\n"  
					"mov %[temp2M1], [%[temp1M1] + %[k]*4]\n" 
					
					"mov %[temp1M2], [%[y] + %[inc3]*8]\n"  
					"mov %[temp2M2], [%[temp1M2] + %[j]*4]\n" 
					
					"imul %[temp2M2], %[temp2M1]\n"
					"add %[result], %[temp2M2]\n"
					
					
					"inc %[k]\n"
					//"jmp atribuicao\n" //laco3
					"jmp laco3\n"
				"atribuicao:\n"
					//"mov matrizC, %[result]\n"
					"mov %[temp1M2], %[result]\n"
					"mov %[temp1M1], [%[matrixTemp] + %[inc1]*8]\n"
					"mov [%[temp1M1] + %[j]*4], %[temp1M2]\n"

					"inc %[j]\n"
					"inc %[inc2]\n"
					
					//"jmp laco3\n" //laco2
					"jmp laco2\n" //
				
		"final:\n"
		"mov %[saida], %[result]\n"
		: [saida] "=r" (r), [matrixTemp] "=r" (matrixTemp)
		: [x] "r" (x), [y] "r" (y),
		  [inc1] "r" (inc1), [inc2] "r" (inc2), [inc3] "r" (inc3),
		  [i] "r" (i), [j] "r" (j), [k] "r" (k), [size] "r" (size),
		  [temp1M1] "r" (temp1M1), [temp2M1] "r" (temp2M1), [temp1M2] "r" (temp1M2), [temp2M2] "r" (temp2M2),
		  [result] "m" (result), [test] "r" (test)
	);
	
//	x = y;
	
	int m, n;
	
	for(m = 0; m < size; m++){
		for(n = 0; n < size; n++){
			printf("%d\t", matrixTemp[m][n]);
		}
		printf("\n");
	}
	
	printf("\nsaida: %d\n", r);
	
	return matrixTemp;
}
