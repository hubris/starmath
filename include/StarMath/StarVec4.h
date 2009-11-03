#ifndef STAR_VEC4_H
#define STAR_VEC4_H

#include <StarMath/StarVec3.h>

#include <StarMath/StarUtils.h>
#include <cassert>

namespace Star
{
  template <typename T> class Vec4;
  template <typename T> Vec4<T> operator *( T, const Vec4<T>& );

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

    template <typename T2> friend Vec4<T2> operator *( T2, const Vec4<T2>& );

    bool operator == ( const Vec4& ) const;
    bool operator != ( const Vec4& ) const;

    Vec4 clamp(const Vec4& a, const Vec4& b) const
    {
        return Vec4(Star::clamp(x, a[0], b[0]),
                    Star::clamp(y, a[1], b[1]),
                    Star::clamp(z, a[2], b[2]),
                    Star::clamp(w, a[3], b[3]));
    }
      /**
       * Convert HSV color into RGB color
       * @param  hsv HSV color with h in [0,360] and s,v in [0,1]
       * @return RGBA color in [0,1], alpha is not changed
       */
      Vec4 HsvToRgb() const
      {
          int hi = (int)(this->x / 60.0f);
          float f = this->x / 60.0f - hi;
          float p = this->z * (1.0f - this->y);
          float q = this->z * (1.0f - f * this->y);
          float t = this->z * (1.0f - (1.0f - f) * this->y);

          switch (hi % 6)
          {
          case 0:
              return Vec4(this->z, t, p, this->w);
          case 1:
              return Vec4(q, this->z, p, this->w);
          case 2:
              return Vec4(p, this->z, t, this->w);
          case 3:
              return Vec4(p, q, this->z, this->w);
          case 4:
              return Vec4(t, p, this->z, this->w);
          case 5:
              return Vec4(this->z, p, q, this->w);
          default:
              assert(0);
              return Vec4(0, 0, 0, 0);
          }
      }
      /**
       * Convert RGB color to HSV
       * @param  rgb RGBA color in [0,1]
       * @return HSV color with h in [0,360] and s,v in [0,1], alpha is not changed
       */
      Vec4 RgbToHsv() const
      {
          float max = std::max(std::max(this->x, this->y), this->z);
          float min = std::min(std::min(this->x, this->y), this->z);
          float dist = max - min;

          if (dist == 0)
              return Vec4(0, 0, max, this->w);

          float s = (max < std::numeric_limits<float>::epsilon()) ? 0 : 1 - min / max;
          Vec4 hsv = Vec4(0, s, max, this->w);
          if (max == this->x)
          {
              hsv.x = (int)(60.0f * (this->y - this->z) / dist) % 360;
          }
          else if (max == this->y)
          {
              hsv.x = 120.0f + (60.0f * (this->z - this->x) / dist);
          }
          else if (max == this->z)
          {
              hsv.x = 240.0f + (60.0f * (this->x - this->y) / dist);
          }

          if (hsv.x < 0)
              hsv.x += 360.0f;

          return hsv;
      }


    // vector operation
    T length() const;
    T normalize();
    T dot(const Vec4& a) const;

    bool isNull() const;
  public:
    T x, y, z, w;
  };

/*****************************************************************************/
  typedef Vec4<float> float4;
  typedef Vec4<double> double4;
  typedef Vec4<int> int4;
  typedef Vec4<unsigned int> uint4;
  typedef Vec4<unsigned char> uchar4;

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
    this->w = w;
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
    return isZero(x-v.x) && isZero(y-v.y) && isZero(z-v.z) && isZero(w-v.w);
  }

/*****************************************************************************/
  template <typename T>
  bool
  Vec4<T>::operator != ( const Vec4<T>& v ) const
  {
    return v.x != x || v.y != y || v.z != z || v.w != w;
  }

  /*****************************************************************************/
  template <typename T>
  bool
  Vec4<T>::isNull() const
  {
    return isZero(x) && isZero(y) && isZero(z) && isZero(w);
  }

  /*****************************************************************************/
  template <typename T>
  T
  Vec4<T>::length() const
  {
    return std::sqrt(dot(*this));
  }

  /*****************************************************************************/
  template <typename T>
  T
  Vec4<T>::normalize()
  {
    T len = length();
    *this *= T(1)/len;

    return len;
  }

  /*****************************************************************************/
  template <typename T>
  T
  Vec4<T>::dot(const Vec4& a) const
  {
    return a.x*x+a.y*y+a.z*z+a.w*w;
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
