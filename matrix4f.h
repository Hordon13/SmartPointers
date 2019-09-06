#ifndef HACKATHON_MATRIX4F_H
#define HACKATHON_MATRIX4F_H

#include <cstdint>

class Matrix4f {
public:

    Matrix4f();

    Matrix4f(float a, float b, float c, float d, float e, float f, float g, float h,
             float i, float j, float k, float l, float m, float n, float o, float p);

    const float *operator[](uint8_t i) const;

    float *operator[](uint8_t i);

    float coeff[4][4];
};

#endif //HACKATHON_MATRIX4F_H