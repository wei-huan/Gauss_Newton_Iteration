#include "utils/Matrix.h"
#include "utils/utils.h"

typedef float Ang_Type;

void Init_Rotate_Matrix(Matrix_Type M);
void Update_Roll_Rot_Matrix(Matrix_Type Roll_RM, Ang_Type roll);
void Update_Pitch_Rot_Matrix(Matrix_Type Pitch_RM, Ang_Type pitch);
void Update_Roll_Rot_Matrix(Matrix_Type Yaw_RM, Ang_Type yaw);
