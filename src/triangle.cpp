#include "geometry.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>

namespace geometry {

// Constructor for the Triangle class
Triangle::Triangle(const Point& p1, const Point& p2, const Point& p3) : p1(p1), p2(p2), p3(p3) {}

// Check if a point is inside the triangle using barycentric coordinates
bool Triangle::contains(const Point& p) const {
    // Calculate the barycentric coordinates
    double denominator = (p2.y - p3.y) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.y - p3.y);
    if (std::abs(denominator) < PRECISION_THRESHOLD) {
        throw std::runtime_error("Degenerate triangle: the points are collinear.");
    }

    double a = ((p2.y - p3.y) * (p.x - p3.x) + (p3.x - p2.x) * (p.y - p3.y)) / denominator;
    double b = ((p3.y - p1.y) * (p.x - p3.x) + (p1.x - p3.x) * (p.y - p3.y)) / denominator;
    double c = 1.0 - a - b;

    return a >= 0 && b >= 0 && c >= 0;
}

// Draw the triangle with formatted output
void Triangle::draw() const {
    std::cout << "Triangle with vertices (" << std::fixed << std::setprecision(2)
              << p1.x << ", " << p1.y << "), (" << p2.x << ", " << p2.y << "), (" 
              << p3.x << ", " << p3.y << ")" << std::endl;
}

// Draw the segments of the triangle with formatted output
void Triangle::drawSegments() const {
    std::cout << "Triangle segments:" << std::endl;
    std::cout << "Segment from (" << std::fixed << std::setprecision(2)
              << p1.x << ", " << p1.y << ") to (" << p2.x << ", " << p2.y << ")" << std::endl;
    std::cout << "Segment from (" << p2.x << ", " << p2.y << ") to (" << p3.x << ", " << p3.y << ")" << std::endl;
    std::cout << "Segment from (" << p3.x << ", " << p3.y << ") to (" << p1.x << ", " << p1.y << ")" << std::endl;
}

// Save the triangle's data to a file
void Triangle::saveToFile(std::ostream& out) const {
    if (!out) {
        throw std::runtime_error("Output stream is not open for writing.");
    }
    out << "Triangle " << std::fixed << std::setprecision(2)
        << p1.x << " " << p1.y << " " << p2.x << " " << p2.y << " " << p3.x << " " << p3.y << std::endl;
}

// Load the triangle's data from a file
void Triangle::loadFromFile(std::istream& in) {
    if (!(in >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y)) {
        throw std::runtime_error("Error reading Triangle data from file: Invalid format or end of file.");
    }
}

std::vector<Point> Triangle::getPoints() const {
    return { p1, p2, p3 };
}

} // namespace geometry
