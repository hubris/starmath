#ifndef STARVEC2_H
#define STARVEC2_H

#include <iostream>

template <typename T> class StarVec2;
template <typename T> StarVec2<T> operator *( T, const StarVec2<T>& );

template <typename T>
class StarVec2
{
public:
  StarVec2() {}
  StarVec2 ( const T * );
  StarVec2 ( T x, T y );

  // casting
  operator T* ();
  operator const T* () const;

  // assignment operators
  StarVec2<T>& operator += ( const StarVec2<T>& );
  StarVec2<T>& operator -= ( const StarVec2<T>& );
  StarVec2<T>& operator *= ( T );
  StarVec2<T>& operator /= ( T );

  // unary operators
  StarVec2 operator + () const;
  StarVec2 operator - () const;

  // binary operators
  StarVec2 operator + ( const StarVec2<T>& ) const;
  StarVec2 operator - ( const StarVec2<T>& ) const;
  StarVec2 operator * ( T ) const;
  StarVec2 operator / ( T ) const;

  template <typename T2> friend StarVec2 operator *( T2, const StarVec2<T2>& );

  bool operator == ( const StarVec2<T>& ) const;
  bool operator != ( const StarVec2<T>& ) const;

public:
  T x, y;
};

/*****************************************************************************/
typedef StarVec2<float> StarFloat2;
typedef StarVec2<double> StarDouble2;
typedef StarVec2<int> StarInt2;
typedef StarVec2<unsigned int> StarUint2;

/*****************************************************************************/
template <typename T>
StarVec2<T>::StarVec2 ( const T *p )
{
  x = p[0];
  y = p[1];
}

/*****************************************************************************/
template <typename T>
StarVec2<T>::StarVec2 ( T x, T y )
: x(x), y(y)
{
}

/*****************************************************************************/
template <typename T>
StarVec2<T>::operator T* ()
{
  return &x;
}

/*****************************************************************************/
template <typename T>
StarVec2<T>::operator const T* () const
{
  return (const T*)&x;
}

/*****************************************************************************/
template <typename T>
StarVec2<T>&
StarVec2<T>::operator += ( const StarVec2<T>& v )
{
  x += v.x;
  y += v.y;

  return *this;
}

/*****************************************************************************/
template <typename T>
StarVec2<T>&
StarVec2<T>::operator -= ( const StarVec2<T>& v )
{
  x -= v.x;
  y -= v.y;

  return *this;
}
/*****************************************************************************/
template <typename T>
StarVec2<T>&
StarVec2<T>::operator *= ( T k )
{
  x *= k;
  y *= k;

  return *this;
}

/*****************************************************************************/
template <typename T>
StarVec2<T>&
StarVec2<T>::operator /= ( T k )
{
  x /= k;
  y /= k;

  return *this;
}

/*****************************************************************************/
template <typename T>
StarVec2<T>
StarVec2<T>::operator + () const
{
  return *this;
}

/*****************************************************************************/
template <typename T>
StarVec2<T>
StarVec2<T>::operator - () const
{
  return StarVec2(-x, -y);
}

/*****************************************************************************/
template <typename T>
StarVec2<T>
StarVec2<T>::operator + ( const StarVec2<T>& v ) const
{
  return StarVec2(x+v.x, y+v.y);
}

/*****************************************************************************/
template <typename T>
StarVec2<T>
StarVec2<T>::operator - ( const StarVec2<T>& v ) const
{
  return StarVec2<T>(x-v.x, y-v.y);
}

/*****************************************************************************/
template <typename T>
StarVec2<T>
StarVec2<T>::operator * ( T k ) const
{
  return StarVec2<T>(x*k, y*k);
}

/*****************************************************************************/
template <typename T>
StarVec2<T>
StarVec2<T>::operator / ( T k ) const
{
  return StarVec2<T>(x/k, y/k);
}

/*****************************************************************************/
template <typename T>
StarVec2<T>
operator * ( T k, const StarVec2<T>& v )
{
  return StarVec2<T>(k*v.x, k*v.y);
}

/*****************************************************************************/
template <typename T>
bool
StarVec2<T>::operator == ( const StarVec2<T>& v ) const
{
  return v.x == x && v.y == y;
}

/*****************************************************************************/
template <typename T>
bool
StarVec2<T>::operator != ( const StarVec2<T>& v ) const
{
  return v.x != x || v.y != y;
}

/*****************************************************************************/
template <typename T>
std::ostream&
operator << (std::ostream& os, const StarVec2<T>& s)
{
  return os << "(" << s.x << ", " << s.y << ")";
}

#endif
