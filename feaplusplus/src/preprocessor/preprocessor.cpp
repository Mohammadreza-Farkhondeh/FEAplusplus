#include "preprocessor.h"

Preprocessor::Preprocessor() {}

void Preprocessor::generateMesh(
    const std::vector<std::vector<double>>& nodeCoordinates,
    const std::vector<std::vector<int>>& elementConnectivity,
    const std::vector<Material>& materials) {
  for (const auto& coord : nodeCoordinates) {
    mesh.addNode(Node(coord[0], coord[1], coord[2]));
  }

  for (size_t i = 0; i < elementConnectivity.size(); ++i) {
    std::vector<Node*> elementNodes;
    for (const auto& nodeIndex : elementConnectivity[i]) {
      elementNodes.push_back(&mesh.getNodes()[nodeIndex]);
    }
    Element element(elementNodes);
    mesh.addElement(element);
    mesh.assignMaterial(element, materials[i]);
  }
}

void Preprocessor::applyBoundaryConditions(
    const std::vector<std::vector<int>>& boundaryNodeIndices,
    const std::vector<int>& boundaryDOFIndices,
    const std::vector<double>& boundaryValues) {
  for (size_t i = 0; i < boundaryNodeIndices.size(); ++i) {
    for (size_t j = 0; j < boundaryNodeIndices[i].size(); ++j) {
      int nodeIndex = boundaryNodeIndices[i][j];
      mesh.applyBoundaryCondition(mesh.getNodes()[nodeIndex],
                                  boundaryDOFIndices[j], boundaryValues[j]);
    }
  }
}

void Preprocessor::applyLoads(
    const std::vector<int>& loadNodeIndices,
    const std::vector<std::vector<double>>& loadVectors) {
  for (size_t i = 0; i < loadNodeIndices.size(); ++i) {
    int nodeIndex = loadNodeIndices[i];
    PointLoad load(loadVectors[i][0], loadVectors[i][1], loadVectors[i][2]);
    mesh.applyLoad(mesh.getNodes()[nodeIndex], load);
  }
}

void Preprocessor::preprocess() {}

const Mesh& Preprocessor::getMesh() const {
  return mesh;
}
