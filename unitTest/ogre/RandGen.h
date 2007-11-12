#include <cstdlib>

/*****************************************************************************/
class FloatRandGen
{
  float m_maxValue;
public:
  FloatRandGen(float maxV) : m_maxValue(maxV)
  {
  }

  float operator()()
  {
    return m_maxValue*(std::rand()/float(RAND_MAX));
  }
};
