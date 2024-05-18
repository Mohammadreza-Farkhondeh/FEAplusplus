#include "mesh.h"

Mesh::Mesh() {
}

void Mesh::addNode(const Node& node) {
    nodes.push_back(node);
}

void Mesh::addElement(const Element& element) {
    elements.push_back(element);
}

void Mesh::assignMaterial(const Element& element, const Material& material) {
}

void Mesh::applyLoad(const Node& node, const Load& load) {
}

void Mesh::generateStiffnessMatrix() {
}
