#ifndef GNI_ACCE_H
#define GNI_ACCE_H

#include <stdio.h>
#include "utils/Matrix.h"
#include "utils/utils.h"

#define PERMIT_DIFF 0.00001

void GNI_Acce(Matrix_Type acce, Matrix_Type bias_coei);
#endif /*GNI_ACCE_H*/
