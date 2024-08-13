// include/geometry/geometry.h
#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <vector>

namespace ODAGeometry {

class Point {
public:
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    friend std::ostream& operator<<(std::ostream& os, const Point& p);
    friend std::istream& operator>>(std::istream& is, Point& p);
};

class Shape {
public:
    virtual bool containsPoint(const Point& p) const = 0;
    virtual std::vector<Point> getDrawSegments() const = 0;
    virtual void serialize(std::ostream& os) const = 0;
    virtual void deserialize(std::istream& is) = 0;
    virtual ~Shape() = default;
};

} // namespace geometry

#endif // GEOMETRY_H