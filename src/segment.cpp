#include "include/segment.h"

segment::segment(point _a, point _b) {
	points.push_back(_a);
	points.push_back(_b);
	points.resize(2);
}

double segment::getLength() {
	return points[0].distanceBetweenPoints(points[1]);
}

std::string segment::getObjectName() const {
	return "odcinek";
}

std::string segment::getObjectCoordinate() const {
	return points[0].getCoordinates("A") + 
		points[1].getCoordinates("B");
}


bool segment::isPointOnSegment(point _point) {
	double a = 0;
	double b = 0;
	createLinearFunction(points[0], points[1], &a, &b);
	if (isPointOnLinearFunction(_point, a, b)) {
		double min_x = fmin(points[0].getX(), points[1].getX());
		double max_x = fmax(points[0].getX(), points[1].getX());
		double min_y = fmin(points[0].getY(), points[1].getY());
		double max_y = fmax(points[0].getY(), points[1].getY());

		if (_point.getX() >= min_x && _point.getX() <= max_x &&
			_point.getY() >= min_y && _point.getY() <= max_y) {
			return true;
		}
	}
	return false;
}

bool segment::areParallel(segment _other) {
	double this_a = 0;
	double this_b = 0;
	double other_a = 0;
	double other_b = 0;

	createLinearFunction(this->points[0], this->points[1], &this_a, &this_b);
	createLinearFunction(_other.points[0], _other.points[1], &other_a, &other_b);

	if (std::abs(this_a - other_a) < 0.5) return true;
	else return false;
}

bool segment::arePerpendicular(segment _other) {
	double this_a = 0;
	double this_b = 0;
	double other_a = 0;
	double other_b = 0;

	createLinearFunction(this->points[0], this->points[1], &this_a, &this_b);
	createLinearFunction(_other.points[0], _other.points[1], &other_a, &other_b);

	if (this_a * other_a == -1) return true;
	else return false;
}

void segment::getIntersectionPoint(segment _other) {
	if (!this->areParallel(_other)) {
		double this_a = 0;
		double this_b = 0;
		double other_a = 0;
		double other_b = 0;

		createLinearFunction(this->points[0], this->points[1], &this_a, &this_b);
		createLinearFunction(_other.points[0], _other.points[1], &other_a, &other_b);


		auto x = (other_b - this_b) / (this_a - other_a);
		auto y = this_a * x + this_b;

		auto min_x = fmin(this->points[0].getX(), this->points[1].getX());
		auto min_y = fmin(this->points[0].getY(), this->points[1].getY());
		auto max_x = fmax(this->points[0].getX(), this->points[1].getX());
		auto max_y = fmax(this->points[0].getY(), this->points[1].getY());

		if (x >= min_x && x <= max_x && y >= min_y && y <= max_y) {
			point result = { x,y };
			std::cout << result.getCoordinates("Punkt przeciecia: ");
		}
		else {
			std::cout << "Brak punktu przeciecia ";
		}
	}
	else std::cout << "Brak punktu przeciecia - odcinki sa rownolegle" << std::endl;
}