#include "functions.h"
#include "fileIO.h"
#include "polygon.h"


int main(int argc, char *argv[])
{
    const int screenWidth = 800;
    const int screenHeight = 600;
    FileIO handler(argv[1], argv[2]);

    Vec3f from(3.0f, 2.0f, 1.5f);
    Vec3f to(0, 0, 0);
    Matrix4f cameraMx = getCameraMx(from, to);
    Matrix4f projectionMx = getProjMx(60.0f, 0.1f, 100);

    std::vector<Polygon> polygons;
    std::vector<Vec3f> points = handler.getPointData();


    // Projecting
    std::vector<Vec3f> projectedPoints;
    for (int j = 0; j < points.size(); ++j) {
        Vec3f temp = vecMxMult(points[j], cameraMx);
        projectedPoints.push_back(vecMxMult(temp, projectionMx));
    }

    // Scaling
    std::vector<Vec3f> scaledPoints;
    for (int k = 0; k < projectedPoints.size(); ++k) {
        scaledPoints.push_back(Vec3f(projectedPoints[k].x * screenWidth / 2.0f + screenHeight / 2.0f,
            projectedPoints[k].y * screenHeight / 2.0f + screenHeight / 2.0f,
            projectedPoints[k].z));
    }

    // Triangle creation
    for (int i = 0; i < handler.getPolyData().size(); i++) {
        Polygon polygone(handler.getPolyData()[i], scaledPoints);
        polygons.push_back(polygone);
    }

    // sort
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

    handler.writeSVG(polygons);

    return 0;
}