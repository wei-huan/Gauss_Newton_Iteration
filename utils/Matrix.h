#ifndef MATRIX_H
#define MATRIX_H

#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include "utils.h"

typedef float Matrix_datatype;
typedef Matrix_datatype* Matrix_data_P_Type;
typedef Matrix_datatype* Matrix_Row_Type;
typedef Matrix_Row_Type* Matrix_Row_P_Type;
typedef Matrix_Row_Type* Matrix_Type;
typedef Matrix_Type* Matrix_P_Type;

// n 为矩阵A的列
#define ele(A, col, i, j)     (*(((Matrix_Row_Type)A) + (col) * (i) + (j)))
#define EOL                   (putchar('\n'))

void Init_Matrix_Zero(Matrix_Type A, unsigned int row, unsigned int col);
void Init_Matrix_Identity(Matrix_Type A, unsigned int m);
void Copy_Matrix(Matrix_Type A, Matrix_Type B, unsigned int row, unsigned int col);
void Matrix_Addition(Matrix_Type A, Matrix_Type B, Matrix_Type C, unsigned int row, unsigned int col);
void Matrix_Subtraction(Matrix_Type A, Matrix_Type B, Matrix_Type C, unsigned int row, unsigned int col);
void Matrix_Multi_Const(Matrix_Type A, Matrix_Type B, Matrix_datatype m, unsigned int row, unsigned int col);
void Matrix_Multiplication(Matrix_Type A, Matrix_Type B, Matrix_Type C, unsigned int row1, unsigned int col1_row2, unsigned int col2);
void Matrix_Inverse_Adjoint_Matrix(Matrix_Type A, Matrix_Type B, unsigned int m);
void Matrix_Inverse_Gauss_Jordan(Matrix_Type A, Matrix_Type B, unsigned int m);
void Visit_Matrix(Matrix_Type A, unsigned int row, unsigned int col);
Matrix_datatype Matrix_Cofactor(Matrix_Type A, unsigned int m, unsigned int i, unsigned int j);
void Matrix_Transpose(Matrix_Type A, Matrix_Type AT, unsigned int row, unsigned int col);
void Matrix_Row_Switch(Matrix_Type A, unsigned int row, unsigned int col, unsigned int row1, unsigned int row2);
void Matrix_Column_Switch(Matrix_Type A, unsigned int row, unsigned int col, unsigned int col1, unsigned int col2);
void Matrix_Row_Multiplication(Matrix_Type A, unsigned int row, unsigned int col, Matrix_datatype multiplier, unsigned int i);
void Matrix_Column_Multiplication(Matrix_Type A, unsigned int row, unsigned int col, Matrix_datatype multiplier, unsigned int j);
void Matrix_Row_Add2Another(Matrix_Type A, unsigned int row, unsigned int col, Matrix_datatype multiplier, unsigned int i1, unsigned int i2);
void Matrix_Column_Add2Another(Matrix_Type A, unsigned int row, unsigned int col, Matrix_datatype multiplier,unsigned int j1, unsigned int j2);
bool is_Matrix_Row_Zero(Matrix_Type A, unsigned int row, unsigned int col, unsigned int i);
bool is_Matrix_Column_Zero(Matrix_Type A, unsigned int row, unsigned int col, unsigned int j);
bool is_Matrix_Upper_Triangle(Matrix_Type A, unsigned int row, unsigned int col);
bool is_Matrix_Lower_Triangle(Matrix_Type A, unsigned int row, unsigned int col);
void Lineral_Equations_Gauss_Jordan(Matrix_Type coei,  Matrix_Type sol, unsigned int var_num);
#endif /*MATRIX_H*/
