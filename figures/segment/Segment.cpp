#include "segment.h"
using namespace Figures_space;
Segment::Segment(const Point &first_point, const Point &second_point)
{
    points_.push_back(first_point);
    points_.push_back(second_point);
}

double Segment::GetLength() const
{
    return points_[0].distanceTo(points_[1]);
}

std::string Segment::GetObjectName() const
{
    return "Segment";
}

std::string Segment::GetObjectCoordinate() const
{
    return points_[0].CoordinatesToString("A") + points_[1].CoordinatesToString("B");
}

bool Segment::IsPointOnSegment(const Point &point_to_verify)
{
    double line_slope = 0;
    double line_intercept = 0;

    CreateLinearFunction(points_[0], points_[1], line_slope, line_intercept);

    if (IsPointOnLinearFunction(point_to_verify, line_slope, line_intercept))
    {
        double x_min = fmin(points_[0].GetXCoordinate(), points_[1].GetXCoordinate());
        double x_max = fmax(points_[0].GetXCoordinate(), points_[1].GetXCoordinate());

        double y_min = fmin(points_[0].GetYCoordinate(), points_[1].GetYCoordinate());
        double y_max = fmax(points_[0].GetYCoordinate(), points_[1].GetYCoordinate());

        if (point_to_verify.GetXCoordinate() >= x_min && point_to_verify.GetXCoordinate() <= x_max &&
            point_to_verify.GetYCoordinate() >= y_min && point_to_verify.GetYCoordinate() <= y_max)
        {
            return true;
        }
    }
    return false;
}

bool Segment::AreSegmentsParallel(const Segment &other_segment)
{
    double this_line_slope = 0;
    double this_line_intercept = 0;
    double other_line_slope = 0;
    double other_line_intercept = 0;

    CreateLinearFunction(points_[0], points_[1], this_line_slope, this_line_intercept);
    CreateLinearFunction(other_segment.points_[0], other_segment.points_[1], other_line_slope, other_line_intercept);

    // Accepting a small error margin (0.2) due to floating point arithmetic
    if (std::abs(this_line_slope - other_line_slope) < 0.2)
        return true;
    else
        return false;
}

bool Segment::AreSegmentsPerpendicular(const Segment &other_segment)
{
    double this_line_slope = 0;
    double this_line_intercept = 0;
    double other_line_slope = 0;
    double other_line_intercept = 0;

    CreateLinearFunction(points_[0], points_[1], this_line_slope, this_line_intercept);
    CreateLinearFunction(other_segment.points_[0], other_segment.points_[1], other_line_slope, other_line_intercept);

    // If the slopes multiply to -1, the lines are perpendicular
    if (this_line_slope * other_line_slope == -1)
        return true;
    else
        return false;
}

void Segment::GetIntersectionPoint(const Segment &other_segment)
{
    if (!AreSegmentsParallel(other_segment))
    {
        double this_line_slope = 0;
        double this_line_intercept = 0;

        double other_line_slope = 0;
        double other_line_intercept = 0;

        CreateLinearFunction(points_[0], points_[1], this_line_slope, this_line_intercept);
        CreateLinearFunction(other_segment.points_[0], other_segment.points_[1], other_line_slope, other_line_intercept);

        auto x_intersection = (other_line_intercept - this_line_intercept) / (this_line_slope - other_line_slope);
        auto y_intersection = this_line_slope * x_intersection + this_line_intercept;

        double x_min = fmin(points_[0].GetXCoordinate(), points_[1].GetXCoordinate());
        double x_max = fmax(points_[0].GetXCoordinate(), points_[1].GetXCoordinate());

        double y_min = fmin(points_[0].GetYCoordinate(), points_[1].GetYCoordinate());
        double y_max = fmax(points_[0].GetYCoordinate(), points_[1].GetYCoordinate());

        if (x_intersection >= x_min && x_intersection <= x_max && y_intersection >= y_min && y_intersection <= y_max)
        {
            Point intersection_point = {x_intersection, y_intersection};
            std::cout << intersection_point.CoordinatesToString("Intersection point: ");
        }
        else
        {
            std::cout << "No intersection point found.";
        }
    }
    else
        std::cout << "No intersection point found - segments are parallel" << std::endl;
}
