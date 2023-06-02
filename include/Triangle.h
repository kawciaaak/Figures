#pragma once

#include "Figure.h"
#include "Point.h"
#include "Segment.h"
#include <string>
#include <vector>

class Triangle : public Figure {
public:
    Triangle() = default;
    Triangle(const Point& pointA, const Point& pointB, const Point& pointC);
    ~Triangle() = default;

    std::string getObjectName() const;
    std::string getObjectCoordinate() const;

    double perimeter();
    double area();

    bool isWithinBounds(const Point& pointA, const Point& pointB, const double& x, const double& y);

    bool areDisconnected(const Triangle& other);
};