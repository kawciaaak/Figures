#pragma once

#include "Point.h"
#include <string>
#include <vector>

class Triangle {
private:
    std::vector<Point> points;

    void createLinearFunction(const Point& point1, const Point& point2, double& slope, double& intercept);
    bool isWithinBounds(const Point& point1, const Point& point2, double x, double y);

public:
    Triangle(const Point& _a, const Point& _b, const Point& _c);

    std::string getObjectName() const;
    std::string getObjectCoordinate() const;

    double perimeter();
    double area();

    bool areDisconnected(const Triangle& other);
};