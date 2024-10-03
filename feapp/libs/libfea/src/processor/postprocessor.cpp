#include "processor/postprocessor.h"
#include <cmath>
#include <stdexcept>

Postprocessor::Postprocessor() {}

std::vector<AnalysisResult> Postprocessor::calculateStresses(const Mesh& mesh) {
  std::vector<AnalysisResult> results;
  const auto& elements = mesh.getElements();

  for (const auto& element : elements) {
    const auto& nodes = element.getNodes();
    size_t numNodes = nodes.size();
    size_t numDOF = numNodes * 3;

    Vector displacementVector(numDOF);
    for (size_t i = 0; i < numNodes; ++i) {
      for (int j = 0; j < 3; ++j) {
        displacementVector[i * 3 + j] = nodes[i]->getDisplacement(j);
      }
    }

    double stress = calculateElementStress(element, displacementVector);
    results.push_back({nodes[0], nodes[1], stress, 0.0, 0.0, 0.0});
  }
  return results;
}

std::vector<AnalysisResult> Postprocessor::calculateStrains(const Mesh& mesh) {
  std::vector<AnalysisResult> results;
  const auto& elements = mesh.getElements();

  for (const auto& element : elements) {
    const auto& nodes = element.getNodes();
    size_t numNodes = nodes.size();
    size_t numDOF = numNodes * 3;

    Vector displacementVector(numDOF);
    for (size_t i = 0; i < numNodes; ++i) {
      for (int j = 0; j < 3; ++j) {
        displacementVector[i * 3 + j] = nodes[i]->getDisplacement(j);
      }
    }

    double strain = calculateElementStrain(element, displacementVector);
    results.push_back({nodes[0], nodes[1], 0.0, strain, 0.0, 0.0});
  }
  return results;
}

std::vector<AnalysisResult> Postprocessor::calculateMoments(const Mesh& mesh) {
  std::vector<AnalysisResult> results;
  const auto& elements = mesh.getElements();

  for (const auto& element : elements) {
    const auto& nodes = element.getNodes();
    size_t numNodes = nodes.size();
    size_t numDOF = numNodes * 3;

    Vector displacementVector(numDOF);
    for (size_t i = 0; i < numNodes; ++i) {
      for (int j = 0; j < 3; ++j) {
        displacementVector[i * 3 + j] = nodes[i]->getDisplacement(j);
      }
    }

    double moment = calculateElementMoment(element, displacementVector);
    results.push_back({nodes[0], nodes[1], 0.0, 0.0, moment, 0.0});
  }
  return results;
}

std::vector<AnalysisResult> Postprocessor::calculateShears(const Mesh& mesh) {
  std::vector<AnalysisResult> results;
  const auto& elements = mesh.getElements();

  for (const auto& element : elements) {
    const auto& nodes = element.getNodes();
    size_t numNodes = nodes.size();
    size_t numDOF = numNodes * 3;

    Vector displacementVector(numDOF);
    for (size_t i = 0; i < numNodes; ++i) {
      for (int j = 0; j < 3; ++j) {
        displacementVector[i * 3 + j] = nodes[i]->getDisplacement(j);
      }
    }

    double shear = calculateElementShear(element, displacementVector);
    results.push_back({nodes[0], nodes[1], 0.0, 0.0, 0.0, shear});
  }
  return results;
}

double Postprocessor::calculateElementStress(
    const Element& element,
    const Vector& displacementVector) const {
  const auto& material = element.getMaterial();
  double E = material.getElasticModulus();

  double strain = calculateElementStrain(element, displacementVector);
  return E * strain;  // Hooke's Law: stress = E * strain
}

double Postprocessor::calculateElementStrain(
    const Element& element,
    const Vector& displacementVector) const {
  const auto& nodes = element.getNodes();
  if (nodes.size() != 2) {
    throw std::invalid_argument(
        "Element should have exactly two nodes for strain calculation.");
  }

  double lengthInitial = getLength(nodes[0], nodes[1]);
  double lengthCurrent =
      getLengthWithDisplacement(nodes[0], nodes[1], displacementVector);

  return (lengthCurrent - lengthInitial) / lengthInitial;
}

double Postprocessor::calculateElementMoment(
    const Element& element,
    const Vector& displacementVector) const {
  const auto& nodes = element.getNodes();
  if (nodes.size() != 2) {
    throw std::invalid_argument(
        "Element should have exactly two nodes for moment calculation.");
  }

  double L = getLength(nodes[0], nodes[1]);
  double EI = element.getMaterial().getElasticModulus() *
              1.0;  // TODO: Replace 1.0 with correct inertia if available

  double theta1 = displacementVector[1];
  double theta2 = displacementVector[4];

  return EI / L * (theta2 - theta1);
}

double Postprocessor::calculateElementShear(
    const Element& element,
    const Vector& displacementVector) const {
  const auto& nodes = element.getNodes();
  if (nodes.size() != 2) {
    throw std::invalid_argument(
        "Element should have exactly two nodes for shear calculation.");
  }

  double L = getLength(nodes[0], nodes[1]);
  double k = element.getMaterial().getShearModulus() *
             element.getMaterial().getCrossSectionArea();

  double v1 = displacementVector[2];
  double v2 = displacementVector[5];

  return k / L * (v2 - v1);
}

double Postprocessor::getLength(const Node* node1, const Node* node2) const {
  auto coords1 = node1->getCoordinates();
  auto coords2 = node2->getCoordinates();

  return std::sqrt(std::pow(coords2[0] - coords1[0], 2) +
                   std::pow(coords2[1] - coords1[1], 2) +
                   std::pow(coords2[2] - coords1[2], 2));
}

double Postprocessor::getLengthWithDisplacement(
    const Node* node1,
    const Node* node2,
    const Vector& displacementVector) const {
  auto coords1 = node1->getCoordinates();
  auto coords2 = node2->getCoordinates();

  double dx1 = coords1[0] + node1->getDisplacement(0);
  double dy1 = coords1[1] + node1->getDisplacement(1);
  double dz1 = coords1[2] + node1->getDisplacement(2);

  double dx2 = coords2[0] + node2->getDisplacement(0);
  double dy2 = coords2[1] + node2->getDisplacement(1);
  double dz2 = coords2[2] + node2->getDisplacement(2);

  return std::sqrt(std::pow(dx2 - dx1, 2) + std::pow(dy2 - dy1, 2) +
                   std::pow(dz2 - dz1, 2));
}
