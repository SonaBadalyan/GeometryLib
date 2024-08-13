#include "geometry.hpp"
#include <sstream>
#include <iomanip>

namespace geometry {

Segment::Segment(const Point& start, const Point& end) : start(start), end(end) {}

bool Segment::contains(const Point& p) const {
    double crossProduct = (p.y - start.y) * (end.x - start.x) - (p.x - start.x) * (end.y - start.y);
    if (std::abs(crossProduct) > 1e-9) return false;

    double dotProduct = (p.x - start.x) * (end.x - start.x) + (p.y - start.y) * (end.y - start.y);
    if (dotProduct < 0) return false;

    double squaredLengthBA = (end.x - start.x) * (end.x - start.x) + (end.y - start.y) * (end.y - start.y);
    return dotProduct <= squaredLengthBA;
}

void Segment::draw() const {
    std::cout << "Segment: " << start << " to " << end << std::endl;
}

void Segment::drawSegments() const {
    std::cout << "Segment: " << start << " to " << end << std::endl;
}

void Segment::saveToFile(std::ostream& out) const {
    out << "Segment " << start.x << " " << start.y << " " << end.x << " " << end.y << std::endl;
}

void Segment::loadFromFile(std::istream& in) {
    in >> start.x >> start.y >> end.x >> end.y;
}

std::vector<Point> Segment::getPoints() const {
    return { start, end };
}

} // namespace geometry
