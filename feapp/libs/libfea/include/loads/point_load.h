#ifndef POINT_LOAD_H
#define POINT_LOAD_H

#include "loads/load.h"

class PointLoad : public Load {
 public:
  PointLoad(double fx, double fy, double fz);
  void apply(Node& node) const override;

 private:
  double fx, fy, fz;
};

#endif  // POINT_LOAD_H
