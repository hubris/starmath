#include <cxxtest/TestSuite.h>

#include <StarMath.h>

#include <limits>
#include <algorithm>
#include <OGRE/OgreMatrix4.h>
#include <OGRE/OgreMatrix3.h>
#include <OGRE/OgreQuaternion.h>

#include "RandGen.h"

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

      starQuat = Star::quaternionf(&randValues[i]);
      ogreQuat = Ogre::Quaternion(randValues[i+3], randValues[i],
                                  randValues[i+1], randValues[i+2]);
      starQuat *= starQuat2;
      ogreQuat = ogreQuat*ogreQuat2;
      TS_ASSERT( isEqual(starQuat, ogreQuat) );

      starQuat *= 5.5f;
      ogreQuat = ogreQuat*5.5f;
      TS_ASSERT( isEqual(starQuat, ogreQuat) );

      starQuat /= 5.5f;
      ogreQuat = ogreQuat*(1.f/5.5f);
      TS_ASSERT( isEqual(starQuat, ogreQuat) );
    }
  }

private:
  /*****************************************************************************/
  bool isEqual(const Star::quaternionf& a1, const Ogre::Quaternion& a2)
  {
    for(size_t i = 0; i < 4; i++)
    {
      if(std::abs(a1[i]-a2[(i+1)%4]) > 12.*std::numeric_limits<float>::epsilon())
        return false;
    }
    return true;
  }
};
