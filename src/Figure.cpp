#include "../include/Figure.h"

void Figure::moveByVector(const double& xVector, const double& yVector) {
    for (auto& point : points) {
        point.moveByVector(xVector, yVector);
    }
}

void Figure::rotateAroundPoint(const double& xCoordinate, const double& yCoordinate, const double& angle) {
    for (auto& point : points) {
        point.rotate(xCoordinate, yCoordinate, angle);
    }
}

void Figure::createLinearFunction(const Point& startPoint, const Point& endPoint, double& coefficientA, double& coefficientB) {
    double deltaX = endPoint.getX() - startPoint.getX();
    double deltaY = endPoint.getY() - startPoint.getY();

    if (deltaX != 0) {
        coefficientA = deltaY / deltaX;
        coefficientB = startPoint.getY() - coefficientB * startPoint.getX();
    }
    else {
        coefficientA = std::numeric_limits<double>::infinity();
        coefficientB = startPoint.getX();
    }
}

bool Figure::isPointOnLinearFunction(const Point& point, const double& coefficientA, const double& coefficientB) const {
    double yExpected = coefficientA * point.getX() + coefficientB;
    return yExpected == point.getY();
}