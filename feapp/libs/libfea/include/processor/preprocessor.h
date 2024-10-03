#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include <vector>
#include "common/common.h"
#include "fea/mesh.h"
#include "geometry/element.h"
#include "geometry/node.h"
#include "loads/load.h"
#include "material/material.h"

class Preprocessor {
 public:
  Preprocessor();

  void generateMesh(const std::vector<std::vector<double>>& nodeCoordinates,
                    const std::vector<std::vector<int>>& elementConnectivity,
                    const std::vector<Material>& materials);

  void applyBoundaryConditions(const std::vector<int>& boundaryNodeIndices,
                               const std::vector<int>& boundaryDOFIndices,
                               const std::vector<double>& boundaryValues);

  void applyLoads(const std::vector<int>& loadNodeIndices,
                  const std::vector<std::vector<double>>& loadVectors);

  const Mesh& getMesh() const;

 private:
  Mesh mesh;
};

#endif  // PREPROCESSOR_H
