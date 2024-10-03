#ifndef MESH_H
#define MESH_H

#include <memory>
#include <unordered_map>
#include <vector>
#include "common/common.h"
#include "geometry/element.h"
#include "geometry/node.h"
#include "loads/load.h"

class Mesh {
 public:
  Mesh();

  void addNode(const Node& node);
  void addElement(const Element& element);
  Node& getNode(int nodeId);

  void assignMaterial(Element& element, const Material& material);
  void applyBoundaryCondition(int nodeId, int dofIndex, double value);
  void applyLoad(int nodeId, const std::shared_ptr<Load> load);

  void generateStiffnessMatrix();

  const std::vector<Node>& getNodes() const;
  const std::vector<Element>& getElements() const;
  const Matrix& getGlobalStiffnessMatrix() const;
  const Vector& getGlobalForceVector() const;

  const std::unordered_map<int, std::vector<std::pair<int, double>>>&
  getBoundaryConditions() const {
    return boundaryConditions;
  }

  const std::unordered_map<int, std::vector<std::shared_ptr<Load>>>& getLoads()
      const {
    return loads;
  }

 private:
  std::vector<Node> nodes;
  std::vector<Element> elements;
  Matrix globalStiffnessMatrix;
  Vector globalForceVector;
  std::unordered_map<int, std::vector<std::pair<int, double>>>
      boundaryConditions;  // Node ID -> Boundary conditions
  std::unordered_map<int, std::vector<std::shared_ptr<Load>>>
      loads;  // Node ID -> Loads
};

#endif  // MESH_H
