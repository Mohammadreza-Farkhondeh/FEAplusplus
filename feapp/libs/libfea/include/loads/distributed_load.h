#ifndef DISTRIBUTED_LOAD_H
#define DISTRIBUTED_LOAD_H

#include <functional>
#include <vector>
#include "loads/load.h"

class DistributedLoad : public Load {
 public:
  DistributedLoad(double totalLoad,
                  const std::vector<Node*>& nodes,
                  std::function<std::vector<double>(const std::vector<Node*>&)>
                      distributionFunction);

  void apply(Node& node) const override;

 private:
  double totalLoad;
  std::vector<Node*> nodes;
  std::function<std::vector<double>(const std::vector<Node*>&)>
      distributionFunction;
};

#endif  // DISTRIBUTED_LOAD_H
