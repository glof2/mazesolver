#ifndef ASTAR_HPP
#define ASTAR_HPP
#include "PathFinder.hpp"
#include "Position.hpp"
#include <memory>
#include <vector>

class AStar : public PathFinder
{
private:
  struct Node
  {
    Position position;
    float g;
    float h;
    float f;
    std::shared_ptr<Node> parent;
  };

  float getH(const Position &from, const Position &to);

  std::shared_ptr<Node> constructNode(const std::shared_ptr<Node> &parent,
                                      const Position &node_position,
                                      const Position &end_position,
                                      const float &g = 0);

public:
  AStar(const Map &map);
  virtual ~AStar() = default;

  virtual void init() override;
  virtual void nextStep() override;

private:
  std::vector<std::shared_ptr<Node>> m_open{};
  std::vector<std::shared_ptr<Node>> m_closed{};
};

#endif
