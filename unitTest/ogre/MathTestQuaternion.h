#include <cxxtest/TestSuite.h>
#include <cxxtest/ValueTraits.h>

#include <StarMath.h>

#include <limits>
#include <algorithm>
#include <OGRE/OgreMatrix4.h>
#include <OGRE/OgreMatrix3.h>
#include <OGRE/OgreQuaternion.h>

#include "RandGen.h"
#include "MathTestStarValueTraits.h"

class MathTestQuaternion : public CxxTest::TestSuite
{
public:
  void testCtor()
  {
    using namespace std;
    using namespace Star;
    vector<float> randValues;
    generate_n(back_inserter(randValues), 4, FloatRandGen(100000.f));

    Star::quaternionf starQuat(randValues[0], randValues[1], randValues[2], randValues[3]);
    Ogre::Quaternion ogreQuat(randValues[3], randValues[0], randValues[1], randValues[2]);
    TS_ASSERT( isEqual(starQuat, ogreQuat) );

    Star::quaternionf starQuat2(&randValues[0]);
    Ogre::Quaternion ogreQuat2(randValues[3], randValues[0], randValues[1], randValues[2]);
    TS_ASSERT( isEqual(starQuat2, ogreQuat2) );

    Star::quaternionf starQuat3(float3(randValues[0], randValues[1], randValues[2]),
                                randValues[3]);
    Ogre::Quaternion ogreQuat3(Ogre::Radian(randValues[3]),
                               Ogre::Vector3(randValues[0], randValues[1], randValues[2]));
    TS_ASSERT( isEqual(starQuat3, ogreQuat3) );
  }

  void testIdentity()
  {
    Star::quaternionf starQuat;
    Ogre::Quaternion ogreQuat = Ogre::Quaternion::IDENTITY;

    starQuat.toIdentity();
    TS_ASSERT( isEqual(starQuat, ogreQuat) );
  }

  void testOperator()
  {
    using namespace std;
    using namespace Star;
    vector<float> randValues;
    const size_t numQuat = 16;
    generate_n(back_inserter(randValues), 4*numQuat, FloatRandGen(1.f));

    for(size_t i = 0; i < (numQuat-1)*4;)
    {
      Star::quaternionf starQuat(&randValues[i]);
      Ogre::Quaternion ogreQuat(randValues[i+3], randValues[i],
                                randValues[i+1], randValues[i+2]);

      i += 4;
      Star::quaternionf starQuat2(&randValues[i]);
      Ogre::Quaternion ogreQuat2(randValues[i+3], randValues[i],
                                randValues[i+1], randValues[i+2]);
      starQuat += starQuat2;
      ogreQuat = ogreQuat+ogreQuat2;
      TS_ASSERT( isEqual(starQuat, ogreQuat) );

      starQuat -= starQuat2;
      ogreQuat = ogreQuat-ogreQuat2;
      TS_ASSERT( isEqual(starQuat, ogreQuat) );

      starQuat = starQuat-starQuat2;
      ogreQuat = ogreQuat-ogreQuat2;
      TS_ASSERT( isEqual(starQuat, ogreQuat) );

      starQuat = starQuat+starQuat2;
      ogreQuat = ogreQuat+ogreQuat2;
      TS_ASSERT( isEqual(starQuat, ogreQuat) );

      starQuat = Star::quaternionf(&randValues[i]);
      ogreQuat = Ogre::Quaternion(randValues[i+3], randValues[i],
                                  randValues[i+1], randValues[i+2]);
      starQuat *= starQuat2;
      ogreQuat = ogreQuat*ogreQuat2;
      TS_ASSERT( isEqual(starQuat, ogreQuat) );

      starQuat = Star::quaternionf(&randValues[i]);
      ogreQuat = Ogre::Quaternion(randValues[i+3], randValues[i],
                                  randValues[i+1], randValues[i+2]);
      starQuat = starQuat*starQuat2;
      ogreQuat = ogreQuat*ogreQuat2;
      TS_ASSERT( isEqual(starQuat, ogreQuat) );

      starQuat = Star::quaternionf(&randValues[i]);
      ogreQuat = Ogre::Quaternion(randValues[i+3], randValues[i],
                                  randValues[i+1], randValues[i+2]);
      starQuat *= 5.5f;
      ogreQuat = ogreQuat*5.5f;
      TS_ASSERT( isEqual(starQuat, ogreQuat) );

      starQuat /= 5.5f;
      ogreQuat = ogreQuat*(1.f/5.5f);
      TS_ASSERT( isEqual(starQuat, ogreQuat) );

      starQuat= Star::quaternionf(&randValues[i]);
      ogreQuat = Ogre::Quaternion(randValues[i+3], randValues[i],
                                  randValues[i+1], randValues[i+2]);
      starQuat = starQuat/5.5f;
      ogreQuat = ogreQuat*(1.f/5.5f);
      TS_ASSERT( isEqual(starQuat, ogreQuat) );

      TS_ASSERT( starQuat==starQuat );
      TS_ASSERT( !(starQuat!=starQuat) );
    }
  }

  void testOperation()
  {
    using namespace std;
    using namespace Star;
    vector<float> randValues;
    const size_t numQuat = 16;
    generate_n(back_inserter(randValues), 4*numQuat, FloatRandGen(1.f));

    for(size_t i = 0; i < (numQuat-1)*4;)
    {
      Star::quaternionf starQuat(&randValues[i]);
      Ogre::Quaternion ogreQuat(randValues[i+3], randValues[i],
                                randValues[i+1], randValues[i+2]);

      i += 4;
      Star::quaternionf starQuat2(&randValues[i]);
      Ogre::Quaternion ogreQuat2(randValues[i+3], randValues[i],
                                randValues[i+1], randValues[i+2]);

      TS_ASSERT_DELTA(starQuat.norm(), ogreQuat.Norm(), std::numeric_limits<float>::epsilon());
      TS_ASSERT_DELTA(starQuat.length(), std::sqrt(ogreQuat.Norm()), std::numeric_limits<float>::epsilon());
      TS_ASSERT_DELTA(starQuat.dot(starQuat2), ogreQuat.Dot(ogreQuat2), std::numeric_limits<float>::epsilon());

      starQuat2 = starQuat.conjugate();
      TS_ASSERT(starQuat2.conjugate() == starQuat);
    }
  }

  void testAxisAngle()
  {
    using namespace std;
    using namespace Star;
    vector<float> randValues;
    const size_t numQuat = 16;
    generate_n(back_inserter(randValues), 4*numQuat, FloatRandGen(1.f));

    for(size_t i = 0; i < (numQuat-1)*4;)
    {
      Star::quaternionf starQuat(&randValues[i]);
      Ogre::Quaternion ogreQuat(randValues[i+3], randValues[i],
                                randValues[i+1], randValues[i+2]);

      i += 4;
      Star::quaternionf starQuat2(&randValues[i]);
      Ogre::Quaternion ogreQuat2(randValues[i+3], randValues[i],
                                randValues[i+1], randValues[i+2]);

      Star::float3 starAxis;
      float starAngle;
      Ogre::Vector3 ogreAxis;
      Ogre::Radian ogreAngle;

      starQuat.toAxisAngle(starAxis, starAngle);
      ogreQuat.ToAngleAxis(ogreAngle, ogreAxis);

      TS_ASSERT_DELTA(starAngle, ogreAngle.valueRadians(), std::numeric_limits<float>::epsilon());
      TS_ASSERT_DELTA(starAxis.x, ogreAxis.x, std::numeric_limits<float>::epsilon());
      TS_ASSERT_DELTA(starAxis.y, ogreAxis.y, std::numeric_limits<float>::epsilon());
      TS_ASSERT_DELTA(starAxis.z, ogreAxis.z, std::numeric_limits<float>::epsilon());

      starQuat2.fromAxisAngle(starAxis, starAngle);
      ogreQuat2.FromAngleAxis(Ogre::Radian(starAngle), Ogre::Vector3(starAxis.x, starAxis.y, starAxis.z));
      TS_ASSERT( isEqual(starQuat2, ogreQuat2) );
    }
  }

  void testRotation()
  {
    Star::quaternionf starQuat;
    Star::float3 axis(5, 3, 2.5);
    axis.normalize();
    starQuat.fromAxisAngle(axis, M_PI/4);

    Star::float4x4 rotMat;
    starQuat.toRotationMatrix(rotMat);

    Star::float3 point(1, 1, 1);
    Star::float3 resMat = rotMat*point;
    Star::float3 resQuat = starQuat.rotate(point);
    TS_ASSERT(resMat == resQuat);
    TS_ASSERT(starQuat.inverse().inverse() == starQuat);
  }

private:
  /*****************************************************************************/
  bool isEqual(const Star::quaternionf& a1, const Ogre::Quaternion& a2)
  {
    for(size_t i = 0; i < 4; i++)
    {
      if(std::abs(a1[i]-a2[(i+1)%4]) > std::numeric_limits<float>::epsilon())
        return false;
    }
    return true;
  }
};
