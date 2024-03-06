#ifndef FIGURES_FIGURES_I_FIGURES_H
#define FIGURES_FIGURES_I_FIGURES_H

#include <string>
#include "..\figures\point\point.h"

class IFigure
{
public:
  virtual void MoveByVector(const double &vector_x_coordinate, const double &vector_y_coordinate) = 0;
  virtual void RotateAroundPointCoordinates(const double &x_coordinate, const double &y_coordinate, const double &angle) = 0;

  virtual std::string GetObjectName() const = 0;
  virtual std::string GetObjectCoordinate() const = 0;
};

#endif // FIGURES_FIGURES_I_FIGURES_H
