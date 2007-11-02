#ifndef STAR_VEC3_H
#define STAR_VEC3_H

namespace Star
{
  template <typename T>
  class Vec3
  {
  public:
    Vec3() {};
    Vec3( const T * );
    Vec3( T x, T y, T z );

    // casting
    operator T* ();
    operator const T* () const;

    // assignment operators
    Vec3& operator += ( const Vec3& );
    Vec3& operator -= ( const Vec3& );
    Vec3& operator *= ( T );
    Vec3& operator /= ( T );

    // unary operators
    Vec3 operator + () const;
    Vec3 operator - () const;

    // binary operators
    Vec3 operator + ( const Vec3& ) const;
    Vec3 operator - ( const Vec3& ) const;
    Vec3 operator * ( T ) const;
    Vec3 operator / ( T ) const;

    friend Vec3<T> operator * ( T, const Vec3<T>& );

    bool operator == ( const Vec3& ) const;
    bool operator != ( const Vec3& ) const;

  public:
    T x, y, z;
  };

/*****************************************************************************/
  typedef Vec3<float> dloat3;
  typedef Vec3<double> double3;
  typedef Vec3<int> int3;
  typedef Vec3<unsigned int> uint3;

/*****************************************************************************/
  template <typename T>
  Vec3<T>::Vec3 ( const T *p )
  {
    x = p[0];
    y = p[1];
    z = p[2];
  }

/*****************************************************************************/
  template <typename T>
  Vec3<T>::Vec3 ( T x, T y, T z )
  : x(x), y(y), z(z)
  {
  }

/*****************************************************************************/
  template <typename T>
  Vec3<T>::operator T* ()
  {
    return &x;
  }

/*****************************************************************************/
  template <typename T>
  Vec3<T>::operator const T* () const
  {
    return (const T*)&x;
  }

/*****************************************************************************/
  template <typename T>
  Vec3<T>&
  Vec3<T>::operator += ( const Vec3<T>& v )
  {
    x += v.x;
    y += v.y;
    z += v.z;

    return *this;
  }

/*****************************************************************************/
  template <typename T>
  Vec3<T>&
  Vec3<T>::operator -= ( const Vec3<T>& v )
  {
    x -= v.x;
    y -= v.y;
    z -= v.z;

    return *this;
  }
/*****************************************************************************/
  template <typename T>
  Vec3<T>&
  Vec3<T>::operator *= ( T k )
  {
    x *= k;
    y *= k;
    z *= k;

    return *this;
  }

/*****************************************************************************/
  template <typename T>
  Vec3<T>&
  Vec3<T>::operator /= ( T k )
  {
    x /= k;
    y /= k;
    z /= k;

    return *this;
  }

/*****************************************************************************/
  template <typename T>
  Vec3<T>
  Vec3<T>::operator + () const
  {
    return *this;
  }

/*****************************************************************************/
  template <typename T>
  Vec3<T>
  Vec3<T>::operator - () const
  {
    return Vec3(-x, -y, -z);
  }

/*****************************************************************************/
  template <typename T>
  Vec3<T>
  Vec3<T>::operator + ( const Vec3<T>& v ) const
  {
    return Vec3(x+v.x, y+v.y, z+v.z);
  }

/*****************************************************************************/
  template <typename T>
  Vec3<T>
  Vec3<T>::operator - ( const Vec3<T>& v ) const
  {
    return Vec3<T>(x-v.x, y-v.y, z-v.z);
  }

/*****************************************************************************/
  template <typename T>
  Vec3<T>
  Vec3<T>::operator * ( T k ) const
  {
    return Vec3<T>(x*k, y*k, z*k);
  }

/*****************************************************************************/
  template <typename T>
  Vec3<T>
  Vec3<T>::operator / ( T k ) const
  {
    return Vec3<T>(x/k, y/k, z/k);
  }

/*****************************************************************************/
  template <typename T>
  Vec3<T>
  operator * ( T k, const Vec3<T>& v )
  {
    return Vec3<T>(k*v.x, k*v.y, k*v.z);
  }

/*****************************************************************************/
  template <typename T>
  bool
  Vec3<T>::operator == ( const Vec3<T>& v ) const
  {
    return v.x == x && v.y == y && v.z == z;
  }

/*****************************************************************************/
  template <typename T>
  bool
  Vec3<T>::operator != ( const Vec3<T>& v ) const
  {
    return v.x != x || v.y != y || v.z != z;
  }
}

/*****************************************************************************/
template <typename T>
std::ostream&
operator << (std::ostream& os, const Star::Vec3<T>& s)
{
  return os << "(" << s.x << ", " << s.y <<  ", " << s.z << ")";
}

#endif
