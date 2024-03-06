#include "Collection.h"

Point Collection::InitPoint()
{
    double x_coordinate = 0;
    double y_coordinate = 0;
    std::cout << "Enter the coordinates of the point:" << std::endl
              << "x = ";
    std::cin >> x_coordinate;
    HandleInputError(x_coordinate, "Error. Please enter x coordinate again:");
    std::cout << std::endl
              << "y = ";
    std::cin >> y_coordinate;
    HandleInputError(y_coordinate, "Error. Please enter y coordinate again:");
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

void Collection::AddFigure()
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
    Point first_point = InitPoint();
    Point second_point = VerifyDifferentPoint(first_point);
    Point third_point;

    bool is_point_valid = false;
    while (!is_point_valid)
    {
        third_point = InitPoint();
        if (ArePointsValid(first_point, second_point, third_point))
        {
            is_point_valid = true;
        }
    }

    if (IsRightTriangle(first_point, second_point, third_point))
    {
        figures_.push_back(std::make_unique<RightTriangle>(first_point, second_point, third_point));
        std::cout << "Right Triangle added" << std::endl;
    }
    else
    {
        figures_.push_back(std::make_unique<Triangle>(first_point, second_point, third_point));
        std::cout << "Triangle added" << std::endl;
    }
}

void Collection::DisplayAllFigures() const
{
    int figure_counter = 1;
    for (const auto &figure : figures_)
    {
        std::cout << "[" << figure_counter << "] " << figure->GetObjectName() << " " << figure->GetObjectCoordinate() << std::endl;
        figure_counter++;
    }
}

void Collection::DisplaySegments(int &choice)
{
    int i = 1;
    for (const auto &figure : figures_)
    {
        if (auto segment = dynamic_cast<RightTriangle *>(figure.get()))
        {
            std::cout << "[" << i << "]" << segment->GetObjectName() << " " << segment->GetObjectCoordinate() << std::endl;
        }
        i++;
    }
    InputIndex(choice);
}

void Collection::DisplayTriangles(int &choice)
{
    int i = 1;
    for (const auto &figure : figures_)
    {
        if (auto right_triangle = dynamic_cast<RightTriangle *>(figure.get()))
        {
            std::cout << "[" << i << "]" << right_triangle->GetObjectName() << " " << right_triangle->GetObjectCoordinate() << std::endl;
        }
        else
        {
            auto triangle = dynamic_cast<Triangle *>(figure.get());
            std::cout << "[" << i << "]" << triangle->GetObjectName() << " " << triangle->GetObjectCoordinate() << std::endl;
        }
        i++;
    }
    InputIndex(choice);
}

void Collection::ChooseFigureIndex(int &user_choice)
{
    DisplayAllFigures();
    std::cout << "Choose a figure : ";
    std::cin >> user_choice;
    HandleInputError(user_choice, "Error. Enter the index again:");
}

void Collection::MoveFigure()
{
    int user_choice = 0;
    double x = 0;
    double y = 0;
    ChooseFigureIndex(user_choice);
    std::cout << std::endl
              << "Enter the vector : x = ";
    std::cin >> x;
    HandleInputError(x, "Error. Enter x coordinate again:");
    std::cout << std::endl
              << "y=";
    std::cin >> y;
    HandleInputError(y, "Error. Enter y coordinate again:");
    figures_[user_choice]->MoveByVector(x, y);
}

void Collection::RotateFigure()
{
    int user_choice = 0;
    double x = 0;
    double y = 0;
    double angle = 0;
    ChooseFigureIndex(user_choice);
    std::cout << std::endl
              << "Enter the vector : x = ";
    std::cin >> x;
    HandleInputError(x, "Error. Enter x coordinate again:");
    std::cout << std::endl
              << "y=";
    std::cin >> y;
    HandleInputError(y, "Error. Enter y coordinate again:");
    std::cout << std::endl
              << "Enter angle (in degrees):";
    std::cin >> angle;
    HandleInputError(angle, "Error. Enter angle again:");
    figures_[user_choice]->RotateAroundPointCoordinates(x, y, angle);
}

void Collection::CalculateDistance()
{
    Point first_point = InitPoint();
    Point second_point = InitPoint();
    std::cout << "The distance between points is " << first_point.distanceTo(second_point) << std::endl;
}

template <typename T>
void Collection::HandleInputError(T &input, const std::string &error_message)
{
    while (std::cin.fail())
    {
        std::cout << error_message;
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cin >> input;
    }
}

void Collection::ClearScreen()
{
    system("cls");
}

Point Collection::VerifyDifferentPoint(const Point &first_point)
{
    Point second_point = InitPoint();
    while (first_point.GetXCoordinate() == second_point.GetXCoordinate() && first_point.GetYCoordinate() == second_point.GetYCoordinate())
    {
        std::cout << "Points must differ from each other\nTry again: ";
        second_point = InitPoint();
    }
    return second_point;
}

bool Collection::ArePointsValid(const Point &first_point, const Point &second_point, const Point &third_point)
{
    if (
        (first_point.GetXCoordinate() == second_point.GetXCoordinate() && first_point.GetYCoordinate() == second_point.GetYCoordinate()) || (second_point.GetXCoordinate() == third_point.GetXCoordinate() && second_point.GetYCoordinate() == third_point.GetYCoordinate()))
    {
        std::cout << "Points must differ from each other" << std::endl
                  << "Try again : ";
    }
    else if (!ArePointsCollinear(first_point, second_point, third_point))
    {
        std::cout << "Points cannot be collinear\nTry again: ";
    }
    else
    {
        return true;
    }
    return false;
}

void Collection::Rotate()
{
    int choice = 0;
    ChooseFigureIndex(choice);
    double x = 0;
    double y = 0;
    double angle = 0;
    std::cout << std::endl
              << "Enter the vector: x=";
    std::cin >> x;
    HandleInputError(x, "Error. Enter x coordinate again:");
    std::cout << std::endl
              << "y=";
    std::cin >> y;
    HandleInputError(y, "Error. Enter y coordinate again:");
    std::cout << std::endl
              << "Enter angle (in degrees):";
    std::cin >> angle;
    HandleInputError(angle, "Error. Enter angle again:");
    figures_[choice]->RotateAroundPointCoordinates(x, y, angle);
}

void Collection::Distance()
{
    Point p1 = InitPoint();
    Point p2 = InitPoint();
    std::cout << "The distance between points is " << p1.distanceTo(p2) << std::endl;
}

void Collection::Length()
{
    int choice = 0;
    DisplaySegments(choice);
    if (auto segment = dynamic_cast<Segment *>(figures_[choice].get()))
    {
        std::cout << "The length of the segment is " << segment->GetLength() << std::endl;
    }
}

void Collection::PointOnSegment()
{
    double x, y = 0;
    int choice = 0;
    std::cout << "Enter the coordinates of the point." << std::endl
              << "x = ";
    std::cin >> x;
    HandleInputError(x, "Error. Enter x coordinate again:");
    std::cout << std::endl
              << "y=";
    std::cin >> y;
    HandleInputError(y, "Error. Enter y coordinate again:");
    std::cout << std::endl;
    Point point(x, y);
    DisplaySegments(choice);
    if (auto segment = dynamic_cast<Segment *>(figures_[choice].get()))
    {
        if (segment->IsPointOnSegment(point))
        {
            std::cout << "The point is on the segment" << std::endl;
        }
        else
        {
            std::cout << "The point is not on the segment" << std::endl;
        }
    }
}

void Collection::Parallel()
{
    int choice_first = 0;
    int choice_second = 0;
    DisplaySegments(choice_first);
    DisplaySegments(choice_second);
    while (choice_first == choice_second)
    {
        std::cout << "You cannot choose the same segment." << std::endl;
        DisplaySegments(choice_second);
    }
    if (auto first_segment = dynamic_cast<Segment *>(figures_[choice_first].get()))
    {
        if (auto second_segment = dynamic_cast<Segment *>(figures_[choice_second].get()))
        {
            Segment segment = *second_segment;
            if (first_segment->AreSegmentsParallel(segment))
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

void Collection::Perpendicular()
{
    int choice_first = 0;
    int choice_second = 0;
    DisplaySegments(choice_first);
    DisplaySegments(choice_second);
    while (choice_first == choice_second)
    {
        std::cout << "You cannot choose the same segment." << std::endl;
        DisplaySegments(choice_second);
    }
    if (auto first_segment = dynamic_cast<Segment *>(figures_[choice_first].get()))
    {
        if (auto second_segment = dynamic_cast<Segment *>(figures_[choice_second].get()))
        {
            Segment segment = *second_segment;
            if (first_segment->AreSegmentsPerpendicular(segment))
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

void Collection::Intersection()
{
    int choice_first = 0;
    int choice_second = 0;
    DisplaySegments(choice_first);
    DisplaySegments(choice_second);
    while (choice_first == choice_second)
    {
        std::cout << "You cannot choose the same segment." << std::endl;
        DisplaySegments(choice_second);
    }
    if (auto first_segment = dynamic_cast<Segment *>(figures_[choice_first].get()))
    {
        if (auto second_segment = dynamic_cast<Segment *>(figures_[choice_second].get()))
        {
            Segment segment = *second_segment;
            first_segment->GetIntersectionPoint(segment);
        }
    }
}

void Collection::AreaAndPerimeter()
{
    int choice = 0;
    DisplayTriangles(choice);
    if (auto triangle = dynamic_cast<Triangle *>(figures_[choice].get()))
    {
        std::cout << "Area: " << triangle->GetArea() << "    Perimeter: " << triangle->GetParimeter() << std::endl;
    }
}

void Collection::Disconnected()
{
    int choice_first = 0;
    int choice_second = 0;
    DisplayTriangles(choice_first);
    DisplayTriangles(choice_second);
    while (choice_first == choice_second)
    {
        std::cout << "You cannot choose the same triangle." << std::endl;
        DisplayTriangles(choice_second);
    }
    if (auto first_triangle = dynamic_cast<Triangle *>(figures_[choice_first].get()))
    {
        if (auto second_triangle = dynamic_cast<Triangle *>(figures_[choice_second].get()))
        {
            Triangle triangle = *second_triangle;
            if (first_triangle->AreTrianglesDisconnected(triangle))
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

void Collection::Hypotenuse()
{
    int index = 0;
    int choice = 0;
    int flag = 0;
    for (int i = 0; i < figures_.size(); i++)
    {
        if (auto right_triangle = dynamic_cast<RightTriangle *>(figures_[i].get()))
        {
            std::cout << i + 1 << ". Right Triangle " << right_triangle->GetObjectCoordinate() << std::endl;
            flag++;
        }
    }
    if (flag > 0)
    {
        std::cout << "Choose: ";
        std::cin >> choice;
        InputIndex(choice);
        if (auto right_triangle = dynamic_cast<RightTriangle *>(figures_[choice - 1].get()))
        {
            std::cout << "The length of the hypotenuse is: " << right_triangle->GetHypotenuseLength() << std::endl;
        }
    }
    else
    {
        std::cout << "No right triangles found" << std::endl;
    }
}

void Collection::MainApp()
{
    int choice = 0;
    bool loop_on = true;
    while (loop_on)
    {
        Menu(choice);
        switch (choice)
        {
        case 1:
            AddFigure();
            break;
        case 2:
            DisplayAllFigures();
            break;
        case 3:
            MoveFigure();
            break;
        case 4:
            RotateFigure();
            break;
        case 5:
            CalculateDistance();
            break;
        case 6:
            Length();
            break;
        case 7:
            PointOnSegment();
            break;
        case 8:
            Parallel();
            break;
        case 9:
            Perpendicular();
            break;
        case 10:
            Intersection();
            break;
        case 11:
            AreaAndPerimeter();
            break;
        case 12:
            Disconnected();
            break;
        case 13:
            Hypotenuse();
            break;
        case 0:
            loop_on = false;
            break;
        default:
            std::cout << "Error. Try again";
            choice = 0;
            break;
        }
        std::string click;
        std::cout << "\nPress any key to continue ";
        std::cin >> click;
        ClearScreen();
    }
}

void Collection::Menu(int &choice)
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
    std::cout << "Choice : ";
    std::cin >> choice;
    HandleInputError(choice, "Error. Enter a number from 0 to 13: ");
}
