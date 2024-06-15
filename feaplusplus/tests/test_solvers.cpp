#include "gtest/gtest.h"
#include "solvers/direct_solver.h"
#include "solvers/iterative_solver.h"
#include "solvers/sparse_solver.h"
#include "geometry/node.h"
#include "geometry/element.h"
#include "material/material.h"
#include "fea/mesh.h"
#include "loads/point_load.h"

class SolverTest : public ::testing::Test {
protected:
    void SetUp() override {
        nodes.emplace_back(new Node(0.0, 0.0, 0.0));
        nodes.emplace_back(new Node(1.0, 0.0, 0.0));

        material = new Material(200.0, 0.3, 7800.0, 250.0);

        elements.emplace_back(new Element({nodes[0], nodes[1]}, *material));

        mesh = new Mesh(elements);

        nodes[0]->applyBoundaryCondition(0, 0.0);
        nodes[0]->applyBoundaryCondition(1, 0.0);
        nodes[0]->applyBoundaryCondition(2, 0.0);

        PointLoad load(100.0, 0.0, 0.0);
        load.apply(*nodes[1]);
    }

    void TearDown() override {
        delete mesh;
        delete material;
        for (auto node : nodes) {
            delete node;
        }
        for (auto element : elements) {
            delete element;
        }
    }

    std::vector<Node*> nodes;
    Material* material;
    std::vector<Element*> elements;
    Mesh* mesh;
};

TEST_F(SolverTest, DirectSolver) {
    DirectSolver solver;
    solver.solve(*mesh);

    EXPECT_NEAR(nodes[1]->getDisplacement(0), 0.5, 1e-5);
    EXPECT_NEAR(nodes[1]->getDisplacement(1), 0.0, 1e-5);
    EXPECT_NEAR(nodes[1]->getDisplacement(2), 0.0, 1e-5);
}

TEST_F(SolverTest, IterativeSolver) {
    IterativeSolver solver;
    solver.solve(*mesh);

    EXPECT_NEAR(nodes[1]->getDisplacement(0), 0.5, 1e-5);
    EXPECT_NEAR(nodes[1]->getDisplacement(1), 0.0, 1e-5);
    EXPECT_NEAR(nodes[1]->getDisplacement(2), 0.0, 1e-5);
}

TEST_F(SolverTest, SparseSolver) {
    SparseSolver solver;
    solver.solve(*mesh);

    EXPECT_NEAR(nodes[1]->getDisplacement(0), 0.5, 1e-5);
    EXPECT_NEAR(nodes[1]->getDisplacement(1), 0.0, 1e-5);
    EXPECT_NEAR(nodes[1]->getDisplacement(2), 0.0, 1e-5);
}
