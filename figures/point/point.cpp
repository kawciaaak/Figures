#define _USE_MATH_DEFINES
#include "point.h"

Point::Point(const double &x_coordinate, const double &y_coordinate)
{
    x_coordinate_ = x_coordinate;
    y_coordinate_ = y_coordinate;
}

void Point::RotateAroundPoint(const double &origin_x_coordinate, const double &origin_y_coordinate, const double &angle)
{
    double rad_angle = angle * M_PI / 180;

    double diff_x = (x_coordinate_ - origin_x_coordinate) * cos(rad_angle) - (y_coordinate_ - origin_y_coordinate) * sin(rad_angle);
    double diff_y = (x_coordinate_ - origin_x_coordinate) * sin(rad_angle) + (y_coordinate_ - origin_y_coordinate) * cos(rad_angle);

    x_coordinate_ = diff_x + origin_x_coordinate;
    y_coordinate_ = diff_y + origin_y_coordinate;
}

void Point::MovePointByVector(const double &vector_x_coordinate, const double &vector_y_coordinate)
{
    x_coordinate_ += vector_x_coordinate;
    y_coordinate_ += vector_y_coordinate;
}

double Point::GetXCoordinate() const
{
    return x_coordinate_;
}

double Point::GetYCoordinate() const
{
    return y_coordinate_;
}

std::string Point::CoordinatesToString(const std::string &point_name) const
{
    return point_name + "(" + std::to_string(x_coordinate_) + "," + std::to_string(y_coordinate_) + ") ";
}

double Point::distanceTo(const Point &other_point) const
{
    return sqrt(pow((other_point.x_coordinate_ - x_coordinate_), 2) + pow((other_point.y_coordinate_ - y_coordinate_), 2));
}

bool Point::operator==(const Point &other_point) const
{
    return (x_coordinate_ == other_point.x_coordinate_ && y_coordinate_ == other_point.y_coordinate_);
}
