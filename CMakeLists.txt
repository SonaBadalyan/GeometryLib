cmake_minimum_required(VERSION 3.10)
project(ODAGeometryLib)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(src)

# Add the library target with the source files
add_library(ODAGeometryLib STATIC
    src/Line.cpp
    src/Point.cpp
    src/Triangle.cpp
    src/Circle.cpp
    src/FileHandler.cpp
    src/LineSegment.cpp
    # Add other source files as needed
)

# Add the executable
add_executable(Driver console/main.cpp)

target_link_libraries(Driver ODAGeometryLib)
# Optionally, link libraries here
# target_link_libraries(MyExecutable PRIVATE some_library)