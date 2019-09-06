#include <iostream>
#include <cmath>
#include "functions.h"
#include "fileIO.h"
#include "polygon.h"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/opencv.hpp"

const int screenWidth = 800;
const int screenHeight = 800;

int x_axis = 0;


cv::Mat calculatAndPaint(FileIO &handler, float x, float z);

void TrackbarCallback(int pos, void *userData)
{
    FileIO *handler = (FileIO *)userData;
    cv::imshow("Window", calculatAndPaint(*handler, 3 * cos(x_axis * 3.14 / 180), 3 * sin(x_axis * 3.14 / 180)));
}


cv::Mat calculatAndPaint(FileIO &handler, float x, float z)
{
    cv::Mat canvas(cv::Size(screenWidth, screenHeight), CV_8UC1);
    canvas = cv::Scalar::all(255);

    bool saved = false;

    std::vector<Polygon> polygons;
    std::vector<Vec3f> points = handler.getPointData();

    Vec3f from(x, 2, z);
    Vec3f to(0, 0, 0);
    Matrix4f cameraMx = getCameraMx(from, to);
    Matrix4f projectionMx = getProjMx(60.0f, 0.1f, 100);

    // Projecting
    std::vector<Vec3f> projectedPoints;
    for (int j = 0; j < points.size(); ++j) {
        Vec3f temp = vecMxMult(points[j], cameraMx);
        projectedPoints.push_back(vecMxMult(temp, projectionMx));
    }

    // Scaling
    std::vector<Vec3f> scaledPoints;
    for (int k = 0; k < projectedPoints.size(); ++k) {
        scaledPoints.push_back(Vec3f(projectedPoints[k].x * screenWidth / 4.0f + screenWidth / 2.0f,
            projectedPoints[k].y * screenHeight / 4.0f + screenHeight / 2.0f,
            projectedPoints[k].z));
    }

    // Triangle creation
    for (int i = 0; i < handler.getPolyData().size(); i++) {
        Polygon polygon(handler.getPolyData()[i], scaledPoints);
        polygons.push_back(polygon);
    }

    // Sort
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

    for (int i = 0; i < polygons.size(); i++) {

        cv::Point pt1(polygons[i].getCoordinates()[0].x, polygons[i].getCoordinates()[0].y);
        cv::Point pt2(polygons[i].getCoordinates()[1].x, polygons[i].getCoordinates()[1].y);
        cv::Point pt3(polygons[i].getCoordinates()[2].x, polygons[i].getCoordinates()[2].y);
        cv::line(canvas, pt1, pt2, (255, 0, 0), 3);
        cv::line(canvas, pt2, pt3, (255, 0, 0), 3);
        cv::line(canvas, pt3, pt1, (255, 0, 0), 3);
        cv::Point points[4];
        points[0] = pt1;
        points[1] = pt2;
        points[2] = pt3;
        points[3] = pt1;
        cv::fillConvexPoly(canvas, points, 4, cv::Scalar::all(128));
    }
    if (!saved) {
        handler.writeSVG(polygons);
        saved = true;
    }
    
    //cv::imshow("Window", canvas);
    

    return canvas;
}

int main(int argc, char *argv[])
{

    FileIO handler(argv[1], argv[2]);
    float x = 3.0;
    float z = 1.5;

    

    cv::Mat canvas(cv::Size(1200, 1200), CV_8UC1);
    canvas = calculatAndPaint(handler, x, z);
    
    cv::imshow("Window", canvas);
    cv::namedWindow("Window");
    cv::createTrackbar("X" , "Window", &x_axis, 360, TrackbarCallback, &handler);
    cv::waitKey(0);

    return 0;
}