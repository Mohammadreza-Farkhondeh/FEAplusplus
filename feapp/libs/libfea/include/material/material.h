#ifndef MATERIAL_H
#define MATERIAL_H

class Material {
 public:
  Material(double elasticModulus,
           double poissonRatio,
           double density,
           double yieldStrength,
           double crossSectionArea);

  double getElasticModulus() const;
  double getPoissonRatio() const;
  double getDensity() const;
  double getYieldStrength() const;
  double getShearModulus() const;
  double getCrossSectionArea() const;

 private:
  double elasticModulus;    // Elastic Modulus (E)
  double poissonRatio;      // Poisson's Ratio (ν)
  double density;           // Density (ρ)
  double yieldStrength;     // Yield Strength (σ_y)
  double crossSectionArea;  // Cross-sectional Area (A)
};

#endif  // MATERIAL_H
