#pragma once

#include "Shape.hpp"
#include "Point.hpp"
#include "Line.hpp"
#include "LineSegment.hpp"
#include "Circle.hpp"
#include "Triangle.hpp"

#include <fstream>
#include <sstream>
#include <memory>
#include <stdexcept>
#include <iostream>

namespace geometry {

class FileHandler {
public:
    // Method to save shapes to a file
    void saveShapesToFile(const std::vector<std::unique_ptr<Shape>>& shapes, const std::string& filename) const;

    // Method to load shapes from a file
    void loadShapesFromFile(std::vector<std::unique_ptr<Shape>>& shapes, const std::string& filename) const;
};

} // namespace geometry
