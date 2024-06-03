#ifndef POSTPROCESSOR_H
#define POSTPROCESSOR_H

#include "common/common.h"
#include "geometry/element.h"
#include "fea/mesh.h"

class Postprocessor {
public:
    Postprocessor();

    // Method to calculate and output stresses for each element
    void calculateStresses(const Mesh& mesh);

    // Method to calculate and output strains for each element
    void calculateStrains(const Mesh& mesh);

    // Method to calculate and output moments for each element
    void calculateMoments(const Mesh& mesh);

    // Method to calculate and output shears for each element
    void calculateShears(const Mesh& mesh);

private:
    // Method to calculate stress for a given element
    double calculateElementStress(const Element& element, const Vector& displacementVector) const;

    // Method to calculate strain for a given element
    double calculateElementStrain(const Element& element, const Vector& displacementVector) const;

    // Method to calculate moment for a given element
    double calculateElementMoment(const Element& element, const Vector& displacementVector) const;

    // Method to calculate shear for a given element
    double calculateElementShear(const Element& element, const Vector& displacementVector) const;
};

#endif // POSTPROCESSOR_H
