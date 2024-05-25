#include "distributed_load.h"

DistributedLoad::DistributedLoad(double magnitude, const std::vector<Node*>& nodes) : magnitude(magnitude), nodes(nodes) {}

void DistributedLoad::apply(Node& node) const {
    for (Node* n : nodes) {
        n->applyLoad(magnitude / nodes.size(), magnitude / nodes.size(), magnitude / nodes.size());
    }
}