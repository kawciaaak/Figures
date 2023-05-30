#include "include/figure.h"

void figure::moveByVector(double _x, double _y) {
	for (auto& p : this->points) {
		p.movePointByVector(_x, _y);
	}
}

void figure::rotateAroundPoint(double _x, double _y,double _angle) {
	for (auto& p : this->points) {
		p.rotatePoint(_x, _y,_angle);
	}
}

void figure::createLinearFunction(point _start_point, point _end_point, double* _a, double* _b) {
	*(_a) = (_end_point.getY() - _start_point.getY() /
		_end_point.getX() - _start_point.getX());
	*(_b) = _start_point.getY() - *(_a)*_start_point.getX();
}

bool figure::isPointOnLinearFunction(point _point, double _a, double _b) {
	if (_a * _point.getX() + _b == _point.getY()) return true;
	else return false;
}