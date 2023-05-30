#pragma once
#include <vector>
#include <iostream>
#include "point.h"


class figure
{
protected:
	std::vector<point> points;
public:
	void moveByVector(double _x, double _y);
	void rotateAroundPoint(double _x, double _y, double angle);
	void createLinearFunction(point _start_point, point _end_point, double* _a, double* _b);
	bool isPointOnLinearFunction(point _p, double _a, double _b);

	virtual std::string getObjectName() const = 0;
	virtual std::string getObjectCoordinate() const = 0;
};

