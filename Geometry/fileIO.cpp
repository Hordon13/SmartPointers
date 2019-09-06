//
// Created by Horváth Donát on 2019. 09. 05..
//

#include "fileIO.h"
#include <fstream>
#include <sstream>
#include <iostream>

FileIO::FileIO(const std::string &inputPath, const std::string &outputPath)
{
    _inputPath = inputPath;
    _outputPath = outputPath;

    readOFF();
}

void FileIO::readOFF()
{
    std::ifstream inputFile(_inputPath);
    inputFile.exceptions(std::ifstream::badbit);

    try {
        int count = 0;
        std::string buffer;

        while (getline(inputFile, buffer)) {

            count++;
            if (count == 2) {

                std::istringstream ssMeta(buffer);
                ssMeta >> _nPoint >> _nPoly;

            }
            else if (count > 2 && count <= (_nPoint + 2)) {

                Vec3f temp;

                std::istringstream ssPoint(buffer);
                ssPoint >> temp.x >> temp.y >> temp.z;

                _pointData.push_back(temp);

            }
            else if (count > _nPoint + 2 && count <= (_nPoint + _nPoly + 2)) {
                Vec3f temp;
                int vertexCount;
                std::istringstream ssPoly(buffer);
                ssPoly >> vertexCount >> temp.x >> temp.y >> temp.z;
                _polyData.push_back(temp);
            }
        }

        inputFile.close();

    }
    catch (const std::ifstream::failure &e) {
        std::cerr << "There was an error while reading the file : " << e.what() << std::endl;
    }
}

void FileIO::writeSVG(std::vector<Polygon> poly)
{
    std::ofstream outputFile(_outputPath);
    outputFile << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"800\" height=\"600\" version=\"1.1\">\n";

    for (int i = 0; i < _nPoly; ++i) {
        std::string data = "<polygon points=\"";
        data += std::to_string(poly.at(i).getCoordinates().at(0).x) + "," +
            std::to_string(poly.at(i).getCoordinates().at(0).y) + " " +
            std::to_string(poly.at(i).getCoordinates().at(1).x) + "," +
            std::to_string(poly.at(i).getCoordinates().at(1).y) + " " +
            std::to_string(poly.at(i).getCoordinates().at(2).x) + "," +
            std::to_string(poly.at(i).getCoordinates().at(2).y);

        data += "\" style=\"fill:white; stroke:black;\"/>\n";
        outputFile << data;
    }

    outputFile << "</svg>";
    outputFile.close();
}

const std::vector<Vec3f> &FileIO::getPolyData() const
{
    return _polyData;
}

const std::vector<Vec3f> &FileIO::getPointData() const
{
    return _pointData;
}
