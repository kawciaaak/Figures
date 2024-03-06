#ifndef FIGURES_LIB_COLLECTION_COLLECTION_H
#define FIGURES_LIB_COLLECTION_COLLECTION_H

#include "..\figures\segment\segment.h"
#include "..\figures\right_triangle\right_triangle.h"
#include <memory>
#include <iostream>

class Collection
{
public:
    Collection() = default;
    ~Collection() = default;

    // Initialization
    Point InitPoint();

    // Figure management
    void AddFigure();
    void AddSegment();
    void AddTriangle();

    // Geometric calculations
    bool ArePointsCollinear(const Point &first_point, const Point &second_point, const Point &third_point) const;
    bool IsRightTriangle(const Point &first_point, const Point &second_point, const Point &third_point) const;

    // Display functions
    void DisplayAllFigures() const;
    void DisplaySegments(int &choice);
    void DisplayTriangles(int &choice);

    // Figure manipulation
    void ChooseFigureIndex(int &user_choice);
    void MoveFigure();
    void RotateFigure();
    void CalculateDistance();

    // Utility functions
    void ClearScreen();
    Point VerifyDifferentPoint(const Point &first_point);
    bool ArePointsValid(const Point &first_point, const Point &second_point, const Point &third_point);
    void Rotate();
    void Distance();
    void Length();
    void PointOnSegment();
    void Parallel();
    void Perpendicular();
    void Intersection();
    void AreaAndPerimeter();
    void Disconnected();
    void Hypotenuse();
    void MainApp();
    void Menu(int &choice);
    void InputPointCoordinates(double &x_coordinate, double &y_coordinate);
    void InputIndex(int &user_choice);
    void InputVector(double &x_vector, double &y_vector);
    void InputAngle(double &angle);

    template <typename T>
    void HandleInputError(T &input, const std::string &error_message);

private:
    std::vector<std::unique_ptr<IFigure>> figures_;
};

#endif // FIGURES_LIB_COLLECTION_COLLECTION_H
