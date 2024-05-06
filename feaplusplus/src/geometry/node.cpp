#include "include/geometry/node.h"

Node::Node(double x, double y, double z) : x_(x), y_(y), z_(z) {}

double Node::get_x() const { return x_; }

double Node::get_y() const { return y_; }

double Node::get_z() const { return z_; }
