#ifndef STAR_VEC4_H
#define STAR_VEC4_H

template <typename T>
class StarVec4
{
public:
  StarVec4() {};
  StarVec4( const T * );
  StarVec4( const StarVec3<T>&, T );
  StarVec4( T x, T y, T z, T w );

  // casting
  operator T* ();
  operator const T* () const;

  // assignment operators
  StarVec4& operator += ( const StarVec4& );
  StarVec4& operator -= ( const StarVec4& );
  StarVec4& operator *= ( T );
  StarVec4& operator /= ( T );

  // unary operators
  StarVec4 operator + () const;
  StarVec4 operator - () const;

  // binary operators
  StarVec4 operator + ( const StarVec4& ) const;
  StarVec4 operator - ( const StarVec4& ) const;
  StarVec4 operator * ( T ) const;
  StarVec4 operator / ( T ) const;

  friend StarVec4<T> operator * ( T, const StarVec4<T>& );

  bool operator == ( const StarVec4& ) const;
  bool operator != ( const StarVec4& ) const;

public:
  T x, y, z, w;
};

/*****************************************************************************/
typedef StarVec4<float> StarFloat4;
typedef StarVec4<double> StarDouble4;
typedef StarVec4<int> StarInt4;
typedef StarVec4<unsigned int> StarUint4;

/*****************************************************************************/
template <typename T>
StarVec4<T>::StarVec4 ( const T *p )
{
  x = p[0];
  y = p[1];
  z = p[2];
  w = p[3];
}

/*****************************************************************************/
template <typename T>
StarVec4<T>::StarVec4 ( T x, T y, T z, T w )
: x(x), y(y), z(z), w(w)
{
}

/*****************************************************************************/
template <typename T>
StarVec4<T>::StarVec4( const StarVec3<T>& v, T w )
{
  x = v.x;
  y = v.y;
  z = v.z;
  w = w;
}

/*****************************************************************************/
template <typename T>
StarVec4<T>::operator T* ()
{
  return &x;
}

/*****************************************************************************/
template <typename T>
StarVec4<T>::operator const T* () const
{
  return (const T*)&x;
}

/*****************************************************************************/
template <typename T>
StarVec4<T>&
StarVec4<T>::operator += ( const StarVec4<T>& v )
{
  x += v.x;
  y += v.y;
  z += v.z;
  w += v.w;

  return *this;
}

/*****************************************************************************/
template <typename T>
StarVec4<T>&
StarVec4<T>::operator -= ( const StarVec4<T>& v )
{
  x -= v.x;
  y -= v.y;
  z -= v.z;
  w -= v.w;

  return *this;
}
/*****************************************************************************/
template <typename T>
StarVec4<T>&
StarVec4<T>::operator *= ( T k )
{
  x *= k;
  y *= k;
  z *= k;
  w *= k;

  return *this;
}

/*****************************************************************************/
template <typename T>
StarVec4<T>&
StarVec4<T>::operator /= ( T k )
{
  x /= k;
  y /= k;
  z /= k;
  w /= k;

  return *this;
}

/*****************************************************************************/
template <typename T>
StarVec4<T>
StarVec4<T>::operator + () const
{
  return *this;
}

/*****************************************************************************/
template <typename T>
StarVec4<T>
StarVec4<T>::operator - () const
{
  return StarVec4(-x, -y, -z, -w);
}

/*****************************************************************************/
template <typename T>
StarVec4<T>
StarVec4<T>::operator + ( const StarVec4<T>& v ) const
{
  return StarVec4(x+v.x, y+v.y, z+v.z, w+v.w);
}

/*****************************************************************************/
template <typename T>
StarVec4<T>
StarVec4<T>::operator - ( const StarVec4<T>& v ) const
{
  return StarVec4<T>(x-v.x, y-v.y, z-v.z, w-v.w);
}

/*****************************************************************************/
template <typename T>
StarVec4<T>
StarVec4<T>::operator * ( T k ) const
{
  return StarVec4<T>(x*k, y*k, z*k, w*k);
}

/*****************************************************************************/
template <typename T>
StarVec4<T>
StarVec4<T>::operator / ( T k ) const
{
  return StarVec4<T>(x/k, y/k, z/k, w/k);
}

/*****************************************************************************/
template <typename T>
StarVec4<T>
operator * ( T k, const StarVec4<T>& v )
{
  return StarVec4<T>(k*v.x, k*v.y, k*v.z, k*v.w);
}

/*****************************************************************************/
template <typename T>
bool
StarVec4<T>::operator == ( const StarVec4<T>& v ) const
{
  return v.x == x && v.y == y && v.z == z && v.w == w;
}

/*****************************************************************************/
template <typename T>
bool
StarVec4<T>::operator != ( const StarVec4<T>& v ) const
{
  return v.x != x || v.y != y || v.z != z || v.w != w;
}

/*****************************************************************************/
template <typename T>
std::ostream&
operator << (std::ostream& os, const StarVec4<T>& s)
{
  return os << "(" << s.x << ", " << s.y <<  ", " << s.z << ", " << s.w << ")";
}

#endif
