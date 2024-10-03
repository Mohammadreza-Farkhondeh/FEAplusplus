#ifndef ANALYSIS_RESULT_H
#define ANALYSIS_RESULT_H

#include <vector>
#include "geometry/node.h"

struct AnalysisResult {
  const Node* node1;
  const Node* node2;
  double stress;
  double strain;
  double moment;
  double shear;
};

#endif  // ANALYSIS_RESULT_H
