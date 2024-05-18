#ifndef POINT_LOAD_H
#define POINT_LOAD_H

#include "geometry/node.h"
#include "loads/load.h"

class PointLoad : public Load {
public:
    PointLoad(double magnitude, const Node& node);

    double getMagnitude() const;
    Node getNode() const;

private:
    double magnitude; // Magnitude of the load
    Node node;        // Node at which the load is applied
};

#endif // POINT_LOAD_H