#include "fea/mesh.h"
#include <stdexcept>

Mesh::Mesh() : globalStiffnessMatrix(), globalForceVector() {}

void Mesh::addNode(const Node& node) {
  nodes.push_back(node);
}

void Mesh::addElement(const Element& element) {
  elements.push_back(element);
}

Node& Mesh::getNode(int nodeId) {
  if (nodeId < 0 || nodeId >= nodes.size()) {
    throw std::out_of_range("Invalid nodeId");
  }
  return nodes[nodeId];
}

void Mesh::assignMaterial(Element& element, const Material& material) {
  element.setMaterial(material);
}

void Mesh::applyBoundaryCondition(int nodeId, int dofIndex, double value) {
  if (nodeId < 0 || nodeId >= nodes.size()) {
    throw std::out_of_range("Invalid nodeId");
  }
  nodes[nodeId].applyBoundaryCondition(dofIndex, value);
  boundaryConditions[nodeId].emplace_back(dofIndex, value);
}
void Mesh::applyLoad(int nodeId, const std::shared_ptr<Load> load) {
  if (nodeId < 0 || nodeId >= nodes.size()) {
    throw std::out_of_range("Invalid nodeId");
  }
  loads[nodeId].push_back(load);
  load->apply(nodes[nodeId]);
}

void Mesh::generateStiffnessMatrix() {
  int totalDOF = nodes.size() * 3;
  globalStiffnessMatrix.resize(totalDOF, std::vector<double>(totalDOF, 0.0));
  globalForceVector.resize(totalDOF);

  for (int i = 0; i < totalDOF; ++i) {
    for (int j = 0; j < totalDOF; ++j) {
      globalStiffnessMatrix[i][j] = 0.0;
    }
    globalForceVector[i] = 0.0;
  }

  for (const auto& element : elements) {
    Matrix elementStiffness = element.computeStiffnessMatrix();
    std::vector<int> dofMap = element.getDOFMap();

    for (size_t i = 0; i < dofMap.size(); ++i) {
      for (size_t j = 0; j < dofMap.size(); ++j) {
        globalStiffnessMatrix[dofMap[i]][dofMap[j]] += elementStiffness[i][j];
      }
    }
  }

  for (const auto& bc : boundaryConditions) {
    int nodeId = bc.first;
    const Node& node = nodes[nodeId];
    for (const auto& [dofIndex, value] : bc.second) {
      int globalIndex = node.getGlobalDOFIndex(dofIndex);
      globalStiffnessMatrix[globalIndex][globalIndex] = 1e30;
      globalForceVector[globalIndex] = value * 1e30;
    }
  }

  for (const auto& loadPair : loads) {
    int nodeId = loadPair.first;
    for (const auto& load : loadPair.second) {
      load->apply(nodes[nodeId]);
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
