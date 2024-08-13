#include "geometry.hpp"
#include <sstream>
#include <iomanip>

namespace geometry {

Circle::Circle(const Point& center, double radius) : center(center), radius(radius) {}

bool Circle::contains(const Point& p) const {
    double distSquared = (p.x - center.x) * (p.x - center.x) + (p.y - center.y) * (p.y - center.y);
    return distSquared <= radius * radius;
}

void Circle::draw() const {
    std::cout << "Circle: center=" << center << ", radius=" << radius << std::endl;
}

void Circle::drawSegments() const {
    std::cout << "Circle with center=" << center << " and radius=" << radius << std::endl;
}

void Circle::saveToFile(std::ostream& out) const {
    out << "Circle " << center.x << " " << center.y << " " << radius << std::endl;
}

void Circle::loadFromFile(std::istream& in) {
    in >> center.x >> center.y >> radius;
}

} // namespace geometry
