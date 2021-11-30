#include "MatrixFunc.h"


/* get index of (i, j) matrix element in 1d array*/
int get_index(int i, int j, int matr_size)
{
	return i * matr_size + j;
}

/* transpose matrix */
double * transpose(double * matrix, int size)
{
	double * res = (double *)malloc(size * size * sizeof(double));

	if (res == NULL)
		return NULL;

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			res[get_index(i, j, size)] = matrix[get_index(j, i, size)];

	return res;
}

/* matrix and vector dot operation (res = Mv) */
double * dot_mv(double * matrix, double * vector, int size)
{
	double * res = (double *)malloc(size * sizeof(double));

	for (int i = 0; i < size; i++)
	{
		double sum = 0;

		for (int j = 0; j < size; j++)
			sum += matrix[get_index(i, j, size)] * vector[j];

		res[i] = sum;
	}

	return res;
}

/* matrix and matrix dot operation (res = AB) */
double * dot_mm(double * matrixA, double * matrixB, int size)
{
	double * res = (double *)malloc(size * size * sizeof(double));

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			res[get_index(i, j, size)] = 0;

			for (int k = 0; k < size; k++)
				res[get_index(i, j, size)] += matrixA[get_index(i, k, size)] * matrixB[get_index(k, j, size)];
		}
	}

	return res;
}

/* matrix and matrix dot operation (res = AB) */
double * p_dot_mm(double * matrixA, double * matrixB, int size)
{
	double *res = (double *)malloc(size * size * sizeof(double));

#pragma omp parallel
	{
		int i, j, k;

#pragma omp for
		for (i = 0; i < size; i++)
			for (j = 0; j < size; j++)
			{
				res[get_index(i, j, size)] = 0;

				for (k = 0; k < size; k++)
					res[get_index(i, j, size)] += matrixA[get_index(i, k, size)] * matrixB[get_index(k, j, size)];
			}
	}

	return res;
}

/* generate sparse positive symmetric matrix */
double * p_generate_matr(int size)
{
	double *Matr = (double *)malloc(size * size * sizeof(double));
	int sparse_amount = 15 * size * size / 100;

	srand(4710);
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			Matr[get_index(i, j, size)] = 0;

			if (i == j)
				Matr[get_index(i, j, size)] = size + rand() % size * 10;

			if (i > j)
				Matr[get_index(i, j, size)] = rand() % 10 / 10.0;
		}

	double *MatrT = transpose(Matr, size);
	double *res = p_dot_mm(MatrT, Matr, size);

	int amount = 0;

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			if (res[get_index(i, j, size)] != 0)
				amount++;
		}

	if (amount > sparse_amount)
		while (amount > sparse_amount)
		{
			int i = rand() % size;
			int j = rand() % size;

			if (i != j && res[get_index(i, j, size)] != 0)
			{
				res[get_index(i, j, size)] = 0;
				res[get_index(j, i, size)] = 0;
				amount -= 2;
			}
		}


	free(Matr);
	free(MatrT);

	return res;
}



double * generate_vec(int size)
{
	double *vec = (double *)malloc(size * sizeof(double));

	srand(4710);

	for (int i = 0; i < size; i++)
		vec[i] = rand() % 100 / 100.0;

	return vec;
}

/* generate sparse positive symmetric matrix */
double * generate_matr(int size)
{
	double *Matr = (double *)malloc(size * size * sizeof(double));
	int sparse_amount = 15 * size * size / 100;

	srand(4710);
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			Matr[get_index(i, j, size)] = 0;

			if (i == j)
				Matr[get_index(i, j, size)] = size + rand() % size * 10;

			if (i > j)
				Matr[get_index(i, j, size)] = rand() % 10 / 10.0;
		}

	double *MatrT = transpose(Matr, size);
	double *res = dot_mm(MatrT, Matr, size);

	int amount = 0;

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			if (res[get_index(i, j, size)] != 0)
				amount++;
		}

	if (amount > sparse_amount)
		while (amount > sparse_amount)
		{
			int i = rand() % size;
			int j = rand() % size;

			if (i != j && res[get_index(i, j, size)] != 0)
			{
				res[get_index(i, j, size)] = 0;
				res[get_index(j, i, size)] = 0;
				amount -= 2;
			}
		}


	free(Matr);
	free(MatrT);

	return res;
}


int is_equal(double * vec1, double * vec2, int size, double eps)
{
	for (int i = 0; i < size; i++)
		if (fabs(vec1[i] - vec2[i]) > eps)
			return 0;

	return 1;
}


void display_matrix(double * Matr, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			printf("%.3f ", Matr[get_index(i, j, size)]);
		}
		printf("\n");
	}
	printf("---------------------------------\n");
}

void display_vector(double * vec, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%.3f ", vec[i]);
	}

	printf("\n");
	printf("---------------------------------\n");
}
