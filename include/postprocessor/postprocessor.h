#ifndef POSTPROCESSOR_H
#define POSTPROCESSOR_H

#include "common/common.h"
#include "geometry/element.h"
#include "material/material.h"
#include "common/analysis_result.h"

class Postprocessor {
public:
    Postprocessor();

    std::vector<AnalysisResult> calculateStresses(const Mesh& mesh);
    std::vector<AnalysisResult> calculateStrains(const Mesh& mesh);
    std::vector<AnalysisResult> calculateMoments(const Mesh& mesh);
    std::vector<AnalysisResult> calculateShears(const Mesh& mesh);

private:
    double calculateElementStress(const Element& element, const Vector& displacementVector) const;
    double calculateElementStrain(const Element& element, const Vector& displacementVector) const;
    double calculateElementMoment(const Element& element, const Vector& displacementVector) const;
    double calculateElementShear(const Element& element, const Vector& displacementVector) const;
};

#endif // POSTPROCESSOR_H
