#include "SequentialSolve.h"

double * s_get_L(double * Matr, int size)
{
	double * L = (double *)malloc(size * size * (sizeof(double)));

	for (int i = 0; i < size * size; i++)
		L[i] = 0;


	for (int i = 0; i < size; i++)
	{
		double sum = 0;

		for (int p = 0; p < i; p++)
		{
			double t = L[get_index(i, p, size)];
			sum += t * t;
		}

		L[get_index(i, i, size)] = sqrt(Matr[get_index(i, i, size)] - sum);

		for (int j = i + 1; j < size; j++)
		{
			double sum = 0;

			for (int p = 0; p < i; p++)
				sum += L[get_index(i, p, size)] * L[get_index(j, p, size)];

			L[get_index(j, i, size)] = (Matr[get_index(j, i, size)] - sum) / L[get_index(i, i, size)];
		}
	}

	return L;
}

double * s_solve_l(double *L, double * b, int size)
{
	double * res = (double *)malloc(size * sizeof(double));

	for (int i = 0; i < size; i++)
	{
		double sum = 0;

		for (int j = 0; j < i; j++)
			sum += res[j] * L[get_index(i, j, size)];

		res[i] = (b[i] - sum) / L[get_index(i, i, size)];
	}

	return res;
}

double * s_solve_u(double *Lt, double * y, int size)
{
	double * res = (double *)malloc(size * sizeof(double));

	for (int i = size - 1; i >= 0; i--)
	{
		double sum = 0;

		for (int j = i + 1; j < size - 1; j++)
			sum += res[j] * Lt[get_index(i, j, size)];

		res[i] = (y[i] - sum) / Lt[get_index(i, i, size)];
	}

	return res;
}

double * s_solve(double *Matr, double *b, int size)
{
	double * L = s_get_L(Matr, size);
	double *Lt = transpose(L, size);
	double * y = s_solve_l(L, b, size);
	double * x = s_solve_u(Lt, y, size);

	free(L);
	free(Lt);
	free(y);

	return(x);
}