#include "geometry.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>

namespace geometry {

// Constructor for the Segment class
Segment::Segment(const Point& start, const Point& end) : start(start), end(end) {
    // Ensure the segment is valid by checking if start and end are not the same
    if (start.x == end.x && start.y == end.y) {
        throw std::invalid_argument("Segment start and end points cannot be the same.");
    }
}

// Check if a point is on the segment
bool Segment::contains(const Point& p) const {
    // Check if the point is collinear with the segment
    double crossProduct = (p.y - start.y) * (end.x - start.x) - (p.x - start.x) * (end.y - start.y);
    if (std::abs(crossProduct) > PRECISION_THRESHOLD) return false;

    // Check if the point is within the bounds of the segment
    double dotProduct = (p.x - start.x) * (end.x - start.x) + (p.y - start.y) * (end.y - start.y);
    if (dotProduct < 0) return false;

    double squaredLengthBA = (end.x - start.x) * (end.x - start.x) + (end.y - start.y) * (end.y - start.y);
    return dotProduct <= squaredLengthBA;
}

// Draw the segment with formatted output
void Segment::draw() const {
    std::cout << "Segment from (" << std::fixed << std::setprecision(2)
              << start.x << ", " << start.y << ") to (" << end.x << ", " << end.y << ")" << std::endl;
}

// Draw the segment with formatted output (redundant with draw())
void Segment::drawSegments() const {
    draw(); // Call the draw method for consistency
}

// Save the segment's data to a file
void Segment::saveToFile(std::ostream& out) const {
    if (out) {
        out << "Segment " << std::fixed << std::setprecision(2)
            << start.x << " " << start.y << " " << end.x << " " << end.y << std::endl;
    } else {
        throw std::runtime_error("Output stream is not open for writing.");
    }
}

// Load the segment's data from a file
void Segment::loadFromFile(std::istream& in) {
    if (!(in >> start.x >> start.y >> end.x >> end.y)) {
        throw std::runtime_error("Error reading Segment data from file: Invalid format or end of file.");
    }
}

std::vector<Point> Segment::getPoints() const {
    return { start, end };
}

} // namespace geometry
