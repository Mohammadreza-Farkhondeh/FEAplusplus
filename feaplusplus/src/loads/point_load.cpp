#include "loads/point_load.h"

PointLoad::PointLoad(double magnitude, const Node& node)
    : magnitude(magnitude), node(node) {}

double PointLoad::getMagnitude() const {
    return magnitude;
}

Node PointLoad::getNode() const {
    return node;
}
