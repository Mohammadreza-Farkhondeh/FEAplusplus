#ifndef SPARSE_SOLVER_H
#define SPARSE_SOLVER_H

#include "solvers/solver.h"

class SparseSolver : public Solver {
 public:
  void solve(const Mesh& mesh) const override;
};

#endif  // SPARSE_SOLVER_H