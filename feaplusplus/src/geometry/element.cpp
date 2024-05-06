#include "include/geometry/element.h"
#include "include/geometry/node.h"

Element::Element(int type, const std::vector<Node*>& nodes) : type_(type), nodes_(nodes) {
}

int Element::get_type() const { return type_; }

const std::vector<Node*>& Element::get_nodes() const { return nodes_; }
