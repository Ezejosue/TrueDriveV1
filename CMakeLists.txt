cmake_minimum_required(VERSION 3.25)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled main.cpp Conductor.cpp Conductor.h Taxi.cpp Taxi.h Empresa.cpp Empresa.h Cliente.cpp Cliente.h)
