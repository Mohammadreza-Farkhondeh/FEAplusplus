#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include "common/common.h"
#include "geometry/node.h"
#include "geometry/element.h"
#include "material/material.h"
#include "loads/load.h"
#include "fea/mesh.h"
#include <vector>

class Preprocessor {
public:
    Preprocessor();

    void generateMesh(const std::vector<std::vector<double>>& nodeCoordinates, 
                      const std::vector<std::vector<int>>& elementConnectivity,
                      const std::vector<Material>& materials);

    void applyBoundaryConditions(const std::vector<std::vector<int>>& boundaryNodeIndices,
                                 const std::vector<int>& boundaryDOFIndices,
                                 const std::vector<double>& boundaryValues);

    void applyLoads(const std::vector<int>& loadNodeIndices,
                    const std::vector<std::vector<double>>& loadVectors);

    void preprocess();

    const Mesh& getMesh() const;

private:
    Mesh mesh;
};

#endif // PREPROCESSOR_H
