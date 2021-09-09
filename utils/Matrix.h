#ifndef MATRIX_H
#define MATRIX_H

#include <math.h>
#include <stdio.h>

typedef float Matrix_datatype;
typedef Matrix_datatype* Matrix_data_P_Type;
typedef Matrix_datatype* Matrix_Row_Type;
typedef Matrix_Row_Type* Matrix_Row_P_Type;
typedef Matrix_Row_Type* Matrix_Type;
typedef Matrix_Type* Matrix_P_Type;

// n 为矩阵A的列
#define ele(A, col, i, j)     (*(((Matrix_Row_Type)A) + (col) * (i) + (j)))
#define EOL                   (putchar('\n'))

void Init_Matrix_Zero(Matrix_Type A, int row, int col);
void Init_Matrix_Identity(Matrix_Type A, int m);
void Copy_Matrix(Matrix_Type A, Matrix_Type B, int row, int col);
void Matrix_Addition(Matrix_Type A, Matrix_Type B, Matrix_Type C, int row, int col);
void Matrix_Subtraction(Matrix_Type A, Matrix_Type B, Matrix_Type C, int row, int col);
void Matrix_Multiplication(Matrix_Type A, Matrix_Type B, Matrix_Type C, int row1, int col1_row2, int col2);
void Matrix_Inverse_Adjoint_Matrix(Matrix_Type A, Matrix_Type B, int m);
void Matrix_Inverse_Gauss_Jordan(Matrix_Type A, Matrix_Type B, int m);
void Visit_Matrix(Matrix_Type A, int row, int col);
Matrix_datatype Matrix_Cofactor(Matrix_Type A, int m, int i, int j);
void Matrix_Transpose(Matrix_Type A, Matrix_Type B, int row, int col);
#endif /*MATRIX_H*/
