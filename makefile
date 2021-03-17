gen-executable: gerador-de-matrizes.c main.c main-asm.c
	gcc -o gerador-de-matrizes.exe gerador-de-matrizes.c
	gcc -o main.exe main.c
	gcc main-asm.c -o main-asm.exe -masm=intel