#ifndef GNI_ACCE_H
#define GNI_ACCE_H

#include <stdio.h>
#include "utils/Matrix.h"

#define PERMIT_DIFF 0.001

void GNI_Acce(Matrix_Type acce, Matrix_Type grad_coff_zero_bias);
#endif /*GNI_ACCE_H*/
