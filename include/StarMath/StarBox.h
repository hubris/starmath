#ifndef STAR_BOX_H
#define STAR_BOX_H

#include <StarMath/StarVec3.h>

#include <limits>
#include <algorithm>

namespace Star
{
  template<typename T>
  class Box
  {
  public:
    /**
     * Create an empty box.
     */
    Box();

    /**
     * Create a Box. min is included but not max.
     * @param min the box min
     * @param max the box max
     */
    Box(const Vec3<T>& min, const Vec3<T>& max);

    /**
     * Set a box min and max. min is included but not max.
     * @param min the box min
     * @param max the box max
     */
    void setMinMax(const Vec3<T>& min, const Vec3<T>& max);

    /**
     * Extend the box     
     * @param pt is the point to add to the box
     */
    void extends(const Vec3<T>& pt);

    /**
     * Get the Box size
     * @return the Box's size
     */
    Vec3<T> getSize() const;

  private:
    Vec3<T> m_min;
    Vec3<T> m_max;    
  };


  /*****************************************************************************/
  typedef Box<float> boxf;
  typedef Box<double> boxd;
  typedef Box<int> boxi;
  typedef Box<unsigned int> boxui;

  /*******************************************************************************/
  template<typename T>
  Box<T>::Box()
  {
    T min = std::numeric_limits<T>::min();
    T max = std::numeric_limits<T>::max();
    if(!std::numeric_limits<T>::isReal())
      setMinMax(min, max);
    else
      setMinMax(-max, max);
  }

  /*******************************************************************************/
  template<typename T>
  Box<T>::Box(const Vec3<T>& min, const Vec3<T>& max)
  {
    setMinMax(min, max);
  }

  /*******************************************************************************/
  template<typename T>
  void
  Box<T>::setMinMax(const Vec3<T>& min, const Vec3<T>& max)    
  {
    m_min = min;
    m_max = max;
  }

  /*******************************************************************************/
  template<typename T>
  void
  Box<T>::extends(const Vec3<T>& pt)
  {
    for(size_t i = 0; i < 3; i++) {
      m_min[i] = std::min(pt[i], m_min[i]);
      m_max[i] = std::max(pt[i], m_max[i]);
    }
  }

  /*******************************************************************************/
  template<typename T>
  Vec3<T>
  Box<T>::getSize() const
  {
    return m_max-m_min;
  }
}

#endif
