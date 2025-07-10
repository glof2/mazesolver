#ifndef MAP_HPP
#define MAP_HPP
#include "Position.hpp"
#include <vector>

class Map
{
public:
  enum class Element
  {
    EMPTY,
    START,
    END,
    WALL,
    INVALID,
  };

private:
  std::vector<std::vector<Element>> m_map{};
  Position m_start{};
  Position m_end{};

public:
  Map(const std::vector<std::vector<char>> &map, const char start = 'S',
      const char end = 'E', const char wall = '#', const char none = ' ');

  const Position &getStartPosition();
  const Position &getEndPosition();
  Element get(const unsigned int x, const unsigned int y);
  Element get(const Position &pos);

  std::size_t getSizeY();
  std::size_t getSizeX(const std::size_t &y);
  bool isTraversable(const unsigned int x, const unsigned int y);
};
#endif
