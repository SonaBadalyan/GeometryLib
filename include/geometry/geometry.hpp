#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <iostream>
#include <vector>
#include <cmath>

namespace geometry {

// Define a constant for precision threshold to handle floating-point comparisons
constexpr double PRECISION_THRESHOLD = 1e-9;

// Define a Point structure representing a 2D point
struct Point {
    double x; // x-coordinate
    double y; // y-coordinate

    // Default constructor initializes to (0, 0)
    Point(double x = 0.0, double y = 0.0) : x(x), y(y) {}

    // Output stream operator for printing the point
    friend std::ostream& operator<<(std::ostream& out, const Point& point) {
        out << "(" << point.x << ", " << point.y << ")";
        return out;
    }

    // Input stream operator for reading the point
    friend std::istream& operator>>(std::istream& in, Point& point) {
        in >> point.x >> point.y;
        return in;
    }

    // Equality operator to compare two points
    bool operator==(const Point& other) const {
        return std::abs(x - other.x) < PRECISION_THRESHOLD &&
               std::abs(y - other.y) < PRECISION_THRESHOLD;
    }

    // Inequality operator to compare two points
    bool operator!=(const Point& other) const {
        return !(*this == other);
    }
};

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

#endif // GEOMETRY_HPP
