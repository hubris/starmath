#ifndef STAR_QUATERNION_H
#define STAR_QUATERNION_H

#include <StarMath/StarUtils.h>
#include <StarMath/StarMatrix.h>

namespace Star
{
  //template <typename T> class Quaternion;
  //template <typename T> Quaternion<T> operator*(T, const Quaternion<T>& );

  /**
   * A quaternion class.
   */
  template <typename T>
  class Quaternion
  {
  public:
    /**
     * Constructor with undefined values.
     */
    Quaternion() {};

    /**
     * Constructor with the specified 4 values.
     */
    Quaternion( const T * );

    /**
     * Constructor.
     */
    Quaternion( T x, T y, T z, T w );

    /**
     * Construct a quaternion representing a rotation.
     * @param axis is the rotation axis
     * @param angle is in radian
     */
    Quaternion(const Vec3<T>& axis, const T angle);

    /**
     * Convert to a pointer.
     */
    operator T* ();

    /**
     * Convert to a constant pointer.
     */
    operator const T* () const;

    /**
     * Addition
     */
    Quaternion& operator += ( const Quaternion& );

    /**
     * Substraction.
     */
    Quaternion& operator -= ( const Quaternion& );

    /**
     * Multiplication.
     */
    Quaternion& operator *= ( const Quaternion& );

    /**
     * Scalar multiplication
     */
    Quaternion& operator *= ( T );

    /**
     * Scalar division
     */
    Quaternion& operator /= ( T );

    /**
     * Nop.
     */
    Quaternion operator + () const;

    /**
     * Return a quaternion with negated values.
     */
    Quaternion operator - () const;

    /**
     * Addition.
     */
    Quaternion operator + ( const Quaternion& ) const;

    /**
     * Substraction.
     */
    Quaternion operator - ( const Quaternion& ) const;

    /**
     * Multiplication.
     */
    Quaternion operator * ( const Quaternion& ) const;

    /**
     * Scalar multiplication.
     */
    Quaternion operator * ( T ) const;

    /**
     * Scalar division.
     */
    Quaternion operator / ( T ) const;

    /**
     * Equality check. Use std's epsilon.
     */
    bool operator == ( const Quaternion& ) const;

    /**
     * Inequality check. Use std's epsilon.
     */
    bool operator != ( const Quaternion& ) const;

    /**
     * Convert to identity quaternion
     */
    void toIdentity();

    /**
     * Inverse quaternion.
     */
    Quaternion inverse() const;

    /**
     * Inverse an unit quaternion.
     */
    Quaternion inverseUnit() const;

    /**
     * Compute the norm (squared length).
     */
    T norm() const;

    /**
     * Compute the length
     */
    T length() const;

    /**
     * Dot product.
     */
    T dot( const Quaternion<T>& q ) const;

    /**
     * Compute the conjugate.
     */
    Quaternion<T> conjugate() const;

    /**
     * Get the axis and the angle of the rotation represented
     * by this quaternion.
     * @param axis is the computed rotation axis
     * @param angle is the computed rotation angle in radian
     */
    void toAxisAngle( Vec3<T>& axis, T& angle ) const;

    /**
     * Construct a quaternion representing a rotation.
     */
    void fromAxisAngle(const Vec3<T>& axis, const T angle);

    /**
     * Convert the rotation represented by this quaternion into
     * a 4x4 matrix.
     */
    void toRotationMatrix(Matrix<T>& rotation) const;

    /**
     * Rotate the specified vector with this quaternion.
     */
    Vec3<T> rotate(const Vec3<T>&v);

  public:
    T x, y, z, w;
  };

  /*****************************************************************************/
  typedef Quaternion<float> quaternionf;
  typedef Quaternion<double> quaterniond;

  /*******************************************************************************/
  template <typename T>
  Quaternion<T>::Quaternion( const T * ptr )
  {
    x = ptr[0];
    y = ptr[1];
    z = ptr[2];
    w = ptr[3];
  }

  /*******************************************************************************/
  template <typename T>
  Quaternion<T>::Quaternion( T x, T y, T z, T w ) :x(x), y(y), z(z), w(w) {}


  /*******************************************************************************/
  template <typename T>
  Quaternion<T>::Quaternion(const Vec3<T>& axis, const T angle)
  {
    fromAxisAngle(axis, angle);
  }

  /*******************************************************************************/
  template <typename T>
  Quaternion<T>::operator T* ()
  {
    return &x;
  }

  /*******************************************************************************/
  template <typename T>
  Quaternion<T>::operator const T* () const
  {
    return &x;
  }

  /*******************************************************************************/
  template <typename T>
  Quaternion<T>&
  Quaternion<T>::operator += ( const Quaternion& q )
  {
    x += q.x;
    y += q.y;
    z += q.z;
    w += q.w;

    return *this;
  }

  /*******************************************************************************/
  template <typename T>
  Quaternion<T>&
  Quaternion<T>::operator -= ( const Quaternion& q )
  {
    x -= q.x;
    y -= q.y;
    z -= q.z;
    w -= q.w;

    return *this;
  }

  /*******************************************************************************/
  template <typename T>
  Quaternion<T>&
  Quaternion<T>::operator *= ( const Quaternion& q )
  {

    T tmpW = w*q.w - x*q.x - y*q.y - z*q.z;
    T tmpX = w*q.x + x*q.w + y*q.z - z*q.y;
    T tmpY = w*q.y - x*q.z + y*q.w + z*q.x;
    z = w*q.z + x*q.y - y*q.x + z*q.w;
    x = tmpX;
    y = tmpY;
    w = tmpW;

    return *this;
  }

  /*******************************************************************************/
  template <typename T>
  Quaternion<T>&
  Quaternion<T>::operator *= ( T k )
  {
    x *= k;
    y *= k;
    z *= k;
    w *= k;

    return *this;
  }

  /*******************************************************************************/
  template <typename T>
  Quaternion<T>&
  Quaternion<T>::operator /= ( T k )
  {
    return *this *= T(1)/k;
  }

  /*******************************************************************************/
  template <typename T>
  Quaternion<T>
  Quaternion<T>::operator + () const
  {
    return *this;
  }

  /*******************************************************************************/
  template <typename T>
  Quaternion<T>
  Quaternion<T>::operator - () const
  {
    return Quaternion<T>(-x, -y, -z, -w);
  }

  /*******************************************************************************/
  template <typename T>
  Quaternion<T>
  Quaternion<T>::operator + ( const Quaternion& q ) const
  {
    return Quaternion<T>(x+q.x, y+q.y, z+q.z, w+q.w);
  }

  /*******************************************************************************/
  template <typename T>
  Quaternion<T>
  Quaternion<T>::operator - ( const Quaternion& q ) const
  {
    return Quaternion<T>(x-q.x, y-q.y, z-q.z, w-q.w);
  }

  /*******************************************************************************/
  template <typename T>
  Quaternion<T>
  Quaternion<T>::operator * ( const Quaternion& q ) const
  {
    return Quaternion<T>(w*q.x + x*q.w + y*q.z - z*q.y,
                         w*q.y - x*q.z + y*q.w + z*q.x,
                         w*q.z + x*q.y - y*q.x + z*q.w,
                         w*q.w - x*q.x - y*q.y - z*q.z);
  }

  /*******************************************************************************/
  template <typename T>
  Quaternion<T>
  Quaternion<T>::operator * ( T k ) const
  {
    return Quaternion<T>(k*x, k*y, k*z, k*w);
  }

  /*******************************************************************************/
  template <typename T>
  Quaternion<T>
  Quaternion<T>::operator / ( T k ) const
  {
    T tmp = T(1)/k;
    return Quaternion<T>(x*tmp, y*tmp, z*tmp, w*tmp);
  }

  /*******************************************************************************/
  template <typename T>
  bool
  Quaternion<T>::operator == ( const Quaternion& q ) const
  {
    return isZero(x-q.x) && isZero(y-q.y) && isZero(z-q.z) && isZero(w-q.w);
  }

  /*******************************************************************************/
  template <typename T>
  bool
  Quaternion<T>::operator != ( const Quaternion& q ) const
  {
    return !(q == *this);
  }

  /*******************************************************************************/
  template <typename T>
  T
  Quaternion<T>::norm() const
  {
    return x*x+y*y+z*z+w*w;
  }

  /*******************************************************************************/
  template <typename T>
  T
  Quaternion<T>::length() const
  {
    return std::sqrt(x*x+y*y+z*z+w*w);
  }

  /*******************************************************************************/
  template <typename T>
  T
  Quaternion<T>::dot( const Quaternion<T>& q ) const
  {
    return x*q.x+y*q.y+z*q.z+w*q.w;
  }

  /*******************************************************************************/
  template <typename T>
  void
  Quaternion<T>::toIdentity()
  {
    x = y = z = 0;
    w = 1;
  }

  /*******************************************************************************/
  template <typename T>
  Quaternion<T>
  Quaternion<T>::conjugate() const
  {
    return Quaternion<T>(-x, -y, -z, w);
  }

  /*******************************************************************************/
  template <typename T>
  void
  Quaternion<T>::toAxisAngle( Vec3<T>& axis, T& angle ) const
  {
    T scale = std::sqrt(x*x+y*y+z*z);
    if(!isZero(scale))
    {
      scale = T(1)/scale;
      angle = T(2)*std::acos(w);
      axis.x = x*scale;
      axis.y = y*scale;
      axis.z = z*scale;
    }
    else
    {
      angle = 0;
      axis.x = 1;
      axis.y = 0;
      axis.z = 0;
    }
  }

  /*******************************************************************************/
  template <typename T>
  void
  Quaternion<T>::fromAxisAngle(const Vec3<T>& axis, const T angle)
  {
    assert(!axis.isNull());

    T theta = angle/T(2);
    T s = std::sin(theta);

    x = axis.x*s;
    y = axis.y*s;
    z = axis.z*s;
    w = std::cos(theta);
  }

  /*******************************************************************************/
  template <typename T>
  Quaternion<T>
  operator * (T k, const Star::Quaternion<T>& q )
  {
    return q*k;
  }

  /*******************************************************************************/
  template <typename T>
  Quaternion<T>
  Quaternion<T>::inverse() const
  {
    Quaternion<T> conj = conjugate();
    return conj/dot(*this);
  }

  /*******************************************************************************/
  template <typename T>
  Quaternion<T>
  Quaternion<T>::inverseUnit() const
  {
    assert(isZero(norm()-T(1)));
    return conjugate();
  }

  /*******************************************************************************/
  template <typename T>
  void
  Quaternion<T>::toRotationMatrix(Matrix<T>& rotation) const
  {
    float x2=x*x;
    float y2=y*y;
    float z2=z*z;

    rotation(0, 0) = 1 - 2*y2 - 2*z2;
    rotation(0, 1) = 2*x*y - 2*w*z;
    rotation(0, 2) = 2*x*z + 2*w*y;
    rotation(0, 3) = 0;

    rotation(1, 0) = 2*x*y + 2*w*z;
    rotation(1, 1) = 1 - 2*x2 - 2*z2;
    rotation(1, 2) = 2*y*z - 2*w*x;
    rotation(1, 3) = 0;

    rotation(2, 0) = 2*x*z - 2*w*y;
    rotation(2, 1) = 2*y*z + 2*w*x;
    rotation(2, 2) = 1 - 2*x2 - 2*y2;
    rotation(2, 3) = 0;

    rotation(3, 0) = rotation(3, 1) = rotation(3, 2) = 0;
    rotation(3, 3) = 1;
  }

  /*****************************************************************************/
  template <typename T>
  Vec3<T>
  Quaternion<T>::rotate(const Vec3<T>&v)
  {
    Quaternion<T> p = Quaternion<T>(v.x, v.y, v.z, T(0));
    p = (*this)*p*inverseUnit();
    return Vec3<T>(p.x, p.y, p.z);
  }

  /*****************************************************************************/
  template <typename T>
  std::ostream&
  operator << (std::ostream& os, const Quaternion<T>& q)
  {
    return os << "(" << q.x << ", " << q.y <<  ", " << q.z << ", " << q.w << ")";
  }

  /*****************************************************************************/
  //Here to avoid circular dependency
  template <typename T>
  void
  Matrix<T>::makeRotationAxis(const Vec3<T> axis, T angle)
  {
    Quaternion<T> q;
    q.fromAxisAngle(axis, angle);
    q.toRotationMatrix(*this);
  }
}


#endif
