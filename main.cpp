#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include "matrix4f.h"
#include "vec3f.h"
#include "functions.h"

int main(int argc, char *argv[])
{
    std::filesystem::path inputPath(argv[1]);
    std::ifstream inputFile(inputPath);

    int count = 0, nPoint = 0, nPoly = 0;
    std::string line;
    while (getline(inputFile, line)) {
        count++;
        if (count == 2) {
            std::istringstream ss(line);
            ss >> nPoint >> nPoly;
        } else if (count > 2 && count <= (nPoint + 2)) {
            std::cout << "Point: " << line << std::endl;
        } else if (count > 2 && count > nPoint && count <= (nPoint + nPoly + 2)) {
            std::cout << "Poly: " << line << std::endl;
        }
    }

    inputFile.close();
	
	// Test matrix stuff
	Vec3f cameraFrom(3.0,2.0,1.5);
    Vec3f cameraTo(0,0,0);

    Matrix4f projectionMx = getProjMx(60, 0.1, 100);
    Matrix4f cameraMx = getCameraMx(cameraFrom, cameraTo);

    printMx(projectionMx);
    std::cout << '\n';
    printMx(cameraMx);
	
	

    return 0;
}