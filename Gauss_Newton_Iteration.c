#include "Gauss_Newton_Iteration.h"

void Gauss_Newton_Iteration(Matrix_Type data, Matrix_Type coei, int coei_num, int rela_num){

    // 雅可比矩阵
    Matrix_datatype J[rela_num][coei_num], JT[coei_num][rela_num];
    // 残差
    Matrix_datatype r[rela_num][1];
    // 变化量
    Matrix_datatype delta[coei_num][1];
    // 迭代停止阈值
    Matrix_datatype d_thre;
    // 参数变化量矩阵
    Matrix_datatype delta[coei_num][1];
    // 黑塞矩阵
    Matrix_datatype Hessain[coei_num][coei_num];
    // 黑塞矩阵逆矩阵
    Matrix_datatype Hessain_Inv[coei_num][coei_num];
    // 中间过程量矩阵
    Matrix_datatype Middle[coei_num][rela_num];
    // 迭代次数, 容忍迭代次数
    unsigned int iter_count = 0, tolerate_count = 100;

    while(d_thre){    
        // 初始化残差
        // r = (target - data[i])^2;

        // 更新雅可比矩阵
        // J[i][j] = 偏导数;

        // JT = J的转置
        Matrix_Transpose((Matrix_Type)J, (Matrix_Type)JT, rela_num, coei_num);

        // 黑塞矩阵求近似解 Hessain = 2 * JT * J;
        Matrix_Multiplication((Matrix_Type)JT, (Matrix_Type)J, (Matrix_Type)Hessain, coei_num, rela_num, coei_num);
        Matrix_Multi_Const((Matrix_Type)Hessain, (Matrix_Type)Hessain, 2.0f, coei_num, coei_num);

        // delta = -0.5f * (Hessain)-1 * JT * r
        Matrix_Inverse_Gauss_Jordan((Matrix_Type)Hessain, (Matrix_Type)Hessain_Inv, coei_num);
        Matrix_Multiplication((Matrix_Type)Hessain_Inv, (Matrix_Type)JT, (Matrix_Type)Middle, coei_num, coei_num, rela_num);
        Matrix_Multiplication((Matrix_Type)Middle, (Matrix_Type)r, (Matrix_Type)delta, coei_num, rela_num, 1);
        Matrix_Multi_Const((Matrix_Type)delta, (Matrix_Type)delta, -0.5f, rela_num, 1);

        // coei = coei + delta;
        Matrix_Addition((Matrix_Type)coei, (Matrix_Type)delta, (Matrix_Type)coei, coei_num, 1);

        iter_count++;
        if(iter_count >= tolerate_count)
            break;
    }

}