#include "../include/Triangle.h"


Triangle::Triangle(const Point& pointA, const Point& pointB, const Point& pointC) {
    points.push_back(pointA);
    points.push_back(pointB);
    points.push_back(pointC);
}

std::string Triangle::getObjectName() const {
    return "Triangle";
}

std::string Triangle::getObjectCoordinate() const {
    return points[0].getCoordinates("A") +
        points[1].getCoordinates("B") +
        points[2].getCoordinates("C");
}

double Triangle::perimeter() {
    return points[0].distanceTo(points[1]) +
        points[1].distanceTo(points[2]) +
        points[2].distanceTo(points[0]);
}

double Triangle::area() {
    auto p = perimeter() / 2;
    return sqrt(p *
        (p - points[0].distanceTo(points[1])) *
        (p - points[1].distanceTo(points[2])) *
        (p - points[2].distanceTo(points[0]))
    );
}

bool Triangle::areDisconnected(const Triangle& other) {
    double thisSlope = 0;
    double thisIntercept = 0;
    double otherSlope = 0;
    double otherIntercept = 0;

    double intersectionX = 0;
    double intersectionY = 0;

    int secondIndex = 0;
    int otherSecondIndex = 0;

    // Iterate through all sides of the triangles
    for (int firstIndex = 0; firstIndex < 3; firstIndex++) {
        // Determine the index of the second point of the side
        secondIndex = (firstIndex != 2) ? firstIndex + 1 : 0;

        // Create a linear function for the side of this triangle
        createLinearFunction(points[firstIndex], points[secondIndex], thisSlope, thisIntercept);

        for (int otherFirstIndex = 0; otherFirstIndex < 3; otherFirstIndex++) {
            // Determine the index of the second point of the side of the other triangle
            otherSecondIndex = (otherFirstIndex != 2) ? otherFirstIndex + 1 : 0;

            // Create a linear function for the side of the other triangle
            createLinearFunction(other.points[otherFirstIndex], other.points[otherSecondIndex], otherSlope, otherIntercept);

            // Check if the lines are not parallel
            if (thisSlope != otherIntercept) {
                // Find intersection point of two lines
                intersectionX = (otherIntercept - thisIntercept) / (thisSlope - otherSlope);
                intersectionY = thisSlope * intersectionX + thisIntercept;

                // Check if intersection point is within the bounds of both lines (i.e., sides of the triangles)
                if (isWithinBounds(points[firstIndex], points[secondIndex], intersectionX, intersectionY) &&
                    isWithinBounds(other.points[otherFirstIndex], other.points[otherSecondIndex], intersectionX, intersectionY)) {
                    return false; // Triangles are not disconnected
                }
            }
        }
    }
    return true; // Triangles are disconnected
}

bool Triangle::isWithinBounds(const Point& pointA, const Point& pointB, const double& x,const double& y) {
    double minX = std::min(pointA.getX(), pointB.getX());
    double minY = std::min(pointA.getY(), pointB.getY());
    double maxX = std::max(pointA.getX(), pointB.getX());
    double maxY = std::max(pointA.getY(), pointB.getY());

    return (x >= minX && x <= maxX && y >= minY && y <= maxY);
}