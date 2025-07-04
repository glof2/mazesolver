#ifndef ASTAR_HPP
#define ASTAR_HPP
#include "PathFinder.hpp"
#include "Position.hpp"
#include <vector>

class AStar : public PathFinder
{
private:
  struct Node
  {
    Position postion;
    float g;
    float h;
    float f;
  };

  std::vector<Node> m_open{};
  std::vector<Node> m_closed{};

public:
  virtual void init() override;
  virtual void nextStep() override;
};

#endif
