#include "geometry.hpp"
#include "file_utils.cpp"
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace geometry;

void drawShape(const Shape& shape) {
    shape.draw();
}

void drawShapeSegments(const Shape& shape) {
    shape.drawSegments();
}

std::vector<Point> findCollinearPoints(const std::vector<Point>& points) {
    std::unordered_map<std::string, std::vector<Point>> lines;

    auto hashPoint = [](const Point& p) {
        return std::to_string(p.x) + "," + std::to_string(p.y);
    };

    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i + 1; j < points.size(); ++j) {
            const Point& p1 = points[i];
            const Point& p2 = points[j];
            std::string key = std::to_string(p1.x) + "," + std::to_string(p1.y) + " to " +
                              std::to_string(p2.x) + "," + std::to_string(p2.y);
            lines[key].push_back(p1);
            lines[key].push_back(p2);
        }
    }

    std::vector<Point> collinearPoints;
    for (const auto& [line, pts] : lines) {
        if (pts.size() > 2) {
            std::cout << "Line: " << line << std::endl;
            for (const auto& pt : pts) {
                std::cout << "  " << hashPoint(pt) << std::endl;
            }
        }
    }

    return collinearPoints;
}

int main() {
    std::vector<Shape*> shapes;
    std::vector<Point> points;

    // Example shapes creation
    shapes.push_back(new Line(Point(1, 1), Point(5, 5)));
    shapes.push_back(new Segment(Point(0, 0), Point(3, 4)));
    shapes.push_back(new Circle(Point(0, 0), 5));
    shapes.push_back(new Triangle(Point(0, 0), Point(5, 0), Point(0, 5)));

    // Draw shapes
    for (const auto& shape : shapes) {
        drawShape(*shape);
        drawShapeSegments(*shape);
    }

    // Save and load shapes
    saveShapesToFile(shapes, "shapes.txt");

    std::vector<Shape*> loadedShapes;
    loadShapesFromFile(loadedShapes, "shapes.txt");

    // Find collinear points
    std::vector<Point> pointsToCheck = {Point(0, 0), Point(1, 1), Point(2, 2), Point(3, 4)};
    findCollinearPoints(pointsToCheck);

    // Clean up
    for (auto shape : shapes) {
        delete shape;
    }
    for (auto shape : loadedShapes) {
        delete shape;
    }

    return 0;
}
