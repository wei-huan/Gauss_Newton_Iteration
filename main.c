#include "GNI_Acce.h"

int main(){
    Matrix_datatype acce[6][3] = {0.0}, grad_coff_zero_bias[6][1] = {0.0}; 
    
    Visit_Matrix((Matrix_Type)acce, 6, 3);
    Visit_Matrix((Matrix_Type)grad_coff_zero_bias, 6, 1);

    GNI_Acce((Matrix_Type)acce, (Matrix_Type)grad_coff_zero_bias);
    Visit_Matrix((Matrix_Type)grad_coff_zero_bias, 6, 1);
}
