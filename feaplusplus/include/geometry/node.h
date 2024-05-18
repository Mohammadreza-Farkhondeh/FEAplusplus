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

private:
    std::vector<double> coordinates;
    std::vector<double> displacements;
};

#endif // NODE_H