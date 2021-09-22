#ifndef GRADIENT_DESCENT
#define GRADIENT_DESCENT

#include <stdio.h>
#include "utils/Matrix.h"
#include "utils/utils.h"

void Gradient_Descent(int var_num, Matrix_Type start_point[var_num][1], Matrix_Type end_point[var_num][1]);
#endif /*GRADIENT_DESCENT*/