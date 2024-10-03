#include "geometry/element.h"
#include "geometry/node.h"
#include "gtest/gtest.h"
#include "material/material.h"

// Add appropriate includes and namespaces as needed

TEST(ElementTest, ComputeStiffnessMatrix) {
  // Create nodes
  Node node1(0.0, 0.0, 0.0);
  Node node2(1.0, 0.0, 0.0);

  // Create material with a cross-sectional area
  Material material(210e9, 0.3, 7800, 250e6, 0.01);

  // Create element
  std::vector<Node*> nodes = {&node1, &node2};
  Element element(nodes, material);

  // Compute stiffness matrix
  Matrix K = element.computeStiffnessMatrix();

  // Verify the stiffness matrix
  // Add assertions based on expected values
}

TEST(ElementTest, Assemble) {
  // Similar setup as above
  // Add assertions for assembling stiffness matrix into global matrix
}
