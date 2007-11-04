#ifndef STAR_UTILS_H
#define STAR_UTILS_H

#include <cmath>
#include <limits>

namespace Star
{
  template<typename T> bool isZero(T val)
  {
    return std::abs(val) < std::numeric_limits<T>::epsilon();
  }
}

#endif
