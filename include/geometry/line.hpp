#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include "Shape"
#include <iostream>
#include <vector>

namespace geometry {

class Line : public Shape {
public:
    Point p1, p2;

    // Constructor for the Line class
    Line(const Point& p1, const Point& p2);

    // Check if a point lies on the line segment
    // The point (x, y) lies on the line if it satisfies the equation Ax + By + C = 0
    bool contains(const Point& p) const override;

    // Draw the line with formatted output
    void draw() const override;

    // Draw the line segment with formatted output
    void drawSegments() const override;

    // Save the line's data to a file
    void saveToFile(std::ostream& out) const override;

    // Load the line's data from a file
    void loadFromFile(std::istream& in) override;

    // Retrieve the points of the line
    std::vector<Point> getPoints() const override;

    // Computes the perpendicular distance from a point to the line.
    // Formula: |Ax + By + C| / √(A^2 + B^2)
    double distanceToPoint(const double A, const double B, const double C, const Point& p) const;
};

} // namespace geometry

#endif // GEOMETRY_HPP
