#ifndef STAR_MATRIX2_H
#define STAR_MATRIX2_H

#include <cassert>
#include <iostream>

#include <StarMath/StarVec2.h>

namespace Star
{
  /**
   * A row-major 2x2 matrix class. Implement a set of matrix operations.
   */
  template <typename T>
  class Matrix2
  {
  public:
    /**
     * Construct an unitialised 2x2 matrix.
     */
    Matrix2() { toIdentity(); };

    /**
     * Construct a 2x2 matrix with the specified values (row major).
     */
    Matrix2( const T * );

    /**
     * Construct a 2x2 matrix with the specified values.
     */
    Matrix2( T e11, T e12,
            T e21, T e22);

    /**
     * Access operator. Acces is done in row major order (y,x).
     */
    T operator () ( size_t row, size_t col ) const;

    /**
     * Access operator. Acces is done in row major order (y,x).
     */
    T& operator () ( size_t row, size_t col );

    /**
     * Return a pointer to the matrix values.
     */
    T* ptr();

    /**
     * Return a const pointer to the matrix values.
     */
    const T* constPtr() const;

    /**
     * Matrix multiplication.
     */
    Matrix2& operator *= ( const Matrix2& );

    /**
     * Matrix addition
     */
    Matrix2& operator += ( const Matrix2& );

    /**
     * Matrix substraction.
     */
    Matrix2& operator -= ( const Matrix2& );

    /**
     * Matrix scalar multiplication
     */
    Matrix2& operator *= ( T );

    /**
     * Matrix scalar division
     */
    Matrix2& operator /= ( T );

    /**
     * Nop
     */
    Matrix2 operator + () const;

    /**
     * Negate the all matrix values
     */
    Matrix2 operator - () const;

    /**
     * Matrix multiplication.
     */
    const Matrix2 operator * ( const Matrix2& ) const;

    /**
     * Matrix addition
     */
    const Matrix2 operator + ( const Matrix2& ) const;

    /**
     * Matrix substraction.
     */
    const Matrix2 operator - ( const Matrix2& ) const;

    /**
     * Matrix scalar multiplication.
     */
    const Matrix2 operator * ( T ) const;

    /**
     * Matrix2 scalar division
     */
    const Matrix2 operator / ( T ) const;

    /**
     * Transform the specified 2D vector.
     */
    Vec2<T> operator * ( const Vec2<T>& ) const;

    /**
     * Compute the matrix trace.
     */
    T trace() const;

    /**
     * Compute the matrix Frobenius norm
     */
    T FrobeniusNorm() const;

    /**
     * Compute the matrix determinant.
     */
    T determinant() const;

    /**
     * Compute the matrix inverse.
     * You must check if the matrix is inversible.
     */
    Matrix2 inverse() const;

    /**
     * Compute the matrix inverse.
     * You must check if the matrix is inversible.
     * @param determinant is the previously computed matrix's determinant
     */
    Matrix2 inverse(T& determinant) const;

    /**
     * Compute the matrix transpose.
     */
    Matrix2 transpose() const;

    /**
     * Matrix2 multiplication with a scalar.
     */
    friend Matrix2 operator * ( T k, const Matrix2& v)
    {
      return Matrix2(k*v(0,0), k*v(0,1),
                    k*v(1,0), k*v(1,1));
    }

    /**
     * Check for exact equality.
     * Doesn't take float imprecesion in account.
     */
    bool operator == ( const Matrix2& ) const;


    /**
     * Check for exact inequality.
     * Doesn't take float imprecesion in account.
     */
    bool operator != ( const Matrix2& ) const;

    /**
     * Create an identity matrix.
     */
    void toIdentity();
  private:
    T m_mat[2][2];
  };

/*****************************************************************************/
  template <typename T>
  Matrix2<T>::Matrix2( const T *p )
  {
    memcpy(&m_mat[0][0], p, sizeof(T)*4);
  }

/*****************************************************************************/
  template <typename T>
  Matrix2<T>::Matrix2( T e11, T e12,
                     T e21, T e22)
  {
    m_mat[0][0] = e11; m_mat[0][1] = e12;
    m_mat[1][0] = e21; m_mat[1][1] = e22;
  }

/*****************************************************************************/
  template <typename T>
  T&
  Matrix2<T>::operator () ( size_t row, size_t col )
  {
    assert(row < 2 && col < 2);
    return m_mat[row][col];
  }

/*****************************************************************************/
  template <typename T>
  T
  Matrix2<T>::operator () ( size_t row, size_t col ) const
  {
    assert(row < 2 && col < 2);
    return m_mat[row][col];
  }

///*****************************************************************************/
//template <typename T>
//Matrix2<T>::operator T* ()
//{
//  return &m_mat[0];
//}
//
///*****************************************************************************/
//template <typename T>
//Matrix2<T>::operator const T* () const
//{
//  return (const T*)(&(m_mat[0]));
//}

/*****************************************************************************/
  template <typename T>
  Matrix2<T>&
  Matrix2<T>::operator *= ( const Matrix2<T>& m )
  {
    Matrix2<T> tmp;
    for ( size_t k = 0; k < 2; k++ )
    {
      for ( size_t j = 0; j < 2; j++ )
      {
        tmp.m_mat[j][k] = 0;
        for ( size_t i = 0; i < 2; i++ )
          tmp.m_mat[j][k] += m_mat[j][i]*m.m_mat[i][k];
      }
    }
    *this = tmp;

    return *this;
  }

/*****************************************************************************/
  template <typename T>
  Matrix2<T>&
  Matrix2<T>::operator += ( const Matrix2<T>& m )
  {
    for ( size_t j = 0; j < 2; j++ )
      for ( size_t i = 0; i < 2; i++ )
        m_mat[j][i] += m.m_mat[j][i];

    return *this;
  }

/*****************************************************************************/
  template <typename T>
  Matrix2<T>&
  Matrix2<T>::operator -= ( const Matrix2<T>& m )
  {
    for ( size_t j = 0; j < 2; j++ )
      for ( size_t i = 0; i < 2; i++ )
        m_mat[j][i] -= m.m_mat[j][i];

    return *this;
  }
/*****************************************************************************/
  template <typename T>
  Matrix2<T>&
  Matrix2<T>::operator *= ( T k )
  {
    for ( size_t j = 0; j < 2; j++ )
      for ( size_t i = 0; i < 2; i++ )
        m_mat[j][i] *= k;

    return *this;
  }

/*****************************************************************************/
  template <typename T>
  Matrix2<T>&
  Matrix2<T>::operator /= ( T k )
  {
    for ( size_t j = 0; j < 2; j++ )
      for ( size_t i = 0; i < 2; i++ )
        m_mat[j][i] /= k;

    return *this;
  }

/*****************************************************************************/
  template <typename T>
  Matrix2<T>
  Matrix2<T>::operator + () const
  {
    return *this;
  }

/*****************************************************************************/
  template <typename T>
  Matrix2<T>
  Matrix2<T>::operator - () const
  {
    return Matrix2<T>(-m_mat[0][0], -m_mat[0][1],
                     -m_mat[1][0], -m_mat[1][1]);
  }

/*****************************************************************************/
  template <typename T>
  const Matrix2<T>
  Matrix2<T>::operator + ( const Matrix2<T>& v ) const
  {
    return Matrix2<T>(m_mat[0][0]+v.m_mat[0][0], m_mat[0][1]+v.m_mat[0][1],
                     m_mat[1][0]+v.m_mat[1][0], m_mat[1][1]+v.m_mat[1][1]);
  }

/*****************************************************************************/
  template <typename T>
  const Matrix2<T>
  Matrix2<T>::operator - ( const Matrix2<T>& v ) const
  {
    return Matrix2<T>(m_mat[0][0]-v.m_mat[0][0], m_mat[0][1]-v.m_mat[0][1],
                     m_mat[1][0]-v.m_mat[1][0], m_mat[1][1]-v.m_mat[1][1]);
  }

/*****************************************************************************/
  template <typename T>
  const Matrix2<T>
  Matrix2<T>::operator * ( T k ) const
  {
    return Matrix2<T>(k*m_mat[0][0], k*m_mat[0][1],
                     k*m_mat[1][0], k*m_mat[1][1]);
  }

/*****************************************************************************/
  template <typename T>
  const Matrix2<T>
  Matrix2<T>::operator * ( const Matrix2<T>& m ) const
  {
    Matrix2<T> tmp;
    for ( size_t k = 0; k < 2; k++ )
    {
      for ( size_t j = 0; j < 2; j++ )
      {
        tmp.m_mat[j][k] = 0;
        for ( size_t i = 0; i < 2; i++ )
          tmp.m_mat[j][k] += m_mat[j][i]*m.m_mat[i][k];
      }
    }

    return tmp;
  }
/*****************************************************************************/
  template <typename T>
  const Matrix2<T>
  Matrix2<T>::operator / ( T k ) const
  {
    return Matrix2<T>(m_mat[0][0]/k, m_mat[0][1]/k,
                     m_mat[1][0]/k, m_mat[1][1]/k);
  }

/*****************************************************************************/
  template <typename T>
  Matrix2<T>
  operator * ( T k, const Matrix2<T>& v )
  {
    return Matrix2<T>(k*v(0, 0), k*v(0, 1),
                     k*v(1, 0), k*v(1, 1));
  }

/*****************************************************************************/
  template <typename T>
  bool
  Matrix2<T>::operator == ( const Matrix2<T>& v ) const
  {
    return memcmp(&m_mat[0][0], &v.m_mat[0][0], 4*sizeof(T)) == 0;
  }

/*****************************************************************************/
  template <typename T>
  void
  Matrix2<T>::toIdentity()
  {
    m_mat[0][0] = 1; m_mat[0][1] = 0;
    m_mat[1][0] = 0; m_mat[1][1] = 1;
  }

 /*****************************************************************************/
  template <typename T>
  T
  Matrix2<T>::determinant() const
  {
    return m_mat[0][0]*m_mat[1][1]-m_mat[1][0]*m_mat[0][1];
  }

  /*****************************************************************************/
  template <typename T>
  T
  Matrix2<T>::trace() const
  {
    return m_mat[0][0]+m_mat[0][1]+m_mat[1][0]+m_mat[1][1];
  }

  /*****************************************************************************/
  template <typename T>
  T
  Matrix2<T>::FrobeniusNorm() const
  {
    return std::sqrt(m_mat[0][0]*m_mat[0][0]+
                     m_mat[0][1]*m_mat[0][1]+
                     m_mat[1][0]*m_mat[1][0]+
                     m_mat[1][1]*m_mat[1][1]);
  }

  /*****************************************************************************/
  template <typename T>
  Matrix2<T>
  Matrix2<T>::inverse() const
  {
    T det;
    return inverse(det);
  }

  /*****************************************************************************/
  template <typename T>
  Matrix2<T>
  Matrix2<T>::inverse(T& det) const
  {
    det = determinant();

    return (T(1)/det)*Matrix2<T>(m_mat[1][1], -m_mat[0][1],
                                -m_mat[1][0], m_mat[0][0]);
  }

  /*****************************************************************************/
  template <typename T>
  Matrix2<T>
  Matrix2<T>::transpose() const
  {
    return Matrix2<T>(m_mat[0][0], m_mat[1][0],
                     m_mat[0][1], m_mat[1][1]);
  }

/*****************************************************************************/
  template <typename T>
  T*
  Matrix2<T>::ptr()
  {
    return (T*)(&m_mat[0][0]);
  }

/*****************************************************************************/
  template <typename T>
  const T*
  Matrix2<T>::constPtr() const
  {
    return (const T*)(&m_mat[0][0]);
  }

/*****************************************************************************/
  template <typename T>
  bool
  Matrix2<T>::operator != ( const Matrix2<T>& v ) const
  {
    return ! ( v == *this );
  }

/*****************************************************************************/
  template <typename T>
  Vec2<T>
  Matrix2<T>::operator* ( const Vec2<T>& v ) const
  {
    return Vec2<T>(m_mat[0][0]*v.x+m_mat[0][1]*v.y,
                   m_mat[1][0]*v.x+m_mat[1][1]*v.y);
  }

/*****************************************************************************/
  template <typename T>
  std::ostream&
  operator << (std::ostream& os, const Matrix2<T>& m)
  {
    for ( size_t j = 0; j < 2; j++ )
    {
      os << "[ ";
      for ( size_t i = 0; i < 2; i++ )
        os << m(j, i) << " ";
      os << "]" << std::endl;
    }
    return os;
  }

/*****************************************************************************/
  /**
   * A 2x2 matrix with float values.
   */
  typedef Matrix2<float> float2x2;

  /**
   * A 2x2 matrix with double values.
   */
  typedef Matrix2<double> double2x2;

  /**
   * A 2x2 matrix with int values.
   */
  typedef Matrix2<int> int2x2;

  /**
   * A 2x2 matrix with uint values.
   */
  typedef Matrix2<unsigned int> uint2x2;
}
#endif
