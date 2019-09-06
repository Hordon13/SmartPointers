#ifndef HACKATHON_POLYGONS_H
#define HACKATHON_POLYGONS_H

#include <vector>
#include "vec3f.h"

class Polygon {
public:
    Polygon(const Vec3f &pointIndexes, const std::vector<Vec3f> &pointCoordinates);

    void fillCoordinates(const Vec3f &pointIndexes, const std::vector<Vec3f> &pointCoordinates);

    void findMinZ();

    const std::vector<Vec3f> &getCoordinates() const;

    const std::vector<float> &getMinZ() const;

private:
    std::vector<Vec3f> _coordinates;
    std::vector<float> _minZ;
};

#endif //HACKATHON_POLYGONS_H