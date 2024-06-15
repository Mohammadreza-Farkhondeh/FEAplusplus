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
    void addNode(const Node& node);
    void addElement(const Element& element);
    void assignMaterial(Element& element, const Material& material);
    void applyBoundaryCondition(Node& node, int dofIndex, double value);
    void applyLoad(Node& node, const Load& load);
    void generateStiffnessMatrix();
    const std::vector<Node>& getNodes() const;
    const std::vector<Element>& getElements() const;
    const Matrix& getGlobalStiffnessMatrix() const;
    const Vector& getGlobalForceVector() const;

private:
    std::vector<Node> nodes;
    std::vector<Element> elements;
    Matrix globalStiffnessMatrix;
    Vector globalForceVector;
    std::unordered_map<Node, std::vector<std::pair<int, double>>> boundaryConditions;
    std::unordered_map<Node, std::vector<Load>> loads;
};

#endif // MESH_H
