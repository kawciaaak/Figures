#pragma once

#include <vector>
#include <iostream>
#include "Point.h"

class Figure {
protected:
    std::vector<Point> points;

public:
    void moveByVector(double x, double y);
    void rotateAroundPoint(double x, double y, double angle);
    void createLinearFunction(const Point& startPoint, const Point& endPoint, double& a, double& b);
    bool isPointOnLinearFunction(const Point& point, double a, double b) const;

    virtual std::string getObjectName() const = 0;
    virtual std::string getObjectCoordinate() const = 0;
};