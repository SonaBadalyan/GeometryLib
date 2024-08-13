# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(ODAGeometry)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the library
add_library(geometry STATIC src/geometry.cpp)

# Specify the include directories
target_include_directories(geometry PUBLIC include)

# Add the test executable
add_executable(geometry_test tests/main.cpp)
target_link_libraries(geometry_test geometry)
