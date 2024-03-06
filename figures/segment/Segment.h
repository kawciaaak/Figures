#ifndef FIGURES_FIGURES_SEGMENT_SEGMENT_H
#define FIGURES_FIGURES_SEGMENT_SEGMENT_H

#include "..\figures\figure.h"
#include <iostream>

class Segment : public Figure
{
public:
    Segment() = default;
    Segment(const Point& first_point, const Point& second_point);
    ~Segment() = default;

    double GetLength() const;
    std::string GetObjectName() const override;
    std::string GetObjectCoordinate() const override;

    bool isPointOnSegment(const Point& pointToCheck);

    bool areSegmentsParallel(const Segment& otherSegment);
    bool areSegmentsPerpendicular(const Segment& otherSegment);
    void getIntersectionPoint(const Segment& otherSegment);
};

#endif // FIGURES_FIGURES_SEGMENT_SEGMENT_H
