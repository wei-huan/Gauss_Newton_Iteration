#include "Rotate_Matrix.h"

void Init_Rotate_Matrix(Matrix_Type M){
    Init_Matrix_Identity((Matrix_Type)M, 3);
}

void Update_Roll_Rot_Matrix(Matrix_Type Roll_RM, Ang_Type roll){
    ele(Roll_RM, 3, 1, 1) = ele(Roll_RM, 3, 2, 2) =  cos(roll);
    ele(Roll_RM, 3, 1, 2) = sin(roll);
    ele(Roll_RM, 3, 2, 1) = sin(-1 * roll);
}

void Update_Pitch_Rot_Matrix(Matrix_Type Pitch_RM, Ang_Type pitch){
    ele(Pitch_RM, 3, 0, 0) = ele(Pitch_RM, 3, 2, 2) =  cos(pitch);
    ele(Pitch_RM, 3, 0, 2) = sin(-1 * pitch);
    ele(Pitch_RM, 3, 2, 0) = sin(pitch);
}

void Update_Yaw_Rot_Matrix(Matrix_Type Yaw_RM, Ang_Type yaw){
    ele(Yaw_RM, 3, 0, 0) = ele(Yaw_RM, 3, 1, 1) =  cos(yaw);
    ele(Yaw_RM, 3, 0, 1) = sin(yaw);
    ele(Yaw_RM, 3, 1, 0) = sin(-1 * yaw);
}
