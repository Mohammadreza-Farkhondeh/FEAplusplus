#ifndef NODE_H
#define NODE_H

#include <vector>

class Node {
public:
    Node(double x, double y, double z);
    int id;

    bool operator==(const Node& other) const {
        return id == other.id && coordinates[0] == other.coordinates[0] && coordinates[1] == other.coordinates[1] && coordinates[2] == other.coordinates[2];
    }

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

namespace std {
    template<>
    struct hash<Node> {
        std::size_t operator()(const Node& node) const {
            std::size_t h1 = std::hash<int>()(node.id);
            std::size_t h2 = std::hash<double>()(node.getCoordinates()[0]);
            std::size_t h3 = std::hash<double>()(node.getCoordinates()[1]);
            std::size_t h4 = std::hash<double>()(node.getCoordinates()[2]);
            return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3);
        }
    };
}

#endif // NODE_H
