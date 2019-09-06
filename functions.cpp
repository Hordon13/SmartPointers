#include <iostream>
#include <cmath>
#include "functions.h"

// Normalize vector
Vec3f Function::normalize(Vec3f v) {
    float invLen = 1 / v.length();
    return Vec3f(v.x * invLen, v.y * invLen, v.z * invLen);
}

Vec3f Function::cross(Vec3f v1, Vec3f v2) {
    return Vec3f(
            v1.y * v2.z - v1.z * v2.y,
            v1.z * v2.x - v1.x * v2.z,
            v1.x * v2.y - v1.y * v2.x);
}

// Calculate scale for projection matrix
float Function::scaleCoeff(float fovDeg) {
    return 1 / (tan(fovDeg * 0.5 * M_PI / 180));
}

// Generate camera matrix
Matrix4f Function::getCameraMx(Vec3f from, Vec3f to) {
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

    // TODO: further research needed
    // translation
    /*
    result[3][0] = from.x;
    result[3][1] = from.y;
    result[3][2] = from.z;
    result[3][3] = 1;
	*/

    return result;
}

// Generate projection matrix
Matrix4f Function::getProjMx(float fovDeg, float clippingN, float clippingF) {
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

// Multiply Vec3f with Matrix4f
Vec3f Function::vecMxMult(Vec3f v, Matrix4f mx) {
    float x = v.x * mx[0][0] + v.y * mx[1][0] + v.z * mx[2][0] + 1 * mx[3][0];
    float y = v.x * mx[0][1] + v.y * mx[1][1] + v.z * mx[2][1] + 1 * mx[3][1];
    float z = v.x * mx[0][2] + v.y * mx[1][2] + v.z * mx[2][2] + 1 * mx[3][2];
    float w = v.x * mx[0][3] + v.y * mx[1][3] + v.z * mx[2][3] + 1 * mx[3][3];

    // TODO: further research needed
    // normalize if w is different than 1 (convert from homogeneous to Cartesian coordinates)
    /*if (w != 1 && w != 0) {
        x /= w;
        y /= w;
        z /= w;
    }*/
    return Vec3f(x, y, z);
}

void Function::sortPolygons(std::vector<Polygon> &polygons) {
    for (int l = 0; l < polygons.size(); ++l) {
        for (int i = 0; i < polygons.size(); ++i) {
            if (polygons[l].getMinZ()[0] > polygons[i].getMinZ()[0]) {
                Polygon temp = polygons[l];
                polygons[l] = polygons[i];
                polygons[i] = temp;
            }
            if (polygons[l].getMinZ()[0] == polygons[i].getMinZ()[0]) {
                if (polygons[l].getMinZ()[1] > polygons[i].getMinZ()[1]) {
                    Polygon temp = polygons[l];
                    polygons[l] = polygons[i];
                    polygons[i] = temp;
                }
                if (polygons[l].getMinZ()[1] == polygons[i].getMinZ()[1]) {
                    if (polygons[l].getMinZ()[2] > polygons[i].getMinZ()[2]) {
                        Polygon temp = polygons[l];
                        polygons[l] = polygons[i];
                        polygons[i] = temp;
                    }
                }
            }
        }
    }
}