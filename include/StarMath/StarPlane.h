#ifndef STAR_PLANE_H
#define STAR_PLANE_H

namespace Star
{
  template<typename T>
  class Plane
  {
  public:
    /**
     * Create a plane.
     * @param normal the plane's normal
     * @param dist the distance to the origin
     */
    Plane(const Vec3<T>& normal, float dist);

    /**
     * Create a plane
     * @param p1 a point on the plane
     * @param p2 a point on the plane
     * @param p3 a point on the plane
     */
    Plane(const Vec3<T>& p1, const Vec3<T>& p2, const Vec3<T>& p3);

    /**
     * Create a plane
     * @param n the plane's normal
     * @param p a point on the plane
     */
    Plane(const Vec3<T>& normal, const Vec3<T>& p);

    /**
     * Get the plane normal
     * @return the plane's normal
     */
    const Vec3<T>& getNormal() const;

    /**
     * Get the plane distance
     * @return the plane's distance
     */
    T getDistance() const;

  private:
    Vec3<T> m_normal;
    T m_distance;
  };


  /*****************************************************************************/
  typedef Plane<float> planef;
  typedef Plane<double> planed;
  typedef Plane<int> planei;
  typedef Plane<unsigned int> planeui;

  /*******************************************************************************/
  template<typename T>
  Plane<T>::Plane(const Vec3<T>& normal, float dist)
    : m_normal(normal), m_distance(dist)
  {
  }

  /*******************************************************************************/
  template<typename T>
  Plane<T>::Plane(const Vec3<T>& p1, const Vec3<T>& p2, const Vec3<T>& p3)
  {
    Vec3<T> v0 = p2-p1;
    Vec3<T> v1 = p3-p1;
    m_normal = v0.cross(v1);
    m_normal.normalize();
    m_distance = m_normal.dot(p1);
  }

  /*******************************************************************************/
  template<typename T>
  Plane<T>::Plane(const Vec3<T>& normal, const Vec3<T>& p)
  {
    m_normal = normal;
    m_distance = m_normal.dot(p);
  }

  /*******************************************************************************/
  template<typename T>
  const Vec3<T>&
  Plane<T>::getNormal() const
  {
    return m_normal;
  }

  /*******************************************************************************/
  template<typename T>
  T
  Plane<T>::getDistance() const
  {
    return m_distance;
  }
}

#endif
