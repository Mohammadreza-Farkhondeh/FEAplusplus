#ifndef NODE_H
#define NODE_H

#include <array>
#include <functional>

class Node {
 public:
  Node(double x, double y, double z);
  int id;

  bool operator==(const Node& other) const;

  void applyBoundaryCondition(int dofIndex, double value);
  void setDisplacement(int dofIndex, double displacement);
  double getDisplacement(int dofIndex) const;
  std::array<double, 3> getCoordinates() const;
  int getGlobalDOFIndex(int localDOFIndex) const;
  void applyLoad(double fx, double fy, double fz);
  std::array<double, 3> getLoads() const;
  std::array<double, 3> getBoundaryConditions() const;

 private:
  std::array<double, 3> coordinates;
  std::array<double, 3> displacements;
  std::array<double, 3> loads;
  std::array<double, 3> boundaryConditions;
};

namespace std {
template <>
struct hash<Node> {
  std::size_t operator()(const Node& node) const {
    std::size_t h1 = std::hash<int>()(node.id);
    auto coordinates = node.getCoordinates();
    std::size_t h2 = std::hash<double>()(coordinates[0]);
    std::size_t h3 = std::hash<double>()(coordinates[1]);
    std::size_t h4 = std::hash<double>()(coordinates[2]);

    std::size_t seed = 0;
    seed ^= h1 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    seed ^= h2 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    seed ^= h3 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    seed ^= h4 + 0x9e3779b9 + (seed << 6) + (seed >> 2);

    return seed;
  }
};
}  // namespace std

#endif  // NODE_H
