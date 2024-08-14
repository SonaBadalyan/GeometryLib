#pragma once

#include <iostream>

namespace geometry {

// Define a constant for precision threshold to handle floating-point comparisons
constexpr double EPSILON = 1e-9;

// Define a Point structure representing a 2D point
struct Point {
    double x; // x-coordinate
    double y; // y-coordinate

    // Default constructor initializes to (0, 0)
    Point(double x = 0.0, double y = 0.0) : x(x), y(y) {}

    // Output stream operator for printing the point
    friend std::ostream& operator<<(std::ostream& out, const Point& point);

    // Input stream operator for reading the point
    friend std::istream& operator>>(std::istream& in, Point& point);

    // Equality operator to compare two points
    bool operator==(const Point& other) const;

    // Inequality operator to compare two points
    bool operator!=(const Point& other) const;

    // Define the operator< for the Point
    bool operator<(const Point& other) const;

    // Computes the distance between this point and another point.
    // Formula: √((x2 - x1)^2 + (y2 - y1)^2)
    double distanceTo(const Point& other) const;
};
} // namespace geometry
