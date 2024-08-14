#include "LineSegment.hpp"

#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <stdexcept>

namespace geometry {


LineSegment::LineSegment(const Point& start, const Point& end) : start(start), end(end) {
    // Ensure the LineSegment is valid by checking if start and end are not the same
    if (start.x == end.x && start.y == end.y) {
        throw std::invalid_argument("LineSegment start and end points cannot be the same.");
    }
}

bool LineSegment::contains(const Point& p) const {
    // Check if the point is collinear with the LineSegment
    double crossProduct = (p.y - start.y) * (end.x - start.x) - (p.x - start.x) * (end.y - start.y);
    if (std::abs(crossProduct) > EPSILON) return false;

    // Check if the point is within the bounds of the LineSegment
    double dotProduct = (p.x - start.x) * (end.x - start.x) + (p.y - start.y) * (end.y - start.y);
    if (dotProduct < 0) return false;

    double squaredLengthBA = (end.x - start.x) * (end.x - start.x) + (end.y - start.y) * (end.y - start.y);
    return dotProduct <= squaredLengthBA;
}

void LineSegment::draw() const {
    std::cout << "LineSegment from (" << std::fixed << std::setprecision(2)
              << start.x << ", " << start.y << ") to (" << end.x << ", " << end.y << ")" << std::endl;
}

void LineSegment::drawSegments() const {
    draw(); // Call the draw method for consistency
}

void LineSegment::saveToFile(std::ostream& out) const {
    if (out) {
        out << "LineSegment " << std::fixed << std::setprecision(2)
            << start.x << " " << start.y << " " << end.x << " " << end.y << std::endl;
    } else {
        throw std::runtime_error("Output stream is not open for writing.");
    }
}

void LineSegment::loadFromFile(std::istream& in) {
    if (!(in >> start.x >> start.y >> end.x >> end.y)) {
        throw std::runtime_error("Error reading LineSegment data from file: Invalid format or end of file.");
    }
}

std::vector<Point> LineSegment::getPoints() const {
    return { start, end };
}

} // namespace geometry
