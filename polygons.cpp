//
// Created by Bence on 2019.09.05..
//

#include "polygons.h"


Polygons::Polygons(const std::vector<int> &pointIndexes, const std::vector<Vec3f> &pointCoordinates)
{
    fillCoordinates(pointIndexes, pointCoordinates);
    findMinZ();
}

void Polygons::fillCoordinates(const std::vector<int> &pointIndexes, const std::vector<Vec3f> &pointCoordinates)
{
    for (int i = 0; i < pointIndexes.size(); i++) {
        _coordinates.push_back(pointCoordinates[pointIndexes[i]]);
    }
}

void Polygons::findMinZ()
{
    _minZ = _coordinates[0].z;
    for (int i = 0; i < _coordinates.size(); ++i) {
        if (_minZ > _coordinates[i].z) {
            _minZ = _coordinates[i].z;
        }
    }
}
