#ifndef FEAPLUSPLUS_ELEMENT_H
#define FEAPLUSPLUS_ELEMENT_H

#include "include/geometry/node.h"  // Include node header for element-node connection

class Element {
public:
  Element(int type, const std::vector<Node*>& nodes);

  int get_type() const { return type_; }
  const std::vector<Node*>& get_nodes() const { return nodes_; }

private:
  int type_;
  std::vector<Node*> nodes_;
};

#endif
