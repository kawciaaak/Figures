#pragma once
#include "figure.h"
class segment : public figure
{
public:
	segment() = default;
	segment(point _a, point _b);
	~segment() = default;

	double getLength();

	std::string getObjectName() const override;
	std::string getObjectCoordinate() const override;

	void getIntersectionPoint(segment _other);
	bool isPointOnSegment(point _point);
	bool areParallel(segment _other);
	bool arePerpendicular(segment _other);
};

