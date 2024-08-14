#include "Line.hpp"

#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <stdexcept>

namespace geometry {

Line::Line(const Point& p1, const Point& p2) : p1(p1), p2(p2) {}


bool Line::contains(const Point& p) const {
    double crossProduct = (p2.y - p1.y) * (p.x - p1.x) - (p2.x - p1.x) * (p.y - p1.y);
    return std::abs(crossProduct) < EPSILON
}

void Line::draw() const {
    std::cout << "Line from (" << std::fixed << std::setprecision(2)
              << p1.x << ", " << p1.y << ") to (" << p2.x << ", " << p2.y << ")" << std::endl;
}

void Line::drawSegments() const {
    std::cout << "Line segment from (" << p1.x << ", " << p1.y 
              << ") to (" << p2.x << ", " << p2.y << ")" << std::endl;
}

void Line::saveToFile(std::ostream& out) const {
    if (out) {
        out << "Line " << p1.x << " " << p1.y << " " << p2.x << " " << p2.y << std::endl;
    } else {
        throw std::runtime_error("Output stream is not open for writing.");
    }
}

void Line::loadFromFile(std::istream& in) {
    if (!(in >> p1.x >> p1.y >> p2.x >> p2.y)) {
        throw std::runtime_error("Error reading Line data from file: Invalid format or end of file.");
    }

    // Validate that the loaded coordinates are not NaN or infinite
    if (std::isnan(p1.x) || std::isnan(p1.y) || std::isnan(p2.x) || std::isnan(p2.y) ||
        std::isinf(p1.x) || std::isinf(p1.y) || std::isinf(p2.x) || std::isinf(p2.y)) {
        throw std::runtime_error("Error reading Line data from file: Invalid coordinate values.");
    }
}

std::vector<Point> Line::getPoints() const {
    return { p1, p2 };
}

double Line::distanceToPoint(const double A, const double B, const double C, const Point& p) const {
    return std::abs(A * p.x + B * p.y + C) / std::sqrt(A * A + B * B);
}

} // namespace geometry
