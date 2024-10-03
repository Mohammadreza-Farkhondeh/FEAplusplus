#include "fea/mesh.h"
#include "geometry/element.h"
#include "geometry/node.h"
#include "gtest/gtest.h"
#include "material/material.h"
#include "solvers/direct_solver.h"
#include "solvers/iterative_solver.h"
#include "solvers/sparse_solver.h"

class SolverTest : public ::testing::Test {
 protected:
  Mesh* mesh;
  std::vector<Element*> elements;
  std::vector<Node*> nodes;  // Define nodes as a member

  void SetUp() override {
    // Create nodes
    Node* node1 = new Node(
        0, 0, 0);  // Assuming Node constructor takes (x, y, z) coordinates
    Node* node2 = new Node(1, 0, 0);
    nodes.push_back(node1);
    nodes.push_back(node2);

    // Create material with appropriate parameters
    Material* material =
        new Material(210e9, 0.3, 7850, 250e6, 0.01);  // Example parameters

    // Create elements
    Element* element1 = new Element(nodes, *material);
    Element* element2 = new Element(nodes, *material);
    elements.push_back(element1);
    elements.push_back(element2);

    // Initialize mesh and add elements
    mesh = new Mesh();
    for (auto element : elements) {
      mesh->addElement(*element);  // Pass the element by reference
    }

    // Clean up material
    delete material;
  }

  void TearDown() override {
    delete mesh;
    for (auto element : elements) {
      delete element;
    }
    for (auto node : nodes) {
      delete node;
    }
  }
};

TEST_F(SolverTest, DirectSolverTest) {
  DirectSolver solver;
  solver.solve(*mesh);

  // Add assertions based on expected results
  EXPECT_NEAR(nodes[1]->getDisplacement(0), 0.5, 1e-5);
  EXPECT_NEAR(nodes[1]->getDisplacement(1), 0.0, 1e-5);
  EXPECT_NEAR(nodes[1]->getDisplacement(2), 0.0, 1e-5);
}

// Repeat similar tests for other solvers
TEST_F(SolverTest, IterativeSolverTest) {
  IterativeSolver solver;
  solver.solve(*mesh);

  EXPECT_NEAR(nodes[1]->getDisplacement(0), 0.5, 1e-5);
  EXPECT_NEAR(nodes[1]->getDisplacement(1), 0.0, 1e-5);
  EXPECT_NEAR(nodes[1]->getDisplacement(2), 0.0, 1e-5);
}

TEST_F(SolverTest, SparseSolverTest) {
  SparseSolver solver;
  solver.solve(*mesh);

  EXPECT_NEAR(nodes[1]->getDisplacement(0), 0.5, 1e-5);
  EXPECT_NEAR(nodes[1]->getDisplacement(1), 0.0, 1e-5);
  EXPECT_NEAR(nodes[1]->getDisplacement(2), 0.0, 1e-5);
}
