#include "material/material.h"

Material::Material(double elasticModulus, double poissonRatio, double density, double yieldStrength, double crossSectionArea)
    : elasticModulus(elasticModulus), poissonRatio(poissonRatio), density(density), yieldStrength(yieldStrength), crossSectionArea(crossSectionArea) {}

double Material::getElasticModulus() const {
    return elasticModulus;
}

double Material::getPoissonRatio() const {
    return poissonRatio;
}

double Material::getDensity() const {
    return density;
}

double Material::getYieldStrength() const {
    return yieldStrength;
}

double Material::getShearModulus() const {
    return elasticModulus / (2 * (1 + poissonRatio));
}

double Material::getCrossSectionArea() const {
    return crossSectionArea;
}
