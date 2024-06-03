#include "material/material.h"

Material::Material(double elasticModulus, double poissonRatio, double density, double yieldStrength)
    : elasticsModulus(elasticModulus), poissonRatio(poissonRatio), density(density), yieldStrength(yieldStrength) {}

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