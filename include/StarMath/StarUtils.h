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

    template<typename T> inline T upDiv(T a, T b)
    {
        return T(ceil(double(a)/double(b)));
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
            return T(1);

        return sin(x)/x;
    }

    template<typename T> inline T lanczos2(T x)
    {
        if (std::abs(x) >= T(2))
            return 0;
        return Star::sinc(M_PI*x)*Star::sinc(M_PI*x/T(2));
    }

    template<typename T> inline T lanczos3(T x)
    {
        if (std::abs(x) >= T(3))
            return 0;
        return Star::sinc(T(M_PI)*x)*Star::sinc(T(M_PI)*x/T(3));
    }

    template<typename T> inline T align(T val, unsigned int alignment)
    {
        return (val+alignment-1) & ~(alignment-1);
    }
}

#endif
