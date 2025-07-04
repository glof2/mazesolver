#include "./../header/AStar.hpp"
#include "PathFinder.hpp"
#include <iostream>

AStar::AStar(const Map& map) : PathFinder(map) {}

void AStar::init() 
{ 
  m_open.push_back({ m_map.getStartPosition(), 0, 0, 0 });
}

void AStar::nextStep() { std::cout << "Next step in ASTAR!\n"; }
