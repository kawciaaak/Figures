#pragma once
#include "Segment.h"
#include "RightTriangle.h"
#include <memory>

class Collection
{
private:
    std::vector<std::unique_ptr<Figure>> figures;

public:
    Collection() = default;
    ~Collection() = default;

    Point createPoint();

    bool arePointsCollinear(const Point& firstPoint, const Point& secondPoint, const Point& thirdPoint) const;
    bool isRightTriangle(const Point& firstPoint, const Point& secondPoint, const Point& thirdPoint) const;
    void addFigure();
    void addSegment();
    void addTriangle();
    void displayAllFigures() const;
    void displaySegments(int& choice);
    void displayTriangles(int& choice);
    void chooseFigureIndex(int& userChoice);
    void moveFigure();
    void rotateFigure();
    void calculateDistance();

    void clearScreen();
    Point verifyDifferentPoint(const Point& firstPoint);
    bool arePointsValid(const Point& firstPoint, const Point& secondPoint, const Point& thirdPoint);
    void rotate();
    void distance();
    void length();
    void pointOnSegment();
    void parallel();
    void perpendicular();
    void intersection();
    void areaAndPerimeter();
    void disconnected();
    void hypotenuse();
    void mainApp();
    void menu(int& choice);
    void inputPointCoordinates(double& xCoordinate, double& yCoordinate);
    void inputIndex(int& userChoice);
    void inputVector(double& xVector, double& yVector);
    void inputAngle(double& angle);

    template <typename T>
    void handleInputError(T& input, const std::string& errorMessage);

};