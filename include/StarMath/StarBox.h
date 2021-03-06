#ifndef STAR_BOX_H
#define STAR_BOX_H

#include <StarMath/StarVec3.h>

#include <limits>
#include <algorithm>
#include <vector>

namespace Star
{
  template<typename T>
  class Box
  {
  public:
    typedef Vec3<T> Dim;

    /**
     * Create an empty box.
     */
    Box();

    /**
     * explicit cast
     */
    template <typename T2>
    explicit Box(const Box<T2>& b)
    {
      const Vec3<T2>& bMin = b.getMin();
      const Vec3<T2>& bMax = b.getMax();
      m_min = Vec3<T>(T2(bMin[0]), T2(bMin[1]), T2(bMin[2]));
      m_max = Vec3<T>(T2(bMax[0]), T2(bMax[1]), T2(bMax[2]));
    }

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
    inline void setMinMax(const Vec3<T>& min, const Vec3<T>& max);

    /**
     * Extend the box
     * @param pt is the point to add to the box
     */
    inline void extends(const Vec3<T>& pt);

    /**
     * Get the Box size
     * @return the Box's size
     */
    inline Vec3<T> getSize() const;

    /**
     * Get the Box min
     * @return the Box's min
     */
    inline const Vec3<T>& getMin() const;

    /**
     * Get the Box max
     * @return the Box's max
     */
    inline const Vec3<T>& getMax() const;

    /**
     * Check for inclusion of vector pos
     * @return true if pos is in [min,max[
     */
    inline bool contains(const Vec3<T>& pos) const;

    /**
     * Return indexed vertices representation of the box
     */
    inline void getGeometry(std::vector<Vec3<T> >& vertices, std::vector<short>& indices) const;

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
    T tmin = std::numeric_limits<T>::min();
    T tmax = std::numeric_limits<T>::max();
    if(!std::numeric_limits<T>::is_integer)
      setMinMax(Vec3<T>(tmin, tmin, tmin), Vec3<T>(tmax, tmax, tmax));
    else
      setMinMax(Vec3<T>(-tmax, -tmax, -tmax), Vec3<T>(tmax, tmax, tmax));
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

  /*******************************************************************************/
  template<typename T>
  const Vec3<T>&
  Box<T>::getMax() const
  {
    return m_max;
  }

  /*******************************************************************************/
  template<typename T>
  const Vec3<T>&
  Box<T>::getMin() const
  {
    return m_min;
  }

  /*******************************************************************************/
  template<typename T>
  bool
  Box<T>::contains(const Vec3<T>& pos) const
  {
    for(size_t i = 0; i < 3; i++) {
      if (pos[i] < m_min[i] || pos[i] >= m_max[i])
        return false;
    }
    return true;
  }

  /*******************************************************************************/
  template<typename T>
  void
  Box<T>::getGeometry(std::vector<Vec3<T> >& vertices, std::vector<short>& indices) const
  {
    vertices.push_back(Vec3<T>(m_min[0], m_min[1], m_min[2]));
    vertices.push_back(Vec3<T>(m_max[0], m_min[1], m_min[2]));
    vertices.push_back(Vec3<T>(m_max[0], m_max[1], m_min[2]));
    vertices.push_back(Vec3<T>(m_min[0], m_max[1], m_min[2]));

    vertices.push_back(Vec3<T>(m_min[0], m_min[1], m_max[2]));
    vertices.push_back(Vec3<T>(m_max[0], m_min[1], m_max[2]));
    vertices.push_back(Vec3<T>(m_max[0], m_max[1], m_max[2]));
    vertices.push_back(Vec3<T>(m_min[0], m_max[1], m_max[2]));

    static short idx[] = { 1, 0, 3,
                           2, 1, 3,
                           4, 5, 7,
                           5, 6, 7,
                           0, 4, 7,
                           0, 7, 3,
                           5, 1, 6,
                           6, 1, 2,
                           0, 1, 5,
                           0, 5, 4,
                           2, 3, 6,
                           6, 3, 7 };
    indices.assign(idx, idx+sizeof(idx)/sizeof(idx[0]));
  }
}

/**
 * ostream operator for vectors
 */
template <typename T>
std::ostream&
operator << (std::ostream& os, const Star::Box<T>& b)
{
  return os << "(" << b.getMin() << " - " << b.getMax() << ")";
}

#endif
