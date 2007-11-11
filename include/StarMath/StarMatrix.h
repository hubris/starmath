#ifndef STAR_MATRIX_H
#define STAR_MATRIX_H

#include <cassert>
#include <iostream>

namespace Star
{
  template <typename T>
  class Matrix
  {
  public:
    Matrix() {};
    Matrix( const T * );
    Matrix( T e11, T e12, T e13, T e14,
            T e21, T e22, T e23, T e24,
            T e31, T e32, T e33, T e34,
            T e41, T e42, T e43, T e44 );

    // access grants
    T operator () ( size_t row, size_t col ) const;
    T& operator () ( size_t row, size_t col );

    T* ptr();
    const T* constPtr() const;

    // assignment operators
    Matrix& operator *= ( const Matrix& );
    Matrix& operator += ( const Matrix& );
    Matrix& operator -= ( const Matrix& );
    Matrix& operator *= ( T );
    Matrix& operator /= ( T );

    // unary operators
    Matrix operator + () const;
    Matrix operator - () const;

    // binary operators
    const Matrix operator * ( const Matrix& ) const;
    const Matrix operator + ( const Matrix& ) const;
    const Matrix operator - ( const Matrix& ) const;
    const Matrix operator * ( T ) const;
    const Matrix operator / ( T ) const;

    /**
     * Return the determinant of the submatrix composed of rows r0, r1, r2
     * and columns c0, c1, c2
     */
    T minor4(size_t r0, size_t r1, size_t r2, size_t c0, size_t c1, size_t c2) const;
    Matrix adjoint4() const;
    T determinant() const;
    Matrix inverse() const;
    Matrix inverse(T& determinant) const;
    Matrix transpose() const;

    // transformations
    void makeTranslation(T x, T y, T z);
    void makeTranslation(const Vec3<T> &tr);
    void makeScaling(const Vec3<T> &scale);
    void makeScaling(T sx, T sy, T sz);
    void makeRotationAxis(const Vec3<T> axis, T angle);

    friend Matrix operator * ( T k, const Matrix& v)
    {
      return Matrix(k*v(0,0), k*v(0,1), k*v(0,2), k*v(0,3),
                    k*v(1,0), k*v(1,1), k*v(1,2), k*v(1,3),
                    k*v(2,0), k*v(2,1), k*v(2,2), k*v(2,3),
                    k*v(3,0), k*v(3,1), k*v(3,2), k*v(3,3));
    }

    bool operator == ( const Matrix& ) const;
    bool operator != ( const Matrix& ) const;

    void toIdentity();
  private:
    T m_mat[4][4];
  };

/*****************************************************************************/
  template <typename T>
  Matrix<T>::Matrix( const T *p )
  {
    memcpy(&m_mat[0][0], p, sizeof(T)*16);
  }

/*****************************************************************************/
  template <typename T>
  Matrix<T>::Matrix( T e11, T e12, T e13, T e14,
                     T e21, T e22, T e23, T e24,
                     T e31, T e32, T e33, T e34,
                     T e41, T e42, T e43, T e44 )
  {
    m_mat[0][0] = e11; m_mat[0][1] = e12; m_mat[0][2] = e13; m_mat[0][3]= e14;
    m_mat[1][0] = e21; m_mat[1][1] = e22; m_mat[1][2] = e23; m_mat[1][3]= e24;
    m_mat[2][0] = e31; m_mat[2][1] = e32; m_mat[2][2] = e33; m_mat[2][3]= e34;
    m_mat[3][0] = e41; m_mat[3][1] = e42; m_mat[3][2] = e43; m_mat[3][3]= e44;
  }

/*****************************************************************************/
  template <typename T>
  T&
  Matrix<T>::operator () ( size_t row, size_t col )
  {
    assert(row < 4 && col < 4);
    return m_mat[row][col];
  }

/*****************************************************************************/
  template <typename T>
  T
  Matrix<T>::operator () ( size_t row, size_t col ) const
  {
    assert(row < 4 && col < 4);
    return m_mat[row][col];
  }

///*****************************************************************************/
//template <typename T>
//Matrix<T>::operator T* ()
//{
//  return &m_mat[0];
//}
//
///*****************************************************************************/
//template <typename T>
//Matrix<T>::operator const T* () const
//{
//  return (const T*)(&(m_mat[0]));
//}

/*****************************************************************************/
  template <typename T>
  Matrix<T>&
  Matrix<T>::operator *= ( const Matrix<T>& m )
  {
    Matrix<T> tmp;
    for ( size_t k = 0; k < 4; k++ )
    {
      for ( size_t j = 0; j < 4; j++ )
      {
        tmp.m_mat[j][k] = 0;
        for ( size_t i = 0; i < 4; i++ )
          tmp.m_mat[j][k] += m_mat[j][i]*m.m_mat[i][k];
      }
    }
    *this = tmp;

    return *this;
  }
/*****************************************************************************/
  template <typename T>
  Matrix<T>&
  Matrix<T>::operator += ( const Matrix<T>& m )
  {
    for ( size_t j = 0; j < 4; j++ )
      for ( size_t i = 0; i < 4; i++ )
        m_mat[j][i] += m.m_mat[j][i];

    return *this;
  }

/*****************************************************************************/
  template <typename T>
  Matrix<T>&
  Matrix<T>::operator -= ( const Matrix<T>& m )
  {
    for ( size_t j = 0; j < 4; j++ )
      for ( size_t i = 0; i < 4; i++ )
        m_mat[j][i] -= m.m_mat[j][i];

    return *this;
  }
/*****************************************************************************/
  template <typename T>
  Matrix<T>&
  Matrix<T>::operator *= ( T k )
  {
    for ( size_t j = 0; j < 4; j++ )
      for ( size_t i = 0; i < 4; i++ )
        m_mat[j][i] *= k;

    return *this;
  }

/*****************************************************************************/
  template <typename T>
  Matrix<T>&
  Matrix<T>::operator /= ( T k )
  {
    for ( size_t j = 0; j < 4; j++ )
      for ( size_t i = 0; i < 4; i++ )
        m_mat[j][i] /= k;

    return *this;
  }

/*****************************************************************************/
  template <typename T>
  Matrix<T>
  Matrix<T>::operator + () const
  {
    return *this;
  }

/*****************************************************************************/
  template <typename T>
  Matrix<T>
  Matrix<T>::operator - () const
  {
    return Matrix<T>(-m_mat[0][0], -m_mat[0][1], -m_mat[0][2], -m_mat[0][3],
                     -m_mat[1][0], -m_mat[1][1], -m_mat[1][2], -m_mat[1][3],
                     -m_mat[2][0], -m_mat[2][1], -m_mat[2][2], -m_mat[2][3],
                     -m_mat[3][0], -m_mat[3][1], -m_mat[3][2], -m_mat[3][3]);
  }

/*****************************************************************************/
  template <typename T>
  const Matrix<T>
  Matrix<T>::operator + ( const Matrix<T>& v ) const
  {
    return Matrix<T>(m_mat[0][0]+v.m_mat[0][0], m_mat[0][1]+v.m_mat[0][1], m_mat[0][2]+v.m_mat[0][2], m_mat[0][3]+v.m_mat[0][3],
                     m_mat[1][0]+v.m_mat[1][0], m_mat[1][1]+v.m_mat[1][1], m_mat[1][2]+v.m_mat[1][2], m_mat[1][3]+v.m_mat[1][3],
                     m_mat[2][0]+v.m_mat[2][0], m_mat[2][1]+v.m_mat[2][1], m_mat[2][2]+v.m_mat[2][2], m_mat[2][3]+v.m_mat[2][3],
                     m_mat[3][0]+v.m_mat[3][0], m_mat[3][1]+v.m_mat[3][1], m_mat[3][2]+v.m_mat[3][2], m_mat[3][3]+v.m_mat[3][3]);
  }

/*****************************************************************************/
  template <typename T>
  const Matrix<T>
  Matrix<T>::operator - ( const Matrix<T>& v ) const
  {
    return Matrix<T>(m_mat[0][0]-v.m_mat[0][0], m_mat[0][1]-v.m_mat[0][1], m_mat[0][2]-v.m_mat[0][2], m_mat[0][3]-v.m_mat[0][3],
                     m_mat[1][0]-v.m_mat[1][0], m_mat[1][1]-v.m_mat[1][1], m_mat[1][2]-v.m_mat[1][2], m_mat[1][3]-v.m_mat[1][3],
                     m_mat[2][0]-v.m_mat[2][0], m_mat[2][1]-v.m_mat[2][1], m_mat[2][2]-v.m_mat[2][2], m_mat[2][3]-v.m_mat[2][3],
                     m_mat[3][0]-v.m_mat[3][0], m_mat[3][1]-v.m_mat[3][1], m_mat[3][2]-v.m_mat[3][2], m_mat[3][3]-v.m_mat[3][3]);
  }

/*****************************************************************************/
  template <typename T>
  const Matrix<T>
  Matrix<T>::operator * ( T k ) const
  {
    return Matrix<T>(k*m_mat[0][0], k*m_mat[0][1], k*m_mat[0][2], k*m_mat[0][3],
                     k*m_mat[1][0], k*m_mat[1][1], k*m_mat[1][2], k*m_mat[1][3],
                     k*m_mat[2][0], k*m_mat[2][1], k*m_mat[2][2], k*m_mat[2][3],
                     k*m_mat[3][0], k*m_mat[3][1], k*m_mat[3][2], k*m_mat[3][3]);
  }

/*****************************************************************************/
  template <typename T>
  const Matrix<T>
  Matrix<T>::operator * ( const Matrix<T>& m ) const
  {
    Matrix<T> tmp;
    for ( size_t k = 0; k < 4; k++ )
    {
      for ( size_t j = 0; j < 4; j++ )
      {
        tmp.m_mat[j][k] = 0;
        for ( size_t i = 0; i < 4; i++ )
          tmp.m_mat[j][k] += m_mat[j][i]*m.m_mat[i][k];
      }
    }

    return tmp;
  }
/*****************************************************************************/
  template <typename T>
  const Matrix<T>
  Matrix<T>::operator / ( T k ) const
  {
    return Matrix<T>(m_mat[0][0]/k, m_mat[0][1]/k, m_mat[0][2]/k, m_mat[0][3]/k,
                     m_mat[1][0]/k, m_mat[1][1]/k, m_mat[1][2]/k, m_mat[1][3]/k,
                     m_mat[2][0]/k, m_mat[2][1]/k, m_mat[2][2]/k, m_mat[2][3]/k,
                     m_mat[3][0]/k, m_mat[3][1]/k, m_mat[3][2]/k, m_mat[3][3]/k);
  }

/*****************************************************************************/
  template <typename T>
  Matrix<T>
  operator * ( T k, const Matrix<T>& v )
  {
    return Matrix<T>(k*v(0, 0), k*v(0, 1), k*v(0, 2), k*v(0, 3),
                     k*v(1, 0), k*v(1, 1), k*v(1, 2), k*v(1, 3),
                     k*v(2, 0), k*v(2, 1), k*v(2, 2), k*v(2, 3),
                     k*v(3, 0), k*v(3, 1), k*v(3, 2), k*v(3, 3));
  }

/*****************************************************************************/
  template <typename T>
  bool
  Matrix<T>::operator == ( const Matrix<T>& v ) const
  {
    return memcmp(&m_mat[0][0], &v.m_mat[0][0], 16*sizeof(float)) == 0;
  }

/*****************************************************************************/
  template <typename T>
  void
  Matrix<T>::toIdentity()
  {
    m_mat[0][0] = 1; m_mat[0][1] = 0; m_mat[0][2] = 0; m_mat[0][3]= 0;
    m_mat[1][0] = 0; m_mat[1][1] = 1; m_mat[1][2] = 0; m_mat[1][3]= 0;
    m_mat[2][0] = 0; m_mat[2][1] = 0; m_mat[2][2] = 1; m_mat[2][3]= 0;
    m_mat[3][0] = 0; m_mat[3][1] = 0; m_mat[3][2] = 0; m_mat[3][3]= 1;
  }

/*****************************************************************************/
  template <typename T>
  T
  Matrix<T>::minor4(size_t r0, size_t r1, size_t r2,
                    size_t c0, size_t c1, size_t c2) const
  {
    return m_mat[r0][c0]*(m_mat[r1][c1]*m_mat[r2][c2]-m_mat[r1][c2]*m_mat[r2][c1])-
           m_mat[r0][c1]*(m_mat[r1][c0]*m_mat[r2][c2]-m_mat[r2][c0]*m_mat[r1][c2])+
           m_mat[r0][c2]*(m_mat[r1][c0]*m_mat[r2][c1]-m_mat[r2][c0]*m_mat[r1][c1]);
  }

 /*****************************************************************************/
  template <typename T>
  T
  Matrix<T>::determinant() const
  {
    //Use Laplace formula
    return m_mat[0][0]*minor4(1, 2, 3, 1, 2, 3) -
           m_mat[0][1]*minor4(1, 2, 3, 0, 2, 3) +
           m_mat[0][2]*minor4(1, 2, 3, 0, 1, 3) -
           m_mat[0][3]*minor4(1, 2, 3, 0, 1, 2);
  }


  /*****************************************************************************/
  template <typename T>
  Matrix<T>
  Matrix<T>::adjoint4() const
  {
    Matrix<T> adj;

    adj(0, 0) =  minor4(1, 2, 3, 1, 2, 3);
    adj(0, 1) = -minor4(0, 2, 3, 1, 2, 3);
    adj(0, 2) =  minor4(0, 1, 3, 1, 2, 3);
    adj(0, 3) = -minor4(0, 1, 2, 1, 2, 3);

    adj(1, 0) = -minor4(1, 2, 3, 0, 2, 3);
    adj(1, 1) =  minor4(0, 2, 3, 0, 2, 3);
    adj(1, 2) = -minor4(0, 1, 3, 0, 2, 3);
    adj(1, 3) =  minor4(0, 1, 2, 0, 2, 3);

    adj(2, 0) =  minor4(1, 2, 3, 0, 1, 3);
    adj(2, 1) = -minor4(0, 2, 3, 0, 1, 3);
    adj(2, 2) =  minor4(0, 1, 3, 0, 1, 3);
    adj(2, 3) = -minor4(0, 1, 2, 0, 1, 3);

    adj(3, 0) = -minor4(1, 2, 3, 0, 1, 2);
    adj(3, 1) =  minor4(0, 2, 3, 0, 1, 2);
    adj(3, 2) = -minor4(0, 1, 3, 0, 1, 2);
    adj(3, 3) =  minor4(0, 1, 2, 0, 1, 2);

    return adj;
  }

  /*****************************************************************************/
  template <typename T>
  Matrix<T>
  Matrix<T>::inverse() const
  {
    T det;
    return inverse(det);
  }

  /*****************************************************************************/
  template <typename T>
  Matrix<T>
  Matrix<T>::inverse(T& det) const
  {
    det = determinant();

    return (T(1)/det)*adjoint4();
  }

  /*****************************************************************************/
  template <typename T>
  Matrix<T>
  Matrix<T>::transpose() const
  {
    return Matrix<T>(m_mat[0][0], m_mat[1][0], m_mat[2][0], m_mat[3][0],
                     m_mat[0][1], m_mat[1][1], m_mat[2][1], m_mat[3][1],
                     m_mat[0][2], m_mat[1][2], m_mat[2][2], m_mat[3][2],
                     m_mat[0][3], m_mat[1][3], m_mat[2][3], m_mat[3][3]);
  }

  /*****************************************************************************/
  template <typename T>
  void
  Matrix<T>::makeTranslation(const Vec3<T> &tr)
  {
    m_mat[0][0] = 1;
    m_mat[0][1] = 0;
    m_mat[0][2] = 0;
    m_mat[0][3] = tr[0];

    m_mat[1][0] = 0;
    m_mat[1][1] = 1;
    m_mat[1][2] = 0;
    m_mat[1][3] = tr[1];

    m_mat[2][0] = 0;
    m_mat[2][1] = 0;
    m_mat[2][2] = 1;
    m_mat[2][3] = tr[2];

    m_mat[3][0] = 0;
    m_mat[3][1] = 0;
    m_mat[3][2] = 0;
    m_mat[3][3] = 1;
  }

  /*****************************************************************************/
  template <typename T>
  void
  Matrix<T>::makeTranslation(T x, T y, T z)
  {
    makeTranslation(Vec3<T>(x ,y ,z));
  }

  /*****************************************************************************/
  template <typename T>
  void
  Matrix<T>::makeScaling(const Vec3<T> &scale)
  {
    m_mat[0][0] = scale[0];
    m_mat[0][1] = 0;
    m_mat[0][2] = 0;
    m_mat[0][3] = 0;

    m_mat[1][0] = 0;
    m_mat[1][1] = scale[1];
    m_mat[1][2] = 0;
    m_mat[1][3] = 0;

    m_mat[2][0] = 0;
    m_mat[2][1] = 0;
    m_mat[2][2] = scale[2];
    m_mat[2][3] = 0;

    m_mat[3][0] = 0;
    m_mat[3][1] = 0;
    m_mat[3][2] = 0;
    m_mat[3][3] = 1;
  }

  /*****************************************************************************/
  template <typename T>
  void
  Matrix<T>::makeScaling(T sx, T sy, T sz)
  {
    makeScaling(Vec3<T>(sx, sy, sz));
  }

/*****************************************************************************/
  template <typename T>
  T*
  Matrix<T>::ptr()
  {
    return (T*)(&m_mat[0][0]);
  }

/*****************************************************************************/
  template <typename T>
  const T*
  Matrix<T>::constPtr() const
  {
    return (const T*)(&m_mat[0][0]);
  }

/*****************************************************************************/
  template <typename T>
  bool
  Matrix<T>::operator != ( const Matrix<T>& v ) const
  {
    return ! ( v == *this );
  }

/*****************************************************************************/
  template <typename T>
  std::ostream&
  operator << (std::ostream& os, const Matrix<T>& m)
  {
    for ( size_t j = 0; j < 4; j++ )
    {
      os << "[ ";
      for ( size_t i = 0; i < 4; i++ )
        os << m(j, i) << " ";
      os << "]" << std::endl;
    }
    return os;
  }

/*****************************************************************************/
  typedef Matrix<float> float4x4;
  typedef Matrix<double> double4x4;
  typedef Matrix<int> int4x4;
  typedef Matrix<unsigned int> uint4x4;
}
#endif
