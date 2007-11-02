#include <cxxtest/TestSuite.h>

#include <StarMath.h>

#include <d3dx10.h>
#include <limits>
#include <algorithm>

class MathTestSuite : public CxxTest::TestSuite
{
public:
  /*****************************************************************************/
  void testMatrixIdentity( void )
  {
    D3DXMATRIX matDx;
    Star::float4x4 matStar;

    D3DXMatrixIdentity(&matDx);
    matStar.toIdentity();

    TS_ASSERT( isEqual(matDx, matStar) );
  }

  /*****************************************************************************/
  void testMatrixConstructors1( void )
  {
    using namespace std;
    vector<float> randValues;
    generate_n(back_inserter(randValues), 16, FloatRandGen(100000.f));

    D3DXMATRIX matDx(&randValues[0]);
    Star::float4x4 matStar(&randValues[0]);
    TS_ASSERT( isEqual(matDx, matStar) );
  }

  /*****************************************************************************/
  void testMatrixConstructors2( void )
  {
    using namespace std;
    vector<float> randValues;
    generate_n(back_inserter(randValues), 16, FloatRandGen(100000.f));

    D3DXMATRIX matDx(randValues[0], randValues[1], randValues[2], randValues[3],
                     randValues[4], randValues[5], randValues[6], randValues[7],
                     randValues[8], randValues[9], randValues[10], randValues[11],
                     randValues[12], randValues[13], randValues[14], randValues[15]);
    Star::float4x4 matStar(randValues[0], randValues[1], randValues[2], randValues[3],
                         randValues[4], randValues[5], randValues[6], randValues[7],
                         randValues[8], randValues[9], randValues[10], randValues[11],
                         randValues[12], randValues[13], randValues[14], randValues[15]);
    TS_ASSERT( isEqual(matDx, matStar) );
  }

  /*****************************************************************************/
  void testMatrixAssignOperator( void )
  {
    using namespace std;

    vector<float> randValues;
    vector<float> randValues2;
    generate_n(back_inserter(randValues), 16, FloatRandGen(100000.f));
    generate_n(back_inserter(randValues2), 16, FloatRandGen(1000.f));

    D3DXMATRIX matDx(&randValues[0]);
    D3DXMATRIX matDx2(&randValues2[0]);
    Star::float4x4 matStar(&randValues[0]);
    Star::float4x4 matStar2(&randValues2[0]);

    matStar *= matStar2;
    matDx *= matDx2;
    TS_ASSERT( isEqual(matDx, matStar) );

    matStar += matStar2;
    matDx += matDx2;
    TS_ASSERT( isEqual(matDx, matStar) );

    matStar -= matStar2;
    matDx -= matDx2;
    TS_ASSERT( isEqual(matDx, matStar) );

    matStar *= randValues[0];
    matDx *= randValues[0];
    TS_ASSERT( isEqual(matDx, matStar) );

    matStar /= 5.5f;
    matDx /= 5.5f;
    TS_ASSERT( isEqual(matDx, matStar) );

    matStar += matStar2;
    matStar -= matStar2;
    matDx += matDx2;
    matDx -= matDx2;
    TS_ASSERT( isEqual(matDx, matStar) );
  }

  /*****************************************************************************/
  void testMatrixUnaryOperator( void )
  {
    using namespace std;

    vector<float> randValues;
    generate_n(back_inserter(randValues), 16, FloatRandGen(100.f));

    D3DXMATRIX matDx(&randValues[0]);
    Star::float4x4 matStar(&randValues[0]);

    matDx = +matDx;
    matStar = +matStar;
    TS_ASSERT( isEqual(matDx, matStar) );

    matDx = -matDx;
    matStar = -matStar;
    TS_ASSERT( isEqual(matDx, matStar) );
  }

  /*****************************************************************************/
  void testMatrixBinaryOperator( void )
  {
    using namespace std;
    vector<float> randValues;
    vector<float> randValues2;
    generate_n(back_inserter(randValues), 16, FloatRandGen(100000.f));
    generate_n(back_inserter(randValues2), 16, FloatRandGen(1000.f));

    D3DXMATRIX matDx(&randValues[0]);
    D3DXMATRIX matDx2(&randValues2[0]);
    Star::float4x4 matStar(&randValues[0]);
    Star::float4x4 matStar2(&randValues2[0]);

    matDx = matDx+matDx2;
    matStar = matStar+matStar2;
    TS_ASSERT( isEqual(matDx, matStar) );

    matDx = matDx-matDx2;
    matStar = matStar-matStar2;
    TS_ASSERT( isEqual(matDx, matStar) );

    matDx = matDx2*matDx*matDx;
    matStar = matStar2*matStar*matStar;
    TS_ASSERT( isEqual(matDx, matStar) );

    matDx = 5*matDx2;
    matStar = 5*matStar2;
    TS_ASSERT( isEqual(matDx, matStar) );

    matDx = matDx2*5;
    matStar = matStar2*5;
    TS_ASSERT( isEqual(matDx, matStar) );

    matDx = matDx2/10.5f;
    matStar = matStar2/10.5f;
    TS_ASSERT( isEqual(matDx, matStar) );

    TS_ASSERT( matDx == matDx && matStar == matStar );
    TS_ASSERT( matDx != matDx2 && matStar != matStar2 );

    TS_ASSERT( isEqual((float*)matDx, matStar.constPtr(), 16) );
    TS_ASSERT( isEqual((float*)matDx, matStar.ptr(), 16) );
}

private:
  /*****************************************************************************/
  bool isEqual(const D3DXMATRIX& mat1, const Star::float4x4& mat2)
  {
   for ( size_t j = 0; j < 4; j++)
      for ( size_t i = 0; i < 4; i++)
        if ( std::abs(mat1(i,j)-mat2(i, j)) > std::numeric_limits<float>::epsilon()  )
          return false;
   return true;
  }

  /*****************************************************************************/
  bool isEqual(const float* a1, const float* a2, size_t n)
  {
      for ( size_t i = 0; i < n; i++)
        if ( std::abs(a1[i]-a2[i]) > std::numeric_limits<float>::epsilon()  )
          return false;
    return true;
  }

  /*****************************************************************************/
  class FloatRandGen
  {
    float m_maxValue;
  public:
    FloatRandGen(float maxV) : m_maxValue(maxV)
    {
      std::srand(0);
    }
    float operator()()
    {
      return std::rand()/float(RAND_MAX);
    }
  };
};
