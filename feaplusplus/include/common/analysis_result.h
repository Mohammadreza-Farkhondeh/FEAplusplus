#ifndef ANALYSIS_RESULT_H
#define ANALYSIS_RESULT_H

#include <vector>

struct AnalysisResult {
    int elementId;
    double stress;
    double strain;
    double moment;
    double shear;
};

#endif // ANALYSIS_RESULT_H
