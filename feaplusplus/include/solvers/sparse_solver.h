#ifndef SPARSE_SOLVER_H
#define SPARSE_SOLVER_H

#include "solver.h"

class SparseSolver : public Solver {
public:
    virtual void solve(const Mesh& mesh) const override;
};

#endif // SPARSE_SOLVER_H
