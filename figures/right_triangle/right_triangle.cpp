#include "right_triangle.h"

RightTriangle::RightTriangle(const Point& pointA, const Point& pointB, const Point& pointC) {
    points_.push_back(pointA);
    points_.push_back(pointB);
    points_.push_back(pointC);
}

double RightTriangle::GetHypotenuseLength() const {
    std::vector<Segment> triangleSides;
    std::vector<double> sideLengths;
    int nextIndex = 0;

    // Construct all sides of the triangle
    for (int i = 0; i < 3; i++) {
        if (i != 2) nextIndex = i + 1;
        else nextIndex = 0;
        triangleSides.push_back(Segment(points_[i], points_[nextIndex]));
    }

    // Calculate and store lengths of the sides
    for (const auto& side : triangleSides) {
        sideLengths.push_back(side.getLength());
    }

    // Return the length of the longest side (hypotenuse)
    return *std::max_element(sideLengths.begin(), sideLengths.end());
}

std::string RightTriangle::GetObjectName() const {
    return "Right triangle";
}
