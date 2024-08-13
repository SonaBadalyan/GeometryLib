#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include "Shape"
#include <iostream>
#include <vector>

namespace geometry {

class Triangle : public Shape {
public:
    Point p1, p2, p3;

    // Constructor for the Triangle class
    Triangle(const Point& p1, const Point& p2, const Point& p3);

    // Check if a point is inside the triangle using barycentric coordinates
    bool contains(const Point& p) const override;

    // Draw the triangle with formatted output
    void draw() const override;

    // Draw the segments of the triangle with formatted output
    void drawSegments() const override;

    // Save the triangle's data to a file
    void saveToFile(std::ostream& out) const override;

    // Load the triangle's data from a file
    void loadFromFile(std::istream& in) override;

    // Retrieve the points of the triangle
    std::vector<Point> getPoints() const override;
};

} // namespace geometry

#endif // GEOMETRY_HPP
