#ifndef HACKATHON_FILEIO_H
#define HACKATHON_FILEIO_H

#include "vec3f.h"
#include <string>
#include <vector>
#include <map>
#include "polygon.h"

class FileIO {
public:
    FileIO(const std::string &inputPath, const std::string &outputPath);

    void writeSVG(std::vector<Polygon> poly);

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

#endif //HACKATHON_FILEIO_H