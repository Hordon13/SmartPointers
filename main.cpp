
#include "fileIO.h"
#include "polygon.h"

int main(int argc, char *argv[])
{
    FileIO handler(argv[1], argv[2]);

    std::vector<Polygon> polygones;
    for (int i = 0; i < handler.getPolyData().size(); i++) {
        Polygon polygone(handler.getPolyData()[i], handler.getPointData());
        polygones.push_back(polygone);
    }

    return 0;
}