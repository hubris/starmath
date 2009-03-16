#ifndef STARVEC2_H
#define STARVEC2_H

#include <iostream>
#include <cmath>

namespace Star
{
  template <typename T> class Vec2;
  template <typename T> Vec2<T> operator *( T, const Vec2<T>& );

  template <typename T>
  class Vec2
  {
  public:
    Vec2() {}
    Vec2 ( const T * );
    Vec2 ( T x, T y );

    // casting
    operator T* ();
    operator const T* () const;

    // assignment operators
    Vec2<T>& operator += ( const Vec2<T>& );
    Vec2<T>& operator -= ( const Vec2<T>& );
    Vec2<T>& operator *= ( T );
    Vec2<T>& operator /= ( T );

    // unary operators
    Vec2 operator + () const;
    Vec2 operator - () const;

    // binary operators
    Vec2 operator + ( const Vec2<T>& ) const;
    Vec2 operator - ( const Vec2<T>& ) const;
    Vec2 operator * ( T ) const;
    Vec2 operator / ( T ) const;

    template <typename T2> friend Vec2 operator *( T2, const Vec2<T2>& );

    bool operator == ( const Vec2<T>& ) const;
    bool operator != ( const Vec2<T>& ) const;

    /**
     * Compute the length of the vector.
     */
    T length() const;

    /**
     * Normalize the vector.
     * @return The vector length
     */
    T normalize();

    /**
     * Dot product.
     */
    T dot(const Vec2& a) const;

  public:
    T x, y;
  };

/*****************************************************************************/
  typedef Vec2<float> float2;
  typedef Vec2<double> double2;
  typedef Vec2<int> int2;
  typedef Vec2<unsigned int> uint2;

/*****************************************************************************/
  template <typename T>
  Vec2<T>::Vec2 ( const T *p )
  {
    x = p[0];
    y = p[1];
  }

/*****************************************************************************/
  template <typename T>
  Vec2<T>::Vec2 ( T x, T y )
  : x(x), y(y)
  {
  }

/*****************************************************************************/
  template <typename T>
  Vec2<T>::operator T* ()
  {
    return &x;
  }

/*****************************************************************************/
  template <typename T>
  Vec2<T>::operator const T* () const
  {
    return (const T*)&x;
  }

/*****************************************************************************/
  template <typename T>
  Vec2<T>&
  Vec2<T>::operator += ( const Vec2<T>& v )
  {
    x += v.x;
    y += v.y;

    return *this;
  }

/*****************************************************************************/
  template <typename T>
  Vec2<T>&
  Vec2<T>::operator -= ( const Vec2<T>& v )
  {
    x -= v.x;
    y -= v.y;

    return *this;
  }
/*****************************************************************************/
  template <typename T>
  Vec2<T>&
  Vec2<T>::operator *= ( T k )
  {
    x *= k;
    y *= k;

    return *this;
  }

/*****************************************************************************/
  template <typename T>
  Vec2<T>&
  Vec2<T>::operator /= ( T k )
  {
    x /= k;
    y /= k;

    return *this;
  }

/*****************************************************************************/
  template <typename T>
  Vec2<T>
  Vec2<T>::operator + () const
  {
    return *this;
  }

/*****************************************************************************/
  template <typename T>
  Vec2<T>
  Vec2<T>::operator - () const
  {
    return Vec2(-x, -y);
  }

/*****************************************************************************/
  template <typename T>
  Vec2<T>
  Vec2<T>::operator + ( const Vec2<T>& v ) const
  {
    return Vec2(x+v.x, y+v.y);
  }

/*****************************************************************************/
  template <typename T>
  Vec2<T>
  Vec2<T>::operator - ( const Vec2<T>& v ) const
  {
    return Vec2<T>(x-v.x, y-v.y);
  }

/*****************************************************************************/
  template <typename T>
  Vec2<T>
  Vec2<T>::operator * ( T k ) const
  {
    return Vec2<T>(x*k, y*k);
  }

/*****************************************************************************/
  template <typename T>
  Vec2<T>
  Vec2<T>::operator / ( T k ) const
  {
    return Vec2<T>(x/k, y/k);
  }

/*****************************************************************************/
  template <typename T>
  Vec2<T>
  operator * ( T k, const Vec2<T>& v )
  {
    return Vec2<T>(k*v.x, k*v.y);
  }

/*****************************************************************************/
  template <typename T>
  bool
  Vec2<T>::operator == ( const Vec2<T>& v ) const
  {
    return v.x == x && v.y == y;
  }

/*****************************************************************************/
  template <typename T>
  bool
  Vec2<T>::operator != ( const Vec2<T>& v ) const
  {
    return v.x != x || v.y != y;
  }

  /*****************************************************************************/
  template <typename T>
  T
  Vec2<T>::length() const
  {
    return std::sqrt(dot(*this));
  }

/*****************************************************************************/
  template <typename T>
  T
  Vec2<T>::normalize()
  {
    T len = length();
    *this *= T(1)/len;

    return len;
  }

/*****************************************************************************/
  template <typename T>
  T
  Vec2<T>::dot(const Vec2& a) const
  {
    return a.x*x+a.y*y;
  }
}


/*****************************************************************************/
template <typename T>
std::ostream&
operator << (std::ostream& os, const Star::Vec2<T>& s)
{
  return os << "(" << s.x << ", " << s.y << ")";
}
#endif
