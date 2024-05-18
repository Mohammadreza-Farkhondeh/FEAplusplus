#ifndef MATERIAL_H
#define MATERIAL_H

#include <cmath>

class Material {
public:
    Material(double youngsModulus, double poissonRatio, double density, double yieldStrength);
    
    double getYoungsModulus() const;
    double getPoissonRatio() const;
    double getDensity() const;
    double getYieldStrength() const;

private:
    double youngsModulus;    // Young's Modulus (E)
    double poissonRatio;     // Poisson's Ratio (ν)
    double density;          // Density (ρ)
    double yieldStrength;    // Yield Strength (σ_y)
};

#endif // MATERIAL_H
