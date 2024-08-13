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

// Function to save shapes to a file
void saveShapesToFile(const std::vector<std::unique_ptr<Shape>>& shapes, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file for writing: " + filename);
    }

    try {
        for (const auto& shape : shapes) {
            if (shape) {
                shape->saveToFile(file);
            } else {
                throw std::runtime_error("Encountered null shape pointer.");
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception occurred while saving shapes: " << e.what() << std::endl;
        throw; // Re-throw to ensure the caller is aware of the failure
    }
}

// Function to load shapes from a file
void loadShapesFromFile(std::vector<std::unique_ptr<Shape>>& shapes, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file for reading: " + filename);
    }

    try {
        std::string type;
        while (file >> type) {
            std::unique_ptr<Shape> shape;

            if (type == "Line") {
                shape = std::make_unique<Line>(Point(), Point());
            } else if (type == "LineSegment") {
                shape = std::make_unique<LineSegment>(Point(), Point());
            } else if (type == "Circle") {
                shape = std::make_unique<Circle>(Point(), 0);
            } else if (type == "Triangle") {
                shape = std::make_unique<Triangle>(Point(), Point(), Point());
            } else {
                throw std::runtime_error("Unknown shape type encountered: " + type);
            }

            if (!shape->loadFromFile(file)) {
                throw std::runtime_error("Failed to load shape from file.");
            }

            shapes.push_back(std::move(shape));
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception occurred while loading shapes: " << e.what() << std::endl;
        throw; // Re-throw to ensure the caller is aware of the failure
    }
}

} // namespace geometry
