#ifndef FIGURES_FIGURES_POINT_POINT_H
#define FIGURES_FIGURES_POINT_POINT_H

#include <cmath>
#include <string>

class Point
{
public:
    Point() = default;
    Point(const double &x_coordinate, const double &y_coordinate);
    ~Point() = default;

    void RotateAroundPoint(const double &origin_x_coordinate, const double &origin_y_coordinate, const double &angle);
    void MovePointByVector(const double &vector_x_coordinate, const double &vector_y_coordinate);

    double distanceTo(const Point &otherPoint) const;

    double GetXCoordinate() const;
    double GetYCoordinate() const;
    std::string CoordinatesToString(const std::string &point_name) const;

    bool operator==(const Point &other_point) const;

protected:
    double x_coordinate_;
    double y_coordinate_;
};

#endif // FIGURES_FIGURES_POINT_POINT_H
