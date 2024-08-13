#include "geometry.hpp"
#include "file_utils.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <exception>
#include <cmath>
#include <iomanip>
#include <algorithm>

constexpr double PRECISION_THRESHOLD = 1e-9;

// Helper function to check if a point is on a line segment
bool isPointOnSegment(const Point& p, const Point& segStart, const Point& segEnd) {
    // Check if the point is within the bounding box of the segment
    double minX = std::min(segStart.x, segEnd.x);
    double maxX = std::max(segStart.x, segEnd.x);
    double minY = std::min(segStart.y, segEnd.y);
    double maxY = std::max(segStart.y, segEnd.y);

    if (p.x < minX - PRECISION_THRESHOLD || p.x > maxX + PRECISION_THRESHOLD ||
        p.y < minY - PRECISION_THRESHOLD || p.y > maxY + PRECISION_THRESHOLD) {
        return false;
    }

    // Check collinearity using the cross product
    double crossProduct = (p.y - segStart.y) * (segEnd.x - segStart.x) - (p.x - segStart.x) * (segEnd.y - segStart.y);
    if (std::abs(crossProduct) > PRECISION_THRESHOLD) {
        return false;
    }

    // Check if the point lies exactly on the segment using dot product
    double dotProduct = (p.x - segStart.x) * (segEnd.x - segStart.x) + (p.y - segStart.y) * (segEnd.y - segStart.y);
    if (dotProduct < 0) {
        return false; // Point is outside the segment on one end
    }

    double squaredLengthBA = (segEnd.x - segStart.x) * (segEnd.x - segStart.x) +
                              (segEnd.y - segStart.y) * (segEnd.y - segStart.y);
    if (dotProduct > squaredLengthBA) {
        return false; // Point is outside the segment on the other end
    }

    return true;
}

// Function to check if a point is within a geometric object
bool isPointWithin(const Point& point, const Shape& shape) {
    try {
        if (const Line* line = dynamic_cast<const Line*>(&shape)) {
            return isPointOnSegment(point, line->start, line->end);
        }
        if (const Segment* segment = dynamic_cast<const Segment*>(&shape)) {
            return isPointOnSegment(point, segment->start, segment->end);
        }
        if (const Circle* circle = dynamic_cast<const Circle*>(&shape)) {
            double dx = point.x - circle->center.x;
            double dy = point.y - circle->center.y;
            double distance = std::sqrt(dx * dx + dy * dy);
            return distance <= circle->radius;
        }
        if (const Triangle* triangle = dynamic_cast<const Triangle*>(&shape)) {
            // Calculate area of the triangle
            double areaOrig = std::abs((triangle->p1.x * (triangle->p2.y - triangle->p3.y) +
                                        triangle->p2.x * (triangle->p3.y - triangle->p1.y) +
                                        triangle->p3.x * (triangle->p1.y - triangle->p2.y)) / 2.0);
            // Calculate areas of triangles formed with the point
            double area1 = std::abs((point.x * (triangle->p2.y - triangle->p3.y) +
                                     triangle->p2.x * (triangle->p3.y - point.y) +
                                     triangle->p3.x * (point.y - triangle->p2.y)) / 2.0);
            double area2 = std::abs((triangle->p1.x * (point.y - triangle->p3.y) +
                                     point.x * (triangle->p3.y - triangle->p1.y) +
                                     triangle->p3.x * (triangle->p1.y - point.y)) / 2.0);
            double area3 = std::abs((triangle->p1.x * (triangle->p2.y - point.y) +
                                     triangle->p2.x * (point.y - triangle->p1.y) +
                                     point.x * (triangle->p1.y - triangle->p2.y)) / 2.0);
            // Point is inside or on the triangle if the sum of areas equals the original area
            return std::abs(areaOrig - (area1 + area2 + area3)) < PRECISION_THRESHOLD;
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception occurred in isPointWithin: " << e.what() << std::endl;
    }
    return false;
}

// Function to draw the object by printing coordinates of its segments
void drawShape(const Shape& shape) {
    try {
        std::vector<std::pair<Point, Point>> segments;

        if (const Line* line = dynamic_cast<const Line*>(&shape)) {
            segments.emplace_back(line->start, line->end);
        } else if (const Segment* segment = dynamic_cast<const Segment*>(&shape)) {
            segments.emplace_back(segment->start, segment->end);
        } else if (const Circle* circle = dynamic_cast<const Circle*>(&shape)) {
            // Approximate the circle with a number of segments
            const int num_segments = 36; // Can be made configurable
            for (int i = 0; i < num_segments; ++i) {
                double theta1 = 2 * M_PI * i / num_segments;
                double theta2 = 2 * M_PI * (i + 1) / num_segments;
                Point p1(circle->center.x + circle->radius * std::cos(theta1),
                         circle->center.y + circle->radius * std::sin(theta1));
                Point p2(circle->center.x + circle->radius * std::cos(theta2),
                         circle->center.y + circle->radius * std::sin(theta2));
                segments.emplace_back(p1, p2);
            }
        } else if (const Triangle* triangle = dynamic_cast<const Triangle*>(&shape)) {
            segments.emplace_back(triangle->p1, triangle->p2);
            segments.emplace_back(triangle->p2, triangle->p3);
            segments.emplace_back(triangle->p3, triangle->p1);
        }

        // Print each segment
        for (const auto& segment : segments) {
            std::cout << "Segment from (" << segment.first.x << ", " << segment.first.y
                      << ") to (" << segment.second.x << ", " << segment.second.y << ")\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception occurred in drawShape: " << e.what() << std::endl;
    }
}

int main() {
    try {
        std::vector<std::unique_ptr<Shape>> shapes;
        shapes.push_back(std::make_unique<Line>(Point(1, 1), Point(5, 5)));
        shapes.push_back(std::make_unique<Segment>(Point(0, 0), Point(3, 4)));
        shapes.push_back(std::make_unique<Circle>(Point(0, 0), 5));
        shapes.push_back(std::make_unique<Triangle>(Point(0, 0), Point(5, 0), Point(0, 5)));

        // Draw each shape
        for (const auto& shape : shapes) {
            drawShape(*shape);
        }

        // Save shapes to file
        if (!saveShapesToFile(shapes, "shapes.txt")) {
            throw std::runtime_error("Failed to save shapes to file!");
        }

        // Load shapes from file
        std::vector<std::unique_ptr<Shape>> loadedShapes;
        if (!loadShapesFromFile(loadedShapes, "shapes.txt")) {
            throw std::runtime_error("Failed to load shapes from file!");
        }

        // Check if specific points are within loaded shapes
        std::vector<Point> pointsToCheck = {Point(0, 0), Point(1, 1), Point(2, 2), Point(3, 4)};
        for (const auto& point : pointsToCheck) {
            std::cout << "Checking point (" << point.x << ", " << point.y << "):\n";
            for (const auto& shape : loadedShapes) {
                if (isPointWithin(point, *shape)) {
                    std::cout << "  Point is within shape.\n";
                } else {
                    std::cout << "  Point is not within shape.\n";
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
