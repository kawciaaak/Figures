#include "../include/Segment.h"

Segment::Segment(const Point& pointA, const Point& pointB) {
    points.push_back(pointA);
    points.push_back(pointB);
}

double Segment::getLength() const {
    return points[0].distanceTo(points[1]);
}

std::string Segment::getObjectName() const {
    return "Segment";
}

std::string Segment::getObjectCoordinate() const {
    return points[0].getCoordinates("A") + points[1].getCoordinates("B");
}

bool Segment::isPointOnSegment(const Point& pointToCheck) {
    double lineSlope = 0;
    double lineIntercept = 0;

    createLinearFunction(points[0], points[1], lineSlope, lineIntercept);

    if (isPointOnLinearFunction(pointToCheck, lineSlope, lineIntercept)) {
        double minX = fmin(points[0].getX(), points[1].getX());
        double maxX = fmax(points[0].getX(), points[1].getX());
        double minY = fmin(points[0].getY(), points[1].getY());
        double maxY = fmax(points[0].getY(), points[1].getY());

        if (pointToCheck.getX() >= minX && pointToCheck.getX() <= maxX &&
            pointToCheck.getY() >= minY && pointToCheck.getY() <= maxY) {
            return true;
        }
    }
    return false;
}

bool Segment::areSegmentsParallel(const Segment& otherSegment) {
    double thisLineSlope = 0;
    double thisLineIntercept = 0;
    double otherLineSlope = 0;
    double otherLineIntercept = 0;

    createLinearFunction(points[0], points[1], thisLineSlope, thisLineIntercept);
    createLinearFunction(otherSegment.points[0], otherSegment.points[1], otherLineSlope, otherLineIntercept);

    // Accepting a small error margin (0.3) due to floating point arithmetic
    if (std::abs(thisLineSlope - otherLineSlope) < 0.3) return true;
    else return false;
}

bool Segment::areSegmentsPerpendicular(const Segment& otherSegment) {
    double thisLineSlope = 0;
    double thisLineIntercept = 0;
    double otherLineSlope = 0;
    double otherLineIntercept = 0;

    createLinearFunction(points[0], points[1], thisLineSlope, thisLineIntercept);
    createLinearFunction(otherSegment.points[0], otherSegment.points[1], otherLineSlope, otherLineIntercept);

    // If the slopes multiply to -1, the lines are perpendicular
    if (thisLineSlope * otherLineSlope == -1) return true;
    else return false;
}



void Segment::getIntersectionPoint(const Segment& otherSegment) {
    if (!areSegmentsParallel(otherSegment)) {
        double thisLineSlope = 0;
        double thisLineIntercept = 0;
        double otherLineSlope = 0;
        double otherLineIntercept = 0;

        createLinearFunction(points[0], points[1], thisLineSlope, thisLineIntercept);
        createLinearFunction(otherSegment.points[0], otherSegment.points[1], otherLineSlope, otherLineIntercept);

        auto intersectionX = (otherLineIntercept - thisLineIntercept) / (thisLineSlope - otherLineSlope);
        auto intersectionY = thisLineSlope * intersectionX + thisLineIntercept;

        double minX = fmin(points[0].getX(), points[1].getX());
        double maxX = fmax(points[0].getX(), points[1].getX());
        double minY = fmin(points[0].getY(), points[1].getY());
        double maxY = fmax(points[0].getY(), points[1].getY());

        if (intersectionX >= minX && intersectionX <= maxX && intersectionY >= minY && intersectionY <= maxY) {
            Point intersectionPoint = { intersectionX, intersectionY };
            std::cout << intersectionPoint.getCoordinates("Intersection point: ");
        }
        else {
            std::cout << "No intersection point found.";
        }
    }
    else std::cout << "No intersection point found - segments are parallel" << std::endl;
}