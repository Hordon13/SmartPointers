cmake_minimum_required(VERSION 3.13)
project(hackathon)

set(CMAKE_CXX_STANDARD 17)

add_executable(hackathon main.cpp matrix4f.cpp matrix4f.h vec3f.cpp vec3f.h functions.h functions.cpp polygon.cpp polygon.h fileIO.cpp fileIO.h)

