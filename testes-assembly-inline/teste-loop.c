/*---------------------------------------------*/
/* No terminal:                                */
/* $ gcc teste.c -o teste.exe -masm=intel      */
/* $ ./teste.exe                               */
/*---------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

int loop();


int main() {

	printf("\nTeste Loop: %d\n", loop());
	
	system("pause");
	return 0;
}

/* Assembly inline b?sico */
asm(
	"loop:\n"
		"XOR    EAX, EAX\n"
		"MOV	ECX, 500\n"   
	"Label:\n"            
		"INC     EAX\n"       
		"LOOP     Label\n"
		"ret"
);


