#ifndef STAR_VEC3_H
#define STAR_VEC3_H

#include <cmath>

namespace Star
{
  template <typename T> class Vec3;
  template <typename T> Vec3<T> operator *( T, const Vec3<T>& );

  /**
   * A 3D vector class.
   */
  template <typename T>
  class Vec3
  {
  public:
    /**
     * Constructor.
     */
    Vec3() {};

    /**
     * Construct a 3D vector with the specified values.
     */
    Vec3( const T * );

    /**
     * Construct a 3D vector with the specified values.
     */
    Vec3( T x, T y, T z );

    /**
     * Get a pointer on the vector values.
     */
    operator T* ();

    /**
     * Get a constant pointer on the vector values.
     */
    operator const T* () const;

    /**
     * Addition.
     */
    Vec3& operator += ( const Vec3& );

    /**
     * Substraction.
     */
    Vec3& operator -= ( const Vec3& );

    /**
     * Scalar multiplication.
     */
    Vec3& operator *= ( T );

    /**
     * Scalar division.
     */
    Vec3& operator /= ( T );

    /**
     * Nop.
     */
    Vec3 operator + () const;

    /**
     * Return a vector with opposite values.
     */
    Vec3 operator - () const;

    /**
     * Addition.
     */
    Vec3 operator + ( const Vec3& ) const;

    /**
     * Substraction.
     */
    Vec3 operator - ( const Vec3& ) const;

    /**
     * Scalar multiplication.
     */
    Vec3 operator * ( T ) const;

    /**
     * Scalar division.
     */
    Vec3 operator / ( T ) const;

    /**
     * Scalar multiplication.
     */
    template <typename T2> friend Vec3<T2> operator * ( T2, const Vec3<T2>& );

    /**
     * Equality check. Use std's epsilon.
     */
    bool operator == ( const Vec3& ) const;

    /**
     * Inequality check. Use std's epsilon.
     */
    bool operator != ( const Vec3& ) const;

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
    T dot(const Vec3& a) const;

    /**
     * Cross product.
     */
    Vec3<T> cross(const Vec3& a) const;

    /**
     * Check for null vector.
     */
    bool isNull() const;

  public:
    /**
     * x coordinate.
     */
    T x;
    /**
     * y coordinate.
     */
    T y;
    /**
     * z coordinate.
     */
    T z;
  };

/*****************************************************************************/

  /**
   * A 3D float vector.
   */
  typedef Vec3<float> float3;

  /**
   * A 3D double vector.
   */
  typedef Vec3<double> double3;

  /**
   * A 3D int vector.
   */
  typedef Vec3<int> int3;

  /**
   * A 3D unsigned int vector.
   */
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
    return isZero(x-v.x) && isZero(y-v.y) && isZero(z-v.z);
  }

/*****************************************************************************/
  template <typename T>
  bool
  Vec3<T>::operator != ( const Vec3<T>& v ) const
  {
    return v.x != x || v.y != y || v.z != z;
  }

/*****************************************************************************/
  template <typename T>
  T
  Vec3<T>::length() const
  {
    return std::sqrt(dot(*this));
  }

/*****************************************************************************/
  template <typename T>
  T
  Vec3<T>::normalize()
  {
    T len = length();
    *this *= T(1)/len;

    return len;
  }

/*****************************************************************************/
  template <typename T>
  T
  Vec3<T>::dot(const Vec3& a) const
  {
    return a.x*x+a.y*y+a.z*z;
  }

/*****************************************************************************/
  template <typename T>
  bool
  Vec3<T>::isNull() const
  {
    return isZero(x) && isZero(y) && isZero(z);
  }

  /*****************************************************************************/
  template <typename T>
  Vec3<T>
  Vec3<T>::cross(const Vec3& a) const
  {
    return Vec3<T>(y*a.z-z*a.y, z*a.x-x*a.z, x*a.y-y*a.x);
  }
}

/*****************************************************************************/

/**
 * ostream operator for vectors
 */
template <typename T>
std::ostream&
operator << (std::ostream& os, const Star::Vec3<T>& s)
{
  return os << "(" << s.x << ", " << s.y <<  ", " << s.z << ")";
}

#endif
