#pragma once
#include "Triangle.h"
#include <algorithm>

// The RightTriangle class represents a right triangle in 2D space.
class RightTriangle : public Triangle
{
public:
    RightTriangle() = default;
    RightTriangle(Point pointA, Point pointB, Point pointC);
    ~RightTriangle() = default;

    double getHypotenuseLength() const;
    std::string getObjectName() const override;
};
