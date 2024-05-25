#include "fea/mesh.h"

Mesh::Mesh() : globalStiffnessMatrix(), globalForceVector() {}

void Mesh::addNode(const Node& node) {
    nodes.push_back(node);
}

void Mesh::addElement(const Element& element) {
    elements.push_back(element);
}

void Mesh::assignMaterial(Element& element, const Material& material) {
    element.setMaterial(material);
}


void Mesh::applyBoundaryCondition(const Node& node, int dofIndex, double value) {
    for (auto& n : nodes) {
        if (n.getCoordinates() == node.getCoordinates()) {
            n.applyBoundaryCondition(dofIndex, value);
            break;
        }
    }
}

void Mesh::applyLoad(const Node& node, const Load& load) {
    loads[node].push_back(load);
}


void Mesh::generateStiffnessMatrix() {
    globalStiffnessMatrix = Matrix(nodes.size() * 3, nodes.size() * 3); // Assuming 3 DOF per node
    for (const auto& element : elements) {
        std::vector<int> dofMap; // Create DOF map for the element
        element.assemble(globalStiffnessMatrix, dofMap);
    }
}

void Mesh::generateStiffnessMatrix() {
    // Initializing the global stiffness matrix size based on the total degrees of freedom
    int totalDOF = nodes.size() * 3; // Assuming 3 DOF per node (x, y, z)
    globalStiffnessMatrix.resize(totalDOF, totalDOF);
    globalForceVector.resize(totalDOF);

    // Performing a loop through each element to assemble the global stiffness matrix
    for (const auto& element : elements) {
        Matrix elementStiffness = element.computeStiffnessMatrix();
        std::vector<int> dofMap = element.getDOFMap();

        // Assembling the element stiffness matrix into the global stiffness matrix
        for (size_t i = 0; i < dofMap.size(); ++i) {
            for (size_t j = 0; j < dofMap.size(); ++j) {
                globalStiffnessMatrix(dofMap[i], dofMap[j]) += elementStiffness(i, j);
            }
        }
    }

    // Applying boundary conditions
    for (const auto& bc : boundaryConditions) {
        const Node& node = bc.first;
        for (const auto& [dofIndex, value] : bc.second) {
            int globalIndex = node.getGlobalDOFIndex(dofIndex);
            globalStiffnessMatrix(globalIndex, globalIndex) = 1e30; // Large number to simulate fixed DOF
            globalForceVector(globalIndex) = value * 1e30;
        }
    }

    // Applying loads
    for (const auto& load : loads) {
        const Node& node = load.first;
        for (const auto& l : load.second) {
            l.apply(node);
        }
    }
}

const std::vector<Node>& Mesh::getNodes() const {
    return nodes;
}

const std::vector<Element>& Mesh::getElements() const {
    return elements;
}

const Matrix& Mesh::getGlobalStiffnessMatrix() const {
    return globalStiffnessMatrix;
}

const Vector& Mesh::getGlobalForceVector() const {
    return globalForceVector;
}