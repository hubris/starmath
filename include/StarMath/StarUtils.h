#ifndef STAR_UTILS_H
#define STAR_UTILS_H

#include <cmath>
#include <limits>

namespace Star
{
  template<typename T> inline bool isZero(T val)
  {
    return std::abs(val) <= std::numeric_limits<T>::epsilon();
  }

  template<typename T> inline T deg2Rad(T val)
  {
    return val*M_PI/T(180);
  }

  template<typename T> inline T rad2Deg(T val)
  {
    return val*T(180)/T(M_PI);
  }

  template<typename T> inline T lerp(const T& a, const T& b, const T& t)
  {
    return a+t*(b-a);
  }

  template<typename T> inline T clamp(const T& v, const T& a, const T& b)
  {
    return std::min(std::max(v, a), b);
  }

  template<typename T> inline T sinc(T x)
  {
    if (std::abs(x) < std::numeric_limits<T>::epsilon())
      return 1.;

    return sin(x)/x;
  }
}

#endif
