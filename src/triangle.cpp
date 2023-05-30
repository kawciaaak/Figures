#include "include/triangle.h"

triangle::triangle(point _a, point _b, point _c) {
	points.push_back(_a);
	points.push_back(_b);
	points.push_back(_c);
	points.resize(3);
}

std::string triangle::getObjectName() const {
	return "trojkat";
}

std::string triangle::getObjectCoordinate() const {
	return points[0].getCoordinates("A") +
		points[1].getCoordinates("B") +
		points[2].getCoordinates("C");
}

double triangle::perimeter() {
	return points[0].distanceBetweenPoints(points[1]) +
		points[1].distanceBetweenPoints(points[2]) +
		points[2].distanceBetweenPoints(points[0]);
}

double triangle::area() {
	auto p = this->perimeter() / 2;
	return sqrt(p *
		(p - points[0].distanceBetweenPoints(points[1])) *
		(p - points[1].distanceBetweenPoints(points[2])) *
		(p - points[2].distanceBetweenPoints(points[0]))
	);
}

bool triangle::areDisconnected(triangle _other) {
	double this_a = 0;
	double this_b = 0;
	double other_a = 0;
	double other_b = 0;

	double x = 0;
	double y = 0;

	auto j = 0;
	auto k = 0;

	for (auto i = 0; i < 3; i++) {
		(i != 2) ? j = i + 1 : j = 0;
		createLinearFunction(this->points[i], this->points[j], &this_a, &this_b);
		for (auto m = 0; m < 3; m++) {
			(m != 2) ? k = m + 1 : k = 0;
			createLinearFunction(_other.points[m], _other.points[k], &other_a, &other_b);
			if (this_a != other_b) {
				x = (other_b - this_b) / (this_a - other_a);
				y = this_a * x + this_b;
				
				auto min_x = fmin(this->points[m].getX(), this->points[k].getX());
				auto min_y = fmin(this->points[m].getY(), this->points[k].getY());
				auto max_x = fmax(this->points[m].getX(), this->points[k].getX());
				auto max_y = fmax(this->points[m].getY(), this->points[k].getY());

				auto other_min_x = fmin(_other.points[m].getX(), _other.points[k].getX());
				auto other_min_y = fmin(_other.points[m].getY(), _other.points[k].getY());
				auto other_max_x = fmax(_other.points[m].getX(), _other.points[k].getX());
				auto other_max_y = fmax(_other.points[m].getY(), _other.points[k].getY());

				if (x >= min_x && x <= max_x && y >= min_y && y <= max_y &&
					x >= other_min_x && x <= other_max_x && y >= other_min_y && y <= other_max_y) {
					return false;
				}
			}
		}
	}
	return true;
}
