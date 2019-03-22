// MPI.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#define _CRT_SECURE_NO_DEPRECATE
#include "pch.h"
#include <stdio.h>
#include <time.h>
#include "mpi.h"

int main(int argc, char* argv[])
{
	int rank, size, len;
	int res1 = 0;
	int res2 = 0;
	int resfinal = 0;

	float milliseconds = 966000.0;
	float seconds = milliseconds / 1000.0;
	float minutes = seconds / 60.0;
	float hours = minutes / 60.0;

	clock_t t_ini, t_fin;
	double secs;
	char version[MPI_MAX_LIBRARY_VERSION_STRING];

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);



	printf("Soy el procesador numero %d de %d trabajando\n", rank, size);
	t_ini = clock();
	for (int j = 0; j < 1590000000; j++)
	{
		res2 = res2 + 2;
	}
	t_fin = clock();
	secs = (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
	printf("---->Resultado, Procesador %d , resultado %d, Tiempo: %.16g segundos\n", rank, res2, (secs * 1000.0) / 1000.0);


	MPI_Get_library_version(version, &len);
	//printf("Hello, world, I am %d of %d, (%s, %d)\n",rank, size, version, len);
	MPI_Finalize();
	return 0;
}