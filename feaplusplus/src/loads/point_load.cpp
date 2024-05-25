#include "point_load.h"

PointLoad::PointLoad(double fx, double fy, double fz) : fx(fx), fy(fy), fz(fz) {}

void PointLoad::apply(Node& node) const {
    node.applyLoad(fx, fy, fz);
}