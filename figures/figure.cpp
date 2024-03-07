#include "figure.h"
namespace Figures{
    namespace GeometricFigures{
void Figure_handler::MoveByVector(const double& vector_x_coordinate, const double& vector_y_coordinate) {
    for (auto& point : points_) {
        point.MovePointByVector(vector_x_coordinate, vector_y_coordinate);
    }
}

void Figure_handler::RotateAroundPointCoordinates(const double& x_coordinate, const double& y_coordinate, const double& angle) {
    for (auto& point : points_) {
        point.RotateAroundPoint(x_coordinate, y_coordinate, angle);
    }
}
}
}