#include "gtest/gtest.h"
#include "material/material.h"

TEST(MaterialTest, GetElasticModulus) {
    Material material(200.0, 0.3, 7800.0, 250.0);
    EXPECT_DOUBLE_EQ(material.getElasticModulus(), 200.0);
}

TEST(MaterialTest, GetPoissonRatio) {
    Material material(200.0, 0.3, 7800.0, 250.0);
    EXPECT_DOUBLE_EQ(material.getPoissonRatio(), 0.3);
}

TEST(MaterialTest, GetDensity) {
    Material material(200.0, 0.3, 7800.0, 250.0);
    EXPECT_DOUBLE_EQ(material.getDensity(), 7800.0);
}

TEST(MaterialTest, GetYieldStrength) {
    Material material(200.0, 0.3, 7800.0, 250.0);
    EXPECT_DOUBLE_EQ(material.getYieldStrength(), 250.0);
}

TEST(MaterialTest, GetShearModulus) {
    Material material(200.0, 0.3, 7800.0, 250.0);
    double expectedShearModulus = material.getElasticModulus() / (2.0 * (1.0 + material.getPoissonRatio()));
    EXPECT_DOUBLE_EQ(material.getShearModulus(), expectedShearModulus);
}
