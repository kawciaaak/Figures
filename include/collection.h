#pragma once
#include "segment.h"
#include "right_triangle.h"
#include <memory>
class collection
{
private:
	std::vector<std::unique_ptr<figure>> figures;
public:
	collection() = default;
	~collection();
	int test();

	void menu(int* _choice);
	void addFigure();
	void move();
	void rotate();
	void length();
	void parallel();
	void perpendicular();
	void intersection();
	void areaAndPerimeter();
	void distance();
	void disconnected();
	void hypotenuse();
	void mainApp();
	void displayFigures() const;
	void displaySegments(int* _choice) const;
	void displayTriangles(int* _choice) const;
	void pickFigure(int* _choice) const;
	void pointOnSegment() const;

	void checkPoints(std::vector<point>& _points);
	point createPoint();
	bool areCollinear(std::vector<point> _points);
	bool isRight(std::vector<point> _points);
};

