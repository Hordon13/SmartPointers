//
// Created by Horváth Donát on 2019. 09. 05..
//

#ifndef HACKATHON_TEMP_FILEIO_H
#define HACKATHON_TEMP_FILEIO_H

#include "vec3f.h"
#include <string>
#include <vector>
#include <map>

class FileIO {
public:
    FileIO(const std::string &inputPath, const std::string &outputPath);

    void writeSVG();

    const std::vector<Vec3f> &getPolyData() const;

    const std::vector<Vec3f> &getPointData() const;

private:
    void readOFF();

    std::string _inputPath;
    std::string _outputPath;
    int _nPoint = 0;
    int _nPoly = 0;

    std::vector<Vec3f> _polyData;
    std::vector<Vec3f> _pointData;
};

#endif //HACKATHON_TEMP_FILEIO_H
