#ifndef SOLVER_H
#define SOLVER_H

#include "mesh.h"

class Solver {
public:
    virtual void solve(const Mesh& mesh) const = 0;
};

#endif // SOLVER_H
