//
// Created by Bray, Matthew D ERDC-RDE-GSL-MS CIV on 11/11/22.
//

#include "MathUtils.h"

bool is_equal(float a, float b, float epsilon) {
    return fabs(a - b) < epsilon;
}

