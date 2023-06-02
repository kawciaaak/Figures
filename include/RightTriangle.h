#pragma once
#include "Triangle.h"
#include <algorithm>

class RightTriangle : public Triangle
{
public:
    RightTriangle() = default;
    RightTriangle(const Point pointA, const Point pointB, const Point pointC);
    ~RightTriangle() = default;

    double getHypotenuseLength() const;
    std::string getObjectName() const override;
};
