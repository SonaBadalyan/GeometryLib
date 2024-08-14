#include "Point.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <stdexcept>

namespace geometry {

std::ostream& operator<<(std::ostream& out, const Point& point) {
    out << "(" << point.x << ", " << point.y << ")";
    return out;
}

std::istream& operator>>(std::istream& in, Point& point) {
    in >> point.x >> point.y;
    return in;
}

bool Point::operator==(const Point& other) const {
    return std::abs(x - other.x) < EPSILON &&
            std::abs(y - other.y) < EPSILON;
}

bool Point::operator!=(const Point& other) const {
    return !(*this == other);
}

bool Point::operator<(const Point& other) const {
    // First compare the x coordinates
    if (x < other.x) {
        return true;
    }
    if (x > other.x) {
        return false;
    }
    
    // If x coordinates are equal, compare the y coordinates
    return y < other.y;
}

double Point::distanceTo(const Point& other) const {
    return std::sqrt(std::pow(other.x - x, 2) + std::pow(other.y - y, 2));
}

} // namespace geometry