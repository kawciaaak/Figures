#pragma once
#include "triangle.h"
#include <algorithm>
class right_triangle : public triangle
{
public:
	right_triangle() = default;
	right_triangle(point _a, point _b, point _c);
	double getHypotenuse();
	std::string getObjectName() const override;
};

