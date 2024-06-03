#include "postprocessor.h"

Postprocessor::Postprocessor() {}

void Postprocessor::calculateStresses(const Mesh& mesh) {
  const auto& elements = mesh.getElements();
  for (const auto& element : elements) {
    const auto& nodes = element.getNodes();
    size_t numNodes = nodes.size();
    size_t numDOF = numNodes * 3;  // Assuming 3 DOF per node

    // Extract displacement vector for the element
    Vector displacementVector(numDOF);
    for (size_t i = 0; i < numNodes; ++i) {
      for (int j = 0; j < 3; ++j) {
        displacementVector[i * 3 + j] = nodes[i]->getDisplacement(j);
      }
    }

    // Calculate stress for the element
    double stress = calculateElementStress(element, displacementVector);
    // Output or store stress data as needed
  }
}

void Postprocessor::calculateStrains(const Mesh& mesh) {
  const auto& elements = mesh.getElements();
  for (const auto& element : elements) {
    const auto& nodes = element.getNodes();
    size_t numNodes = nodes.size();
    size_t numDOF = numNodes * 3;  // Assuming 3 DOF per node

    // Extract displacement vector for the element
    Vector displacementVector(numDOF);
    for (size_t i = 0; i < numNodes; ++i) {
      for (int j = 0; j < 3; ++j) {
        displacementVector[i * 3 + j] = nodes[i]->getDisplacement(j);
      }
    }

    // Calculate strain for the element
    double strain = calculateElementStrain(element, displacementVector);
    // Output or store strain data as needed
  }
}

void Postprocessor::calculateMoments(const Mesh& mesh) {
  const auto& elements = mesh.getElements();
  for (const auto& element : elements) {
    const auto& nodes = element.getNodes();
    size_t numNodes = nodes.size();
    size_t numDOF = numNodes * 3;  // Assuming 3 DOF per node

    // Extract displacement vector for the element
    Vector displacementVector(numDOF);
    for (size_t i = 0; i < numNodes; ++i) {
      for (int j = 0; j < 3; ++j) {
        displacementVector[i * 3 + j] = nodes[i]->getDisplacement(j);
      }
    }

    // Calculate moment for the element
    double moment = calculateElementMoment(element, displacementVector);
    // Output or store moment data as needed
  }
}

void Postprocessor::calculateShears(const Mesh& mesh) {
  const auto& elements = mesh.getElements();
  for (const auto& element : elements) {
    const auto& nodes = element.getNodes();
    size_t numNodes = nodes.size();
    size_t numDOF = numNodes * 3;  // Assuming 3 DOF per node

    // Extract displacement vector for the element
    Vector displacementVector(numDOF);
    for (size_t i = 0; i < numNodes; ++i) {
      for (int j = 0; j < 3; ++j) {
        displacementVector[i * 3 + j] = nodes[i]->getDisplacement(j);
      }
    }

    // Calculate shear for the element
    double shear = calculateElementShear(element, displacementVector);
    // Output or store shear data as needed
  }
}

double Postprocessor::calculateElementStress(
    const Element& element,
    const Vector& displacementVector) const {
  // Assuming linear elastic material properties
  const auto& material = element.getMaterial();
  double E = material.getElasticModulus();    // Elastic Modulus
  double A = material.getCrossSectionArea();  // Cross-sectional Area

  // Compute strain for the element
  double strain = calculateElementStrain(element, displacementVector);

  // Compute stress using Hooke's Law
  double stress = E * strain;

  return stress;
}

double Postprocessor::calculateElementStrain(
    const Element& element,
    const Vector& displacementVector) const {
  // Placeholder implementation; actual implementation depends on element type
  // and material properties For linear elements, strain can be calculated from
  // displacements For nonlinear elements, strain calculation can be more
  // complex
  return 0.0;
}

// double Postprocessor::calculateElementMoment
