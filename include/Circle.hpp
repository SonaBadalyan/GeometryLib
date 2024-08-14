#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include "Shape.hpp"
#include <iostream>
#include <vector>

namespace geometry {

class Circle : public Shape {
public:
    Point center;
    double radius;

    // Constructor for the Circle class
    Circle(const Point& center, double radius);

    // Determines if a point lies on the circumference of the circle.
    // A point lies on the circle if the distance from the center equals the radius.
    bool contains(const Point& p) const override;

    // Draw the circle with formatted output
    void draw() const override;

    // Draw the circle segments with formatted output
    void drawSegments() const override;

    // Save the circle's data to a file
    void saveToFile(std::ostream& out) const override;

    // Load the circle's data from a file
    void loadFromFile(std::istream& in) override;

    // Retrieve the points of the circle
    std::vector<Point> getPoints() const override;
};

} // namespace geometry

#endif // GEOMETRY_HPP
