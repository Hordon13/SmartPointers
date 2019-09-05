//
// Created by zbora on 2019-09-05.
//

#ifndef HACKATHON_TEMP_VEC3F_H
#define HACKATHON_TEMP_VEC3F_H


class Vec3f {
public:
    Vec3f();

    Vec3f(float xc, float yc, float zc);

    float length();

    Vec3f operator-(const Vec3f &v);

    Vec3f operator+(const Vec3f &v);

    float x;
    float y;
    float z;
};


#endif //HACKATHON_TEMP_VEC3F_H
