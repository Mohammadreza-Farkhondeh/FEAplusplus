#include "geometry/element.h"
#include "geometry/node.h"
#include "gtest/gtest.h"
#include "material/material.h"

TEST(ElementTest, Constructor) {
  Node node1(0.0, 0.0, 0.0);
  Node node2(1.0, 0.0, 0.0);

  Material material(210e9, 0.3, 7800, 250e6, 0.01);

  std::vector<Node*> nodes = {&node1, &node2};
  Element element(nodes, material);

  EXPECT_EQ(element.getNodes().size(), 2);
  EXPECT_EQ(element.getMaterial().getElasticModulus(), 210e9);
  EXPECT_EQ(element.getMaterial().getCrossSectionArea(), 0.01);
}

TEST(ElementTest, ComputeStiffnessMatrix) {
  Node node1(0.0, 0.0, 0.0);
  Node node2(1.0, 0.0, 0.0);

  Material material(210e9, 0.3, 7800, 250e6, 0.01);

  std::vector<Node*> nodes = {&node1, &node2};
  Element element(nodes, material);

  Matrix K = element.computeStiffnessMatrix();
}

TEST(ElementTest, Assemble) {
  Node node1(0.0, 0.0, 0.0);
  Node node2(1.0, 0.0, 0.0);

  Material material(210e9, 0.3, 7800, 250e6, 0.01);

  std::vector<Node*> nodes = {&node1, &node2};
  Element element(nodes, material);
}

TEST(ElementTest, GetDOFMap) {
  Node node1(0.0, 0.0, 0.0);
  Node node2(1.0, 0.0, 0.0);

  Material material(210e9, 0.3, 7800, 250e6, 0.01);

  std::vector<Node*> nodes = {&node1, &node2};
  Element element(nodes, material);

  std::vector<int> dofMap = element.getDOFMap();
}
