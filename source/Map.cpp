#include "Map.hpp"

Map::Map(const std::vector<std::vector<char>> &map, const char start,
         const char end, const char wall, const char none)
    : m_map(map.size(), std::vector<Element>{})

{
  for (unsigned int y{}; y < map.size(); ++y)
  {
    (m_map[y]).resize((map[y]).size());

    for (unsigned int x{}; x < (map[y]).size(); ++x)
    {
      if(map[y][x] == start)
      {
        m_map[y][x] = Element::START;
        m_start = Position{x,y};
      }
      else if (map[y][x] == end)
      {
        m_map[y][x] = Element::END;
        m_end = Position{x, y};
      }
      else if (map[y][x] == wall)
      {
        m_map[y][x] = Element::WALL;
      }
      else if (map[y][x] == none)
      {
        m_map[y][x] = Element::EMPTY;
      }
      else 
      {
        m_map[y][x] = Element::EMPTY;
      }
    }
  }
}


const Position& Map::getStartPosition()
{
  return m_start;
}
const Position& Map::getEndPosition()
{
  return m_end;
}

Map::Element Map::get(unsigned int x, unsigned int y)
{
  return m_map[y][x];
}

Map::Element Map::get(const Position& pos)
{
  return get(pos.x, pos.y);
}
