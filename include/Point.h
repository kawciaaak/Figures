#pragma once
#include <cmath>
#include <string>


class Point
{
protected:
    double x;
    double y;
public:
    Point() = default;
    Point(const double& xCoordinate, const double& yCoordinate);
    ~Point() = default;

    void rotate(const double& xOrigin, const double& yOrigin, const double& angle);
    void moveByVector(const double& xDistance, const double& yDistance);

    double distanceTo(const Point& otherPoint) const;

    double getX() const;
    double getY() const;
    std::string getCoordinates(const std::string& pointName) const;

    bool operator==(const Point& otherPoint) const;
};
