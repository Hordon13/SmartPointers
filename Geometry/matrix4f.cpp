//
// Created by zbora on 2019-09-05.
//

#include "matrix4f.h"


Matrix4f::Matrix4f()
{
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            coeff[i][j] = 0;
        }
    }
}

Matrix4f::Matrix4f(float a, float b, float c, float d, float e, float f, float g, float h,
    float i, float j, float k, float l, float m, float n, float o, float p)
{
    coeff[0][0] = a;
    coeff[0][1] = b;
    coeff[0][2] = c;
    coeff[0][3] = d;
    coeff[1][0] = e;
    coeff[1][1] = f;
    coeff[1][2] = g;
    coeff[1][3] = h;
    coeff[2][0] = i;
    coeff[2][1] = j;
    coeff[2][2] = k;
    coeff[2][3] = l;
    coeff[3][0] = m;
    coeff[3][1] = n;
    coeff[3][2] = o;
    coeff[3][3] = p;
}

const float *Matrix4f::operator[](uint8_t i) const
{
    return coeff[i];
}

float *Matrix4f::operator[](uint8_t i)
{
    return coeff[i];
}
