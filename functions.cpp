#include <iostream>
#include <cmath>
#include "functions.h"

// Normalize vector
Vec3f normalize(Vec3f v)
{
    float invLen = 1 / v.length();
    return Vec3f(v.x * invLen, v.y * invLen, v.z * invLen);
}

Vec3f cross(Vec3f v1, Vec3f v2)
{
    return Vec3f(
            v1.y * v2.z - v1.z * v2.y,
            v1.z * v2.x - v1.x * v2.z,
            v1.x * v2.y - v1.y * v2.x);
}

// Calculate scale for projection matrix
float scaleCoeff(float fovDeg)
{
    return 1 / (tan(fovDeg * 0.5 * M_PI / 180));
}

// Generate camera matrix
Matrix4f getCameraMx(Vec3f from, Vec3f to)
{
    Matrix4f result;

    // forward for the (z-axis)
    Vec3f forward = normalize(from - to);
    result[2][0] = forward.x;
    result[2][1] = forward.y;
    result[2][2] = forward.z;
    result[2][3] = 0;

    // right vector
    Vec3f tmp(0, 1, 0);
    Vec3f right = cross(normalize(tmp), forward);
    result[0][0] = right.x;
    result[0][1] = right.y;
    result[0][2] = right.z;
    result[0][3] = 0;

    // uo vector
    Vec3f up = cross(forward, right);
    result[1][0] = up.x;
    result[1][1] = up.y;
    result[1][2] = up.z;
    result[1][3] = 0;

    // translation
    result[3][0] = from.x;
    result[3][1] = from.y;
    result[3][2] = from.z;
    result[3][3] = 1;

    return result;
}

// Generate projection matrix
Matrix4f getProjMx(float fovDeg, float clippingN, float clippingF)
{
    Matrix4f mx;

    float remapZ1 = -clippingF / (clippingF - clippingN);
    float remapZ2 = -clippingF * clippingN / (clippingF - clippingN);

    mx[0][0] = scaleCoeff(fovDeg);
    mx[1][1] = scaleCoeff(fovDeg);
    mx[2][3] = -1;
    mx[2][2] = remapZ1;
    mx[3][2] = remapZ2;

    return mx;
}

// Print 2D matrix
void printMx(Matrix4f mx)
{
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << mx[i][j] << "\t";
        }
        std::cout << '\n';
    }
}

// Print 1D matrix
void printMx(Vec3f v)
{
    std::cout << v.x << "\t" << v.y << "\t" << v.z << "\t" << '\n';
}

// Multiply Matrix4f with Matrix4f
Matrix4f mxMult(Matrix4f mx1, Matrix4f mx2)
{
    Matrix4f result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                result[i][j] += mx1[i][k] * mx2[k][j];
            }
        }
    }

    return result;
}

// Multiply Vec3f with Matrix4f
Vec3f vecMxMult(Vec3f v, Matrix4f mx)
{
    float x = v.x * mx[0][0] + v.y * mx[1][0] + v.z * mx[2][0] + 1 * mx[3][0];
    float y = v.x * mx[0][1] + v.y * mx[1][1] + v.z * mx[2][1] + 1 * mx[3][1];
    float z = v.x * mx[0][2] + v.y * mx[1][2] + v.z * mx[2][2] + 1 * mx[3][2];
    float w = v.x * mx[0][3] + v.y * mx[1][3] + v.z * mx[2][3] + 1 * mx[3][3];

    // normalize if w is different than 1 (convert from homogeneous to Cartesian coordinates)
    if (w != 1) {
        x /= w;
        y /= w;
        z /= w;
    }
    return Vec3f(x,y,z);
}