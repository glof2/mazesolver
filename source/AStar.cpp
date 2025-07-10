#include "./../header/AStar.hpp"
#include "PathFinder.hpp"
#include "Position.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <memory>

float AStar::getH(const Position &from, const Position &to)
{
  // Manhattan style
  return std::abs((int)(from.x - to.x)) + std::abs((int)(from.y - to.y));
}

std::shared_ptr<AStar::Node>
AStar::constructNode(const std::shared_ptr<Node> &parent,
                     const Position &node_position,
                     const Position &end_position, const float &g)
{
  std::shared_ptr<Node> new_node{std::make_shared<Node>()};
  new_node->position = node_position;
  new_node->g = g;
  new_node->h = getH(node_position, end_position);
  new_node->f = new_node->h + new_node->g;
  new_node->parent = parent;

  return new_node;
}

AStar::AStar(const Map &map) : PathFinder(map) {}

void AStar::init()
{
  Position start_pos{m_map.getStartPosition()};
  float g{0};

  m_open.push_back(
      constructNode(nullptr, start_pos, m_map.getEndPosition(), g));
}

void AStar::nextStep()
{
  if (m_open.size() == 0)
  {
    std::cout << "NO OPEN LEFT!\n";
    return;
  }

  // Find the node with the least F on the open list
  const std::vector<std::shared_ptr<Node>>::iterator current_it{
      (std::min_element(m_open.begin(), m_open.end(),
                        [](const auto &a, const auto &b)
                        { return a->f < b->f; }))};

  std::shared_ptr<Node> current{(*current_it)};

  // Add current node to the closed list
  m_closed.push_back(current);

  // Erase the current node from the open list
  m_open.erase(current_it);

  // Generate successors
  std::vector<std::shared_ptr<Node>> successors(4, nullptr);
  const float g{current->g + 1};

  // Calculate positions
  Position above{current->position};
  above.y -= 1;

  Position below{current->position};
  below.y += 1;

  Position left{current->position};
  left.x -= 1;

  Position right{current->position};
  right.x += 1;

  successors[0] = constructNode(current, above, m_map.getEndPosition(), g);

  successors[1] = constructNode(current, below, m_map.getEndPosition(), g);

  successors[2] = constructNode(current, left, m_map.getEndPosition(), g);

  successors[3] = constructNode(current, right, m_map.getEndPosition(), g);

  // Verify successors
  for (auto &successor : successors)
  {

    // Check if it's the goal
    const Position end_position{m_map.getEndPosition()};
    if (successor->position.x == end_position.x &&
        successor->position.y == end_position.y)
    {
      // Stop search ...
      std::cout << "FOUND SOLUTION!\n";
      std::shared_ptr<Node> ptr{successor};
      std::vector<std::vector<bool>> solution(
          m_map.getSizeX(0), std::vector<bool>(m_map.getSizeY(), false));
      while (ptr != nullptr)
      {
        std::cout << " -> ";
        std::cout << "(" << ptr->position.x << ", " << ptr->position.y << ")";

        if (solution[ptr->position.y].size() != m_map.getSizeX(ptr->position.y))
        {
          solution[ptr->position.y].resize(m_map.getSizeX(ptr->position.y));
        }
        solution[ptr->position.y][ptr->position.x] = true;

        ptr = ptr->parent;
      }

      std::cout << "\n\n";

      // Print map
      for (int y{}; y < m_map.getSizeY(); ++y)
      {
        for (int x{}; x < m_map.getSizeX(y); ++x)
        {
          if (solution[y][x])
          {
            std::cout << "X";
          }
          else if (m_map.isTraversable(x, y))
          {
            std::cout << " ";
          }
          else
          {
            std::cout << "#";
          }
        }
        std::cout << '\n';
      }

      std::cout << '\n';
      //      std::cout << "parent: " << ptr->parent << '\n';

      continue;
    }

    // Check if the coordinates are valid
    if (successor->position.y < 0 || successor->position.y >= m_map.getSizeY())
    {
      continue;
    }

    if (successor->position.x < 0 ||
        successor->position.x >= m_map.getSizeX(successor->position.y))
    {

      continue;
    }

    // Check if the position is "walkable"
    if (!m_map.isTraversable(successor->position.x, successor->position.y))
    {

      continue;
    }

    // Check if it's in the closed list
    std::vector<std::shared_ptr<Node>>::iterator closed_it{
        std::find_if(m_closed.begin(), m_closed.end(),
                     [successor](const std::shared_ptr<Node> &a)
                     {
                       return a->position.x == successor->position.x &&
                              a->position.y == successor->position.y;
                     })};

    if (closed_it != m_closed.end())
    {

      continue;
    }

    // Check if it's in open list
    std::vector<std::shared_ptr<Node>>::iterator open_it{
        std::find_if(m_open.begin(), m_open.end(),
                     [successor](const std::shared_ptr<Node> &a)
                     {
                       return a->position.x == successor->position.x &&
                              a->position.y == successor->position.y;
                     })};

    if (open_it != m_open.end())
    {
      if (successor->f >= (*open_it)->f)
      {

        continue;
      }

      // Erase the higher cost open node
      m_open.erase(open_it);
    }

    // Add successor to the open list
    m_open.push_back(successor);
  }
}
