#include "geometry/element.h"
#include <array>
#include <cmath>
#include <vector>

Element::Element(const std::vector<Node*>& nodes, const Material& material)
    : nodes(nodes), material(material) {}

const std::vector<Node*>& Element::getNodes() const {
  return nodes;
}

Material Element::getMaterial() const {
  return material;
}

void Element::setMaterial(const Material& newMaterial) {
  material = newMaterial;
}

Matrix Element::computeStiffnessMatrix() const {
  const size_t numNodes = nodes.size();
  const size_t dofPerNode = 3;
  const size_t totalDof = numNodes * dofPerNode;

  Matrix stiffnessMatrix(totalDof, std::vector<double>(totalDof, 0.0));

  const auto x1 = nodes[0]->getCoordinates();
  const auto x2 = nodes[1]->getCoordinates();
  const double L = computeLength(x1, x2);

  const auto directionCosines = computeDirectionCosines(x1, x2, L);
  const double EA_L = computeEA_L(material, L);

  const Matrix k_local = computeLocalStiffnessMatrix(directionCosines, EA_L);

  assembleGlobalStiffnessMatrix(stiffnessMatrix, k_local, totalDof, dofPerNode);

  return stiffnessMatrix;
}

double Element::computeLength(const std::array<double, 3>& x1,
                              const std::array<double, 3>& x2) const {
  return std::sqrt(std::pow(x2[0] - x1[0], 2) + std::pow(x2[1] - x1[1], 2) +
                   std::pow(x2[2] - x1[2], 2));
}

std::array<double, 3> Element::computeDirectionCosines(
    const std::array<double, 3>& x1,
    const std::array<double, 3>& x2,
    double L) const {
  return {(x2[0] - x1[0]) / L, (x2[1] - x1[1]) / L, (x2[2] - x1[2]) / L};
}

double Element::computeEA_L(const Material& material, double L) const {
  const double E = material.getElasticModulus();
  const double A = material.getCrossSectionArea();
  return (E * A) / L;
}

Matrix Element::computeLocalStiffnessMatrix(
    const std::array<double, 3>& directionCosines,
    double EA_L) const {
  const double l = directionCosines[0];
  const double m = directionCosines[1];
  const double n = directionCosines[2];

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

  return k_local;
}

void Element::assembleGlobalStiffnessMatrix(Matrix& stiffnessMatrix,
                                            const Matrix& k_local,
                                            size_t totalDof,
                                            size_t dofPerNode) const {
  for (size_t i = 0; i < totalDof; ++i) {
    for (size_t j = 0; j < totalDof; ++j) {
      stiffnessMatrix[i][j] = k_local[i % dofPerNode][j % dofPerNode];
    }
  }
}

void Element::assemble(Matrix& globalStiffnessMatrix,
                       const std::vector<int>& dofMap) const {
  const Matrix localStiffnessMatrix = computeStiffnessMatrix();
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
