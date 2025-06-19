#ifndef PATH_FINDER_HPP
#define PATH_FINDER_HPP

#include "Map.hpp"

class PathFinder
{
protected:
  Map m_map{};
public:
  // --- Public member functions ---
  virtual ~PathFinder() = default;
  virtual void nextStep() = 0;
  virtual const Map& get() const;
  virtual void setMap(const Map& map);
};


#endif
