#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

class Vec3f {
public:
    Vec3f()
    { x = y = z = 0; }

    Vec3f(float xc, float yc, float zc)
    {
        x = xc;
        y = yc;
        z = zc;
    }

    float length()
    {
        return sqrt(x * x + y * y + z * z);
    }

    Vec3f operator-(const Vec3f &v)
    {
        return Vec3f(x - v.x, y - v.y, z - v.z);
    }

    Vec3f operator+(const Vec3f &v)
    {
        return Vec3f(x + v.x, y + v.y, z + v.z);
    }

    float x;
    float y;
    float z;
};

class Matrix4f {
public:

    Matrix4f()
    {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                coeff[i][j] = 0;
            }
        }
    }

    Matrix4f(float a, float b, float c, float d, float e, float f, float g, float h,
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

    const float *operator[](uint8_t i) const
    { return coeff[i]; }

    float *operator[](uint8_t i)
    { return coeff[i]; }

    float coeff[4][4];
};

// Normalize vector
Vec3f normalize(Vec3f v)
{
    float invLen = 1 / v.length();
    return Vec3f(v.x * invLen, v.y * invLen, v.z * invLen);
}

// Calculate scale for projection matrix
float scaleCoeff(float fovDeg)
{
    return 1 / (tan(fovDeg * 0.5 * M_PI / 180));
}

// Generate camera matrix
template<typename T>
std::vector<std::vector<T>> cameraMx(std::vector<T> from, std::vector<T> to)
{

}

// Generate projection matrix
Matrix4f projMx(float fovDeg, float clippingN, float clippingF)
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
template<typename T>
void printMx(std::vector<std::vector<T>> mx)
{
    for (int i = 0; i < mx.size(); ++i) {
        for (int j = 0; j < mx[0].size(); ++j) {
            std::cout << mx[i][j] << "\t";
        }
        std::cout << '\n';
    }
}


void printMx(Vec3f v)
{
    std::cout << v.x << "\t" << v.y << "\t" << v.z << "\t" << '\n';
}

// Multiply vector with matrix
template<typename T>
std::vector<T> mxMult(std::vector<T> mx1, std::vector<std::vector<T>> mx2)
{
    std::vector<T> result;
    result.resize(mx1.size());
    for (int i = 0; i < mx1.size(); ++i) {
        for (int j = 0; j < mx2.size(); ++j) {
            result[i] += mx1[i] * mx2[j][i];
        }
    }

    return result;
}

//template<typename T>
//void writeSVF(std::vector<std::vector<T>>)


int main()
{
    // Cube
    std::vector<std::vector<float>> points = {{0, 0, 0},
                                              {1, 0, 0},
                                              {1, 1, 0},
                                              {0, 1, 0},
                                              {0, 0, 1},
                                              {1, 0, 1},
                                              {1, 1, 1},
                                              {0, 1, 1}};

    // Make homogeneous coordinates
    for (int i = 0; i < points.size(); ++i) {
        points[i].push_back(1);
    }

    Vec3f from(-3.0, -2.0, -1.5);
    Vec3f to(0, 0, 0);
    printMx(normalize(from - to));


    std::vector<std::vector<float>> projectionMx = projMx(60.0f, 0.1f, 50.f);
    std::vector<std::vector<float>> projectedPoints;

    for (int j = 0; j < points.size(); ++j) {
        projectedPoints.push_back(mxMult(points[j], projectionMx));
    }

    //printMx(projectedPoints);

    return 0;
}