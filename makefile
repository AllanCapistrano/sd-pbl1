gen-executable: gerador-de-matrizes.c main.c main-asm.c
	gcc -o gerador-de-matrizes gerador-de-matrizes.c
	gcc -o main main.c
	gcc main-asm.c -o main-asm -masm=intel