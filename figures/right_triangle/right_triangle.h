#ifndef FIGURES_FIGURES_RIGHT_TRIANGLE_RIGHT_TRIANGLE_H
#define FIGURES_FIGURES_RIGHT_TRIANGLE_RIGHT_TRIANGLE_H

#include "..\figures\triangle\triangle.h"
#include <algorithm>

namespace Figures_space{
class RightTriangle : public Triangle
{
public:
    RightTriangle() = delete;
    RightTriangle(const Point &first_point, const Point &second_point, const Point &third_point);
    ~RightTriangle() = default;

    double GetHypotenuseLength() const;
    std::string GetObjectName() const override;
};
} //  namespace Figures_space

#endif // FIGURES_FIGURES_RIGHT_TRIANGLE_RIGHT_TRIANGLE_H
