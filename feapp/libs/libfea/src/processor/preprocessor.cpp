#include "processor/preprocessor.h"
#include "loads/distributed_load.h"
#include "loads/point_load.h"

Preprocessor::Preprocessor() {}

const Mesh& Preprocessor::getMesh() const {
  return mesh;
}

void Preprocessor::generateMesh(
    const std::vector<std::vector<double>>& nodeCoordinates,
    const std::vector<std::vector<int>>& elementConnectivity,
    const std::vector<Material>& materials) {
  for (size_t i = 0; i < nodeCoordinates.size(); ++i) {
    Node node(nodeCoordinates[i][0], nodeCoordinates[i][1],
              nodeCoordinates[i][2]);
    mesh.addNode(node);
  }

  for (size_t i = 0; i < elementConnectivity.size(); ++i) {
    std::vector<Node*> elementNodes;
    for (int nodeIndex : elementConnectivity[i]) {
      elementNodes.push_back(&mesh.getNode(nodeIndex));
    }
    Element element(elementNodes, materials[i]);
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
  if (loadNodeIndices.size() != loadVectors.size()) {
    throw std::runtime_error(
        "Mismatched loadNodeIndices and loadVectors size.");
  }

  for (size_t i = 0; i < loadNodeIndices.size(); ++i) {
    const auto& loadVector = loadVectors[i];

    if (loadVector.size() == 3) {
      std::shared_ptr<Load> load = std::make_shared<PointLoad>(
          loadVector[0], loadVector[1], loadVector[2]);
      mesh.applyLoad(loadNodeIndices[i], load);

    } else if (loadVector.size() > 3) {
      double totalLoad = loadVector[0];

      std::vector<Node*> nodes;
      for (int j = 0; j < loadNodeIndices.size(); ++j) {
        nodes.push_back(&mesh.getNode(loadNodeIndices[j]));
      }

      auto distributionFunction =
          [](const std::vector<Node*>& nodes) -> std::vector<double> {
        size_t numNodes = nodes.size();
        std::vector<double> distributedLoads(numNodes, 1.0 / numNodes);
        return distributedLoads;
      };

      std::shared_ptr<Load> load = std::make_shared<DistributedLoad>(
          totalLoad, nodes, distributionFunction);
      mesh.applyLoad(loadNodeIndices[i], load);

    } else {
      throw std::runtime_error("Invalid load vector size.");
    }
  }
}
