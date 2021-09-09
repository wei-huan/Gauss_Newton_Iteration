#include "GNI_Acce.h"

// acce是6个姿态下的3轴加速度数据矩阵acce[6][3]
// grad_coff_zero_bias是6行1列的矩阵, 前三行是零偏系数, 后三行是刻度系数
void GNI_Acce(Matrix_Type acce, Matrix_Type grad_coff_zero_bias){

    int count = 0;
    // D是6个参数的变化矩阵
    Matrix_datatype D[6][1] = {0.0};
    // 6个姿态的偏导数矩阵
    Matrix_datatype prtl_deri[6][6] = {0.0};
    // 偏导数乘法矩阵
    Matrix_datatype M[6][6] = {0.0};
    // 偏导数乘目标
    Matrix_datatype A[6][1] = {0.0};
    // 偏导数乘法逆矩阵
    Matrix_datatype M_Inv[6][6] = {0.0};
    // 加速度计的平方和系数
    Matrix_datatype A_Square_Sum[6][1] = {0.0};

    // 求加速度计平方和
    for(int i = 0; i < 6; i++)
        A_Square_Sum[i][0] = pow(ele(acce, 3, i, 0), 2) + pow(ele(acce, 3, i, 1), 2) + pow(ele(acce, 3, i, 2), 2); 

    // 零偏系数初始化为0, 刻度系数初始化为1
    for(int i = 0; i < 3; i++)
        ele(grad_coff_zero_bias, 1, i, 0) = 0.0f;
    for(int i = 3; i < 6; i++)
        ele(grad_coff_zero_bias, 1, i, 0) = 1.0f;
    
    while(1){
        /* 求6个姿态下的关于6个系数的偏导数 */
        // 求关于零偏系数的偏导数
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 6; j++)
                // df/dox = -2 * (amx - dx) * kx^2
                prtl_deri[i][j] = -2.0f * (ele(acce, 3, j, i) - ele(grad_coff_zero_bias, 1, i, 0)) * pow(ele(grad_coff_zero_bias, 1, i + 3, 0), 2);

        // 求关于刻度系数的偏导数
        for(int i = 3; i < 6; i++)
            for(int j = 0; j < 6; j++)
                // df/dkx = 2 * (amx - dx) ^ 2 * kx
                prtl_deri[i][j] = 2.0f * pow(ele(acce, 3, j, i - 3) - ele(grad_coff_zero_bias, 1, i - 3, 0), 2) * ele(grad_coff_zero_bias, 1, i, 0);

        Init_Matrix_Zero((Matrix_Type)M, 6, 6);
        for(int i = 0; i < 6; i++)
            for(int j = 0; j < 6; j++)
                for(int t = 0; t < 6; t++)
                    // Mij = Σ6(df/dci * df/dcj)
                    M[i][j] += prtl_deri[i][t] * prtl_deri[j][t];

        Init_Matrix_Zero((Matrix_Type)A, 6, 1);
        for(int i = 0; i < 6; i++)
            for(int j = 0; j < 6; j++)
                // Ai = Σ6(df/dci * (T - fk0)) 
                A[i][0] += prtl_deri[i][j] * (1 - A_Square_Sum[j][0]);

        // A = M * D
        // D = M-1 * A;
        Matrix_Inverse_Adjoint_Matrix((Matrix_Type)M, (Matrix_Type)M_Inv, 6);
        Matrix_Multiplication((Matrix_Type)M_Inv, (Matrix_Type)A, (Matrix_Type)D, 6, 6, 1);

        // prtl_deri += D;
        Matrix_Addition((Matrix_Type)grad_coff_zero_bias, (Matrix_Type)D, (Matrix_Type)grad_coff_zero_bias, 6, 1);
        
        // 如果变化量已经很小了, 说明迭代得差不多了
        count = 0;

        for(int i = 0; i < 6; i++)
            if(abs(D[i][0]) <= PERMIT_DIFF)
                count++;

        if(count == 6)
            break;
    }
}
