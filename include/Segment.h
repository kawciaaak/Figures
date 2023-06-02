#pragma once
#include "Figure.h"

class Segment : public Figure
{
public:
    Segment() = default;
    Segment(Point pointA, Point pointB);
    ~Segment() = default;

    double getLength() const;

    std::string getObjectName() const override;
    std::string getObjectCoordinate() const override;

    bool isPointOnSegment(Point pointToCheck);
    bool areSegmentsParallel(Segment otherSegment);
    bool areSegmentsPerpendicular(Segment otherSegment);
    void getIntersectionPoint(Segment otherSegment);
};