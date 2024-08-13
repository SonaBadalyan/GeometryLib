#include "geometry.hpp"
#include <sstream>
#include <iomanip>

namespace geometry {

Line::Line(const Point& p1, const Point& p2) : p1(p1), p2(p2) {}

bool Line::contains(const Point& p) const {
    double crossProduct = (p2.y - p1.y) * (p.x - p1.x) - (p2.x - p1.x) * (p.y - p1.y);
    return std::abs(crossProduct) < 1e-9;
}

void Line::draw() const {
    std::cout << "Line: " << p1 << " to " << p2 << std::endl;
}

void Line::drawSegments() const {
    std::cout << "Line segment: " << p1 << " to " << p2 << std::endl;
}

void Line::saveToFile(std::ostream& out) const {
    out << "Line " << p1.x << " " << p1.y << " " << p2.x << " " << p2.y << std::endl;
}

void Line::loadFromFile(std::istream& in) {
    in >> p1.x >> p1.y >> p2.x >> p2.y;
}

std::vector<Point> Line::getPoints() const {
    return { p1, p2 };
}

} // namespace geometry

