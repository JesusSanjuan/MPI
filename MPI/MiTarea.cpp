// MPI.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#define _CRT_SECURE_NO_DEPRECATE
#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpi.h"

#define MAX_LARGO_PALABRA 50

int main(int argc, char* argv[])
{

	int rank, size, len;
	int n;
	const int largo = 3;
	char palabras[largo] = {'a','b','c' };
	char **palabras2;
	char *buffer = NULL;
	int *cuentas = 0;
	FILE *f;
	//char palabra_actual[MAX_LARGO_PALABRA];
	int i = 0, a=0, c;

	char version[MPI_MAX_LIBRARY_VERSION_STRING];
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);


	if (argc < 3) {
		fprintf(stderr, "Uso: %s ARCHIVO PALABRA1 PALABRA2 ...\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	n = argc - 2;
	palabras2 = argv + 2;
	cuentas = (int *) malloc(argc * sizeof(int));
	if (cuentas == NULL) {
		fprintf(stderr, "Memoria insuficiente para ejecutar el programa.\n");
		exit(EXIT_FAILURE);
	}

	f = fopen(argv[1], "r");
	
	if (f == NULL) {
		fprintf(stderr, "No se pudo abrir el archivo %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	else
	{
		c = fgetc(f);
		buffer = (char*)realloc(NULL, sizeof(char));
	}

	

	for (i = 0; i < largo; i++) {
		cuentas[i] = 0;
	}

	while (!feof(f)) {
	//	fscanf(f, "%s", palabra_actual);
		buffer[a] = c;
		a++;
		buffer = (char*)realloc(buffer, (a + 1) * sizeof(char));
		c = fgetc(f);
	/*	for (i = 0; i < n; i++) {
			if (strcmp(palabra_actual, palabras[i]) == 0) {
				cuentas[i]++;
			}
		}*/
	}
	fclose(f);

/*	for (i = 0; i < n; i++) {
		printf("%6d\t %s Procesador: %d\n", cuentas[i], palabras[i], rank);
	}*/

	int x = 0;
	int div = a / size;

	for (int i = 0; i < size; i++)
	{
		if (rank == i)
		{
			int tope = div * (i + 1);
			for (int ii = 0; ii < largo; ii++)
			{
				
				while (x < tope)
				{

				
						//printf("%c\t %c \n", buffer[x], palabras[ii]);
						if (buffer[x] == palabras[ii] )
						//if (strcmp(buffer[x], palabras[largo]) == 0)
						{
							cuentas[ii]= cuentas[ii]+1;
						}
								
					x++;
				}
			}
		}
		x = x + div;
	}

	for (int i = 0; i < largo; i++) {
		printf("%6d\t %c Procesador: %d\n", cuentas[i], palabras[i], rank);
	}

	
	free(cuentas);
	MPI_Get_library_version(version, &len);
	MPI_Finalize();

	return 0;
}
