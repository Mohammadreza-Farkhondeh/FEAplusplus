#ifndef DIRECT_SOLVER_H
#define DIRECT_SOLVER_H

#include "solver.h"

class DirectSolver : public Solver {
public:
    virtual void solve(const Mesh& mesh) const override;
};

#endif // DIRECT_SOLVER_H
