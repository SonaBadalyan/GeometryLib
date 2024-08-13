#include "Point"
#include <cmath>

namespace geometry {

friend std::ostream& Point::operator<<(std::ostream& out, const Point& point) {
    out << "(" << point.x << ", " << point.y << ")";
    return out;
}

friend std::istream& Point::operator>>(std::istream& in, Point& point) {
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

double Point::distanceTo(const Point& other) const {
    return std::sqrt(std::pow(other.x - x, 2) + std::pow(other.y - y, 2));
}

} // namespace geometry