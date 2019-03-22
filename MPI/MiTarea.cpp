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
	char **palabras;
	int *cuentas = 0;
	FILE *f;
	char palabra_actual[MAX_LARGO_PALABRA];
	int i;

	char version[MPI_MAX_LIBRARY_VERSION_STRING];



	if (argc < 3) {
		fprintf(stderr, "Uso: %s ARCHIVO PALABRA1 PALABRA2 ...\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	n = argc - 2;
	palabras = argv + 2;

	cuentas = malloc(argc * sizeof(int));
	if (cuentas == NULL) {
		fprintf(stderr, "Memoria insuficiente para ejecutar el programa.\n");
		exit(EXIT_FAILURE);
	}

	f = fopen(argv[1], "r");
	if (f == NULL) {
		fprintf(stderr, "No se pudo abrir el archivo %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	for (i = 0; i < n; i++) {
		cuentas[i] = 0;
	}

	while (!feof(f)) {
		fscanf(f, "%s", palabra_actual);
		for (i = 0; i < n; i++) {
			if (strcmp(palabra_actual, palabras[i]) == 0) {
				cuentas[i]++;
			}
		}
	}

	for (i = 0; i < n; i++) {
		printf("%6d\t %s Procesador: %d\n", cuentas[i], palabras[i], rank);
	}
	fclose(f);
	free(cuentas);
	MPI_Get_library_version(version, &len);
	MPI_Finalize();

	return 0;
}
