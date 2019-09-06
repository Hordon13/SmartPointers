#include "polygon.h"
#include <algorithm>

Polygon::Polygon(const Vec3f &pointIndexes, const std::vector<Vec3f> &pointCoordinates) {
    fillCoordinates(pointIndexes, pointCoordinates);
    findMinZ();
}

void Polygon::fillCoordinates(const Vec3f &pointIndexes, const std::vector<Vec3f> &pointCoordinates) {
    _coordinates.push_back(pointCoordinates[pointIndexes.x]);
    _coordinates.push_back(pointCoordinates[pointIndexes.y]);
    _coordinates.push_back(pointCoordinates[pointIndexes.z]);
}

void Polygon::findMinZ() {
    _minZ.push_back(_coordinates[0].z);
    _minZ.push_back(_coordinates[1].z);
    _minZ.push_back(_coordinates[2].z);
    std::sort(_minZ.begin(), _minZ.end());
}

const std::vector<Vec3f> &Polygon::getCoordinates() const {
    return _coordinates;
}

const std::vector<float> &Polygon::getMinZ() const {
    return _minZ;
}

