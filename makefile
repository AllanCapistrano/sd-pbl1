gen-executable: gerador-de-matrizes.c main.c
	gcc -o gerador-de-matrizes.exe gerador-de-matrizes.c
	gcc -o main.exe main.c