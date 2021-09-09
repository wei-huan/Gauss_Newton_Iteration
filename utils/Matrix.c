#include "Matrix.h"

//row行, col列
void Visit_Matrix(Matrix_Type A, int row, int col){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++)
            printf("%.2f ", ele(A, col, i, j));
        EOL;
    }
}

// 初始化row行, col列矩阵为零矩阵
void Init_Matrix_Zero(Matrix_Type A, int row, int col){
    for(int i = 0; i < row; i++)
        for(int j = 0; j < col; j++)
            ele(A, col, i, j) = 0;
}

// 初始化方阵为单位矩阵
void Init_Matrix_Identity(Matrix_Type A, int m){
    for(int i = 0; i < m; i++)
        for(int j = 0; j < m; j++)
            if(i == j)
                ele(A, m, i, j) = 1;
            else
                ele(A, m, i, j) = 0;
}

// 复制矩阵 A 给 B, row行, col列
void Copy_Matrix(Matrix_Type A, Matrix_Type B, int row, int col){
    for(int i = 0; i < row; i++)
        for(int j = 0; j < col; j++)
            ele(B, col, i, j) = ele(A, col, i, j);
}

// C = A + B, row行, col列
void Matrix_Addition(Matrix_Type A, Matrix_Type B, Matrix_Type C, int row, int col){
    for(int i = 0; i < row; i++)
        for(int j = 0; j < col; j++)
            ele(C, col, i, j) = ele(A, col, i, j) + ele(B, col, i, j);
}

// C = A - B, row行, col列
void Matrix_Subtraction(Matrix_Type A, Matrix_Type B, Matrix_Type C, int row, int col){

    for(int i = 0; i < row; i++)
        for(int j = 0; j < col; j++)
            ele(C, col, i, j) = ele(A, col, i, j) - ele(B, col, i, j);
}

//C = A * B, A在左, B在右, Amt, Btn
void Matrix_Multiplication(Matrix_Type A, Matrix_Type B, Matrix_Type C, int m, int t, int n){
    Matrix_datatype tmp;

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            tmp = (Matrix_datatype)0;

            for(int k = 0; k < t; k++)
                tmp += ele(A, t, i, k) * ele(B, n, k, j);

            ele(C, n, i, j) = tmp;
        }
    }
}

// B = A-1 A为m阶方阵, B = A-1 = A* / detA
void Matrix_Inverse_Adjoint_Matrix(Matrix_Type A, Matrix_Type B, int m){
    Matrix_datatype detA = 0.0;

    // 求 A 的伴随矩阵
    for(int i = 0; i < m; i++)
        for(int j = 0; j < m; j++)
            ele(B, m, i, j) = pow(-1, i + j) * Matrix_Cofactor(A, m, j, i);
        
    // Visit_Matrix(B, m, m);

    // 求 A 的行列式 detA
    for(int j = 0; j < m; j++)
        detA += ele(A, m, 0, j) * ele(B, m, 0, j);
    // printf("detA: %.2f\n", detA);

    //detA == 0说明矩阵不可逆
    if(detA == 0){
        printf("矩阵不可逆\n");
        return;
    }
    
    // 逆矩阵 B
    for(int i = 0; i < m; i++)
        for(int j = 0; j < m; j++)
            ele(B, m, i, j)= ele(B, m, i, j) / detA;
}

// 高斯约当消元法求A的逆矩阵B
void Matrix_Inverse_Gauss_Jordan(Matrix_Type A, Matrix_Type B, int m){
    Init_Matrix_Identity(B, m);
    
    //
}

// 求矩阵关于某一个元素aij的代数余子式, 即二维数组矩阵A下标为ij的元素的代数余子式
Matrix_datatype Matrix_Cofactor(Matrix_Type A, int m, int i, int j){
    if(m == 1){
        printf("矩阵小于2阶\n");
        return 0;
    }

    if(m == 2)
        return ele(A, 2, 1 - i, 1 - j);

    Matrix_datatype cofactor = 0;

    if(m == 3){
        Matrix_datatype B[2][2];
        int a = 0, b = 0;

        for(int x = 0; x < m; x++){
            for(int y = 0; y < m; y++)
                if((x != i) && (y != j))
                    B[a][b++] = ele(A, m, x, y);

            if(x != i)
                a++;
            
            b = 0;
        }

        cofactor = B[0][0] * B[1][1] - B[0][1] * B[1][0];

        return cofactor;
    }

    Matrix_datatype tmp1, tmp2;
    int count_p, x_jump_p, y_jump_p;
    int count_n, x_jump_n, y_jump_n;

    for(int x = 0; x < m; x++){
        tmp1 = tmp2 = (Matrix_datatype)1;
        count_p = count_n = x_jump_p = y_jump_p = x_jump_n = y_jump_n = 0;

        if(x != i){
            for(int y = 0; y < m; y++){
                if(y == j)
                    y_jump_p = 1;

                if(((x + y) % m) == i)
                    x_jump_p = 1;

                if(count_p != m - 1){
                    tmp1 = tmp1 * ele(A, m, (x + y + x_jump_p) % m, (y + y_jump_p) % m);
                    count_p++;
                }

                if(((x + y) % m) == i)
                    x_jump_n = 1;
            
                if((m - 1 - y) == j)
                    y_jump_n = 1;

                if(count_n != m - 1){
                    tmp2 = tmp2 * ele(A, m, (x + y + x_jump_n) % m, (m - 1 - y - y_jump_n) % m);
                    count_n++;
                }
            }
            // printf("tmp1: %d\n", tmp1);
            // printf("tmp2: %d\n", tmp2);
            cofactor += (tmp1 - tmp2);
        }
    }

    return cofactor;
}

// B = AT
void Matrix_Transpose(Matrix_Type A, Matrix_Type B, int row, int col){
    for(int i = 0; i < row; i++)
        for(int j = 0; j < col; j++)
            ele(B, row, j, i) = ele(A, col, i, j);
}

