#ifndef NODE_H
#define NODE_H

#include <vector>

class Node {
public:
    Node(double x, double y, double z);

    void applyBoundaryCondition(int dofIndex, double value);
    void setDisplacement(int dofIndex, double displacement);
    double getDisplacement(int dofIndex) const;
    std::vector<double> getCoordinates() const;
    int getGlobalDOFIndex(int localDOFIndex) const;
    void applyLoad(double fx, double fy, double fz);
    std::vector<double> getLoads() const;
    std::vector<double> getBoundaryConditions() const;

private:
    std::vector<double> coordinates;
    std::vector<double> displacements;
    std::vector<double> loads;
    std::vector<double> boundaryConditions;
};

#endif // NODE_H
