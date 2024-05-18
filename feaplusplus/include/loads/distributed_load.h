#ifndef DISTRIBUTED_LOAD_H
#define DISTRIBUTED_LOAD_H

#include "geometry/node.h"
#include "loads/load.h"

class DistributedLoad : public Load {
public:
    DistributedLoad(double magnitude, const std::vector<Node>& nodes);

    double getMagnitude() const;
    std::vector<Node> getNodes() const;

private:
    double magnitude;          // Magnitude of the load
    std::vector<Node> nodes;  // Nodes to which the load is applied
};

#endif // DISTRIBUTED_LOAD_H
