#ifndef STAR_VEC3_H
#define STAR_VEC3_H

template <typename T>
class StarVec3
{
public:
  StarVec3() {};
  StarVec3( const T * );
  StarVec3( T x, T y, T z );

  // casting
  operator T* ();
  operator const T* () const;

  // assignment operators
  StarVec3& operator += ( const StarVec3& );
  StarVec3& operator -= ( const StarVec3& );
  StarVec3& operator *= ( T );
  StarVec3& operator /= ( T );

  // unary operators
  StarVec3 operator + () const;
  StarVec3 operator - () const;

  // binary operators
  StarVec3 operator + ( const StarVec3& ) const;
  StarVec3 operator - ( const StarVec3& ) const;
  StarVec3 operator * ( T ) const;
  StarVec3 operator / ( T ) const;

  friend StarVec3<T> operator * ( T, const StarVec3<T>& );

  bool operator == ( const StarVec3& ) const;
  bool operator != ( const StarVec3& ) const;

public:
  T x, y, z;
};

/*****************************************************************************/
typedef StarVec3<float> StarFloat3;
typedef StarVec3<double> StarDouble3;
typedef StarVec3<int> StarInt3;
typedef StarVec3<unsigned int> StarUint3;

/*****************************************************************************/
template <typename T>
StarVec3<T>::StarVec3 ( const T *p )
{
  x = p[0];
  y = p[1];
  z = p[2];
}

/*****************************************************************************/
template <typename T>
StarVec3<T>::StarVec3 ( T x, T y, T z )
: x(x), y(y), z(z)
{
}

/*****************************************************************************/
template <typename T>
StarVec3<T>::operator T* ()
{
  return &x;
}

/*****************************************************************************/
template <typename T>
StarVec3<T>::operator const T* () const
{
  return (const T*)&x;
}

/*****************************************************************************/
template <typename T>
StarVec3<T>&
StarVec3<T>::operator += ( const StarVec3<T>& v )
{
  x += v.x;
  y += v.y;
  z += v.z;

  return *this;
}

/*****************************************************************************/
template <typename T>
StarVec3<T>&
StarVec3<T>::operator -= ( const StarVec3<T>& v )
{
  x -= v.x;
  y -= v.y;
  z -= v.z;

  return *this;
}
/*****************************************************************************/
template <typename T>
StarVec3<T>&
StarVec3<T>::operator *= ( T k )
{
  x *= k;
  y *= k;
  z *= k;

  return *this;
}

/*****************************************************************************/
template <typename T>
StarVec3<T>&
StarVec3<T>::operator /= ( T k )
{
  x /= k;
  y /= k;
  z /= k;

  return *this;
}

/*****************************************************************************/
template <typename T>
StarVec3<T>
StarVec3<T>::operator + () const
{
  return *this;
}

/*****************************************************************************/
template <typename T>
StarVec3<T>
StarVec3<T>::operator - () const
{
  return StarVec3(-x, -y, -z);
}

/*****************************************************************************/
template <typename T>
StarVec3<T>
StarVec3<T>::operator + ( const StarVec3<T>& v ) const
{
  return StarVec3(x+v.x, y+v.y, z+v.z);
}

/*****************************************************************************/
template <typename T>
StarVec3<T>
StarVec3<T>::operator - ( const StarVec3<T>& v ) const
{
  return StarVec3<T>(x-v.x, y-v.y, z-v.z);
}

/*****************************************************************************/
template <typename T>
StarVec3<T>
StarVec3<T>::operator * ( T k ) const
{
  return StarVec3<T>(x*k, y*k, z*k);
}

/*****************************************************************************/
template <typename T>
StarVec3<T>
StarVec3<T>::operator / ( T k ) const
{
  return StarVec3<T>(x/k, y/k, z/k);
}

/*****************************************************************************/
template <typename T>
StarVec3<T>
operator * ( T k, const StarVec3<T>& v )
{
  return StarVec3<T>(k*v.x, k*v.y, k*v.z);
}

/*****************************************************************************/
template <typename T>
bool
StarVec3<T>::operator == ( const StarVec3<T>& v ) const
{
  return v.x == x && v.y == y && v.z == z;
}

/*****************************************************************************/
template <typename T>
bool
StarVec3<T>::operator != ( const StarVec3<T>& v ) const
{
  return v.x != x || v.y != y || v.z != z;
}

/*****************************************************************************/
template <typename T>
std::ostream&
operator << (std::ostream& os, const StarVec3<T>& s)
{
  return os << "(" << s.x << ", " << s.y <<  ", " << s.z << ")";
}

#endif
