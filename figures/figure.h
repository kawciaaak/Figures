#ifndef FIGURES_FIGURES_FIGURES_H
#define FIGURES_FIGURES_FIGURES_H

#include "i_figure.h"
#include <vector>

class Figure : public IFigure
{
public:
    Figure();

    void MoveByVector(const double &vector_x_coordinate, const double &vector_y_coordinate) override;
    void RotateAroundPointCoordinates(const double &x_coordinate, const double &y_coordinate, const double &angle) override;

    std::string GetObjectName() const = 0;
    std::string GetObjectCoordinate() const = 0;

    virtual void CreateLinearFunction(const Point &, const Point &, const double &, const double &) = 0;
    virtual bool IsPointOnLinearFunction(const Point &, const double &, const double &) = 0;

protected:
    std::vector<Point> points_;
};

#endif // FIGURES_FIGURES_FIGURES_H
