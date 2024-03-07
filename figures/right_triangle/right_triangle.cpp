#include "right_triangle.h"
namespace Figures{
    namespace GeometricFigures{
RightTriangle::RightTriangle(const Point &first_point, const Point &second_point, const Point &third_point)
{
    points_.push_back(first_point);
    points_.push_back(second_point);
    points_.push_back(third_point);
}

double RightTriangle::GetHypotenuseLength() const
{
    std::vector<Segment> triangle_sides;
    std::vector<double> side_lengths;
    int next_index = 0;

    // Construct all sides of the triangle
    for (int i = 0; i < 3; i++)
    {
        if (i != 2)
            next_index = i + 1;
        else
            next_index = 0;
        triangle_sides.push_back(Segment(points_[i], points_[next_index]));
    }

    // Calculate and store lengths of the sides
    for (const auto &side : triangle_sides)
    {
        side_lengths.push_back(side.GetLength());
    }

    // Return the length of the longest side (hypotenuse)
    return *std::max_element(side_lengths.begin(), side_lengths.end());
}

std::string RightTriangle::GetObjectName() const
{
    return "Right triangle";
}
}
}