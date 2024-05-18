#ifndef MESH_H
#define MESH_H

#include "geometry/node.h"
#include "geometry/element.h"
#include "loads/load.h"
#include <vector>

class Mesh {
public:
    Mesh();

    void addNode(const Node& node);
    void addElement(const Element& element);
    void assignMaterial(const Element& element, const Material& material);
    void applyBoundaryCondition(const Node& node, int dofIndex, double value);
    void applyLoad(const Node& node, const Load& load);
    void generateStiffnessMatrix();

private:
    std::vector<Node> nodes;
    std::vector<Element> elements;
};

#endif // MESH_H
