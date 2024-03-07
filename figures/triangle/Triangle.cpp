#include "triangle.h"
namespace Figures{
    namespace GeometricFigures{
Triangle::Triangle(const Point &first_point, const Point &second_point, const Point &third_point)
{
    points_.push_back(first_point);
    points_.push_back(second_point);
    points_.push_back(third_point);
}

std::string Triangle::GetObjectCoordinate() const
{
    return points_[0].CoordinatesToString("A") +
           points_[1].CoordinatesToString("B") +
           points_[2].CoordinatesToString("C");
}

std::string Triangle::GetObjectName() const
{
    return "Triangle";
}

double Triangle::GetParimeter() const
{
    return points_[0].distanceTo(points_[1]) +
           points_[1].distanceTo(points_[2]) +
           points_[2].distanceTo(points_[0]);
}

double Triangle::GetArea() const
{
    const auto &parimeter = GetParimeter() / 2;

    return sqrt(parimeter *
                (parimeter - points_[0].distanceTo(points_[1])) *
                (parimeter - points_[1].distanceTo(points_[2])) *
                (parimeter - points_[2].distanceTo(points_[0])));
}

bool Triangle::AreTrianglesDisconnected(const Triangle &other)
{
    double this_slope = 0;
    double this_intercept = 0;

    double other_slope = 0;
    double other_intercept = 0;

    double x_intersection = 0;
    double y_intersection = 0;

    int second_index = 0;
    int other_second_ndex = 0;

    // Iterate through all sides of the triangles
    for (int first_index = 0; first_index < 3; first_index++)
    {
        // Determine the index of the second point of the side
        second_index = (first_index != 2) ? first_index + 1 : 0;

        // Create a linear function for the side of this triangle
        CreateLinearFunction(points_[first_index], points_[second_index], this_slope, this_intercept);

        for (int other_first_index = 0; other_first_index < 3; other_first_index++)
        {
            // Determine the index of the second point of the side of the other triangle
            other_second_ndex = (other_first_index != 2) ? other_first_index + 1 : 0;

            // Create a linear function for the side of the other triangle
            CreateLinearFunction(other.points_[other_first_index], other.points_[other_second_ndex], other_slope, other_intercept);

            // Check if the lines are not parallel
            if (this_slope != other_intercept)
            {
                // Find intersection point of two lines
                x_intersection = (other_intercept - this_intercept) / (this_slope - other_slope);
                y_intersection = this_slope * x_intersection + this_intercept;

                // Check if intersection point is within the bounds of both lines (i.e., sides of the triangles)
                if (IsWithinBounds(points_[first_index], points_[second_index], x_intersection, y_intersection) &&
                    IsWithinBounds(other.points_[other_first_index], other.points_[other_second_ndex], x_intersection, y_intersection))
                {
                    return false; // Triangles are not disconnected
                }
            }
        }
    }
    return true; // Triangles are disconnected
}

bool Triangle::IsWithinBounds(const Point &first_point, const Point &second_point, const double &x, const double &y) const
{
    double x_min = std::min(first_point.GetXCoordinate(), second_point.GetXCoordinate());
    double x_max = std::max(first_point.GetXCoordinate(), second_point.GetXCoordinate());

    double y_min = std::min(first_point.GetYCoordinate(), second_point.GetYCoordinate());
    double y_max = std::max(first_point.GetYCoordinate(), second_point.GetYCoordinate());

    return (x >= x_min && x <= x_max && y >= y_min && y <= y_max);
}
}
}