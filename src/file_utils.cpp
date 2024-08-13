#include "geometry.hpp"
#include <fstream>
#include <sstream>

namespace geometry {

void saveShapesToFile(const std::vector<Shape*>& shapes, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& shape : shapes) {
            shape->saveToFile(file);
        }
    }
}

void loadShapesFromFile(std::vector<Shape*>& shapes, const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string type;
        while (file >> type) {
            if (type == "Line") {
                auto* line = new Line(Point(), Point());
                line->loadFromFile(file);
                shapes.push_back(line);
            } else if (type == "Segment") {
                auto* segment = new Segment(Point(), Point());
                segment->loadFromFile(file);
                shapes.push_back(segment);
            } else if (type == "Circle") {
                auto* circle = new Circle(Point(), 0);
                circle->loadFromFile(file);
                shapes.push_back(circle);
            } else if (type == "Triangle") {
                auto* triangle = new Triangle(Point(), Point(), Point());
                triangle->loadFromFile(file);
                shapes.push_back(triangle);
            }
        }
    }
}

} // namespace geometry
