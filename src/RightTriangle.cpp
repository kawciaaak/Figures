#include "include/RightTriangle.h"

RightTriangle::RightTriangle(Point pointA, Point pointB, Point pointC) {
    points.push_back(pointA);
    points.push_back(pointB);
    points.push_back(pointC);
}

double RightTriangle::getHypotenuseLength() const {
    std::vector<Segment> triangleSides;
    std::vector<double> sideLengths;
    int nextIndex = 0;

    // Construct all sides of the triangle
    for (int i = 0; i < 3; i++) {
        nextIndex = (i != 2) ? i + 1 : 0;
        triangleSides.push_back(Segment(points[i], points[nextIndex]));
    }

    // Calculate and store lengths of the sides
    for (const auto& side : triangleSides) {
        sideLengths.push_back(side.getLength());
    }

    // Return the length of the longest side (hypotenuse)
    return *std::max_element(sideLengths.begin(), sideLengths.end());
}

std::string RightTriangle::getObjectName() const {
    return "Right triangle";
}
