#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

// Normalize vector
template<typename T>
std::vector<T> normalize(std::vector<T> v){
    std::vector<T> result(v);
    T sum = 0;
    for (int i = 0; i < v.size(); ++i) {
        sum += v[i] * v[i];
    }
    double length = sqrt(sum);
    for (int j = 0; j < result.size(); ++j) {
        result[j] = result[j] / length;
    }
    return result;
}

// Calculate scale for projection matrix
template<typename T>
T scaleCoeff(T fovDeg){
    return 1/(tan(fovDeg * 0.5 * M_PI / 180));
}

// Generate projection matrix
template<typename T>
std::vector<std::vector<T>> projMx(T fovDeg, T clippingN, T clippingF){
    std::vector<std::vector<T>> mx;
    mx.resize(4, std::vector<T>(4, 0));

    T remapZ1 = -clippingF / (clippingF - clippingN);
    T remapZ2 = -clippingF * clippingN / (clippingF - clippingN);

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

// Print 1D matrix
template<typename T>
void printMx(std::vector<T> mx)
{
    for (int i = 0; i < mx.size(); ++i) {
        std::cout << mx[i] << "\t";
    }
    std::cout << '\n';
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

    std::vector<float> vv = {2,2,2};
    printMx(normalize(vv));


    std::vector<std::vector<float>> projectionMx = projMx(60.0f, 0.1f, 50.f);
    std::vector<std::vector<float>> projectedPoints;

    for (int j = 0; j < points.size(); ++j) {
        projectedPoints.push_back(mxMult(points[j], projectionMx));
    }

    //printMx(projectedPoints);

    return 0;
}