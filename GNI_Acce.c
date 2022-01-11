#include "GNI_Acce.h"

// 第一种思路, 详见论文基于高斯牛顿迭代法的MEMS加速度计标定方法_桂毅 ./Docs
// // acce是6个姿态下的3轴加速度数据矩阵, 六行三列acce[6][3]
// // grad_coff_zero_bias是6行1列的矩阵, 前三行是零偏系数, 后三行是刻度系数
// void GNI_Acce(Matrix_Type acce, Matrix_Type bias_coei){

//     int cnt = 0;
//     // D是6个参数的变化矩阵
//     Matrix_datatype D[6][1] = {0.0};
//     // 6个姿态的偏导数矩阵, 即雅可比矩阵
//     Matrix_datatype JT[6][6] = {0.0}, J[6][6] = {0.0};
//     // 偏导数乘法矩阵
//     Matrix_datatype M[6][6] = {0.0};
//     // 偏导数乘目标
//     Matrix_datatype A[6][1] = {0.0};
//     // 偏导数乘法逆矩阵
//     Matrix_datatype M_Inv[6][6] = {0.0};
//     // 加速度计的平方和系数
//     Matrix_datatype A_Square_Sum[6][1] = {0.0};

//     // 零偏系数初始化为0, 刻度系数初始化为1
//     for(int i = 0; i < 3; i++)
//         ele(bias_coei, 1, i, 0) = 0.0f;
//     for(int i = 3; i < 6; i++)
//         ele(bias_coei, 1, i, 0) = 1.0f;

//     // 六个姿态下加速度计矫正公式平方和
//     for(int i = 0; i < 6; i++)
//         //((amx - dx) * kx)^2 + ((amy - dy) * ky)^2 + ((amz - dz) * kz)^2 
//         A_Square_Sum[i][0] = pow((ele(acce, 3, i, 0) - ele(bias_coei, 1, 0, 0)) * ele(bias_coei, 1, 3, 0), 2)\
//                            + pow((ele(acce, 3, i, 1) - ele(bias_coei, 1, 1, 0)) * ele(bias_coei, 1, 4, 0), 2)\
//                            + pow((ele(acce, 3, i, 2) - ele(bias_coei, 1, 2, 0)) * ele(bias_coei, 1, 5, 0), 2);

//     // get_var_name(A_Square_Sum);
//     // Visit_Matrix((Matrix_Type)A_Square_Sum, 6, 1);

//     while(cnt != 6){
//         /* 求6个姿态下的关于6个系数的偏导数, 即雅可比矩阵 */
//         // 求关于零偏系数的偏导数
//         for(int i = 0; i < 3; i++)
//             for(int j = 0; j < 6; j++)
//                 // df/dox = -2 * (amx - dx) * kx^2
//                 JT[i][j] = -2.0f * (ele(acce, 3, j, i) - ele(bias_coei, 1, i, 0)) * pow(ele(bias_coei, 1, i + 3, 0), 2);

//         // 求关于刻度系数的偏导数
//         for(int i = 3; i < 6; i++)
//             for(int j = 0; j < 6; j++)
//                 // df/dkx = 2 * (amx - dx) ^ 2 * kx
//                 JT[i][j] = 2.0f * pow(ele(acce, 3, j, i - 3) - ele(bias_coei, 1, i - 3, 0), 2) * ele(bias_coei, 1, i, 0);

//         Matrix_Transpose((Matrix_Type)JT, (Matrix_Type)J, 6, 6);
//         Init_Matrix_Zero((Matrix_Type)M, 6, 6);

//         for(int i = 0; i < 6; i++)
//             for(int j = 0; j < 6; j++)
//                 for(int t = 0; t < 6; t++)
//                     // Mij = Σ6(df/dci * df/dcj)
//                     M[i][j] += JT[i][t] * JT[j][t];
        
//         // get_var_name(M);
//         // Visit_Matrix((Matrix_Type)M, 6, 6);

//         Init_Matrix_Zero((Matrix_Type)A, 6, 1);
//         for(int i = 0; i < 6; i++)
//             for(int j = 0; j < 6; j++)
//                 // Ai = Σ6(df/dci * (T - fk0))
//                 A[i][0] += JT[i][j] * (1 - A_Square_Sum[j][0]);

//         // get_var_name(A);
//         // Visit_Matrix((Matrix_Type)A, 6, 1);

//         // A = M * D;
//         // D = M-1 * A;
//         Matrix_Inverse_Gauss_JTordan((Matrix_Type)M, (Matrix_Type)M_Inv, 6);
//         Matrix_Multiplication((Matrix_Type)M_Inv, (Matrix_Type)A, (Matrix_Type)D, 6, 6, 1);

//         // // M * D = A; 
//         // Lineral_Equations_Gauss_JTordan((Matrix_Type)M, (Matrix_Type)A, 6);

//         // get_var_name(D);
//         // Visit_Matrix((Matrix_Type)D, 6, 1);

//         // bias_coei += D;
//         Matrix_Addition((Matrix_Type)bias_coei, (Matrix_Type)D, (Matrix_Type)bias_coei, 6, 1);
        
//         // 更新残差即, 加速度计矫正公式平方和
//         for(int i = 0; i < 6; i++)
//             //((amx - dx) * kx)^2 + ((amy - dy) * ky)^2 + ((amz - dz) * kz)^2 
//             A_Square_Sum[i][0] = pow((ele(acce, 3, i, 0) - ele(bias_coei, 1, 0, 0)) * ele(bias_coei, 1, 3, 0), 2)\
//                                + pow((ele(acce, 3, i, 1) - ele(bias_coei, 1, 1, 0)) * ele(bias_coei, 1, 4, 0), 2)\
//                                + pow((ele(acce, 3, i, 2) - ele(bias_coei, 1, 2, 0)) * ele(bias_coei, 1, 5, 0), 2);



//         // 如果变化量已经很小了, 说明迭代得差不多了
//         cnt = 0;

//         for(int i = 0; i < 6; i++)
//             if(abstract(D[i][0]) <= PERMIT_DIFF)
//                 cnt++;
//     }        
    
//     // get_var_name(A_Square_Sum);
//     // Visit_Matrix((Matrix_Type)A_Square_Sum, 6, 1);
// }

// 另一种思路, 详见四轴课程祁朋组课件
// acce是6个姿态下的3轴加速度数据矩阵, 六行三列acce[6][3]
// grad_coff_zero_bias是6行1列的矩阵, 前三行是零偏系数, 后三行是刻度系数
void GNI_Acce(Matrix_Type acce, Matrix_Type bias_coei){

    int iter_cnt = 0, cnt = 0;
    // 迭代次数上限值
    int iter_thre = 10;
    // D是6个参数的变化矩阵
    Matrix_datatype D[6][1] = {0.0};
    // 6个姿态的偏导数矩阵, 即雅可比矩阵
    Matrix_datatype JT[6][6] = {0.0}, J[6][6] = {0.0};
    // 偏导数乘法矩阵
    Matrix_datatype M[6][6] = {0.0};
    // 偏导数乘目标
    Matrix_datatype A[6][1] = {0.0};
    // 偏导数乘法逆矩阵
    Matrix_datatype M_Inv[6][6] = {0.0};
    // 加速度计的平方和系数
    Matrix_datatype A_Square_Sum[6][1] = {0.0};
    // 加速度计的残差
    Matrix_datatype r[6][1] = {0.0};

    // 零偏系数初始化为0, 刻度系数初始化为1
    for(int i = 0; i < 3; i++)
        ele(bias_coei, 1, i, 0) = 0.0f;
    for(int i = 3; i < 6; i++)
        ele(bias_coei, 1, i, 0) = 1.0f;

    // 六个姿态下加速度计矫正公式平方和
    for(int i = 0; i < 6; i++)
        //((amx - dx) * kx)^2 + ((amy - dy) * ky)^2 + ((amz - dz) * kz)^2 
        A_Square_Sum[i][0] = pow((ele(acce, 3, i, 0) - ele(bias_coei, 1, 0, 0)) * ele(bias_coei, 1, 3, 0), 2)\
                           + pow((ele(acce, 3, i, 1) - ele(bias_coei, 1, 1, 0)) * ele(bias_coei, 1, 4, 0), 2)\
                           + pow((ele(acce, 3, i, 2) - ele(bias_coei, 1, 2, 0)) * ele(bias_coei, 1, 5, 0), 2);

    // 六个姿态下加速度计的残差
    for(int i = 0; i < 6; i++)
        //((amx - dx) * kx)^2 + ((amy - dy) * ky)^2 + ((amz - dz) * kz)^2 
        r[i][0] = 1 - A_Square_Sum[i][0];

    // get_var_name(A_Square_Sum);
    // Visit_Matrix((Matrix_Type)A_Square_Sum, 6, 1);

    while(cnt != 6){
        /* 求6个姿态下的关于6个系数的偏导数, 即雅可比矩阵 */
        // 求关于零偏系数的偏导数
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 6; j++)
                // df/dox = 2 * (amx - dx) * kx^2
                JT[i][j] = 2.0f * (ele(acce, 3, j, i) - ele(bias_coei, 1, i, 0)) * pow(ele(bias_coei, 1, i + 3, 0), 2);

        // 求关于刻度系数的偏导数
        for(int i = 3; i < 6; i++)
            for(int j = 0; j < 6; j++)
                // df/dkx = -2 * (amx - dx) ^ 2 * kx
                JT[i][j] = -2.0f * pow(ele(acce, 3, j, i - 3) - ele(bias_coei, 1, i - 3, 0), 2) * ele(bias_coei, 1, i, 0);

        Matrix_Transpose((Matrix_Type)JT, (Matrix_Type)J, 6, 6);
        Init_Matrix_Zero((Matrix_Type)M, 6, 6);

        // 计算简化的海瑟矩阵 / 2, 即JTJr
        Matrix_Multiplication((Matrix_Type)JT, (Matrix_Type)J, (Matrix_Type)M, 6, 6, 6);
        
        // get_var_name(M);
        // Visit_Matrix((Matrix_Type)M, 6, 6);

        // 计算JT*r
        Matrix_Multiplication((Matrix_Type)JT, (Matrix_Type)r, (Matrix_Type)A, 6, 6, 1);

        // get_var_name(A);
        // Visit_Matrix((Matrix_Type)A, 6, 1);

        // D = M-1 * A;
        Matrix_Inverse_Gauss_Jordan((Matrix_Type)M, (Matrix_Type)M_Inv, 6);
        Matrix_Multiplication((Matrix_Type)M_Inv, (Matrix_Type)A, (Matrix_Type)D, 6, 6, 1);

        // // M * D = A; 
        // Lineral_Equations_Gauss_Jordan((Matrix_Type)M, (Matrix_Type)A, 6);

        // get_var_name(D);
        // Visit_Matrix((Matrix_Type)D, 6, 1);

        // 更新零偏误差和刻度误差
        // bias_coei -= D;
        Matrix_Subtraction((Matrix_Type)bias_coei, (Matrix_Type)D, (Matrix_Type)bias_coei, 6, 1);
        
        // 更新残差即, 加速度计矫正公式平方和
        for(int i = 0; i < 6; i++)
            //((amx - dx) * kx)^2 + ((amy - dy) * ky)^2 + ((amz - dz) * kz)^2 
            A_Square_Sum[i][0] = pow((ele(acce, 3, i, 0) - ele(bias_coei, 1, 0, 0)) * ele(bias_coei, 1, 3, 0), 2)\
                               + pow((ele(acce, 3, i, 1) - ele(bias_coei, 1, 1, 0)) * ele(bias_coei, 1, 4, 0), 2)\
                               + pow((ele(acce, 3, i, 2) - ele(bias_coei, 1, 2, 0)) * ele(bias_coei, 1, 5, 0), 2);

        for(int i = 0; i < 6; i++)
            //((amx - dx) * kx)^2 + ((amy - dy) * ky)^2 + ((amz - dz) * kz)^2 
            r[i][0] = 1 - A_Square_Sum[i][0];

        // 如果变化量已经很小了, 说明迭代得差不多了
        cnt = 0;

        for(int i = 0; i < 6; i++)
            if(abstract(D[i][0]) <= PERMIT_DIFF)
                cnt++;

        iter_cnt++;
        if(iter_cnt > iter_thre)
            break;
    }        
    
    // get_var_name(A_Square_Sum);
    // Visit_Matrix((Matrix_Type)A_Square_Sum, 6, 1);
}
