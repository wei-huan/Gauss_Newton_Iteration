#include "test.h"

int test_matrix(){    
    Matrix_datatype A[4][4] = {0.0}, B[4][4] = {0.0}, C[4][4] = {0.0};

    A[0][0] = 6.0f;  A[0][1] = -2.0f; A[0][2] = 1.0f;  A[0][3] = -1.0f;
    A[1][0] = 2.0f;  A[1][1] = 3.0f;  A[1][2] = 1.0f;  A[1][3] = -2.0f;
    A[2][0] = 0.0f;  A[2][1] = 4.0f;  A[2][2] = -1.0f; A[2][3] = 5.0f;
    A[3][0] = -1.0f;  A[3][1] = -4.0f;  A[3][2] = -2.0f; A[3][3] = 7.0f;

    Visit_Matrix((Matrix_Type)A, 4, 4);
    Matrix_Inverse_Adjoint_Matrix((Matrix_Type)A, (Matrix_Type)B, 4);
    Matrix_Multiplication((Matrix_Type)A, (Matrix_Type)B, (Matrix_Type)C, 4, 4, 4);
    Visit_Matrix((Matrix_Type)B, 4, 4);
    Visit_Matrix((Matrix_Type)C, 4, 4);

    exit(0);
}