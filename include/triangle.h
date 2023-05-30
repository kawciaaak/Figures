#pragma once
#include "figure.h"
#include "segment.h"
class triangle : public figure
{
public:
	triangle() = default;
	triangle(point _a, point _b, point _c);
	~triangle() = default;

	std::string getObjectName()const override;
	std::string getObjectCoordinate()const  override;

	double perimeter();
	double area();

	bool areDisconnected(triangle _other);
};

