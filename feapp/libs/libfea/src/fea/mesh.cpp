#include "fea/mesh.h"

#include <stdexcept>

Mesh::Mesh() : globalStiffnessMatrix(), globalForceVector() {}

void Mesh::addNode(const Node& node) {
  nodes.push_back(node);
}

void Mesh::addElement(const Element& element) {
  elements.push_back(element);
}

void Mesh::assignMaterial(Element& element, const Material& material) {
  element.setMaterial(material);
}

void Mesh::applyBoundaryCondition(const Node& node,
                                  int dofIndex,
                                  double value) {
  for (auto& n : nodes) {
    if (n.getCoordinates() == node.getCoordinates()) {
      n.applyBoundaryCondition(dofIndex, value);
      boundaryConditions[&n].emplace_back(dofIndex, value);
      break;
    }
  }
}

void Mesh::applyLoad(const Node& node, const Load& load) {
  for (auto& n : nodes) {
    if (n.getCoordinates() == node.getCoordinates()) {
      loads[&n].push_back(load);
      load.apply(n);
      break;
    }
  }
}

void Mesh::generateStiffnessMatrix() {
  int totalDOF = nodes.size() * 3;  // Assuming 3 DOF per node (x, y, z)
  globalStiffnessMatrix.resize(totalDOF, totalDOF);
  globalForceVector.resize(totalDOF);

  // Initialize stiffness matrix and force vector to zero
  for (int i = 0; i < totalDOF; ++i) {
    for (int j = 0; j < totalDOF; ++j) {
      globalStiffnessMatrix(i, j) = 0.0;
    }
    globalForceVector(i) = 0.0;
  }

  // Assemble the global stiffness matrix
  for (const auto& element : elements) {
    Matrix elementStiffness = element.computeStiffnessMatrix();
    std::vector<int> dofMap = element.getDOFMap();

    for (size_t i = 0; i < dofMap.size(); ++i) {
      for (size_t j = 0; j < dofMap.size(); ++j) {
        globalStiffnessMatrix(dofMap[i], dofMap[j]) += elementStiffness(i, j);
      }
    }
  }

  for (const auto& bc : boundaryConditions) {
    const Node& node = bc.first;
    for (const auto& [dofIndex, value] : bc.second) {
      int globalIndex = node->getGlobalDOFIndex(dofIndex);
      globalStiffnessMatrix(globalIndex, globalIndex) =
          1e30;  // Large number to simulate fixed DOF
      globalForceVector(globalIndex) = value * 1e30;
    }
  }

  for (const auto& loadPair : loads) {
    const Node* node = loadPair.first;
    for (const auto& load : loadPair.second) {
      load.apply(*const_cast<Node*>(node));
    }
  }
}

const std::vector<Node>& Mesh::getNodes() const {
  return nodes;
}

const std::vector<Element>& Mesh::getElements() const {
  return elements;
}

const Matrix& Mesh::getGlobalStiffnessMatrix() const {
  return globalStiffnessMatrix;
}

const Vector& Mesh::getGlobalForceVector() const {
  return globalForceVector;
}
