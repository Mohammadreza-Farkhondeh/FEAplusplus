#include "material/material.h"

Material::Material(double youngsModulus, double poissonRatio, double density, double yieldStrength)
    : youngsModulus(youngsModulus), poissonRatio(poissonRatio), density(density), yieldStrength(yieldStrength) {}

double Material::getYoungsModulus() const {
    return youngsModulus;
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