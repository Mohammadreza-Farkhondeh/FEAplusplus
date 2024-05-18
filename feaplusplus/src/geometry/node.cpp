#include "geometry/node.h"

Node::Node(double x, double y, double z) : coordinates({x, y, z}), displacements(0, 0.0) {}

void Node::applyBoundaryCondition(int dofIndex, double value) {
    displacements[dofIndex] = value;
}

void Node::setDisplacement(int dofIndex, double displacement) {
    displacements[dofIndex] = displacement;
}

double Node::getDisplacement(int dofIndex) const {
    return displacements[dofIndex];
}

std::vector<double> Node::getCoordinates() const {
    return coordinates;
}
