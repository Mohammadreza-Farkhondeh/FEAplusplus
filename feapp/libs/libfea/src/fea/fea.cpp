#include "fea/fea.h"

FEA::FEA() : solver(nullptr) {}

void FEA::setSolver(Solver* solver) {
  this->solver = solver;
}

void FEA::setupModel(const Mesh& mesh) {
  this->mesh = mesh;
  this->mesh.generateStiffnessMatrix();
}

void FEA::analyze() {
  if (solver) {
    solver->solve(mesh);
  } else {
    std::cerr << "No solver set!" << std::endl;
  }
}
