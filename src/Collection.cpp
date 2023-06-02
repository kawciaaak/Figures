#include "include/Collection.h"

Point Collection::createPoint() {
    double x = 0;
    double y = 0;
    std::cout << "Enter the coordinates of the point:\n x= ";
    std::cin >> x;
    handleInputError(x, "Error. Please enter x coordinate again:");
    std::cout << "\n y= ";
    std::cin >> y;
    handleInputError(y, "Error. Please enter y coordinate again:");
    clearScreen();
    return Point(x, y);
}

bool Collection::arePointsCollinear(const Point& firstPoint, const Point& secondPoint, const Point& thirdPoint) const {
    return (firstPoint.getY() - secondPoint.getY()) *
        (firstPoint.getX() - thirdPoint.getX()) ==
        (firstPoint.getY() - thirdPoint.getY()) *
        (firstPoint.getX() - secondPoint.getX());
}

bool Collection::isRightTriangle(const Point& firstPoint, const Point& secondPoint, const Point& thirdPoint) const {
    std::vector<Segment> triangleSides;
    std::vector<double> sides;

    triangleSides.push_back(Segment(firstPoint, secondPoint));
    triangleSides.push_back(Segment(secondPoint, thirdPoint));
    triangleSides.push_back(Segment(thirdPoint, firstPoint));

    for (const auto& side : triangleSides) {
        sides.push_back(side.getLength());
    }
    std::sort(sides.begin(), sides.end());

    return std::pow(sides[0], 2) + std::pow(sides[1], 2) == std::pow(sides[2], 2);
}

void Collection::addFigure() {
    int userChoice = 0;
    std::cout << "[1] Segment\n[2] Triangle\nNext step: ";
    std::cin >> userChoice;
    switch (userChoice) {
    case 1:
        addSegment();
        break;
    case 2:
        addTriangle();
        break;
    default:
        showError("Error. Try again");
        clearScreen();
        break;
    }
}

void Collection::addSegment() {
    Point firstPoint = createPoint();
    Point secondPoint = createPoint();

    while (firstPoint.getX() == secondPoint.getX() && firstPoint.getY() == secondPoint.getY()) {
        showError("Points must differ from each other\nTry again: ");
        secondPoint = createPoint();
    }

    figures.push_back(std::make_unique<Segment>(firstPoint, secondPoint));
    std::cout << "Segment added" << std::endl;
}

void Collection::addTriangle() {
    Point firstPoint = createPoint();
    Point secondPoint = verifyDifferentPoint(firstPoint);
    Point thirdPoint;

    bool isPointValid = false;
    while (!isPointValid) {
        thirdPoint = createPoint();
        if (arePointsValid(firstPoint, secondPoint, thirdPoint)) {
            isPointValid = true;
        }
    }

    addTriangleToFigures(firstPoint, secondPoint, thirdPoint);
}

void Collection::displayAllFigures() const {
    int figureCounter = 1;
    for (const auto& figure : figures) {
        std::cout << "[" << figureCounter << "] " << figure->getObjectName() << " " << figure->getObjectCoordinate() << std::endl;
        figureCounter++;
    }
}

void Collection::chooseFigureIndex(int& userChoice) {
    displayAllFigures();
    std::cout << "Choose a figure : ";
    std::cin >> userChoice;
    handleInputError(userChoice, "Error. Enter the index again:");
}

void Collection::moveFigure() {
    int userChoice = 0;
    double x = 0;
    double y = 0;
    chooseFigureIndex(userChoice);
    std::cout << "\nEnter the vector: x=";
    std::cin >> x;
    handleInputError(x, "Error. Enter x coordinate again:");
    std::cout << "y=";
    std::cin >> y;
    handleInputError(y, "Error. Enter y coordinate again:");
    figures[userChoice]->moveByVector(x, y);
}

void Collection::rotateFigure() {
    int userChoice = 0;
    double x = 0;
    double y = 0;
    double angle = 0;
    chooseFigureIndex(userChoice);
    std::cout << "\nEnter the vector: x=";
    std::cin >> x;
    handleInputError(x, "Error. Enter x coordinate again:");
    std::cout << "y=";
    std::cin >> y;
    handleInputError(y, "Error. Enter y coordinate again:");
    std::cout << "Enter angle (in degrees):";
    std::cin >> angle;
    handleInputError(angle, "Error. Enter angle again:");
    figures[userChoice]->rotateAroundPoint(x, y, angle);
}

void Collection::calculateDistance() {
    Point firstPoint = createPoint();
    Point secondPoint = createPoint();
    std::cout << "The distance between points is " << firstPoint.distanceBetweenPoints(secondPoint) << std::endl;
}

void Collection::handleInputError(double& input, const std::string& errorMessage) {
    while (std::cin.fail()) {
        std::cout << errorMessage;
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cin >> input;
    }
}

void Collection::clearScreen() {
    system("cls");
}

void Collection::showError(const std::string& errorMessage) {
    std::cout << errorMessage << std::endl;
    userChoice = 0;
}

Point Collection::verifyDifferentPoint(const Point& firstPoint) {
    Point secondPoint = createPoint();
    while (firstPoint.getX() == secondPoint.getX() && firstPoint.getY() == secondPoint.getY()) {
        showError("Points must differ from each other\nTry again: ");
        secondPoint = createPoint();
    }
    return secondPoint;
}

bool Collection::arePointsValid(const Point& firstPoint, const Point& secondPoint, const Point& thirdPoint) {
    if (
        (firstPoint.getX() == secondPoint.getX() && firstPoint.getY() == secondPoint.getY())
        || (secondPoint.getX() == thirdPoint.getX() && secondPoint.getY() == thirdPoint.getY())) {
        showError("Points must differ from each other\nTry again: ");
    }
    else if (!arePointsCollinear(firstPoint, secondPoint, thirdPoint)) {
        showError("Points cannot be collinear\nTry again: ");
    }
    else {
        return true;
    }
    return false;
}

void Collection::rotate() {
    int choice = 0;
    chooseFigureIndex(choice);
    double x = 0;
    double y = 0;
    double angle = 0;
    std::cout << std::endl << "Enter the vector: x=";
    std::cin >> x;
    handleInputError(x, "Error. Enter x coordinate again:");
    std::cout << "y=";
    std::cin >> y;
    handleInputError(y, "Error. Enter y coordinate again:");
    std::cout << "Enter angle (in degrees):";
    std::cin >> angle;
    handleInputError(angle, "Error. Enter angle again:");
    figures[choice]->rotateAroundPoint(x, y, angle);
}

void Collection::distance() {
    Point p1 = createPoint();
    Point p2 = createPoint();
    std::cout << "The distance between points is " << p1.distanceBetweenPoints(p2) << std::endl;
}

void Collection::length() {
    int choice = 0;
    displaySegments(choice);
    if (auto segment = dynamic_cast<Segment*>(figures[choice].get())) {
        std::cout << "The length of the segment is " << segment->getLength() << std::endl;
    }
}

void Collection::pointOnSegment() const {
    double x, y = 0;
    int choice = 0;
    std::cout << "Enter the coordinates of the point. x=";
    std::cin >> x;
    handleInputError(x, "Error. Enter x coordinate again:");
    std::cout << "y=";
    std::cin >> y;
    handleInputError(y, "Error. Enter y coordinate again:");
    std::cout << std::endl;
    Point point(x, y);
    displaySegments(choice);
    if (auto segment = dynamic_cast<Segment*>(figures[choice].get())) {
        if (segment->isPointOnSegment(point)) {
            std::cout << "The point is on the segment" << std::endl;
        }
        else {
            std::cout << "The point is not on the segment" << std::endl;
        }
    }
}

void Collection::parallel() {
    int choiceFirst = 0;
    int choiceSecond = 0;
    displaySegments(choiceFirst);
    displaySegments(choiceSecond);
    while (choiceFirst == choiceSecond) {
        std::cout << "You cannot choose the same segment." << std::endl;
        displaySegments(choiceSecond);
    }
    if (auto firstSegment = dynamic_cast<Segment*>(figures[choiceFirst].get())) {
        if (auto secondSegment = dynamic_cast<Segment*>(figures[choiceSecond].get())) {
            Segment segment = *secondSegment;
            if (firstSegment->areParallel(segment)) {
                std::cout << "The segments are parallel" << std::endl;
            }
            else {
                std::cout << "The segments are not parallel" << std::endl;
            }
        }
    }
}

void Collection::perpendicular() {
    int choiceFirst = 0;
    int choiceSecond = 0;
    displaySegments(choiceFirst);
    displaySegments(choiceSecond);
    while (choiceFirst == choiceSecond) {
        std::cout << "You cannot choose the same segment." << std::endl;
        displaySegments(choiceSecond);
    }
    if (auto firstSegment = dynamic_cast<Segment*>(figures[choiceFirst].get())) {
        if (auto secondSegment = dynamic_cast<Segment*>(figures[choiceSecond].get())) {
            Segment segment = *secondSegment;
            if (firstSegment->arePerpendicular(segment)) {
                std::cout << "The segments are perpendicular" << std::endl;
            }
            else {
                std::cout << "The segments are not perpendicular" << std::endl;
            }
        }
    }
}

void Collection::intersection() {
    int choiceFirst = 0;
    int choiceSecond = 0;
    displaySegments(choiceFirst);
    displaySegments(choiceSecond);
    while (choiceFirst == choiceSecond) {
        std::cout << "You cannot choose the same segment." << std::endl;
        displaySegments(choiceSecond);
    }
    if (auto firstSegment = dynamic_cast<Segment*>(figures[choiceFirst].get())) {
        if (auto secondSegment = dynamic_cast<Segment*>(figures[choiceSecond].get())) {
            Segment segment = *secondSegment;
            firstSegment->getIntersectionPoint(segment);
        }
    }
}

void Collection::areaAndPerimeter() {
    int choice = 0;
    displayTriangles(choice);
    if (auto triangle = dynamic_cast<Triangle*>(figures[choice].get())) {
        std::cout << "Area: " << triangle->area() << "    Perimeter: " << triangle->perimeter() << std::endl;
    }
}

void Collection::disconnected() {
    int choiceFirst = 0;
    int choiceSecond = 0;
    displayTriangles(choiceFirst);
    displayTriangles(choiceSecond);
    while (choiceFirst == choiceSecond) {
        std::cout << "You cannot choose the same triangle." << std::endl;
        displayTriangles(choiceSecond);
    }
    if (auto firstTriangle = dynamic_cast<Triangle*>(figures[choiceFirst].get())) {
        if (auto secondTriangle = dynamic_cast<Triangle*>(figures[choiceSecond].get())) {
            Triangle triangle = *secondTriangle;
            if (firstTriangle->areDisconnected(triangle)) {
                std::cout << "The triangles are disconnected" << std::endl;
            }
            else {
                std::cout << "The triangles are not disconnected" << std::endl;
            }
        }
    }
}

void Collection::hypotenuse() {
    int index = 0;
    int choice = 0;
    int flag = 0;
    for (int i = 0; i < figures.size(); i++) {
        if (auto rightTriangle = dynamic_cast<RightTriangle*>(figures[i].get())) {
            std::cout << i + 1 << ". Right Triangle " << rightTriangle->getObjectCoordinate() << std::endl;
            flag++;
        }
    }
    if (flag > 0) {
        std::cout << "Choose: ";
        std::cin >> choice;
        handleInputError(choice, "Error. Enter the index again:");
        if (auto rightTriangle = dynamic_cast<RightTriangle*>(figures[choice - 1].get())) {
            std::cout << "The length of the hypotenuse is: " << rightTriangle->getHypotenuse() << std::endl;
        }
    }
    else {
        std::cout << "No right triangles found" << std::endl;
    }
}

void Collection::mainApp() {
    int choice = 0;
    bool loopOn = true;
    while (loopOn) {
        menu(choice);
        switch (choice) {
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
            showError("Error. Try again");
            choice = 0;
            break;
        }
        std::string click;
        std::cout << "\nPress any key to continue ";
        std::cin >> click;
        clearScreen();
    }
}

void Collection::menu(int& choice) {
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

double Collection::getDoubleInput(const std::string& prompt) {
    double value;
    std::cout << "\n" << prompt;
    std::cin >> value;
    while (std::cin.fail()) {
        std::cout << "Error. Enter the value again: ";
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cin >> value;
    }
    return value;
}

void Collection::inputPointCoordinates(double& x, double& y) {
    std::cout << "Enter the coordinates of the point:\n x= ";
    std::cin >> x;
    handleInputError(x, "Error. Please enter x coordinate again:");
    std::cout << "\n y= ";
    std::cin >> y;
    handleInputError(y, "Error. Please enter y coordinate again:");
    clearScreen();
}

void Collection::inputIndex(int& userChoice) {
    std::cout << "Choose a figure : ";
    std::cin >> userChoice;
    handleInputError(userChoice, "Error. Enter the index again:");
}

void Collection::inputVector(double& x, double& y) {
    std::cout << "\nEnter the vector: x=";
    std::cin >> x;
    handleInputError(x, "Error. Enter x coordinate again:");
    std::cout << "y=";
    std::cin >> y;
    handleInputError(y, "Error. Enter y coordinate again:");
}

void Collection::inputAngle(double& angle) {
    std::cout << "Enter angle (in degrees):";
    std::cin >> angle;
    handleInputError(angle, "Error. Enter angle again:");
}

