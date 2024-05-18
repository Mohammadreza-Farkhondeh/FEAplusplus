#ifndef ELEMENT_H
#define ELEMENT_H

#include <vector>
#include "geometry/node.h"
#include "material/material.h"
#include "common/common.h"

class Element {
public:
    Element(const std::vector<Node*>& nodes, const Material& material);
    const std::vector<Node*>& getNodes() const;
    Matrix computeStiffnessMatrix() const;
    void assemble(Matrix& globalStiffnessMatrix, const std::vector<int>& dofMap) const;

private:
    std::vector<Node*> nodes;
    Material material;
    std::vector<std::vector<int>> connectivity;
};

#endif // ELEMENT_H
