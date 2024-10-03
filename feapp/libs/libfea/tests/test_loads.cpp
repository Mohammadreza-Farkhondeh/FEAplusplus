#include "gtest/gtest.h"
#include "geometry/node.h"
#include "loads/point_load.h"
#include "loads/distributed_load.h"

// PointLoad tests
TEST(PointLoadTest, ApplyPointLoad) {
    Node node(0.0, 0.0, 0.0);
    PointLoad pointLoad(100.0, 200.0, 300.0);

    pointLoad.apply(node);

    std::vector<double> loads = node.getLoads();
    EXPECT_DOUBLE_EQ(loads[0], 100.0);
    EXPECT_DOUBLE_EQ(loads[1], 200.0);
    EXPECT_DOUBLE_EQ(loads[2], 300.0);
}

// Example uniform load distribution function
std::vector<double> uniformLoadDistribution(const std::vector<Node*>& nodes) {
    double totalLoad = 100.0;  // Example total load
    std::vector<double> loads(nodes.size(), totalLoad / nodes.size());
    return loads;
}

// Example linearly varying load distribution function
std::vector<double> linearLoadDistribution(const std::vector<Node*>& nodes) {
    std::vector<double> loads;
    double totalLoad = 100.0;  // Example total load
    double totalLength = nodes.size();  // Simplified, in practice use actual length
    for (size_t i = 0; i < nodes.size(); ++i) {
        loads.push_back(totalLoad * (i + 1) / totalLength);
    }
    return loads;
}

// DistributedLoad tests
TEST(DistributedLoadTest, ApplyUniformDistributedLoad) {
    std::vector<Node*> nodes = {
        new Node(0.0, 0.0, 0.0),
        new Node(1.0, 0.0, 0.0),
        new Node(2.0, 0.0, 0.0)
    };
    DistributedLoad distLoad(300.0, nodes, uniformLoadDistribution);

    for (Node* node : nodes) {
        distLoad.apply(*node);
    }

    for (Node* node : nodes) {
        std::vector<double> loads = node->getLoads();
        EXPECT_DOUBLE_EQ(loads[0], 100.0);
        EXPECT_DOUBLE_EQ(loads[1], 100.0);
        EXPECT_DOUBLE_EQ(loads[2], 100.0);
    }

    for (Node* node : nodes) {
        delete node;
    }
}

TEST(DistributedLoadTest, ApplyLinearDistributedLoad) {
    std::vector<Node*> nodes = {
        new Node(0.0, 0.0, 0.0),
        new Node(1.0, 0.0, 0.0),
        new Node(2.0, 0.0, 0.0)
    };
    DistributedLoad distLoad(300.0, nodes, linearLoadDistribution);

    for (Node* node : nodes) {
        distLoad.apply(*node);
    }

    double expectedLoads[] = {33.3333, 66.6667, 100.0};

    for (size_t i = 0; i < nodes.size(); ++i) {
        std::vector<double> loads = nodes[i]->getLoads();
        EXPECT_NEAR(loads[0], expectedLoads[i], 1e-4);
        EXPECT_NEAR(loads[1], expectedLoads[i], 1e-4);
        EXPECT_NEAR(loads[2], expectedLoads[i], 1e-4);
    }

    for (Node* node : nodes) {
        delete node;
    }
}
