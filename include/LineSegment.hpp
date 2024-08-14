#pragma once

#include "Shape.hpp"
#include <iostream>
#include <vector>

namespace geometry {

class LineSegment : public Shape {
public:
    Point start, end;

    // Constructor for the LineSegment class
    LineSegment(const Point& start, const Point& end);

    // Determines if a point lies on this line segment.
    // A point lies on the segment if it is collinear with the segment's endpoints
    // and lies between them.
    bool contains(const Point& p) const override;

    // Draw the LineSegment with formatted output
    void draw() const override;

    // Draw the LineSegment with formatted output (redundant with draw())
    void drawSegments() const override;

    // Save the LineSegment's data to a file
    void saveToFile(std::ostream& out) const override;

    // Load the LineSegment's data from a file
    void loadFromFile(std::istream& in) override;

    // Retrieve the points of the LineSegment
    std::vector<Point> getPoints() const override;
};

} // namespace geometry
