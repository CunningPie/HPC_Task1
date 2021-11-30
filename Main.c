#include "SequentialSolve.h"
#include "ParallelSolve.h"

#include "time.h"


void main(void)
{
	omp_set_dynamic(0);


	int N = 4000;
	omp_set_num_threads(4);
	clock_t b_gen_m = clock();
	double * Matr = p_generate_matr(N);
	clock_t e_gen_m = clock();

	printf("Generation matrix A time: %f \n", (double)(e_gen_m - b_gen_m) / CLOCKS_PER_SEC);

	for (int i = 1; i <= 16; i++)
	{
		omp_set_num_threads(i);

		for (int j = 0; j < 4; j++)
		{
			double * b = generate_vec(N);

			clock_t b_p_solve = clock();
			double * x = p_solve(Matr, b, N);
			clock_t e_p_solve = clock();

			double * mul = dot_mv(Matr, x, N);

			if (is_equal(mul, b, N, 0.01) == 1)
				printf("Equal\n");
			else
				printf("Not equal\n");

			printf("Threads number: %i\n", i);
			printf("Solving time: %f \n", (double)(e_p_solve - b_p_solve) / CLOCKS_PER_SEC);


			free(b);
			free(x);
			free(mul);
		}
	}

	free(Matr);
	/*
	clock_t b_gen_m = clock();
	double * Matr1 = generate_matr(N);
	clock_t e_gen_m = clock();
	display_matrix(Matr1, N);
	printf("Sequential generation matrix A time: %f \n", (double)(e_gen_m - b_gen_m) / CLOCKS_PER_SEC);
	
	b_gen_m = clock();
	double * Matr2 = p_generate_matr(N);
	e_gen_m = clock();
	display_matrix(Matr2, N);
	printf("Parallel generation matrix A time: %f \n", (double)(e_gen_m - b_gen_m) / CLOCKS_PER_SEC);

	if (is_equal(Matr1, Matr2, N, 0.01) == 1)
		printf("Equal\n");
	else
		printf("Not equal\n");

	free(Matr1);
	free(Matr2);*/
	/*
	omp_set_num_threads(4);
	clock_t b_gen_m = clock();
	double * Matr = p_generate_matr(N);
	clock_t e_gen_m = clock();
	//display_matrix(Matr, N);
	printf("Parallel generation matrix A time: %f \n", (double)(e_gen_m - b_gen_m) / CLOCKS_PER_SEC);

	b_gen_m = clock();
	double * Matr2 = s_get_L(Matr, N);
	e_gen_m = clock();
	//display_matrix(Matr2, N);
	printf("Get L sequential time: %f \n", (double)(e_gen_m - b_gen_m) / CLOCKS_PER_SEC);

	b_gen_m = clock();
	double * Matr3 = p_get_L(Matr, N);
	e_gen_m = clock();
	//display_matrix(Matr3, N);
	printf("Get L parallel time: %f \n", (double)(e_gen_m - b_gen_m) / CLOCKS_PER_SEC);



	if (is_equal(Matr2, Matr3, N, 0.01) == 1)
		printf("Equal\n");
	else
		printf("Not equal\n");

	free(Matr);
	free(Matr2); 
	free(Matr3);

	*/
	/*
	int sum = 0;
	clock_t b = clock();
	for (int i = 0; i < 2000000000; i++)
		sum++;
	clock_t e = clock();
	printf("seq: %i \n", sum);
	printf("time: %f \n", (double)(e - b) / CLOCKS_PER_SEC);

	sum = 0;

	b = clock();

	int i = 0;

	omp_set_num_threads(16);
	#pragma omp parallel
	#pragma omp for reduction(+:sum)
	for (i = 0; i < 2000000000; i++) {
		sum++;
	}

	e = clock();
	printf("par: %i \n", sum);
	printf("time: %f \n", (double)(e - b) / CLOCKS_PER_SEC);*/
	
	getchar();
}
