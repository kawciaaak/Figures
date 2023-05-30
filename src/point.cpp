#define _USE_MATH_DEFINES
#include "include/point.h"


point::point(double _x, double _y) {
	x = _x;
	y = _y;
}

void point::rotatePoint(double _x, double _y, double _angle){
	double rad = _angle * M_PI / 180;

	double new_x = (x - _x) * cos(rad) - (y - _y) * sin(rad);
	double new_y = (x - _x) * sin(rad) - (y - _y) * cos(rad);

	this->x = new_x + _x;
	this->y = new_y + _y;
}

void point::movePointByVector(double _x, double _y) {
	this->x = x + _x;
	this->y = y + _y;
}


double point::getX() const {
	return this->x;
}

double point::getY() const {
	return this->y;
}

std::string point::getCoordinates(std::string _point_name) const {
	return _point_name + "(" + 
		std::to_string(x) + "," +
		std::to_string(y) + ") ";
}

double point::distanceBetweenPoints(point _other) const {
	return sqrt(
		pow((_other.getX() - this->x), 2) +
		pow((_other.getY() - this->y), 2)
	);
}

bool point::operator==(point _other) const {
	return x == _other.x && y == _other.y;
}
