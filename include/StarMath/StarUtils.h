#ifndef STAR_UTILS_H
#define STAR_UTILS_H

#include <cmath>
#include <limits>

namespace Star
{
  template<typename T> bool isZero(T val)
  {
    return std::abs(val) <= std::numeric_limits<T>::epsilon();
  }

  template<typename T> T deg2Rad(T val)
  {
    return val*M_PI/T(180);
  }

  template<typename T> T rad2Deg(T val)
  {
    return val*T(180)/T(M_PI);
  }
}

#endif
