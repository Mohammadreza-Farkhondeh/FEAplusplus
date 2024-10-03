#ifndef FEA_H
#define FEA_H

#include "fea/mesh.h"
#include "postprocessor/postprocessor.h"
#include "solvers/solver.h"

class FEA {
 public:
  FEA();

  void setSolver(Solver* solver);
  void setupModel(const Mesh& mesh);
  void analyze();
  void visualizeResults();
  void generateReport();

 private:
  Mesh mesh;
  Solver* solver;
  Postprocessor postprocessor;
};

#endif  // FEA_H
