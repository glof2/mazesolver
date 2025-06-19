#ifndef PATH_FINDER_HPP
#define PATH_FINDER_HPP

#include "Map.hpp"

class PathFinder
{
private:
  // Probably won't need anything here!
public:
  // --- Public member functions ---
  virtual ~PathFinder() = default;
  virtual void nextStep() = 0;
  virtual const Map& get() const = 0;
};


#endif
