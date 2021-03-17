#include <stdio.h>
#include <stdlib.h>

void salvarVetor();

int main(){
	
	salvarVetor();
	
	
	return 0;
}

void salvarVetor(){
	int v[2][2] = {{1, 2}, {3, 4}};
	int y = 0, i = 0, b = 0;
	int a[4] = {0, 0, 0, 0};
	int *x;
	
	asm(
		"mov %[x], 0\n"
		"loop1:\n"
			"cmp %[x], 4\n"
			"jge end\n"
			"mov %[y], 0\n"
			"loop2:\n"
				"cmp %[y], 2\n"
				"jge loop1\n"
				"mov %[b], DWORD PTR [%[v] + %[x]*4]\n"
				"mov DWORD PTR [%[a] + %[x]*4], %[b]\n"
				"inc %[y]\n"
				"inc %[x]\n"
				"jmp loop2\n"
		"end:\n"
		:[x] "+r" (x), [y] "+r" (y), [b] "+r" (b), [a] "+m" (a), [v] "+m" (v)
	);
	
	for(int m = 0; m < 4; m++){
//		for(int n = 0; n < 2; n++){
//			printf("%d\t", a[m][n]);
//		}
		printf("%d\t", a[m]);	
	}

}
