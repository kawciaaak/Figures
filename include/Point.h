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
    Point(double xCoordinate, double yCoordinate);
    ~Point() = default;

    void rotate(double xOrigin, double yOrigin, double angle);
    void moveByVector(double xDistance, double yDistance);

    double distanceTo(Point otherPoint) const;

    double getX() const;
    double getY() const;
    std::string getCoordinates(std::string pointName) const;

    bool operator==(Point otherPoint) const;
};
