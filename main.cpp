#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>

int main(int argc, char *argv[])
{
    std::filesystem::path inputPath(argv[1]);
    std::ifstream inputFile(inputPath);

    int count = 0, nPoint = 0, nPoly = 0;
    std::string line;
    while (getline(inputFile, line)) {
        count++;
        if (count == 2) {
            std::istringstream ss(line);
            ss >> nPoint >> nPoly;
        } else if (count > 2 && count <= (nPoint + 2)) {
            std::cout << "Point: " << line << std::endl;
        } else if (count > 2 && count > nPoint && count <= (nPoint + nPoly + 2)) {
            std::cout << "Poly: " << line << std::endl;
        }
    }

    inputFile.close();

    return 0;
}