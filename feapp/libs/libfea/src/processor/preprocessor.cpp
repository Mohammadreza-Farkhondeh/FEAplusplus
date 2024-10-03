#include "processor/preprocessor.h"

Preprocessor::Preprocessor() {}

void Preprocessor::generateMesh(
    const std::vector<std::vector<double>>& nodeCoordinates,
    const std::vector<std::vector<int>>& elementConnectivity,
    const std::vector<Material>& materials) {
  for (size_t i = 0; i < nodeCoordinates.size(); ++i) {
    Node node(i, nodeCoordinates[i]);
    mesh.addNode(node);
  }

  for (size_t i = 0; i < elementConnectivity.size(); ++i) {
    Element element(i, elementConnectivity[i], materials[i]);
    mesh.addElement(element);
  }
}

void Preprocessor::applyBoundaryConditions(
    const std::vector<int>& boundaryNodeIndices,
    const std::vector<int>& boundaryDOFIndices,
    const std::vector<double>& boundaryValues) {
  for (size_t i = 0; i < boundaryNodeIndices.size(); ++i) {
    mesh.applyBoundaryCondition(boundaryNodeIndices[i], boundaryDOFIndices[i],
                                boundaryValues[i]);
  }
}

void Preprocessor::applyLoads(
    const std::vector<int>& loadNodeIndices,
    const std::vector<std::vector<double>>& loadVectors) {
  for (size_t i = 0; i < loadNodeIndices.size(); ++i) {
    mesh.applyLoad(loadNodeIndices[i], loadVectors[i]);
  }
}

const Mesh& Preprocessor::getMesh() const {
  return mesh;
}
