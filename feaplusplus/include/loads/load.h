#ifndef LOAD_H
#define LOAD_H

#include "geometry/node.h"

class Load {
public:
    virtual void apply(Node& node) const = 0;
};

#endif // LOAD_H