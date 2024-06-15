#include "gtest/gtest.h"
#include "geometry/node.h"
#include "geometry/element.h"
#include "material/material.h"

// Test Node class
TEST(NodeTest, Constructor) {
    Node node(1.0, 2.0, 3.0);
    std::vector<double> coordinates = node.getCoordinates();
    EXPECT_DOUBLE_EQ(coordinates[0], 1.0);
    EXPECT_DOUBLE_EQ(coordinates[1], 2.0);
    EXPECT_DOUBLE_EQ(coordinates[2], 3.0);
}

TEST(NodeTest, ApplyBoundaryCondition) {
    Node node(1.0, 2.0, 3.0);
    node.applyBoundaryCondition(0, 5.0);
    node.applyBoundaryCondition(1, 10.0);
    node.applyBoundaryCondition(2, 15.0);
    std::vector<double> bcs = node.getBoundaryConditions();
    EXPECT_DOUBLE_EQ(bcs[0], 5.0);
    EXPECT_DOUBLE_EQ(bcs[1], 10.0);
    EXPECT_DOUBLE_EQ(bcs[2], 15.0);
}

TEST(NodeTest, SetDisplacement) {
    Node node(1.0, 2.0, 3.0);
    node.setDisplacement(0, 1.5);
    node.setDisplacement(1, 2.5);
    node.setDisplacement(2, 3.5);
    EXPECT_DOUBLE_EQ(node.getDisplacement(0), 1.5);
    EXPECT_DOUBLE_EQ(node.getDisplacement(1), 2.5);
    EXPECT_DOUBLE_EQ(node.getDisplacement(2), 3.5);
}

TEST(NodeTest, ApplyLoad) {
    Node node(1.0, 2.0, 3.0);
    node.applyLoad(100.0, 200.0, 300.0);
    std::vector<double> loads = node.getLoads();
    EXPECT_DOUBLE_EQ(loads[0], 100.0);
    EXPECT_DOUBLE_EQ(loads[1], 200.0);
    EXPECT_DOUBLE_EQ(loads[2], 300.0);
}

// Test Element class
TEST(ElementTest, Constructor) {
    std::vector<Node*> nodes;
    nodes.push_back(new Node(1.0, 2.0, 3.0));
    nodes.push_back(new Node(4.0, 5.0, 6.0));
    Material material(210e9, 0.3, 7800, 250e6);
    Element element(nodes, material);
    EXPECT_EQ(element.getNodes().size(), 2);
}

TEST(ElementTest, ComputeStiffnessMatrix) {
    std::vector<Node*> nodes;
    nodes.push_back(new Node(0.0, 0.0, 0.0));
    nodes.push_back(new Node(1.0, 0.0, 0.0));
    Material material(210e9, 0.3, 7800, 250e6);
    Element element(nodes, material);

    Matrix stiffnessMatrix = element.computeStiffnessMatrix();
    double E = material.getElasticModulus();
    double A = material.getCrossSectionArea();
    double L = 1.0;
    double EA_L = (E * A) / L;

    EXPECT_DOUBLE_EQ(stiffnessMatrix[0][0], EA_L);
    EXPECT_DOUBLE_EQ(stiffnessMatrix[0][3], -EA_L);
    EXPECT_DOUBLE_EQ(stiffnessMatrix[3][0], -EA_L);
    EXPECT_DOUBLE_EQ(stiffnessMatrix[3][3], EA_L);
}

TEST(ElementTest, Assemble) {
    std::vector<Node*> nodes;
    nodes.push_back(new Node(0.0, 0.0, 0.0));
    nodes.push_back(new Node(1.0, 0.0, 0.0));
    Material material(210e9, 0.3, 7800, 250e6);
    Element element(nodes, material);

    size_t totalDof = 6;
    Matrix globalStiffnessMatrix(totalDof, std::vector<double>(totalDof, 0.0));
    std::vector<int> dofMap = element.getDOFMap();

    element.assemble(globalStiffnessMatrix, dofMap);

    double E = material.getElasticModulus();
    double A = material.getCrossSectionArea();
    double L = 1.0;
    double EA_L = (E * A) / L;

    EXPECT_DOUBLE_EQ(globalStiffnessMatrix[0][0], EA_L);
    EXPECT_DOUBLE_EQ(globalStiffnessMatrix[0][3], -EA_L);
    EXPECT_DOUBLE_EQ(globalStiffnessMatrix[3][0], -EA_L);
    EXPECT_DOUBLE_EQ(globalStiffnessMatrix[3][3], EA_L);
}

TEST(ElementTest, GetDOFMap) {
    std::vector<Node*> nodes;
    nodes.push_back(new Node(0.0, 0.0, 0.0));
    nodes.push_back(new Node(1.0, 0.0, 0.0));
    Material material(210e9, 0.3, 7800, 250e6);
    Element element(nodes, material);

    std::vector<int> dofMap = element.getDOFMap();
    EXPECT_EQ(dofMap.size(), 6);
    EXPECT_EQ(dofMap[0], 0);
    EXPECT_EQ(dofMap[1], 1);
    EXPECT_EQ(dofMap[2], 2);
    EXPECT_EQ(dofMap[3], 0);
    EXPECT_EQ(dofMap[4], 1);
    EXPECT_EQ(dofMap[5], 2);
}
