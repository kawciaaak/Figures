#include "../include/Figure.h"

void Figure::moveByVector(double x, double y) {
    for (auto& point : points) {
        point.moveByVector(x, y);
    }
}

void Figure::rotateAroundPoint(double x, double y, double angle) {
    for (auto& point : points) {
        point.rotate(x, y, angle);
    }
}

void Figure::createLinearFunction(const Point& startPoint, const Point& endPoint, double& a, double& b) {
    double deltaX = endPoint.getX() - startPoint.getX();
    double deltaY = endPoint.getY() - startPoint.getY();

    if (deltaX != 0) {
        a = deltaY / deltaX;
        b = startPoint.getY() - a * startPoint.getX();
    }
    else {
        a = std::numeric_limits<double>::infinity();
        b = startPoint.getX();
    }
}

bool Figure::isPointOnLinearFunction(const Point& point, double a, double b) const {
    double y_expected = a * point.getX() + b;
    return (std::fabs(y_expected - point.getY()) <= std::numeric_limits<double>::epsilon());
}