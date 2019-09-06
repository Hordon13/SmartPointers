#ifndef HACKATHON_TEMP_FUNCTIONS_H
#define HACKATHON_TEMP_FUNCTIONS_H

#include "matrix4f.h"
#include "vec3f.h"

// Normalize vector
Vec3f normalize(Vec3f v);

Vec3f cross(Vec3f v1, Vec3f v2);

// Calculate scale for projection matrix
float scaleCoeff(float fovDeg);

// Generate camera matrix
Matrix4f getCameraMx(Vec3f from, Vec3f to);

// Generate projection matrix
Matrix4f getProjMx(float fovDeg, float clippingN, float clippingF);

// Print 2D matrix
void printMx(Matrix4f mx);

// Print 1D matrix
void printMx(Vec3f v);

// Multiply Matrix4f with Matrix4f
Matrix4f mxMult(Matrix4f mx1, Matrix4f mx2);

// Multiply Vec3f with Matrix4f
Vec3f vecMxMult(Vec3f v, Matrix4f mx);

#endif //HACKATHON_TEMP_FUNCTIONS_H
