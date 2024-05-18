#include "loads/distributed_load.h"

DistributedLoad::DistributedLoad(double magnitude, const std::vector<Node>& nodes)
    : magnitude(magnitude), nodes(nodes) {}

double DistributedLoad::getMagnitude() const {
    return magnitude;
}

std::vector<Node> DistributedLoad::getNodes() const {
    return nodes;
}
