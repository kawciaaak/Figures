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

    void navigateMenu(int& userChoice);
    void addFigure();
    void addSegment();
    void addTriangle();
    void moveFigure();
    void rotateFigure();
    void calculateLength();
    void checkParallel();
    void checkPerpendicular();
    void findIntersection();
    void calculateAreaAndPerimeter();
    void calculateDistance();
    void checkDisconnected();
    void calculateHypotenuse();
    void runApplication();
    void displayAllFigures() const;
    void displaySegments(int& userChoice);
    void displayTriangles(int& userChoice);
    void pickFigure(int& userChoice);
    void checkPointOnSegment() const;

    Point createPoint();
    bool checkIfCollinear(Point firstPoint, Point secondPoint, Point thirdPoint) const;
    bool checkIfRight(Point firstPoint, Point secondPoint, Point thirdPoint) const;
    void handleInputError(double& input, const std::string& errorMessage);
    void clearScreen();
    void showError(const std::string& errorMessage);
    Point verifyPoint(Point firstPoint);
    bool checkPointsValidity(Point firstPoint, Point secondPoint, Point thirdPoint);
    void addTriangleToFigures(Point firstPoint, Point secondPoint, Point thirdPoint);
    void inputPointCoordinates(double& x, double& y);
    void inputIndex(int& userChoice);
    void inputVector(double& x, double& y);
    void inputAngle(double& angle);
};
