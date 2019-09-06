#include <cmath>
#include "vec3f.h"

Vec3f::Vec3f()
{ x = y = z = 0; }

Vec3f::Vec3f(float xc, float yc, float zc)
{
    x = xc;
    y = yc;
    z = zc;
}

float Vec3f::length()
{
    return sqrt(x * x + y * y + z * z);
}

Vec3f Vec3f::operator-(const Vec3f &v)
{
    return Vec3f(x - v.x, y - v.y, z - v.z);
}

Vec3f Vec3f::operator+(const Vec3f &v)
{
    return Vec3f(x + v.x, y + v.y, z + v.z);
}
