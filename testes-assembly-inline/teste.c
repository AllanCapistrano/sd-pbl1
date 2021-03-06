/*---------------------------------------------*/
/* No terminal:                                */
/* $ gcc teste.c -o teste.exe -masm=intel      */
/* $ ./teste.exe                               */
/*---------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

int basicMult(int a, int b, int c, int d);
int sumLeaExtAsm(int x, int y);
int mult(int x, int y, int z);

int main() {

	printf("\nSoma (lea) - Extended Asm: %d\n", sumLeaExtAsm(15, 2));
	printf("Multiplicacao Basica: %d\n", basicMult(1, 2, 3, 4));
	printf("Multiplicacao - Extended Asm: %d\n\n", mult(5, 10, 2));
	
	system("pause");
	return 0;
}

/* Assembly inline básico */
asm(
	"basicMult:\n"
		"mov eax, ecx\n"
		"imul eax, edx\n"
		"imul eax, r8d\n"
		"imul eax, r9d\n"
		"ret"
);

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

/* Multiplicação utilizando Extended Asm */
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
