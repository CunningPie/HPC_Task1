#include "MatrixFunc.h"

double * s_get_L(double * Matr, int size);
double * s_solve_l(double *L, double * b, int size);
double * s_solve_u(double *Lt, double * y, int size);
double * s_solve(double *Matr, double *b, int size);