#ifndef FIGURES_TRIANGLE_TRIANGLE_H
#define FIGURES_TRIANGLE_TRIANGLE_H

#include "..\figures\segment\segment.h"

class Triangle : public Figure
{
public:
    Triangle() = default;
    Triangle(const Point &first_point, const Point &second_point, const Point &third_point);
    ~Triangle() = default;

    std::string GetObjectName() const;
    std::string GetObjectCoordinate() const;
    double GetParimeter() const;
    double GetArea() const;

    bool IsWithinBounds(const Point &first_point, const Point &second_point, const double &x, const double &y) const;
    bool AreTrianglesDisconnected(const Triangle &other);

    void CreateLinearFunction(const Point &, const Point &, const double &, const double &) override;
    bool IsPointOnLinearFunction(const Point &, const double &, const double &) override;
};

#endif // FIGURES_TRIANGLE_TRIANGLE_H
