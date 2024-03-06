#ifndef FIGURES_TRIANGLE_TRIANGLE_H
#define FIGURES_TRIANGLE_TRIANGLE_H

#include "..\figures\segment\segment.h"

class Triangle : public Figure
{
public:
    Triangle() = delete;
    Triangle(const Point &first_point, const Point &second_point, const Point &third_point);
    ~Triangle() = default;

    constexpr char *GetObjectName() { return "Triangle"; }
    std::string GetObjectCoordinate() const;
    double GetParimeter() const;
    double GetArea() const;

    bool IsWithinBounds(const Point &first_point, const Point &second_point, const double &x, const double &y) const;
    bool AreTrianglesDisconnected(const Triangle &other) const;
};

#endif // FIGURES_TRIANGLE_TRIANGLE_H
