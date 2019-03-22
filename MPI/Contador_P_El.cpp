// MPI.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#define _CRT_SECURE_NO_DEPRECATE
#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char* argv[])
{
	int rank, size, len;
	char version[MPI_MAX_LIBRARY_VERSION_STRING];

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	FILE* archivo = fopen("el_quijote2.txt", "r");
	char *buffer = NULL;
	int i = 0, c;
	c = fgetc(archivo);
	buffer = (char*)realloc(NULL, sizeof(char));

	while (!feof(archivo))
	{
		buffer[i] = c;
		i++;
		buffer = (char*)realloc(buffer, (i + 1) * sizeof(char));
		c = fgetc(archivo);
	}

	//buffer[i] = '0';
	//printf("%s", buffer);
	//free(buffer);

	fclose(archivo);

	int x = 0, n = 0;
	int div = i / size;
	int Total = 0;

	for (int i = 0; i < size; i++)
	{
		if (rank == i)
		{
			int tope = div * (i + 1);
			while (x < tope)
			{
				if (buffer[x] == 'z' || buffer[x] == 'Z')
					n++;
				x++;
			}
		}
		x = x + div;
	}

	MPI_Get_library_version(version, &len);
	printf("Hello, world, I am %d of %d, I have found %d Z's, (%s, %d) \n",
		rank, size, n, version, len);
	
	MPI_Finalize();

	return 0;
}