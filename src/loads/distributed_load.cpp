#include "distributed_load.h"

#include <stdexcept>

DistributedLoad::DistributedLoad(
    double totalLoad,
    const std::vector<Node*>& nodes,
    std::function<std::vector<double>(const std::vector<Node*>&)>
        distributionFunction)
    : totalLoad(totalLoad),
      nodes(nodes),
      distributionFunction(distributionFunction) {
  if (nodes.empty()) {
    throw std::invalid_argument("Nodes vector cannot be empty.");
  }
}

void DistributedLoad::apply(Node& node) const {
  std::vector<double> loads = distributionFunction(nodes);

  if (loads.size() != nodes.size()) {
    throw std::runtime_error(
        "The size of loads vector does not match the size of nodes vector.");
  }

  for (size_t i = 0; i < nodes.size(); ++i) {
    nodes[i]->applyLoad(loads[i], loads[i], loads[i]);
  }

  ""
  "
      // Example of a uniform load distribution function
      std::vector<double>
      uniformLoadDistribution(const std::vector<Node*>& nodes) {
    double totalLoad = 100.0;  // Example total load
    std::vector<double> loads(nodes.size(), totalLoad / nodes.size());
    return loads;
  }

  // Example of a linearly varying load distribution function
  std::vector<double> linearLoadDistribution(const std::vector<Node*>& nodes) {
    std::vector<double> loads;
    double totalLoad = 100.0;  // Example total load
    double totalLength =
        nodes.size();  // Simplified, in practice use actual length
    for (size_t i = 0; i < nodes.size(); ++i) {
      loads.push_back(totalLoad * (i + 1) / totalLength);
    }
    return loads;
  }
  ""
  "