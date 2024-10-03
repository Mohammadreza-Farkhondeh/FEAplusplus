#ifndef ITERATIVE_SOLVER_H
#define ITERATIVE_SOLVER_H

#include "solvers/solver.h"

class IterativeSolver : public Solver {
 public:
  void solve(const Mesh& mesh) const override;
};

#endif  // ITERATIVE_SOLVER_H