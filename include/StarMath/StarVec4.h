#ifndef STAR_VEC4_H
#define STAR_VEC4_H


namespace Star
{
  template <typename T>
  class Vec4
  {
  public:
    Vec4() {};
    Vec4( const T * );
    Vec4( const Vec3<T>&, T );
    Vec4( T x, T y, T z, T w );

    // casting
    operator T* ();
    operator const T* () const;

    // assignment operators
    Vec4& operator += ( const Vec4& );
    Vec4& operator -= ( const Vec4& );
    Vec4& operator *= ( T );
    Vec4& operator /= ( T );

    // unary operators
    Vec4 operator + () const;
    Vec4 operator - () const;

    // binary operators
    Vec4 operator + ( const Vec4& ) const;
    Vec4 operator - ( const Vec4& ) const;
    Vec4 operator * ( T ) const;
    Vec4 operator / ( T ) const;

    friend Vec4<T> operator * ( T, const Vec4<T>& );

    bool operator == ( const Vec4& ) const;
    bool operator != ( const Vec4& ) const;

  public:
    T x, y, z, w;
  };

/*****************************************************************************/
  typedef Vec4<float> float4;
  typedef Vec4<double> double4;
  typedef Vec4<int> int4;
  typedef Vec4<unsigned int> uint4;

/*****************************************************************************/
  template <typename T>
  Vec4<T>::Vec4 ( const T *p )
  {
    x = p[0];
    y = p[1];
    z = p[2];
    w = p[3];
  }

/*****************************************************************************/
  template <typename T>
  Vec4<T>::Vec4 ( T x, T y, T z, T w )
  : x(x), y(y), z(z), w(w)
  {
  }

/*****************************************************************************/
  template <typename T>
  Vec4<T>::Vec4( const Vec3<T>& v, T w )
  {
    x = v.x;
    y = v.y;
    z = v.z;
    w = w;
  }

/*****************************************************************************/
  template <typename T>
  Vec4<T>::operator T* ()
  {
    return &x;
  }

/*****************************************************************************/
  template <typename T>
  Vec4<T>::operator const T* () const
  {
    return (const T*)&x;
  }

/*****************************************************************************/
  template <typename T>
  Vec4<T>&
  Vec4<T>::operator += ( const Vec4<T>& v )
  {
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;

    return *this;
  }

/*****************************************************************************/
  template <typename T>
  Vec4<T>&
  Vec4<T>::operator -= ( const Vec4<T>& v )
  {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;

    return *this;
  }
/*****************************************************************************/
  template <typename T>
  Vec4<T>&
  Vec4<T>::operator *= ( T k )
  {
    x *= k;
    y *= k;
    z *= k;
    w *= k;

    return *this;
  }

/*****************************************************************************/
  template <typename T>
  Vec4<T>&
  Vec4<T>::operator /= ( T k )
  {
    x /= k;
    y /= k;
    z /= k;
    w /= k;

    return *this;
  }

/*****************************************************************************/
  template <typename T>
  Vec4<T>
  Vec4<T>::operator + () const
  {
    return *this;
  }

/*****************************************************************************/
  template <typename T>
  Vec4<T>
  Vec4<T>::operator - () const
  {
    return Vec4(-x, -y, -z, -w);
  }

/*****************************************************************************/
  template <typename T>
  Vec4<T>
  Vec4<T>::operator + ( const Vec4<T>& v ) const
  {
    return Vec4(x+v.x, y+v.y, z+v.z, w+v.w);
  }

/*****************************************************************************/
  template <typename T>
  Vec4<T>
  Vec4<T>::operator - ( const Vec4<T>& v ) const
  {
    return Vec4<T>(x-v.x, y-v.y, z-v.z, w-v.w);
  }

/*****************************************************************************/
  template <typename T>
  Vec4<T>
  Vec4<T>::operator * ( T k ) const
  {
    return Vec4<T>(x*k, y*k, z*k, w*k);
  }

/*****************************************************************************/
  template <typename T>
  Vec4<T>
  Vec4<T>::operator / ( T k ) const
  {
    return Vec4<T>(x/k, y/k, z/k, w/k);
  }

/*****************************************************************************/
  template <typename T>
  Vec4<T>
  operator * ( T k, const Vec4<T>& v )
  {
    return Vec4<T>(k*v.x, k*v.y, k*v.z, k*v.w);
  }

/*****************************************************************************/
  template <typename T>
  bool
  Vec4<T>::operator == ( const Vec4<T>& v ) const
  {
    return v.x == x && v.y == y && v.z == z && v.w == w;
  }

/*****************************************************************************/
  template <typename T>
  bool
  Vec4<T>::operator != ( const Vec4<T>& v ) const
  {
    return v.x != x || v.y != y || v.z != z || v.w != w;
  }

}
/*****************************************************************************/
template <typename T>
std::ostream&
operator << (std::ostream& os, const Star::Vec4<T>& s)
{
  return os << "(" << s.x << ", " << s.y <<  ", " << s.z << ", " << s.w << ")";
}

#endif