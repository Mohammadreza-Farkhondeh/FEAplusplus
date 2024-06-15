#include "solvers/sparse_solver.h"

#include <Eigen/Sparse>

void SparseSolver::solve(const Mesh& mesh) const {
  const Matrix& K = mesh.getGlobalStiffnessMatrix();
  const Vector& F = mesh.getGlobalForceVector();
  Vector displacements(F.size());

  Eigen::SparseMatrix<double> K_eigen(K.size(), K[0].size());
  for (size_t i = 0; i < K.size(); ++i) {
    for (size_t j = 0; j < K[i].size(); ++j) {
      K_eigen.insert(i, j) = K[i][j];
    }
  }
  Eigen::VectorXd F_eigen = Eigen::VectorXd::Map(F.data(), F.size());
  Eigen::SparseLU<Eigen::SparseMatrix<double>> solver;
  solver.compute(K_eigen);
  Eigen::VectorXd displacements_eigen = solver.solve(F_eigen);

  for (size_t i = 0; i < displacements.size(); ++i) {
    displacements[i] = displacements_eigen(i);
  }

  for (size_t i = 0; i < mesh.getNodes().size(); ++i) {
    for (int j = 0; j < 3; ++j) {
      mesh.getNode(i).setDisplacement(j, displacements[3 * i + j]);
    }
  }
}
