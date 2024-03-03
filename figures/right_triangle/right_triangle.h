#ifndef FIGURES_FIGURES_RIGHT_TRIANGLE_RIGHT_TRIANGLE_H
#define FIGURES_FIGURES_RIGHT_TRIANGLE_RIGHT_TRIANGLE_H

#include "..\figures\triangle\triangle.h"
#include <algorithm>

class RightTriangle : public Triangle
{
public:
    RightTriangle() = delete;
    RightTriangle(const Point& pointA, const Point& pointB, const Point& pointC);
    ~RightTriangle() = default;

    double GetHypotenuseLength() const; 
    std::string GetObjectName() const override; 
};

#endif // FIGURES_FIGURES_RIGHT_TRIANGLE_RIGHT_TRIANGLE_H
