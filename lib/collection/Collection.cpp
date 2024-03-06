#include "collection.h"

Point Collection::InitPoint()
{
    double x_coordinate = 0;
    double y_coordinate = 0;
    std::cout << "Enter the coordinates of the point:" << std::endl
              << "x = ";
    std::cin >> x_coordinate;
    handleInputError(x_coordinate, "Error. Please enter x coordinate again:");
    std::cout << std::endl
              << "y = ";
    std::cin >> y_coordinate;
    handleInputError(y_coordinate, "Error. Please enter y coordinate again:");
    ClearScreen();
    return Point(x_coordinate, y_coordinate);
}

bool Collection::ArePointsCollinear(const Point &first_point, const Point &second_point, const Point &third_point) const
{
    return (first_point.GetXCoordinate() - second_point.GetYCoordinate()) *
               (first_point.GetXCoordinate() - third_point.GetXCoordinate()) ==
           (first_point.GetYCoordinate() - third_point.GetYCoordinate()) *
               (first_point.GetXCoordinate() - second_point.GetXCoordinate());
}

bool Collection::IsRightTriangle(const Point &first_point, const Point &second_point, const Point &third_point) const
{
    std::vector<Segment> triangle_sides;
    std::vector<double> sides;

    triangle_sides.push_back(Segment(first_point, second_point));
    triangle_sides.push_back(Segment(second_point, third_point));
    triangle_sides.push_back(Segment(third_point, first_point));

    for (const auto &triangle_side : triangle_sides)
    {
        sides.push_back(triangle_side.GetLength());
    }
    std::sort(sides.begin(), sides.end());

    return (std::pow(sides[0], 2) + std::pow(sides[1], 2)) == std::pow(sides[2], 2);
}

void Collection::  AddFigure()
{
    int user_choice = 0;
    std::cout << "[1] Segment" << std::endl
              << "[2] Triangle" << std::endl
              << "Next step : ";
    std::cin >> user_choice;
    switch (user_choice)
    {
    case 1:
        AddSegment();
        break;
    case 2:
        AddTriangle();
        break;
    default:
        std::cout << "Error. Try again";
        ClearScreen();
        break;
    }
}

void Collection::AddSegment()
{
    Point first_point = InitPoint();
    Point second_point = InitPoint();

    while (first_point.GetXCoordinate() == second_point.GetXCoordinate() && first_point.GetYCoordinate() == second_point.GetYCoordinate())
    {
        std::cout << "Points must differ from each other" << std::endl
                  << "Try again : ";
        second_point = InitPoint();
    }

    figures_.push_back(std::make_unique<Segment>(first_point, second_point));
    std::cout << "Segment added" << std::endl;
}

void Collection::AddTriangle()
{
    Point firstPoint = createPoint();
    Point secondPoint = verifyDifferentPoint(firstPoint);
    Point thirdPoint;

    bool isPointValid = false;
    while (!isPointValid)
    {
        thirdPoint = createPoint();
        if (arePointsValid(firstPoint, secondPoint, thirdPoint))
        {
            isPointValid = true;
        }
    }

    if (isRightTriangle(firstPoint, secondPoint, thirdPoint))
    {
        figures.push_back(std::make_unique<RightTriangle>(firstPoint, secondPoint, thirdPoint));
        std::cout << "Right Triangle added" << std::endl;
    }
    else
    {
        figures.push_back(std::make_unique<Triangle>(firstPoint, secondPoint, thirdPoint));
        std::cout << "Triangle added" << std::endl;
    }
}

void Collection::displayAllFigures() const
{
    int figureCounter = 1;
    for (const auto &figure : figures)
    {
        std::cout << "[" << figureCounter << "] " << figure->getObjectName() << " " << figure->getObjectCoordinate() << std::endl;
        figureCounter++;
    }
}

void Collection::displaySegments(int &choice)
{
    int i = 1;
    for (const auto &figure : figures)
    {
        if (auto segment = dynamic_cast<RightTriangle *>(figure.get()))
        {
            std::cout << "[" << i << "]" << segment->getObjectName() << " " << segment->getObjectCoordinate() << std::endl;
        }
        i++;
    }
    inputIndex(choice);
}

void Collection::displayTriangles(int &choice)
{
    int i = 1;
    for (const auto &figure : figures)
    {
        if (auto rightTriangle = dynamic_cast<RightTriangle *>(figure.get()))
        {
            std::cout << "[" << i << "]" << rightTriangle->getObjectName() << " " << rightTriangle->getObjectCoordinate() << std::endl;
        }
        else
        {
            auto triangle = dynamic_cast<Triangle *>(figure.get());
            std::cout << "[" << i << "]" << triangle->getObjectName() << " " << triangle->getObjectCoordinate() << std::endl;
        }
        i++;
    }
    inputIndex(choice);
}

void Collection::chooseFigureIndex(int &userChoice)
{
    displayAllFigures();
    std::cout << "Choose a figure : ";
    std::cin >> userChoice;
    handleInputError(userChoice, "Error. Enter the index again:");
}

void Collection::moveFigure()
{
    int userChoice = 0;
    double x = 0;
    double y = 0;
    chooseFigureIndex(userChoice);
    std::cout << std::endl
              << "Enter the vector : x = ";
    std::cin >> x;
    handleInputError(x, "Error. Enter x coordinate again:");
    std::cout << std::endl
              << "y=";
    std::cin >> y;
    handleInputError(y, "Error. Enter y coordinate again:");
    figures[userChoice]->moveByVector(x, y);
}

void Collection::rotateFigure()
{
    int userChoice = 0;
    double x = 0;
    double y = 0;
    double angle = 0;
    chooseFigureIndex(userChoice);
    std::cout << std::endl
              << "Enter the vector : x = ";
    std::cin >> x;
    handleInputError(x, "Error. Enter x coordinate again:");
    std::cout << std::endl
              << "y=";
    std::cin >> y;
    handleInputError(y, "Error. Enter y coordinate again:");
    std::cout << std::endl
              << "Enter angle (in degrees):";
    std::cin >> angle;
    handleInputError(angle, "Error. Enter angle again:");
    figures[userChoice]->rotateAroundPoint(x, y, angle);
}

void Collection::calculateDistance()
{
    Point firstPoint = createPoint();
    Point secondPoint = createPoint();
    std::cout << "The distance between points is " << firstPoint.distanceTo(secondPoint) << std::endl;
}

template <typename T>
void Collection::handleInputError(T &input, const std::string &errorMessage)
{
    while (std::cin.fail())
    {
        std::cout << errorMessage;
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cin >> input;
    }
}

void Collection::clearScreen()
{
    system("cls");
}

Point Collection::verifyDifferentPoint(const Point &firstPoint)
{
    Point secondPoint = createPoint();
    while (firstPoint.getX() == secondPoint.getX() && firstPoint.getY() == secondPoint.getY())
    {
        std::cout << "Points must differ from each other\nTry again: ";
        secondPoint = createPoint();
    }
    return secondPoint;
}

bool Collection::arePointsValid(const Point &firstPoint, const Point &secondPoint, const Point &thirdPoint)
{
    if (
        (firstPoint.getX() == secondPoint.getX() && firstPoint.getY() == secondPoint.getY()) || (secondPoint.getX() == thirdPoint.getX() && secondPoint.getY() == thirdPoint.getY()))
    {
        std::cout << "Points must differ from each other" << std::endl
                  << "Try again : ";
    }
    else if (!arePointsCollinear(firstPoint, secondPoint, thirdPoint))
    {
        std::cout << "Points cannot be collinear\nTry again: ";
    }
    else
    {
        return true;
    }
    return false;
}

void Collection::rotate()
{
    int choice = 0;
    chooseFigureIndex(choice);
    double x = 0;
    double y = 0;
    double angle = 0;
    std::cout << std::endl
              << "Enter the vector: x=";
    std::cin >> x;
    handleInputError(x, "Error. Enter x coordinate again:");
    std::cout << std::endl
              << "y=";
    std::cin >> y;
    handleInputError(y, "Error. Enter y coordinate again:");
    std::cout << std::endl
              << "Enter angle (in degrees):";
    std::cin >> angle;
    handleInputError(angle, "Error. Enter angle again:");
    figures[choice]->rotateAroundPoint(x, y, angle);
}

void Collection::distance()
{
    Point p1 = createPoint();
    Point p2 = createPoint();
    std::cout << "The distance between points is " << p1.distanceTo(p2) << std::endl;
}

void Collection::length()
{
    int choice = 0;
    displaySegments(choice);
    if (auto segment = dynamic_cast<Segment *>(figures[choice].get()))
    {
        std::cout << "The length of the segment is " << segment->getLength() << std::endl;
    }
}

void Collection::pointOnSegment()
{
    double x, y = 0;
    int choice = 0;
    std::cout << "Enter the coordinates of the point." << std::endl
              << "x = ";
    std::cin >> x;
    handleInputError(x, "Error. Enter x coordinate again:");
    std::cout << std::endl
              << "y=";
    std::cin >> y;
    handleInputError(y, "Error. Enter y coordinate again:");
    std::cout << std::endl;
    Point point(x, y);
    displaySegments(choice);
    if (auto segment = dynamic_cast<Segment *>(figures[choice].get()))
    {
        if (segment->isPointOnSegment(point))
        {
            std::cout << "The point is on the segment" << std::endl;
        }
        else
        {
            std::cout << "The point is not on the segment" << std::endl;
        }
    }
}

void Collection::parallel()
{
    int choiceFirst = 0;
    int choiceSecond = 0;
    displaySegments(choiceFirst);
    displaySegments(choiceSecond);
    while (choiceFirst == choiceSecond)
    {
        std::cout << "You cannot choose the same segment." << std::endl;
        displaySegments(choiceSecond);
    }
    if (auto firstSegment = dynamic_cast<Segment *>(figures[choiceFirst].get()))
    {
        if (auto secondSegment = dynamic_cast<Segment *>(figures[choiceSecond].get()))
        {
            Segment segment = *secondSegment;
            if (firstSegment->areSegmentsParallel(segment))
            {
                std::cout << "The segments are parallel" << std::endl;
            }
            else
            {
                std::cout << "The segments are not parallel" << std::endl;
            }
        }
    }
}

void Collection::perpendicular()
{
    int choiceFirst = 0;
    int choiceSecond = 0;
    displaySegments(choiceFirst);
    displaySegments(choiceSecond);
    while (choiceFirst == choiceSecond)
    {
        std::cout << "You cannot choose the same segment." << std::endl;
        displaySegments(choiceSecond);
    }
    if (auto firstSegment = dynamic_cast<Segment *>(figures[choiceFirst].get()))
    {
        if (auto secondSegment = dynamic_cast<Segment *>(figures[choiceSecond].get()))
        {
            Segment segment = *secondSegment;
            if (firstSegment->areSegmentsPerpendicular(segment))
            {
                std::cout << "The segments are perpendicular" << std::endl;
            }
            else
            {
                std::cout << "The segments are not perpendicular" << std::endl;
            }
        }
    }
}

void Collection::intersection()
{
    int choiceFirst = 0;
    int choiceSecond = 0;
    displaySegments(choiceFirst);
    displaySegments(choiceSecond);
    while (choiceFirst == choiceSecond)
    {
        std::cout << "You cannot choose the same segment." << std::endl;
        displaySegments(choiceSecond);
    }
    if (auto firstSegment = dynamic_cast<Segment *>(figures[choiceFirst].get()))
    {
        if (auto secondSegment = dynamic_cast<Segment *>(figures[choiceSecond].get()))
        {
            Segment segment = *secondSegment;
            firstSegment->getIntersectionPoint(segment);
        }
    }
}

void Collection::areaAndPerimeter()
{
    int choice = 0;
    displayTriangles(choice);
    if (auto triangle = dynamic_cast<Triangle *>(figures[choice].get()))
    {
        std::cout << "Area: " << triangle->area() << "    Perimeter: " << triangle->perimeter() << std::endl;
    }
}

void Collection::disconnected()
{
    int choiceFirst = 0;
    int choiceSecond = 0;
    displayTriangles(choiceFirst);
    displayTriangles(choiceSecond);
    while (choiceFirst == choiceSecond)
    {
        std::cout << "You cannot choose the same triangle." << std::endl;
        displayTriangles(choiceSecond);
    }
    if (auto firstTriangle = dynamic_cast<Triangle *>(figures[choiceFirst].get()))
    {
        if (auto secondTriangle = dynamic_cast<Triangle *>(figures[choiceSecond].get()))
        {
            Triangle triangle = *secondTriangle;
            if (firstTriangle->areDisconnected(triangle))
            {
                std::cout << "The triangles are disconnected" << std::endl;
            }
            else
            {
                std::cout << "The triangles are not disconnected" << std::endl;
            }
        }
    }
}

void Collection::hypotenuse()
{
    int index = 0;
    int choice = 0;
    int flag = 0;
    for (int i = 0; i < figures.size(); i++)
    {
        if (auto rightTriangle = dynamic_cast<RightTriangle *>(figures[i].get()))
        {
            std::cout << i + 1 << ". Right Triangle " << rightTriangle->getObjectCoordinate() << std::endl;
            flag++;
        }
    }
    if (flag > 0)
    {
        std::cout << "Choose: ";
        std::cin >> choice;
        inputIndex(choice);
        if (auto rightTriangle = dynamic_cast<RightTriangle *>(figures[choice - 1].get()))
        {
            std::cout << "The length of the hypotenuse is: " << rightTriangle->getHypotenuseLength() << std::endl;
        }
    }
    else
    {
        std::cout << "No right triangles found" << std::endl;
    }
}

void Collection::mainApp()
{
    int choice = 0;
    bool loopOn = true;
    while (loopOn)
    {
        menu(choice);
        switch (choice)
        {
        case 1:
            addFigure();
            break;
        case 2:
            displayAllFigures();
            break;
        case 3:
            moveFigure();
            break;
        case 4:
            rotateFigure();
            break;
        case 5:
            calculateDistance();
            break;
        case 6:
            length();
            break;
        case 7:
            pointOnSegment();
            break;
        case 8:
            parallel();
            break;
        case 9:
            perpendicular();
            break;
        case 10:
            intersection();
            break;
        case 11:
            areaAndPerimeter();
            break;
        case 12:
            disconnected();
            break;
        case 13:
            hypotenuse();
            break;
        case 0:
            loopOn = false;
            break;
        default:
            std::cout << "Error. Try again";
            choice = 0;
            break;
        }
        std::string click;
        std::cout << "\nPress any key to continue ";
        std::cin >> click;
        clearScreen();
    }
}

void Collection::menu(int &choice)
{
    std::cout << "MENU" << std::endl;
    std::cout << "[1] Add figure" << std::endl;
    std::cout << "[2] Display all figures" << std::endl;
    std::cout << "[3] Move figure" << std::endl;
    std::cout << "[4] Rotate figure" << std::endl;
    std::cout << "[5] Calculate distance" << std::endl;
    std::cout << "[6] Calculate length" << std::endl;
    std::cout << "[7] Check if point is on segment" << std::endl;
    std::cout << "[8] Check if segments are parallel" << std::endl;
    std::cout << "[9] Check if segments are perpendicular" << std::endl;
    std::cout << "[10] Calculate intersection of segments" << std::endl;
    std::cout << "[11] Calculate area and perimeter of triangle" << std::endl;
    std::cout << "[12] Check if triangles are disconnected" << std::endl;
    std::cout << "[13] Calculate hypotenuse of right triangle" << std::endl;
    std::cout << "[0] Exit" << std::endl;
    std::cout << "Next step: ";
    std::cin >> choice;
    handleInputError(choice, "Error. Enter the choice again:");
}

void Collection::inputPointCoordinates(double &xCoordinate, double &yCoordinate)
{
    std::cout << "Enter the coordinates of the point:\n x= ";
    std::cin >> xCoordinate;
    handleInputError(xCoordinate, "Error. Please enter x coordinate again:");
    std::cout << "\n y= ";
    std::cin >> yCoordinate;
    handleInputError(yCoordinate, "Error. Please enter y coordinate again:");
    clearScreen();
}

void Collection::inputIndex(int &userChoice)
{
    std::cout << "Choose a figure : ";
    std::cin >> userChoice;
    handleInputError(userChoice, "Error. Enter the index again:");
}

void Collection::inputVector(double &xVector, double &yVector)
{
    std::cout << "\nEnter the vector: x=";
    std::cin >> xVector;
    handleInputError(xVector, "Error. Enter x coordinate again:");
    std::cout << "y=";
    std::cin >> yVector;
    handleInputError(yVector, "Error. Enter y coordinate again:");
}

void Collection::inputAngle(double &angle)
{
    std::cout << "Enter angle (in degrees):";
    std::cin >> angle;
    handleInputError(angle, "Error. Enter angle again:");
}
