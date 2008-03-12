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
    const size_t numPlanes = 16;
    generate_n(back_inserter(randValues), numPlanes*4, FloatRandGen(100000.f));

    for ( size_t i = 0; i < numPlanes; i+=4 )
    {
      Star::planef starPlane(Star::float3(randValues[i], randValues[i+1], randValues[i+2]), randValues[i+3]);
      Ogre::Plane ogrePlane(Ogre::Vector3(randValues[i], randValues[i+1], randValues[i+2]), randValues[i+3]);
      TS_ASSERT( isEqual(starPlane, ogrePlane) );
    }
  }


private:
  /*****************************************************************************/
  bool isEqual(const Star::planef& a1, const Ogre::Plane& a2)
  {
    Star::float3 starN = a1.getNormal();
    float eps = std::numeric_limits<float>::epsilon();

    for(size_t i = 0; i < 3; i++)
    {
      if(std::abs(starN[i]-a2.normal[i]) > eps)
        return false;
    }
    return true;
  }
};
