#ifndef DISTRIBUTED_LOAD_H
#define DISTRIBUTED_LOAD_H

#include "geometry/node.h"
#include "loads/load.h"
#include <vector>
#include <functional>

class DistributedLoad : public Load {
public:
    DistributedLoad(double totalLoad, const std::vector<Node*>& nodes, std::function<std::vector<double>(const std::vector<Node*>&)> distributionFunction);

    void apply(Node& node) const override;

private:
    double totalLoad;
    std::vector<Node*> nodes;
    std::function<std::vector<double>(const std::vector<Node*>&)> distributionFunction;
};

#endif // DISTRIBUTED_LOAD_H
