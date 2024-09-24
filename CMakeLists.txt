cmake_minimum_required(VERSION 3.5.0)
project(LinuxSocketServer VERSION 0.1.0 LANGUAGES C CXX)

file(GLOB SOURCES "src/*.cpp" "src/common/*.cpp")
file(GLOB HEADERS "src/*.h" "src/common/*.h")

add_executable(LinuxSocketServer ${SOURCES} ${HEADERS})
