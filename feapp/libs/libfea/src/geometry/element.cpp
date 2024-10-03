#include "geometry/element.h"

#include <cmath>

Element::Element(const std::vector<Node*>& nodes, const Material& material)
    : nodes(nodes), material(material) {}

const std::vector<Node*>& Element::getNodes() const {
  return nodes;
}

Material Element::getMaterial() const {
  return material;
}
Matrix Element::computeStiffnessMatrix() const {
  size_t numNodes = nodes.size();
  size_t dofPerNode = 3;
  size_t totalDof = numNodes * dofPerNode;

  Matrix stiffnessMatrix(totalDof, std::vector<double>(totalDof, 0.0));

  std::vector<double> x1 = nodes[0]->getCoordinates();
  std::vector<double> x2 = nodes[1]->getCoordinates();
  double L = std::sqrt(std::pow(x2[0] - x1[0], 2) + std::pow(x2[1] - x1[1], 2) +
                       std::pow(x2[2] - x1[2], 2));

  double l = (x2[0] - x1[0]) / L;
  double m = (x2[1] - x1[1]) / L;
  double n = (x2[2] - x1[2]) / L;

  double E = material.getElasticModulus();
  double A = material.getCrossSectionArea();
  double EA_L = (E * A) / L;

  Matrix k_local = {{l * l, l * m, l * n, -l * l, -l * m, -l * n},
                    {m * l, m * m, m * n, -m * l, -m * m, -m * n},
                    {n * l, n * m, n * n, -n * l, -n * m, -n * n},
                    {-l * l, -l * m, -l * n, l * l, l * m, l * n},
                    {-m * l, -m * m, -m * n, m * l, m * m, m * n},
                    {-n * l, -n * m, -n * n, n * l, n * m, n * n}};

  for (auto& row : k_local) {
    for (auto& value : row) {
      value *= EA_L;
    }
  }

  for (size_t i = 0; i < totalDof; ++i) {
    for (size_t j = 0; j < totalDof; ++j) {
      stiffnessMatrix[i][j] = k_local[i % dofPerNode][j % dofPerNode];
    }
  }

  return stiffnessMatrix;
}

void Element::assemble(Matrix& globalStiffnessMatrix,
                       const std::vector<int>& dofMap) const {
  Matrix localStiffnessMatrix = computeStiffnessMatrix();
  for (size_t i = 0; i < dofMap.size(); ++i) {
    for (size_t j = 0; j < dofMap.size(); ++j) {
      globalStiffnessMatrix[dofMap[i]][dofMap[j]] += localStiffnessMatrix[i][j];
    }
  }
}

std::vector<int> Element::getDOFMap() const {
  std::vector<int> dofMap;
  for (const Node* node : nodes) {
    for (int dof = 0; dof < 3; ++dof) {
      dofMap.push_back(node->getGlobalDOFIndex(dof));
    }
  }
  return dofMap;
}
