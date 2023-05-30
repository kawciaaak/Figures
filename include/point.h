#pragma once
#include <cmath>
#include <string>

class point
{
protected:
	double x;
	double y;
public:
	point() = default;
	point(double _x, double _y);
	~point() = default;

	void rotatePoint(double _x, double _y, double _angle);
	void movePointByVector(double _x, double _y);

	double distanceBetweenPoints(point _other) const;

	double getX() const;
	double getY() const;
	std::string getCoordinates(std::string _point_name) const;

	bool operator==(point _other) const;
};

