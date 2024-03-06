#include "segment.h"

Segment::Segment(const Point& first_point, const Point& second_point) {
    points_.push_back(first_point);
    points_.push_back(second_point);
}

double Segment::GetLength() const {
    return points_[0].distanceTo(points_[1]);
}

std::string Segment::GetObjectName() const {
    return "Segment";
}

std::string Segment::GetObjectCoordinate() const {
    return points_[0].CoordinatesToString("A") + points_[1].CoordinatesToString("B");
}

bool Segment::isPointOnSegment(const Point& pointToCheck) {
    double lineSlope = 0;
    double lineIntercept = 0;

 //   createLinearFunction(points[0], points[1], lineSlope, lineIntercept);

    if ( /*isPointOnLinearFunction(pointToCheck, lineSlope, lineIntercept) */) {
        double minX = fmin(points_[0].GetXCoordinate(), points_[1].GetXCoordinate());
        double maxX = fmax(points_[0].GetXCoordinate(), points_[1].GetXCoordinate());
        double minY = fmin(points_[0].GetYCoordinate(), points_[1].GetYCoordinate());
        double maxY = fmax(points_[0].GetYCoordinate(), points_[1].GetYCoordinate());

        if (pointToCheck.GetXCoordinate() >= minX && pointToCheck.GetXCoordinate() <= maxX &&
            pointToCheck.GetYCoordinate() >= minY && pointToCheck.GetYCoordinate() <= maxY) {
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

  //  createLinearFunction(points_[0], points_[1], thisLineSlope, thisLineIntercept);
 //   createLinearFunction(otherSegment.points_[0], otherSegment.points_[1], otherLineSlope, otherLineIntercept);

    // Accepting a small error margin (0.3) due to floating point arithmetic
    if (std::abs(thisLineSlope - otherLineSlope) < 0.3) return true;
    else return false;
}

bool Segment::areSegmentsPerpendicular(const Segment& otherSegment) {
    double thisLineSlope = 0;
    double thisLineIntercept = 0;
    double otherLineSlope = 0;
    double otherLineIntercept = 0;

  //  createLinearFunction(points_[0], points_[1], thisLineSlope, thisLineIntercept);
   // createLinearFunction(otherSegment.points_[0], otherSegment.points_[1], otherLineSlope, otherLineIntercept);

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

       // createLinearFunction(points_[0], points_[1], thisLineSlope, thisLineIntercept);
       // createLinearFunction(otherSegment.points_[0], otherSegment.points_[1], otherLineSlope, otherLineIntercept);

        auto intersectionX = (otherLineIntercept - thisLineIntercept) / (thisLineSlope - otherLineSlope);
        auto intersectionY = thisLineSlope * intersectionX + thisLineIntercept;

        double minX = fmin(points_[0].GetXCoordinate(), points_[1].GetXCoordinate());
        double maxX = fmax(points_[0].GetXCoordinate(), points_[1].GetXCoordinate());
        double minY = fmin(points_[0].GetYCoordinate(), points_[1].GetYCoordinate());
        double maxY = fmax(points_[0].GetYCoordinate(), points_[1].GetYCoordinate());

        if (intersectionX >= minX && intersectionX <= maxX && intersectionY >= minY && intersectionY <= maxY) {
            Point intersectionPoint = { intersectionX, intersectionY };
            std::cout << intersectionPoint.CoordinatesToString("Intersection point: ");
        }
        else {
            std::cout << "No intersection point found.";
        }
    }
    else std::cout << "No intersection point found - segments are parallel" << std::endl;
}