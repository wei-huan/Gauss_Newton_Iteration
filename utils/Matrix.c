#include "Matrix.h"

//row行, col列
void Visit_Matrix(Matrix_Type A, unsigned int row, unsigned int col){
    for(unsigned int i = 0; i < row; i++){
        for(unsigned int j = 0; j < col; j++)
            printf("%.2f ", ele(A, col, i, j));
        EOL;
    }
}

// 初始化row行, col列矩阵为零矩阵
void Init_Matrix_Zero(Matrix_Type A, unsigned int row, unsigned int col){
    for(unsigned int i = 0; i < row; i++)
        for(unsigned int j = 0; j < col; j++)
            ele(A, col, i, j) = 0;
}

// 初始化方阵为单位矩阵
void Init_Matrix_Identity(Matrix_Type A, unsigned int m){
    for(unsigned int i = 0; i < m; i++)
        for(unsigned int j = 0; j < m; j++)
            if(i == j)
                ele(A, m, i, j) = 1;
            else
                ele(A, m, i, j) = 0;
}

// 复制矩阵 A 给 B, row行, col列
void Copy_Matrix(Matrix_Type A, Matrix_Type B, unsigned int row, unsigned int col){
    for(unsigned int i = 0; i < row; i++)
        for(unsigned int j = 0; j < col; j++)
            ele(B, col, i, j) = ele(A, col, i, j);
}

// C = A + B, row行, col列
void Matrix_Addition(Matrix_Type A, Matrix_Type B, Matrix_Type C, unsigned int row, unsigned int col){
    for(unsigned int i = 0; i < row; i++)
        for(unsigned int j = 0; j < col; j++)
            ele(C, col, i, j) = ele(A, col, i, j) + ele(B, col, i, j);
}

// C = A - B, row行, col列
void Matrix_Subtraction(Matrix_Type A, Matrix_Type B, Matrix_Type C, unsigned int row, unsigned int col){

    for(unsigned int i = 0; i < row; i++)
        for(unsigned int j = 0; j < col; j++)
            ele(C, col, i, j) = ele(A, col, i, j) - ele(B, col, i, j);
}

//C = A * B, A在左, B在右, Amt, Btn
void Matrix_Multiplication(Matrix_Type A, Matrix_Type B, Matrix_Type C, unsigned int row1, unsigned int col1_row2, unsigned int col2){
    Matrix_datatype tmp;

    for(unsigned int i = 0; i < row1; i++){
        for(unsigned int j = 0; j < col2; j++){
            tmp = (Matrix_datatype)0;

            for(unsigned int k = 0; k < col1_row2; k++)
                tmp += ele(A, col1_row2, i, k) * ele(B, col2, k, j);

            ele(C, col2, i, j) = tmp;
        }
    }
}

// B = A-1 A为m阶方阵, B = A-1 = A* / detA
void Matrix_Inverse_Adjoint_Matrix(Matrix_Type A, Matrix_Type B, unsigned int m){
    Matrix_datatype detA = 0.0;

    // 求 A 的伴随矩阵
    for(unsigned int i = 0; i < m; i++)
        for(unsigned int j = 0; j < m; j++)
            ele(B, m, i, j) = pow(-1, i + j) * Matrix_Cofactor(A, m, j, i);
        
    // Visit_Matrix(B, m, m);

    // 求 A 的行列式 detA
    for(unsigned int j = 0; j < m; j++)
        detA += ele(A, m, 0, j) * ele(B, m, 0, j);
    printf("detA: %.2f\n", detA);

    //detA == 0说明矩阵不可逆
    if(detA == 0){
        printf("矩阵不可逆\n");
        return;
    }
    
    // 逆矩阵 B
    for(unsigned int i = 0; i < m; i++)
        for(unsigned int j = 0; j < m; j++)
            ele(B, m, i, j)= ele(B, m, i, j) / detA;
}

// 高斯约当消元法求A的逆矩阵B, 即行初等变换
void Matrix_Inverse_Gauss_Jordan(Matrix_Type A, Matrix_Type B, unsigned int m){
    unsigned int switch_row = 0;

    // 将B初始化为单位矩阵
    Init_Matrix_Identity(B, m);
    
    /* 行初等变换将A化为单位矩阵, 同时对B做相同的操作 */
    // 对每一列做相同的操作
    for(unsigned int j = 0; j < m; j++){
        for(unsigned int i = j; i < m; i++){
            // 先确定a[i][j]是不是0, 如果是得先调换另一行
            if(ele(A, m, i, j) == (Matrix_datatype)0.0f){
                // 如果没得调换说明有全0列, 说明没有逆矩阵, 直接退出函数
                if(is_Matrix_Column_Zero((Matrix_Type)A, m, m, j) == true){
                    printf("矩阵有全0列, 没有逆矩阵");
                    return ;
                }

                // 如果有该列有非0元则找到首个非0元所在的行调换
                switch_row = 0;
                while(ele(A, m, switch_row, j) == (Matrix_datatype)0.0f)
                    switch_row++;

                Matrix_Row_Switch((Matrix_Type)A, m, m, i, switch_row);
                Matrix_Row_Switch((Matrix_Type)B, m, m, i, switch_row);
            }

            // 将a[i][j]系数化为1
            Matrix_Row_Multiplication((Matrix_Type)A, m, m, (1.0f / ele(A, m, i, j)), i);
            Matrix_Row_Multiplication((Matrix_Type)B, m, m, (1.0f / ele(B, m, i, j)), i);

            // 将其他列化为0
            for(unsigned int k = 0; k < m; k++){
                if(k != i){
                    Matrix_Row_Add2Another((Matrix_Type)A, m, m, (-1.0f * ele(A, m, k, j)), i, k);
                    Matrix_Row_Add2Another((Matrix_Type)B, m, m, (-1.0f * ele(B, m, k, j)), i, k);
                }
            }
        }
    }
}

// 求矩阵关于某一个元素aij的代数余子式, 即二维数组矩阵A下标为ij的元素的代数余子式
Matrix_datatype Matrix_Cofactor(Matrix_Type A, unsigned int m, unsigned int i, unsigned int j){
    if(m == 1){
        printf("矩阵小于2阶\n");
        return 0;
    }

    if(m == 2)
        return ele(A, 2, 1 - i, 1 - j);

    Matrix_datatype cofactor = 0;

    if(m == 3){
        Matrix_datatype B[2][2];
        unsigned int a = 0, b = 0;

        for(unsigned int x = 0; x < m; x++){
            for(unsigned int y = 0; y < m; y++)
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
    unsigned int count_p, x_jump_p, y_jump_p;
    unsigned int count_n, x_jump_n, y_jump_n;

    for(unsigned int x = 0; x < m; x++){
        tmp1 = tmp2 = (Matrix_datatype)1;
        count_p = count_n = x_jump_p = y_jump_p = x_jump_n = y_jump_n = 0;

        if(x != i){
            for(unsigned int y = 0; y < m; y++){
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
void Matrix_Transpose(Matrix_Type A, Matrix_Type B, unsigned int row, unsigned int col){
    for(unsigned int i = 0; i < row; i++)
        for(unsigned int j = 0; j < col; j++)
            ele(B, row, j, i) = ele(A, col, i, j);
}

// 行初等变换, 交换两行元素
void Matrix_Row_Switch(Matrix_Type A, unsigned int row, unsigned int col, unsigned int i1, unsigned int i2){
    Matrix_datatype switch_aid;

    // 检查输入行数是否在范围内
    if(i1 >= row || i2 >= row){
        printf("行数超出矩阵的行大小\n");
        return ;
    }

    // 交换第row1和row2行
    for(unsigned int j = 0; j < col; j++){
        switch_aid = ele(A, col, i1, j);
        ele(A, col, i1, j) = ele(A, col, i2, j);
        ele(A, col, i2, j) = switch_aid;
    }
}

// 列初等变换, 交换两列元素
void Matrix_Column_Switch(Matrix_Type A, unsigned int row, unsigned int col, unsigned int j1, unsigned int j2){
    Matrix_datatype switch_aid;

    // 检查输入列数是否在范围内
    if(j1 >= col || j2 >= col){
        printf("列数超出矩阵的列大小\n");
        return ;
    }

    // 交换第row1和row2行
    for(unsigned int i = 0; i < col; i++){
        switch_aid = ele(A, col, i, j1);
        ele(A, col, i, j1) = ele(A, col, i, j2);
        ele(A, col, i, j2) = switch_aid;
    }
}

// 行初等变换, 第i行元乘非零数
void Matrix_Row_Multiplication(Matrix_Type A, unsigned int row, unsigned int col, Matrix_datatype multiplier, unsigned int i){
    // 检查输入行数是否在范围内
    if(i >= row){
        printf("行数超出矩阵的行大小\n");
        return ;
    }

    // 检查乘数是否非零
    if(multiplier == 0){
        printf("乘数为零\n");
        return ;
    }

    for(unsigned int j = 0; j < col; j++)
        ele(A, col, i, j) = multiplier * ele(A, col, i, j);
}

// 列初等变换, 第j列元乘非零数
void Matrix_Column_Multiplication(Matrix_Type A, unsigned int row, unsigned int col, Matrix_datatype multiplier, unsigned int j){
    // 检查输入列数是否在范围内
    if(j >= col){
        printf("列数超出矩阵的列大小\n");
        return ;
    }

    // 检查乘数是否非零
    if(multiplier == 0){
        printf("乘数为零\n");
        return ;
    }

    for(unsigned int i = 0; i < row; i++)
        ele(A, col, i, j) = multiplier * ele(A, col, i, j);
}

// 行初等变换, 第i1行元乘一个数加给i2行元
void Matrix_Row_Add2Another(Matrix_Type A, unsigned int row, unsigned int col, Matrix_datatype multiplier, unsigned int i1, unsigned int i2){
    // 检查输入行数是否在范围内
    if(i1 >= row || i2 >= row){
        printf("行数超出矩阵的行大小\n");
        return ;
    }

    for(unsigned int j = 0; j < col; j++)
        ele(A, col, i2, j) += multiplier * ele(A, col, i1, j);
}

// 列初等变换, 第j1列元乘一个数加给j2列元
void Matrix_Column_Add2Another(Matrix_Type A, unsigned int row, unsigned int col, Matrix_datatype multiplier, unsigned int j1, unsigned int j2){
    // 检查输入列数是否在范围内
    if(j1 >= col || j2 >= col){
        printf("列数超出矩阵的列大小\n");
        return ;
    }

    for(unsigned int i = 0; i < row; i++)
        ele(A, col, i, j2) += multiplier * ele(A, col, i, j1);
}

// 检查矩阵A第i行是不是全为0
bool is_Matrix_Row_Zero(Matrix_Type A, unsigned int row, unsigned int col, unsigned int i){
    for(unsigned int j = 0; j < col; j++)
        if(ele(A, col, i, j) != (Matrix_datatype)0)
            return false;

    return true;
}

// 检查矩阵A第j列是不是全为0
bool is_Matrix_Column_Zero(Matrix_Type A, unsigned int row, unsigned int col, unsigned int j){
    for(unsigned int i = 0; i < row; i++)
        if(ele(A, col, i, j) != (Matrix_datatype)0)
            return false;

    return true;
}