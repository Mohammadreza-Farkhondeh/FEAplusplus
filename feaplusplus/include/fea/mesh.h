#ifndef MESH_H
#define MESH_H

#include "common/common.h"
#include "geometry/node.h"
#include "geometry/element.h"
#include "loads/load.h"
#include <vector>
#include <unordered_map>

class Mesh {
public:
    Mesh();

    // Methods to add nodes and elements
    void addNode(const Node& node);
    void addElement(const Element& element);

    // Method to assign material to an element
    void assignMaterial(Element& element, const Material& material);

    // Methods to apply boundary conditions and loads
    void applyBoundaryCondition(Node& node, int dofIndex, double value);
    void applyLoad(Node& node, const Load& load);

    // Method to generate the global stiffness matrix
    void generateStiffnessMatrix();

    // Getters for nodes and elements
    const std::vector<Node>& getNodes() const;
    const std::vector<Element>& getElements() const;

    // Getters for global stiffness matrix and force vector
    const Matrix& getGlobalStiffnessMatrix() const;
    const Vector& getGlobalForceVector() const;

private:
    std::vector<Node> nodes;
    std::vector<Element> elements;
    Matrix globalStiffnessMatrix;
    Vector globalForceVector;
    std::unordered_map<Node, std::vector<std::pair<int, double>>> boundaryConditions; // Node -> (DOF, value)
    std::unordered_map<Node, std::vector<Load>> loads; // Node -> Loads
};

#endif // MESH_H
