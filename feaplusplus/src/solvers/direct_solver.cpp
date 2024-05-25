#include "solvers/direct_solver.h"
#include <Eigen/Dense>

void DirectSolver::solve(const Mesh& mesh) const {
    const Matrix& K = mesh.getGlobalStiffnessMatrix();
    const Vector& F = mesh.getGlobalForceVector();
    Vector displacements(F.size());

    // Using Eigen's LU decomposition to solve K * displacements = F
    Eigen::MatrixXd K_eigen = Eigen::MatrixXd::Map(K.data(), K.size(), K[0].size());
    Eigen::VectorXd F_eigen = Eigen::VectorXd::Map(F.data(), F.size());
    Eigen::VectorXd displacements_eigen = K_eigen.fullPivLu().solve(F_eigen);

    // Copy the solution back to the displacements vector
    for (size_t i = 0; i < displacements.size(); ++i) {
        displacements[i] = displacements_eigen(i);
    }

    // Apply the displacements back to the mesh nodes
    for (size_t i = 0; i < mesh.getNodes().size(); ++i) {
        for (int j = 0; j < 3; ++j) {
            mesh.getNode(i).setDisplacement(j, displacements[3 * i + j]);
        }
    }
}
