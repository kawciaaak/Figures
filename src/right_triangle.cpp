#include "include/right_triangle.h"

right_triangle::right_triangle(point _a, point _b, point _c) {
	points.clear();
	points.push_back(_a);
	points.push_back(_b);
	points.push_back(_c);
	points.resize(3);
}

double right_triangle::getHypotenuse() {
	std::vector<segment> triangleSides;
	std::vector<double> sides;
	auto j = 0;
	for (auto i = 0; i < 3; i++) {
		(i != 2) ? j++ : j = 0;
		triangleSides.push_back(segment(points[i], points[j]));
	}
	for (auto s : triangleSides) {
		sides.push_back(s.getLength());
	}
	return *std::max_element(sides.begin(),sides.end());
}

std::string right_triangle::getObjectName() const {
	return "trojkat prostokatny";
}