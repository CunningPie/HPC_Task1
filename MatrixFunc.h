#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "omp.h"


int get_index(int i, int j, int matr_size);
double * transpose(double * matrix, int size);
double * dot_mv(double * matrix, double * vector, int size);
double * dot_mm(double * matrixA, double * matrixB, int size);
double * p_dot_mm(double * matrixA, double * matrixB, int size);

double * generate_vec(int size);
double * generate_matr(int size);
double * p_generate_matr(int size);

void display_matrix(double * Matr, int size);
void display_vector(double * vec, int size);
int is_equal(double * vec1, double * vec2, int size, double eps);