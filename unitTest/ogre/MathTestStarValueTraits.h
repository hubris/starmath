#ifdef CXXTEST_RUNNING
#include <stdio.h>
#include <sstream>

#include <StarMath.h>

namespace CxxTest
{
  CXXTEST_TEMPLATE_INSTANTIATION
  class ValueTraits<Star::quaternionf>
  {
    std::string str;

  public:
    ValueTraits( const Star::quaternionf &m )
    {
      std::ostringstream ss;
      ss << m;
      str = ss.str();
    }
    const char *asString() const { return str.c_str(); }
  };
};
#endif
