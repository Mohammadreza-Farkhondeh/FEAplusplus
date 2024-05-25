#ifndef DISTRIBUTED_LOAD_H
#define DISTRIBUTED_LOAD_H

#include "geometry/node.h"
#include "loads/load.h"
#include <vector>

class DistributedLoad : public Load {
public:
    DistributedLoad(double magnitude, const std::vector<Node*>& nodes);

    void apply(Node& node) const override;

private:
    double magnitude;
    std::vector<Node*> nodes;
};

#endif // DISTRIBUTED_LOAD_H
