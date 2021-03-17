/*----------------------------------------------------------*/
/* No terminal:                                             */
/* $ gcc asMultMatrix.c -o asMultMatrix.exe -masm=intel     */
/* $ ./asMultMatix.exe                                      */
/*----------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>


int **threeLoopArray(int ** x, int ** y, int ** z, int size);

int main() {
	int **a, **b;
	int **c;
	int i, j;
	int size = 3;

	a = (int**)malloc(sizeof(int*) * size);
	b = (int**)malloc(sizeof(int*) * size);
	c = (int**)malloc(sizeof(int*) * size);
 
	for(i = 0; i < size; i++){
		a[i] = (int *)malloc(sizeof(int) * size);
	    b[i] = (int *)malloc(sizeof(int) * size);
	    c[i] = (int *)malloc(sizeof(int) * size);
	}
	
	a[0][0] = 11;
	a[0][1] = 26;
	a[0][2] = 35;
	a[1][0] = 47;
	a[1][1] = 23;
	a[1][2] = 19;
	a[2][0] = 67;
	a[2][1] = 71;
	a[2][2] = 40;

	b[0][0] = 23;
	b[0][1] = 24;
	b[0][2] = 52;
	b[1][0] = 8;
	b[1][1] = 25;
	b[1][2] = 31;
	b[2][0] = 33;
	b[2][1] = 45;
	b[2][2] = 53;

	c = threeLoopArray(a, b, c, size);

	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			printf("\nc[%d][%d] = %d", i, j, c[i][j]);
		}
	}


	threeLoopArray(a, b, c, size);

	for(i = 0; i < size; i++){
		free(a[i]);
		free(b[i]);
		free(c[i]);
	}
		
	free(a);
	free(b);
	free(c);
	
	return 0;
}

int **threeLoopArray(int ** x, int ** y, int ** z, int size){
	int i = -1, j = 0, k = 0, result = 0;
	int temp1M1, temp2M1, temp1M2, temp2M2;
	int * inc1, *inc2, *inc3, *inc4;
	int *arrayTemp;
	
	arrayTemp = (int *)malloc(sizeof(int) * (size * size));
	
	asm(
		"multMatrix:\n"
			"mov %[inc1], -1\n"
			"mov %[inc4], 0\n"
			
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
				
				"mov %[result], 0\n"
				"mov %[k], 0\n"
				"mov %[inc3], -1\n"
				"laco3:\n"
					"cmp %[k], %[size]\n"
					"jge atribuicao\n"
					
					"inc %[inc3]\n"
					
					"mov %[temp1M1], [%[x] + %[inc1]*8]\n"  
					"mov %[temp2M1], [%[temp1M1] + %[k]*4]\n" 
					
					"mov %[temp1M2], [%[y] + %[inc3]*8]\n"  
					"mov %[temp2M2], [%[temp1M2] + %[j]*4]\n" 
					
					"imul %[temp2M2], %[temp2M1]\n"
					"add %[result], %[temp2M2]\n"
					
					"inc %[k]\n"
					"jmp laco3\n"
				"atribuicao:\n"
					"mov %[temp1M2], %[result]\n"
					"mov [%[arrayTemp] + %[inc4]*4], %[temp1M2]\n"
					
					"inc %[inc4]\n"

					"inc %[j]\n"
					"inc %[inc2]\n"
					
					"jmp laco2\n"
				
		"final:\n"
		: [arrayTemp] "+r" (arrayTemp)
		: [x] "r" (x), [y] "r" (y),
		  [inc1] "r" (inc1), [inc2] "r" (inc2), [inc3] "r" (inc3), [inc4] "r" (inc4),
		  [i] "r" (i), [j] "r" (j), [k] "r" (k), [size] "m" (size),
		  [temp1M1] "r" (temp1M1), [temp2M1] "r" (temp2M1), [temp1M2] "r" (temp1M2), [temp2M2] "r" (temp2M2),
		  [result] "m" (result)
	);
	
//	for(n = 0; n < (size * size); n++){
//		printf("ola: %d\n", arrayTemp[n]);
//	}

	k = 0;
	
	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			z[i][j] = arrayTemp[k];
			k++;
		}
	}
	
	free(arrayTemp);
	
	return z;
}
