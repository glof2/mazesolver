#include "./../header/PathFinder.hpp"

PathFinder::PathFinder(const Map& map) : m_map{map} {}

const Map& PathFinder::get() const

{
  return m_map;
}

void PathFinder::setMap(const Map& map)
{
  m_map = map;
}
