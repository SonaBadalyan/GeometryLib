// src/geometry.cpp
#include "geometry/geometry.h"

namespace ODAGeometry {

std::ostream& Point::operator<<(std::ostream& os, const Point& p) {
    os << p.x << " " << p.y;
    return os;
}

std::istream& Point::operator>>(std::istream& is, Point& p) {
    is >> p.x >> p.y;
    return is;
}

} // namespace geometry