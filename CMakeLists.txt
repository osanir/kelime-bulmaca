cmake_minimum_required(VERSION 3.13)
project(kelime_bulmaca)

set(CMAKE_CXX_STANDARD 17)

add_executable(kelime_bulmaca main.cpp src/Program.cpp include/Program.h include/WordMap.h src/Map.cpp include/Map.h)