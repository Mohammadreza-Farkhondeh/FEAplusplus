#include "solvers/solver.h"

Solver::Solver() {}

void Solver::addElement(const Element& element) {
    elements.push_back(element);
}

void Solver::solve() {
    // Placeholder for solver algorithm
    std::cout << "Solving FEA problem with " << elements.size() << " elements." << std::endl;
}