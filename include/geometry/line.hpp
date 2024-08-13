#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <iostream>
#include <vector>
#include <cmath>

namespace geometry {

class Line : public Shape {
public:
    Point p1, p2;

    Line(const Point& p1, const Point& p2);

    bool contains(const Point& p) const override;
    void draw() const override;
    void drawSegments() const override;
    void saveToFile(std::ostream& out) const override;
    void loadFromFile(std::istream& in) override;
    std::vector<Point> getPoints() const override;
};

} // namespace geometry

#endif // GEOMETRY_HPP
