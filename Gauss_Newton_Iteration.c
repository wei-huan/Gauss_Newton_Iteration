#include "Gauss_Newton_Iteration.h"

void Gauss_Newton_Iteration(Matrix_Type data, Matrix_Type coei, int coei_num){

    // 雅可比矩阵
    Matrix_datatype J[coei_num][1], JT[1][coei_num], JTJ[coei_num][coei_num];
    // 残差
    Matrix_datatype r;
    // 变化量
    Matrix_datatype delta[coei_num][1];
    // 迭代停止阈值
    Matrix_datatype d_thre;
    // 参数变化量列矩阵
    Matrix_datatype coei_d[coei_num][1];

    // 初始化残差
    // r = ;

    while(d_thre){
        // 更新雅可比矩阵

    }
}