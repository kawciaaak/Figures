#include "triangle.h"

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

bool Triangle::AreTrianglesDisconnected(const Triangle &other) const
{
    double thisSlope = 0;
    double thisIntercept = 0;
    double otherSlope = 0;
    double otherIntercept = 0;

    double intersectionX = 0;
    double intersectionY = 0;

    int secondIndex = 0;
    int otherSecondIndex = 0;

    // Iterate through all sides of the triangles
    for (int firstIndex = 0; firstIndex < 3; firstIndex++)
    {
        // Determine the index of the second point of the side
        secondIndex = (firstIndex != 2) ? firstIndex + 1 : 0;

        // Create a linear function for the side of this triangle
        //    createLinearFunction(points_[firstIndex], points_[secondIndex], thisSlope, thisIntercept);

        for (int otherFirstIndex = 0; otherFirstIndex < 3; otherFirstIndex++)
        {
            // Determine the index of the second point of the side of the other triangle
            otherSecondIndex = (otherFirstIndex != 2) ? otherFirstIndex + 1 : 0;

            // Create a linear function for the side of the other triangle
            //   createLinearFunction(other.points_[otherFirstIndex], other.points_[otherSecondIndex], otherSlope, otherIntercept);

            // Check if the lines are not parallel
            if (thisSlope != otherIntercept)
            {
                // Find intersection point of two lines
                intersectionX = (otherIntercept - thisIntercept) / (thisSlope - otherSlope);
                intersectionY = thisSlope * intersectionX + thisIntercept;

                // Check if intersection point is within the bounds of both lines (i.e., sides of the triangles)
                if (/*isWithinBounds(points_[firstIndex], points_[secondIndex], intersectionX, intersectionY) &&
                    isWithinBounds(other.points_[otherFirstIndex], other.points_[otherSecondIndex], intersectionX, intersectionY) */
                )
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