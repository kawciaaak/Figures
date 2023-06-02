#define _USE_MATH_DEFINES
#include "../include/Point.h"

Point::Point(double xCoordinate, double yCoordinate) {
    x = xCoordinate;
    y = yCoordinate;
}

void Point::rotate(double xOrigin, double yOrigin, double angle) {
    double rad = angle * M_PI / 180;

    double newX = (x - xOrigin) * cos(rad) - (y - yOrigin) * sin(rad);
    double newY = (x - xOrigin) * sin(rad) + (y - yOrigin) * cos(rad);

    this->x = newX + xOrigin;
    this->y = newY + yOrigin;
}

void Point::moveByVector(double xDistance, double yDistance) {
    this->x += xDistance;
    this->y += yDistance;
}

double Point::getX() const {
    return this->x;
}

double Point::getY() const {
    return this->y;
}

std::string Point::getCoordinates(std::string pointName) const {
    return pointName + "(" + std::to_string(x) + "," + std::to_string(y) + ") ";
}

double Point::distanceTo(Point otherPoint) const {
    return sqrt(pow((otherPoint.getX() - this->x), 2) + pow((otherPoint.getY() - this->y), 2));
}

bool Point::operator==(Point otherPoint) const {
    return (x == otherPoint.x && y == otherPoint.y);
}
