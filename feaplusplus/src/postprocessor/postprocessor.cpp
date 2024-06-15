#include "postprocessor.h"
#include "common/analysis_result.h"

Postprocessor::Postprocessor() {}

std::vector<AnalysisResult> Postprocessor::calculateStresses(const Mesh& mesh) {
  std::vector<AnalysisResult> results;
  const auto& elements = mesh.getElements();
  for (const auto& element : elements) {
    const auto& nodes = element.getNodes();
    size_t numNodes = nodes.size();
    size_t numDOF = numNodes * 3;  // Assuming 3 DOF per node

    Vector displacementVector(numDOF);
    for (size_t i = 0; i < numNodes; ++i) {
      for (int j = 0; j < 3; ++j) {
        displacementVector[i * 3 + j] = nodes[i]->getDisplacement(j);
      }
    }

    double stress = calculateElementStress(element, displacementVector);
    results.push_back({element.getId(), stress, 0.0, 0.0, 0.0});
  }
  return results;
}

std::vector<AnalysisResult> Postprocessor::calculateStrains(const Mesh& mesh) {
  std::vector<AnalysisResult> results;
  const auto& elements = mesh.getElements();
  for (const auto& element : elements) {
    const auto& nodes = element.getNodes();
    size_t numNodes = nodes.size();
    size_t numDOF = numNodes * 3;  // Assuming 3 DOF per node

    Vector displacementVector(numDOF);
    for (size_t i = 0; i < numNodes; ++i) {
      for (int j = 0; j < 3; ++j) {
        displacementVector[i * 3 + j] = nodes[i]->getDisplacement(j);
      }
    }

    double strain = calculateElementStrain(element, displacementVector);
    results.push_back({element.getId(), 0.0, strain, 0.0, 0.0});
  }
  return results;
}

std::vector<AnalysisResult> Postprocessor::calculateMoments(const Mesh& mesh) {
  std::vector<AnalysisResult> results;
  const auto& elements = mesh.getElements();
  for (const auto& element : elements) {
    const auto& nodes = element.getNodes();
    size_t numNodes = nodes.size();
    size_t numDOF = numNodes * 3;  // Assuming 3 DOF per node

    Vector displacementVector(numDOF);
    for (size_t i = 0; i < numNodes; ++i) {
      for (int j = 0; j < 3; ++j) {
        displacementVector[i * 3 + j] = nodes[i]->getDisplacement(j);
      }
    }

    double moment = calculateElementMoment(element, displacementVector);
    results.push_back({element.getId(), 0.0, 0.0, moment, 0.0});
  }
  return results;
}

std::vector<AnalysisResult> Postprocessor::calculateShears(const Mesh& mesh) {
  std::vector<AnalysisResult> results;
  const auto& elements = mesh.getElements();
  for (const auto& element : elements) {
    const auto& nodes = element.getNodes();
    size_t numNodes = nodes.size();
    size_t numDOF = numNodes * 3;  // Assuming 3 DOF per node

    Vector displacementVector(numDOF);
    for (size_t i = 0; i < numNodes; ++i) {
      for (int j = 0; j < 3; ++j) {
        displacementVector[i * 3 + j] = nodes[i]->getDisplacement(j);
      }
    }

    double shear = calculateElementShear(element, displacementVector);
    results.push_back({element.getId(), 0.0, 0.0, 0.0, shear});
  }
  return results;
}

double Postprocessor::calculateElementStress(
    const Element& element,
    const Vector& displacementVector) const {
  const auto& material = element.getMaterial();
  double E = material.getElasticModulus();

  double strain = calculateElementStrain(element, displacementVector);
  double stress = E * strain;

  return stress;
}

double Postprocessor::calculateElementStrain(
    const Element& element,
    const Vector& displacementVector) const {
  const auto& nodes = element.getNodes();
  if (nodes.size() != 2) {
    throw std::invalid_argument(
        "Element should have exactly two nodes for strain calculation.");
  }

  double lengthInitial =
      (nodes[1]->getCoordinates() - nodes[0]->getCoordinates()).norm();
  double lengthCurrent =
      ((nodes[1]->getCoordinates() + nodes[1]->getDisplacements()) -
       (nodes[0]->getCoordinates() + nodes[0]->getDisplacements()))
          .norm();

  double strain = (lengthCurrent - lengthInitial) / lengthInitial;
  return strain;
}

double Postprocessor::calculateElementMoment(
    const Element& element,
    const Vector& displacementVector) const {
  // Placeholder implementation
  // For truss elements, moments are typically zero as they do not resist
  // bending For beam elements, a more complex calculation is needed considering
  // beam theory
  return 0.0;
}

double Postprocessor::calculateElementShear(
    const Element& element,
    const Vector& displacementVector) const {
  // Placeholder implementation
  // For truss elements, shear is typically zero as they do not resist shear
  // forces For beam elements, a more complex calculation is needed considering
  // shear force distribution
  return 0.0;
}
