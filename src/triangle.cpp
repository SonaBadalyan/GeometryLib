#include "geometry.hpp"
#include <sstream>
#include <iomanip>

namespace geometry {

Triangle::Triangle(const Point& p1, const Point& p2, const Point& p3) : p1(p1), p2(p2), p3(p3) {}

bool Triangle::contains(const Point& p) const {
    double denominator = (p2.y - p3.y) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.y - p3.y);
    double a = ((p2.y - p3.y) * (p.x - p3.x) + (p3.x - p2.x) * (p.y - p3.y)) / denominator;
    double b = ((p3.y - p1.y) * (p.x - p3.x) + (p1.x - p3.x) * (p.y - p3.y)) / denominator;
    double c = 1.0 - a - b;
    return a >= 0 && b >= 0 && c >= 0;
}

void Triangle::draw() const {
    std::cout << "Triangle: " << p1 << ", " << p2 << ", " << p3 << std::endl;
}

void Triangle::drawSegments() const {
    std::cout << "Triangle segments:" << std::endl;
    std::cout << "Segment: " << p1 << " to " << p2 << std::endl;
    std::cout << "Segment: " << p2 << " to " << p3 << std::endl;
    std::cout << "Segment: " << p3 << " to " << p1 << std::endl;
}

void Triangle::saveToFile(std::ostream& out) const {
    out << "Triangle " << p1.x << " " << p1.y << " " << p2.x << " " << p2.y << " " << p3.x << " " << p3.y << std::endl;
}

void Triangle::loadFromFile(std::istream& in) {
    in >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y;
}

std::vector<Point> Triangle::getPoints() const {
    return { p1, p2, p3 };
}

} // namespace geometry
