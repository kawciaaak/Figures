#include "..\figures\segment\segment.h"
#include "..\figures\right_triangle\right_triangle.h"
#include <memory>
#include <iostream>

class Collection
{
private:
    std::vector<std::unique_ptr<IFigure>> figures_;

public:
    Collection() = default;
    ~Collection() = default;

    Point InitPoint();
    void AddFigure();
    void AddSegment();
    void AddTriangle();

    bool ArePointsCollinear(const Point &first_point, const Point &second_point, const Point &third_point) const;
    bool IsRightTriangle(const Point &first_point, const Point &second_point, const Point &third_point) const;

    void displayAllFigures() const;
    void displaySegments(int &choice);
    void displayTriangles(int &choice);

    void chooseFigureIndex(int &userChoice);
    void moveFigure();
    void rotateFigure();
    void calculateDistance();

    void ClearScreen();
    Point verifyDifferentPoint(const Point &first_point);
    bool arePointsValid(const Point &first_point, const Point &second_point, const Point &third_point);
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
    void menu(int &choice);
    void inputPointCoordinates(double &xCoordinate, double &yCoordinate);
    void inputIndex(int &userChoice);
    void inputVector(double &xVector, double &yVector);
    void inputAngle(double &angle);

    template <typename T>
    void handleInputError(T &input, const std::string &errorMessage);
};