#include "Gradient_Descent.h"

// void Gradient_Descent(int var_num, Matrix_Type start_point[var_num][1], Matrix_Type end_point[var_num][1]){
//     // 步长
//     Matrix_datatype path = 0.01f;
//     // 偏导矩阵, 即梯度向量
//     Matrix_datatype grad_vec[var_num][1];
//     // 变化值
//     Matrix_datatype delta[var_num][1];
//     // 阈值
//     Matrix_datatype end_thre = 0.01f;
//     int thre_count = 0;
//     // 迭代次数
//     int iter_count = 0;

//     // 初始化
//     Copy_Matrix((Matrix_Type)start_point, (Matrix_Type)end_point, var_num, 1);

//     while(thre_count < var_num){
//         // 更新梯度向量
//         for(int i = 0; i < var_num; i++)
//             grad_vec[i][0] = 0.0f; //偏导数

//         // 更新变化量
//         for(int i = 0; i < var_num; i++)
//             delta[i][0] = path * grad_vec[i][0];

//         Matrix_Subtraction((Matrix_Type)end_point, (Matrix_Type)delta, (Matrix_Type)end_point, var_num, 1);

//         // 判断是否结束
//         thre_count = 0;
//         for(int i = 0; i < var_num; i++)
//             if(delta[i][0] < end_thre)
//                 thre_count++;

//         iter_count++;
//         if(iter_count > 100)
//             break;
//     }
// }
