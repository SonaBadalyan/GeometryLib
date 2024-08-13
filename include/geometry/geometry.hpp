#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <iostream>
#include <vector>
#include <cmath>

namespace geometry {

struct Point {
    double x, y;

    Point(double x = 0, double y = 0) : x(x), y(y) {}

    friend std::ostream& operator<<(std::ostream& out, const Point& point) {
        out << "(" << point.x << ", " << point.y << ")";
        return out;
    }

    friend std::istream& operator>>(std::istream& in, Point& point) {
        in >> point.x >> point.y;
        return in;
    }
};

class Shape {
public:
    virtual ~Shape() = default;
    virtual bool contains(const Point& p) const = 0;
    virtual void draw() const = 0;
    virtual void drawSegments() const = 0;
    virtual void saveToFile(std::ostream& out) const = 0;
    virtual void loadFromFile(std::istream& in) = 0;
    virtual std::vector<Point> getPoints() const = 0;
};

} // namespace geometry

#endif // GEOMETRY_HPP
