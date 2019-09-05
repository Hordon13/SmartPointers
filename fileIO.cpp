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
    inputFile.exceptions(std::ifstream::eofbit | std::ifstream::failbit | std::ifstream::badbit);

    try {
        int count = 0;
        std::string buffer;

        while (getline(inputFile, buffer)) {

            count++;
            if (count == 2) {

                std::istringstream ssMeta(buffer);
                ssMeta >> _nPoint >> _nPoly;

            } else if (count > 2 && count <= (_nPoint + 2)) {

                Vec3f temp;

                std::istringstream ssPoint(buffer);
                ssPoint >> temp.x >> temp.y >> temp.z;

                _pointData.push_back(temp);

            } else if (count > 2 && count > _nPoint + 2 && count <= (_nPoint + _nPoly + 3)) {
                Vec3f temp;
                int edges;
                std::istringstream ssPoly(buffer);
                ssPoly >> edges >> temp.x >> temp.y >> temp.z;
                _polyData.push_back(temp);
            }
        }

        inputFile.close();

    } catch (std::exception const &e) {
        std::cerr << "There was an error while reading the file : " << e.what() << std::endl;
    }
}

void FileIO::writeSVG()
{

}

const std::vector<Vec3f> &FileIO::getPolyData() const
{
    return _polyData;
}

const std::vector<Vec3f> &FileIO::getPointData() const
{
    return _pointData;
}
