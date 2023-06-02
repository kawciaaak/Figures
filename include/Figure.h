#pragma once

#include <vector>
#include <iostream>
#include "Point.h"

class Figure {
protected:
    std::vector<Point> points;

public:
    void moveByVector(const double& xVector, const double& yVector);
    void rotateAroundPoint(const double& xCoordinate, const double& yCoordinate, const double& angle);
    void createLinearFunction(const Point& startPoint, const Point& endPoint, double& coefficientA, double& coefficientB);
    bool isPointOnLinearFunction(const Point& point, const double& coefficientA, const double& coefficientB) const;

    virtual std::string getObjectName() const = 0;
    virtual std::string getObjectCoordinate() const = 0;
};