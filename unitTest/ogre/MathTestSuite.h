#include <cxxtest/TestSuite.h>

#include <StarMath.h>

#include <limits>
#include <algorithm>
#include <OGRE/OgreMatrix4.h>
#include <OGRE/OgreMatrix3.h>

#include "RandGen.h"

class MathTestSuite : public CxxTest::TestSuite
{
public:
  /*****************************************************************************/
  void testMatrixIdentity( void )
  {
    Star::float4x4 matStar;
    Ogre::Matrix4 matOgre = Ogre::Matrix4::IDENTITY;

    matStar.toIdentity();
    TS_ASSERT( isEqual(matOgre, matStar) );
  }

  /*****************************************************************************/
  void testMatrixConstructors1( void )
  {
    using namespace std;
    vector<float> randValues;
    generate_n(back_inserter(randValues), 16, FloatRandGen(100000.f));

    Star::float4x4 matStar(&randValues[0]);
    TS_ASSERT( true );
  }

  /*****************************************************************************/
  void testMatrixConstructors2( void )
  {
    using namespace std;
    vector<float> randValues;
    generate_n(back_inserter(randValues), 16, FloatRandGen(100000.f));

    Ogre::Matrix4 matOgre(randValues[0], randValues[1], randValues[2], randValues[3],
                     randValues[4], randValues[5], randValues[6], randValues[7],
                     randValues[8], randValues[9], randValues[10], randValues[11],
                     randValues[12], randValues[13], randValues[14], randValues[15]);
    Star::float4x4 matStar(randValues[0], randValues[1], randValues[2], randValues[3],
                         randValues[4], randValues[5], randValues[6], randValues[7],
                         randValues[8], randValues[9], randValues[10], randValues[11],
                         randValues[12], randValues[13], randValues[14], randValues[15]);
    TS_ASSERT( isEqual(matOgre, matStar) );
  }

  /*****************************************************************************/
  void testMatrixAssignOperator( void )
  {
    using namespace std;

    vector<float> randValues;
    vector<float> randValues2;
    generate_n(back_inserter(randValues), 16, FloatRandGen(100000.f));
    generate_n(back_inserter(randValues2), 16, FloatRandGen(1000.f));

    Ogre::Matrix4 matDx, matDx2;
    ogreMatCopy(matDx, &randValues[0]);
    ogreMatCopy(matDx2, &randValues2[0]);

    Star::float4x4 matStar(&randValues[0]);
    Star::float4x4 matStar2(&randValues2[0]);

    matStar *= matStar2;
    TS_ASSERT( true );

    matStar += matStar2;
    TS_ASSERT( true );

    matStar -= matStar2;
    TS_ASSERT( true );

    matStar *= randValues[0];
    TS_ASSERT( true );

    matStar /= 5.5f;
    TS_ASSERT( true );

    matStar += matStar2;
    matStar -= matStar2;
    TS_ASSERT( true );
  }

    /*****************************************************************************/
  void testMatrixBinaryOperator( void )
  {
    using namespace std;
    vector<float> randValues;
    vector<float> randValues2;
    generate_n(back_inserter(randValues), 16, FloatRandGen(100000.f));
    generate_n(back_inserter(randValues2), 16, FloatRandGen(1000.f));

    Ogre::Matrix4 matDx, matDx2;
    ogreMatCopy(matDx, &randValues[0]);
    ogreMatCopy(matDx2, &randValues2[0]);

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

    matDx = matDx2*5;
    matStar = matStar2*5;
    TS_ASSERT( isEqual(matDx, matStar) );

    TS_ASSERT( matDx == matDx && matStar == matStar );
    TS_ASSERT( matDx != matDx2 && matStar != matStar2 );

    TS_ASSERT( isEqual((float*)&matDx[0][0], matStar.constPtr(), 16) );
    TS_ASSERT( isEqual((float*)&matDx[0][0], matStar.ptr(), 16) );
  }

  /*****************************************************************************/
  void testMatrixDeterminant( void )
  {
    using namespace std;
    for ( size_t i = 0; i < 50; i++ )
    {
      vector<float> randValues;
      generate_n(back_inserter(randValues), 16, FloatRandGen(10.f));

      Ogre::Matrix4 matDx;
      ogreMatCopy(matDx, &randValues[0]);

      Star::float4x4 matStar(&randValues[0]);
      float A = matStar.determinant();
      float B = matDx.determinant();
      TS_ASSERT(fabs((A-B)/B) < RELATIVE_TOLERANCE);
    }
  }

  /*****************************************************************************/
  void testMatrixInvert( void )
  {
    using namespace std;
    for ( size_t i = 0; i < 50; i++ )
    {
      vector<float> randValues;
      generate_n(back_inserter(randValues), 16, FloatRandGen(100.f));

      Ogre::Matrix4 matDx;
      ogreMatCopy(matDx, &randValues[0]);

      Star::float4x4 matStar(&randValues[0]);

      if ( std::abs(matStar.determinant()) > std::numeric_limits<float>::epsilon() )
      {
        matStar = matStar.inverse();
        matDx = matDx.inverse();
        TS_ASSERT( isEqual(matDx, matStar) );
      }
    }
  }

  /*****************************************************************************/
  void testMatrixTranspose( void )
  {
    using namespace std;
    for ( size_t i = 0; i < 50; i++ )
    {
      vector<float> randValues;
      generate_n(back_inserter(randValues), 16, FloatRandGen(100.f));

      Ogre::Matrix4 matDx;
      ogreMatCopy(matDx, &randValues[0]);

      Star::float4x4 matStar(&randValues[0]);

      matStar = matStar.transpose();
      matDx = matDx.transpose();
      TS_ASSERT( isEqual(matDx, matStar) );
    }
  }

  /*****************************************************************************/
  void testMatrixTranslation( void )
  {
    using namespace std;
    for ( size_t i = 0; i < 50; i++ )
    {
      vector<float> randValues;
      generate_n(back_inserter(randValues), 16, FloatRandGen(100.f));

      Ogre::Matrix4 matDx;
      ogreMatCopy(matDx, &randValues[0]);

      Star::float4x4 matStar(&randValues[0]);

      matDx.makeTrans(randValues[0], randValues[1], randValues[2]);
      matStar.makeTranslation(randValues[0], randValues[1], randValues[2]);
      TS_ASSERT( isEqual(matDx, matStar) );
    }
  }

  /*****************************************************************************/
  void testMatrixScale( void )
  {
    using namespace std;
    for ( size_t i = 0; i < 50; i++ )
    {
      vector<float> randValues;
      generate_n(back_inserter(randValues), 16, FloatRandGen(100.f));

      Ogre::Matrix4 matDx;
      ogreMatCopy(matDx, &randValues[0]);

      Star::float4x4 matStar(&randValues[0]);

      matDx = Ogre::Matrix4::IDENTITY;
      matDx.setScale(Ogre::Vector3(randValues[0], randValues[1], randValues[2]));
      matStar.makeScaling(randValues[0], randValues[1], randValues[2]);
      TS_ASSERT( isEqual(matDx, matStar) );
    }
  }

  /*****************************************************************************/
  void testMatrixRotate( void )
  {
    using namespace std;
    vector<float> randValues;
    generate_n(back_inserter(randValues), 3*50, FloatRandGen(2*M_PI));
    for ( size_t i = 0; i < 3*49; i++ )
    {
      Ogre::Matrix3 matDxTmp;
      Ogre::Matrix4 matDx;
      Star::float4x4 matStar;

      Ogre::Vector3 ogreAxis = Ogre::Vector3(randValues[i], randValues[i+1], randValues[i+2]);
      Star::float3 starAxis = Star::float3(randValues[i], randValues[i+1], randValues[i+2]);
      starAxis.normalize();
      ogreAxis.normalise();

      matDxTmp.FromAxisAngle(ogreAxis, Ogre::Radian(randValues[i]));
      matDx[3][0] = matDx[3][1] = matDx[3][2] = 0;
      matDx[3][3] = 1;
      matDx[0][3] = matDx[1][3] = matDx[2][3] = 0;
      matDx = matDxTmp;
      matStar.makeRotationAxis(starAxis, randValues[i]);

      TS_ASSERT( isEqual(matDx, matStar) );
    }
  }

private:
  static const float RELATIVE_TOLERANCE = 0.001;

  /*****************************************************************************/
  void ogreMatCopy(Ogre::Matrix4& mat1, float*data)
  {
    for(size_t j = 0; j < 4; j++ )
      for(size_t i = 0; i < 4; i++ )
        mat1[j][i] = *data++;
  }

/*****************************************************************************/
  bool isEqual(const Ogre::Matrix4& mat1, const Star::float4x4& mat2)
  {
   for ( size_t j = 0; j < 4; j++)
      for ( size_t i = 0; i < 4; i++)
        if ( std::abs((mat1[i][j]-mat2(i, j))/mat2(i, j)) > RELATIVE_TOLERANCE  )
          return false;
   return true;
  }

  /*****************************************************************************/
  bool isEqual(const float* a1, const float* a2, size_t n)
  {
    for ( size_t i = 0; i < n; i++)
      if ( std::abs((a1[i]-a2[i])/a2[i]) > RELATIVE_TOLERANCE )
        return false;
    return true;
  }
};
