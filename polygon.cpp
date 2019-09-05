//
// Created by Bence on 2019.09.05..
//

#include "polygon.h"


Polygon::Polygon(const Vec3f &pointIndexes, const std::vector<Vec3f> &pointCoordinates)
{
    fillCoordinates(pointIndexes, pointCoordinates);
    findMinZ();
}

void Polygon::fillCoordinates(const Vec3f &pointIndexes, const std::vector<Vec3f> &pointCoordinates)
{
        _coordinates.push_back(pointCoordinates[pointIndexes.x]);
        _coordinates.push_back(pointCoordinates[pointIndexes.y]);
        _coordinates.push_back(pointCoordinates[pointIndexes.z]);
}

void Polygon::findMinZ()
{
    _minZ = _coordinates[0].z;
    for (int i = 0; i < _coordinates.size(); ++i) {
        if (_minZ > _coordinates[i].z) {
            _minZ = _coordinates[i].z;
        }
    }
}
