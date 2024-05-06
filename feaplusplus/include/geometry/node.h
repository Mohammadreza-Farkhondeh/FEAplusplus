#ifndef FEAPLUSPLUS_NODE_H
#define FEAPLUSPLUS_NODE_H

class Node {
public:
  // Constructor to initialize node coordinates
  Node(double x, double y, double z = 0.0);

  // Getters for node coordinates
  double get_x() const { return x_; }
  double get_y() const { return y_; }
  double get_z() const { return z_; }

private:
  // Member variables to store coordinates
  double x_;
  double y_;
  double z_;
};

#endif