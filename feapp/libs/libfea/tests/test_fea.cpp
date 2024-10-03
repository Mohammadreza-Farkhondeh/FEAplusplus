#include "gtest/gtest.h"
#include "fea/mesh.h"
#include "geometry/node.h"
#include "geometry/element.h"
#include "material/material.h"
#include "loads/point_load.h"
#include "solvers/direct_solver.h"
#include "solvers/iterative_solver.h"
#include "solvers/sparse_solver.h"

class FEATest : public ::testing::Test {
protected:
    FEATest() 
        : material(200.0, 0.3, 7800.0, 250.0, 0.01), 
          nodes{Node(0.0, 0.0, 0.0), Node(1.0, 0.0, 0.0)}, 
          elements{Element({&nodes[0], &nodes[1]}, material)} {}

    void SetUp() override {
        mesh.addNode(nodes[0]);
        mesh.addNode(nodes[1]);
        mesh.addElement(elements[0]);

        mesh.applyBoundaryCondition(nodes[0], 0, 0.0);
        mesh.applyBoundaryCondition(nodes[0], 1, 0.0);
        mesh.applyBoundaryCondition(nodes[0], 2, 0.0);

        PointLoad load(100.0, 0.0, 0.0);
        mesh.applyLoad(nodes[1], load);
    }

    std::vector<Node> nodes;
    Material material;
    std::vector<Element> elements;
    Mesh mesh;
};

TEST_F(FEATest, AddNodesAndElements) {
    EXPECT_EQ(mesh.getNodes().size(), 2);
    EXPECT_EQ(mesh.getElements().size(), 1);
}

TEST_F(FEATest, ApplyBoundaryConditions) {
    const auto& bc = mesh.getBoundaryConditions();
    EXPECT_EQ(bc.at(nodes[0]).size(), 3);
}

TEST_F(FEATest, ApplyLoads) {
    const auto& loads = mesh.getLoads();
    EXPECT_EQ(loads.at(nodes[1]).size(), 1);
}

TEST_F(FEATest, GenerateStiffnessMatrixAndForceVector) {
    mesh.generateStiffnessMatrix();

    const Matrix& K = mesh.getGlobalStiffnessMatrix();
    const Vector& F = mesh.getGlobalForceVector();

    EXPECT_EQ(K.size(), 6);
    EXPECT_EQ(K[0].size(), 6);
    EXPECT_EQ(F.size(), 6);

    EXPECT_NEAR(F[3], 100.0, 1e-5);
    EXPECT_NEAR(F[4], 0.0, 1e-5);
    EXPECT_NEAR(F[5], 0.0, 1e-5);
}

class FEASolverTest : public FEATest {
protected:
    FEASolverTest() = default;

    void SetUp() override {
        FEATest::SetUp();
        mesh.generateStiffnessMatrix();
    }
};

TEST_F(FEASolverTest, DirectSolver) {
    DirectSolver solver;
    solver.solve(mesh);

    EXPECT_NEAR(nodes[1].getDisplacement(0), 0.5, 1e-5);
    EXPECT_NEAR(nodes[1].getDisplacement(1), 0.0, 1e-5);
    EXPECT_NEAR(nodes[1].getDisplacement(2), 0.0, 1e-5);
}

TEST_F(FEASolverTest, IterativeSolver) {
    IterativeSolver solver;
    solver.solve(mesh);

    EXPECT_NEAR(nodes[1].getDisplacement(0), 0.5, 1e-5);
    EXPECT_NEAR(nodes[1].getDisplacement(1), 0.0, 1e-5);
    EXPECT_NEAR(nodes[1].getDisplacement(2), 0.0, 1e-5);
}

TEST_F(FEASolverTest, SparseSolver) {
    SparseSolver solver;
    solver.solve(mesh);

    EXPECT_NEAR(nodes[1].getDisplacement(0), 0.5, 1e-5);
    EXPECT_NEAR(nodes[1].getDisplacement(1), 0.0, 1e-5);
    EXPECT_NEAR(nodes[1].getDisplacement(2), 0.0, 1e-5);
}
