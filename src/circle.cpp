#include "Circle.hpp"

#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <stdexcept>

namespace geometry {

Circle::Circle(const Point& center, double radius) : center(center), radius(radius) {
    // Ensure that radius is non-negative
    if (radius < 0) {
        throw std::invalid_argument("Radius cannot be negative.");
    }
}

bool Circle::contains(const Point& p) const {
    double distSquared = (p.x - center.x) * (p.x - center.x) + (p.y - center.y) * (p.y - center.y);
    return distSquared <= radius * radius;
}

void Circle::draw() const {
    std::cout << "Circle with center (" << std::fixed << std::setprecision(2)
              << center.x << ", " << center.y << ") and radius " << radius << std::endl;
}

void Circle::drawSegments() const {
    std::cout << "Circle with center (" << center.x << ", " << center.y
              << ") and radius " << radius << std::endl;
}

void Circle::saveToFile(std::ostream& out) const {
    if (out) {
        out << "Circle " << std::fixed << std::setprecision(2)
            << center.x << " " << center.y << " " << radius << std::endl;
    } else {
        throw std::runtime_error("Output stream is not open for writing.");
    }
}

void Circle::loadFromFile(std::istream& in) {
    if (!(in >> center.x >> center.y >> radius)) {
        throw std::runtime_error("Error reading Circle data from file: Invalid format or end of file.");
    }

    // Validate that the radius is non-negative
    if (radius < 0) {
        throw std::runtime_error("Error reading Circle data from file: Negative radius value.");
    }
}

std::vector<Point> Circle::getPoints() const override {
    std::vector<Point> points;

    // Calculate the number of points based on a fixed criterion
    int numPoints = 36; // Default number of points, can be adjusted or calculated

    // Calculate the angle increment inside the function
    double angleIncrement = 2 * M_PI / numPoints; 

    for (int i = 0; i < numPoints; ++i) {
        double angle = i * angleIncrement;
        Point p;
        p.x = radius * cos(angle);
        p.y = radius * sin(angle);
        points.push_back(p);
    }

    return points;
}

} // namespace geometry
