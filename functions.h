#ifndef HACKATHON_TEMP_FUNCTIONS_H
#define HACKATHON_TEMP_FUNCTIONS_H

#include "matrix4f.h"
#include "vec3f.h"
#include "polygon.h"

class Function {
public:
    // Normalize vector
    static Vec3f normalize(Vec3f v);

    // Vector cross product
    static Vec3f cross(Vec3f v1, Vec3f v2);

    // Calculate scale for projection matrix
    static float scaleCoeff(float fovDeg);

    // Generate camera matrix
    static Matrix4f getCameraMx(Vec3f from, Vec3f to);

    // Generate projection matrix
    static Matrix4f getProjMx(float fovDeg, float clippingN, float clippingF);

    // Multiply Vec3f with Matrix4f
    static Vec3f vecMxMult(Vec3f v, Matrix4f mx);

    // Determine triangle order
    static void sortPolygons(std::vector<Polygon> &polygons);
};

#endif //HACKATHON_TEMP_FUNCTIONS_H