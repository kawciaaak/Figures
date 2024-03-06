#ifndef FIGURES_FIGURES_SEGMENT_SEGMENT_H
#define FIGURES_FIGURES_SEGMENT_SEGMENT_H

#include "..\figures\figure.h"
#include <iostream>

class Segment : public Figure
{
public:
  Segment() = default;
  Segment(const Point &first_point, const Point &second_point);
  ~Segment() = default;

  double GetLength() const;
  std::string GetObjectName() const override;
  std::string GetObjectCoordinate() const override;

  bool IsPointOnSegment(const Point &point_to_verify);

  bool AreSegmentsParallel(const Segment &other_segment);
  bool AreSegmentsPerpendicular(const Segment &other_segment);
  void GetIntersectionPoint(const Segment &other_segment);

  void CreateLinearFunction(const Point &, const Point &, const double &, const double &) override;
  bool IsPointOnLinearFunction(const Point &, const double &, const double &) override;
};

#endif // FIGURES_FIGURES_SEGMENT_SEGMENT_H
