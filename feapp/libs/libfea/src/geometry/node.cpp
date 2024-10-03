#include "geometry/node.h"

Node::Node(double x, double y, double z)
    : coordinates{x, y, z},
      displacements{0.0, 0.0, 0.0},
      loads{0.0, 0.0, 0.0},
      boundaryConditions{0.0, 0.0, 0.0} {}

bool Node::operator==(const Node& other) const {
  return id == other.id && coordinates == other.coordinates;
}

void Node::applyBoundaryCondition(int dofIndex, double value) {
  if (dofIndex >= 0 && dofIndex < 3) {
    boundaryConditions[dofIndex] = value;
  }
}

void Node::setDisplacement(int dofIndex, double displacement) {
  if (dofIndex >= 0 && dofIndex < 3) {
    displacements[dofIndex] = displacement;
  }
}

double Node::getDisplacement(int dofIndex) const {
  if (dofIndex >= 0 && dofIndex < 3) {
    return displacements[dofIndex];
  }
  return 0.0;
}

std::array<double, 3> Node::getCoordinates() const {
  return coordinates;
}

int Node::getGlobalDOFIndex(int localDOFIndex) const {
  return localDOFIndex;
}

void Node::applyLoad(double fx, double fy, double fz) {
  loads[0] += fx;
  loads[1] += fy;
  loads[2] += fz;
}

std::array<double, 3> Node::getLoads() const {
  return loads;
}

std::array<double, 3> Node::getBoundaryConditions() const {
  return boundaryConditions;
}
