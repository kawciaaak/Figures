#pragma once
#include "Figure.h"

class Segment : public Figure
{
public:
    Segment() = default;
    Segment(const Point& pointA, const Point& pointB);
    ~Segment() = default;

    double getLength() const;

    std::string getObjectName() const override;
    std::string getObjectCoordinate() const override;

    bool isPointOnSegment(const Point& pointToCheck);
    bool areSegmentsParallel(const Segment& otherSegment);
    bool areSegmentsPerpendicular(const Segment& otherSegment);
    void getIntersectionPoint(const Segment& otherSegment);
};