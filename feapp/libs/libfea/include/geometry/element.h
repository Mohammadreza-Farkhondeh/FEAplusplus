#ifndef ELEMENT_H
#define ELEMENT_H

#include <array>
#include <vector>
#include "common/common.h"
#include "geometry/node.h"
#include "material/material.h"

class Element {
 public:
  Element(const std::vector<Node*>& nodes, const Material& material);

  const std::vector<Node*>& getNodes() const;
  Material getMaterial() const;
  void setMaterial(const Material& newMaterial);
  Matrix computeStiffnessMatrix() const;
  void assemble(Matrix& globalStiffnessMatrix,
                const std::vector<int>& dofMap) const;
  std::vector<int> getDOFMap() const;

 private:
  double computeLength(const std::array<double, 3>& x1,
                       const std::array<double, 3>& x2) const;
  std::array<double, 3> computeDirectionCosines(const std::array<double, 3>& x1,
                                                const std::array<double, 3>& x2,
                                                double L) const;
  double computeEA_L(const Material& material, double L) const;
  Matrix computeLocalStiffnessMatrix(
      const std::array<double, 3>& directionCosines,
      double EA_L) const;
  void assembleGlobalStiffnessMatrix(Matrix& stiffnessMatrix,
                                     const Matrix& k_local,
                                     size_t totalDof,
                                     size_t dofPerNode) const;

  std::vector<Node*> nodes;
  Material material;
};

#endif  // ELEMENT_H
