#include "geometry.hpp"
#include "file_utils.hpp"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <algorithm>

using namespace geometry;

// Precision threshold for floating-point comparisons
constexpr double PRECISION_THRESHOLD = 1e-10;

// Function to check if a point is on a line segment
bool isPointOnSegment(const Point& p, const Point& p1, const Point& p2) {
    double cross = (p.y - p1.y) * (p2.x - p1.x) - (p.x - p1.x) * (p2.y - p1.y);
    if (std::abs(cross) > PRECISION_THRESHOLD) return false; // Not collinear

    double dot = (p.x - p1.x) * (p2.x - p1.x) + (p.y - p1.y) * (p2.y - p1.y);
    if (dot < 0) return false; // Behind p1

    double len_sq = (p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y);
    if (dot > len_sq) return false; // Beyond p2

    return true;
}

// Function to generate a unique key for a line defined by two points
std::string generateLineKey(const Point& p1, const Point& p2) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2)
        << std::min(p1.x, p2.x) << "," << std::min(p1.y, p2.y) << " to "
        << std::max(p1.x, p2.x) << "," << std::max(p1.y, p2.y);
    return oss.str();
}

// Function to remove duplicate points from a vector
std::vector<Point> removeDuplicates(std::vector<Point> points) {
    std::sort(points.begin(), points.end(),
              [](const Point& a, const Point& b) {
                  return std::tie(a.x, a.y) < std::tie(b.x, b.y);
              });
    auto last = std::unique(points.begin(), points.end(),
                            [](const Point& a, const Point& b) {
                                return a.x == b.x && a.y == b.y;
                            });
    points.erase(last, points.end());
    return points;
}

// Function to find and display collinear points
void findAndDisplayCollinearPoints(const std::vector<Point>& points) {
    std::unordered_map<std::string, std::vector<Point>> lines;

    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i + 1; j < points.size(); ++j) {
            const Point& p1 = points[i];
            const Point& p2 = points[j];
            std::string key = generateLineKey(p1, p2);

            // Collect all points collinear with p1 and p2
            std::vector<Point> collinearPoints;
            for (const auto& p : points) {
                if (isPointOnSegment(p, p1, p2)) {
                    collinearPoints.push_back(p);
                }
            }

            // Add line and its collinear points if there are more than 2 collinear points
            if (collinearPoints.size() > 2) {
                collinearPoints = removeDuplicates(collinearPoints);
                if (!collinearPoints.empty()) {
                    lines[key] = collinearPoints;
                }
            }
        }
    }

    // Display the collected collinear points
    for (const auto& [line, pts] : lines) {
        std::cout << "Line: " << line << std::endl;
        for (const auto& pt : pts) {
            std::cout << "  Point: (" << pt.x << ", " << pt.y << ")" << std::endl;
        }
    }
}

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;

    // Example shapes creation
    shapes.push_back(std::make_unique<Line>(Point(1, 1), Point(5, 5)));
    shapes.push_back(std::make_unique<Segment>(Point(0, 0), Point(3, 4)));
    shapes.push_back(std::make_unique<Circle>(Point(0, 0), 5));
    shapes.push_back(std::make_unique<Triangle>(Point(0, 0), Point(5, 0), Point(0, 5)));

    // Draw shapes
    for (const auto& shape : shapes) {
        draw(*shape);
        drawSegments(*shape);
    }

    // Save shapes to file
    if (!saveShapesToFile(shapes, "shapes.txt")) {
        std::cerr << "Failed to save shapes to file!" << std::endl;
        return 1;
    }

    // Load shapes from file
    std::vector<std::unique_ptr<Shape>> loadedShapes;
    if (!loadShapesFromFile(loadedShapes, "shapes.txt")) {
        std::cerr << "Failed to load shapes from file!" << std::endl;
        return 1;
    }

    // Find and display collinear points
    std::vector<Point> pointsToCheck = {Point(0, 0), Point(1, 1), Point(2, 2), Point(3, 4)};
    findAndDisplayCollinearPoints(pointsToCheck);

    return 0;
}
