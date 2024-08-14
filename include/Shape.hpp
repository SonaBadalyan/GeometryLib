#pragma once

#include "Point.hpp"

#include <iostream>
#include <vector>

namespace geometry {

// Abstract base class for all geometric shapes
class Shape {
public:
    virtual ~Shape() = default;

    // Check if the given point is within the shape
    virtual bool contains(const Point& p) const = 0;

    // Draw the shape to the console (or other output)
    virtual void draw() const = 0;

    // Draw the shape's segments (useful for complex shapes)
    virtual void drawSegments() const = 0;

    // Save the shape to a file
    virtual void saveToFile(std::ostream& out) const = 0;

    // Load the shape from a file
    virtual void loadFromFile(std::istream& in) = 0;

    // Get the points that define the shape
    virtual std::vector<Point> getPoints() const = 0;
};

} // namespace geometry
