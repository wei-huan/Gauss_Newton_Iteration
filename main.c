#include "GNI_Acce.h"
#include <time.h>

int main(){
    Matrix_datatype acce[6][3] = {0.0}, bias_coei[6][1] = {0.0};
    Matrix_datatype acce_corr[6][3] = {0.0};
    clock_t start, finish;

    acce[0][0] =  0.22f;  acce[0][1] =  0.30f; acce[0][2] =  0.92f;  
    acce[1][0] = -0.21f;  acce[1][1] =  0.18f; acce[1][2] = -0.89f;  
    acce[2][0] =  0.93f;  acce[2][1] =  0.20f; acce[2][2] =  0.26f;  
    acce[3][0] = -0.92f;  acce[3][1] = -0.22f; acce[3][2] =  0.21f;
    acce[4][0] =  0.3f;   acce[4][1] =  0.95f; acce[4][2] =  0.13f;  
    acce[5][0] =  0.12f;  acce[5][1] = -0.97f; acce[5][2] = -0.16f;

    get_var_name(acce);
    Visit_Matrix((Matrix_Type)acce, 6, 3);

    start = clock();
    for(int i = 0; i <10000; i++)
        GNI_Acce((Matrix_Type)acce, (Matrix_Type)bias_coei);
    finish = clock();

    printf("run_time %2.5lfms\n", (double)(finish - start)/1000);
    get_var_name(bias_coei);
    Visit_Matrix((Matrix_Type)bias_coei, 6, 1);

    for(int i = 0; i < 6; i++)
        for(int j = 0; j < 3; j++)
            acce_corr[i][j] = (acce[i][j] - bias_coei[j][0]) * bias_coei[j + 3][0];

    get_var_name(acce_corr);
    Visit_Matrix((Matrix_Type)acce_corr, 6, 3);

    return 0;    
}

    // Matrix_datatype A[3][3] = {0.0}, X[3][1] = {0.0};

    // A[0][0] =  1.0f; A[0][1] =  2.0f; A[0][2] =  1.0f;
    // A[1][0] =  1.0f; A[1][1] =  2.0f; A[1][2] =  1.0f;
    // A[2][0] =  1.0f; A[2][1] = -1.0f; A[2][2] = -1.0f;

    // X[0][0] =  0.0f;
    // X[1][0] =  1.0f;
    // X[2][0] =  2.0f;

    // Lineral_Equations_Gauss_Jordan((Matrix_Type)A,  (Matrix_Type)X, 3);
    // get_var_name(X);
    // Visit_Matrix((Matrix_Type)X, 3, 1);

    // acce[0][0] =  0.2f;  acce[0][1] =  0.2f;  acce[0][2] =  0.9f;  
    // acce[1][0] = -0.2f;  acce[1][1] =  0.2f;  acce[1][2] = -0.9f;  
    // acce[2][0] =  0.9f;  acce[2][1] =  0.2f;  acce[2][2] =  0.2f;  
    // acce[3][0] = -0.9f;  acce[3][1] = -0.2f;  acce[3][2] =  0.2f;
    // acce[4][0] =  0.2f;  acce[4][1] =  0.9f;  acce[4][2] =  0.2f;  
    // acce[5][0] =  0.2f;  acce[5][1] = -0.9f;  acce[5][2] = -0.2f;