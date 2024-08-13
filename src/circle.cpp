#include "geometry.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <stdexcept>

namespace geometry {

// Constructor for the Circle class
Circle::Circle(const Point& center, double radius) : center(center), radius(radius) {
    // Ensure that radius is non-negative
    if (radius < 0) {
        throw std::invalid_argument("Radius cannot be negative.");
    }
}

// Check if a point is within the circle
bool Circle::contains(const Point& p) const {
    double distSquared = (p.x - center.x) * (p.x - center.x) + (p.y - center.y) * (p.y - center.y);
    return distSquared <= radius * radius;
}

// Draw the circle with formatted output
void Circle::draw() const {
    std::cout << "Circle with center (" << std::fixed << std::setprecision(2)
              << center.x << ", " << center.y << ") and radius " << radius << std::endl;
}

// Draw the circle segments with formatted output
void Circle::drawSegments() const {
    std::cout << "Circle with center (" << center.x << ", " << center.y
              << ") and radius " << radius << std::endl;
}

// Save the circle's data to a file
void Circle::saveToFile(std::ostream& out) const {
    if (out) {
        out << "Circle " << std::fixed << std::setprecision(2)
            << center.x << " " << center.y << " " << radius << std::endl;
    } else {
        throw std::runtime_error("Output stream is not open for writing.");
    }
}

// Load the circle's data from a file
void Circle::loadFromFile(std::istream& in) {
    if (!(in >> center.x >> center.y >> radius)) {
        throw std::runtime_error("Error reading Circle data from file: Invalid format or end of file.");
    }

    // Validate that the radius is non-negative
    if (radius < 0) {
        throw std::runtime_error("Error reading Circle data from file: Negative radius value.");
    }
}

} // namespace geometry
