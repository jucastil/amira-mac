/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Nick Thompson (MMM yyyy)
** Modified by : David Mott (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/



#ifndef _SB_BOX_
#define _SB_BOX_

#include <Inventor/SbBase.h>
#include <Inventor/SbVec.h>
#include <Inventor/SbMatrix.h>
#include <Inventor/STL/iostream>

class SbBox3s;
class SbBox3i32;
class SbBox3f;
class SbBox3d;

class SbXfBox3d;
class SbXfBox3f;

/**
 * @VSGEXT 3D box class.
 *
 * @ingroup Basics
 *
 * @DESCRIPTION
 *   3D box which has planes parallel to the major axes and is specified by two
 *   points on a diagonal. This class is part of the standard Open Inventor datatype
 *   classes and is used as input and output to geometry operations (see
 *   SoGetBoundingBoxAction).
 *
 * @SEE_ALSO
 *    SbXfBox3f,
 *    SbBox2f,
 *    SbBox3s,
 *    SbBox2i32,
 *    SbBox2s,
 *    SbVec3i32,
 *    SbVec3s,
 *    SbVec2f,
 *    SbVec2i32,
 *    SbVec2s,
 *    SbMatrix,
 *    SoGetBoundingBoxAction
 *
 * [OIVJAVA-WRAPPER-CLASS BASIC_TYPE{true},LAYOUTED_ARRAY_TYPE{int,6}]
 */
class INVENTORBASE_API SbBox3i32 {

 public:
  /**
   * Constructor for a 3D integer32 box.  The box is initially empty.
   */
  SbBox3i32()
    { makeEmpty(); }

  /**
   * Constructor for a 3D integer32 box. @B xmin @b, @B ymin @b,
   * @B zmin @b, @B xmax @b, @B ymax @b and @B zmax @b are the bounds of the box.
   */
  SbBox3i32(int xmin, int ymin, int zmin,
          int xmax, int ymax, int zmax)
    { m_min.setValue(xmin, ymin, zmin); m_max.setValue(xmax, ymax, zmax); }

  /**
   * Constructor for a 3D integer32 box.
   * @B m_min @b and @B m_max @b are the corners of the diagonal that define the box.
   */
  SbBox3i32(const SbVec3i32 &_min, const SbVec3i32 &_max)
    { m_min = _min; m_max = _max; }

  /**
   * Constructor given an SbBox3s (adapter).
   */
  SbBox3i32( const SbBox3s &box );

  /**
   * Destructor.
   */
  ~SbBox3i32()
    {}

  /**
   * Returns the minimum point of the box. The minimum point is the
   * corner of the box with the lowest X, Y, and Z values.
   * [OIVJAVA-WRAPPER NO_WRAP]
   */
  const SbVec3i32 &getMin() const
    { return m_min; }

  /**
   * Returns the maximum point of the box. The maximum point is the
   * corner of the box with the highest X, Y, and Z values.
   * [OIVJAVA-WRAPPER NO_WRAP]
   */
  const SbVec3i32 &getMax() const
    { return m_max; }

  /**
   * Returns the minimum point of the box. The minimum point is the
   * corner of the box with the lowest X, Y, and Z values.
   */
  SbVec3i32 &getMin()
    { return m_min; }

  /**
   * Returns the maximum point of the box. The maximum point is the
   * corner of the box with the highest X, Y, and Z values.
   */
  SbVec3i32 &getMax()
    { return m_max; }

  /**
   * Returns the center of the box.
   */
  SbVec3f getCenter() const;

  /**
   * Extends this box (if necessary) to contain the specified point.
   */
  void extendBy(const SbVec3f &pt);

  /**
   * Extends this box (if necessary) to contain the specified box.
   */
  void extendBy(const SbBox3i32 &bb);

  /**
   * Returns TRUE if the specified point intersects this box.
   */
  SbBool intersect(const SbVec3f &pt) const;

  /**
   * Returns TRUE if the specified box intersects this box.
   */
  SbBool intersect(const SbBox3i32 &bb) const;

  /**
  * Returns TRUE if the specified point intersects this box.
  */
  SbBool intersect(const SbVec3i32 &pt) const;

  /**
   * Returns the intersection of the specified box with this box.
   * Returned box is empty if there is no intersection.
   */
  SbBox3i32 intersection(const SbBox3i32& box) const;

  /**
   * Returns TRUE if the specified box is fully contained inside this box.
   */
  inline SbBool contains(const SbBox3i32 &bb) const
  {
    SbBool contained = true;
    for( int i = 0; i < 3 && contained; i++ )
    {
      contained &= bb.m_min[i] >= m_min[i] &&
                   bb.m_min[i] <= m_max[i] &&
                   bb.m_max[i] <= m_max[i];
    }

    return contained;
  }

  /**
   * Returns TRUE if bounding box is completely outside the
   * view-volume defined by the model+view+projection matrix given.
   * "cullBits" keeps track of which view-volume clipping planes the
   * box is completely inside of; if a 'parent' bounding box of this
   * bounding box was found to be completely inside the left/right
   * clipping planes, the low bit of cullBits will be set to zero,
   * and this routine will not test this box against those planes.
   * When cullBits is zero, it is a waste of time to call this
   * function!  Before calling this the first time, set cullBits to
   * 7 (SoGLRenderAction and SoSeparator will handle this
   * automatically for render culling).
   */
  SbBool outside(const SbMatrix &MVP, int &cullBits) const;

  /**
   * Sets the corners of the box.
   */
  void setBounds(int xmin, int ymin, int zmin,
                 int xmax, int ymax, int zmax)
    { m_min.setValue(xmin, ymin, zmin); m_max.setValue(xmax, ymax, zmax); }

  /**
   * Sets the corners of the box.
   */
  void setBounds(const SbVec3i32 &_min, const SbVec3i32 &_max)
    { m_min = _min; m_max = _max; }

  /**
   * Gets the corners of the box.
   */
  void getBounds(int &xmin, int &ymin, int &zmin,
                 int &xmax, int &ymax, int &zmax) const
    { m_min.getValue(xmin, ymin, zmin); m_max.getValue(xmax, ymax, zmax); }

  /**
   * Gets the corners of the box.
   * [OIVJAVA-WRAPPER NAME{getMinMax}]
   */
  void getBounds(SbVec3i32 &_min, SbVec3i32 &_max) const
    { _min = m_min; _max = m_max; }

  /**
   * Returns the closest point on the box to the given point.
   * (Returns the point on the center of the Z face if passed the center.)
   */
  SbVec3f getClosestPoint(const SbVec3f &point) const;

  /**
   * Gets box origin which is the same as the minimum corner of the box.
   */
  void getOrigin(int &originX, int &originY, int &originZ) const
    { originX = m_min[0]; originY = m_min[1]; originZ = m_min[2]; }

  /**
   * Gets box size.
   * [OIVJAVA-WRAPPER NO_WRAP]
   */
  void getSize(int &sizeX, int &sizeY, int &sizeZ) const {
    if ( m_max[0] < m_min[0] ) {
      sizeX = 0;
      sizeY = 0;
      sizeZ = 0;
    }
    else {
      sizeX = m_max[0] - m_min[0];
      sizeY = m_max[1] - m_min[1];
      sizeZ = m_max[2] - m_min[2];
    }
  }

  /**
   * Gets box size.
   */
  SbVec3i32 getSize() const
  {
    if ( m_max[0] < m_min[0] )
      return SbVec3i32(0, 0, 0);

    return m_max-m_min;
  }

  /**
   * Makes an empty box.
   */
  void makeEmpty();

  /**
   * Returns TRUE if the box is empty, and FALSE otherwise.
   */
  SbBool isEmpty() const
    { return m_max[0] < m_min[0]; }

  /**
   * Returns TRUE if all three dimensions of the box have positive size, and FALSE
   * otherwise.
   */
  SbBool hasVolume() const
    { return (m_max[0] > m_min[0] && m_max[1] > m_min[1] && m_max[2] > m_min[2]); }

  /**
   * Finds the span of a box along a specified direction. The span is the total
   * distance the box occupies along a given direction. The total distance is
   * returned in the form of a minimum and maximum distance from the origin of each
   * of the corners of the box along the given direction. The difference between
   * these two values is the span.
   */
  void getSpan(const SbVec3f &direction, float &dMin, float &dMax) const;

  /**
   * Transforms box by matrix, enlarging box to contain result.
   */
  void transform(const SbMatrix &m);

  /**
   * Returns the volume of the box.
   */
  float getVolume() const;

  /**
   * Assignment operator given an SbBox3s (adapter).
   */
  SbBox3i32 operator = (const SbBox3s &box);

  /**
  * Writes the box to the specified output stream.
  */
  INVENTORBASE_API friend inline std::ostream& operator << (std::ostream& os, const SbBox3i32& b);

  /**
   * Equality comparison.
   */
  INVENTORBASE_API friend int operator ==(const SbBox3i32 &b1, const SbBox3i32 &b2);

  /**
   * Inequality comparison.
   */
  INVENTORBASE_API friend int operator !=(const SbBox3i32 &b1, const SbBox3i32 &b2)
  { return !(b1 == b2); }

 private:
  // Minimum and maximum points
  SbVec3i32 m_min, m_max;
};

/**
 * @VSGEXT 3D box class.
 *
 * @ingroup Basics
 *
 * @DESCRIPTION
 *   3D box which has planes parallel to the major axes and is specified by two
 *   points on a diagonal. This class is part of the standard Open Inventor datatype
 *   classes and is used as input and output to geometry operations (see
 *   SoGetBoundingBoxAction).
 *
 * @SEE_ALSO
 *    SbXfBox3f,
 *    SbBox2f,
 *    SbBox2s,
 *    SbVec3s,
 *    SbVec2f,
 *    SbVec2s,
 *    SbMatrix,
 *    SoGetBoundingBoxAction
 *
 * [OIVJAVA-WRAPPER-CLASS BASIC_TYPE{true},LAYOUTED_ARRAY_TYPE{short,6}]
 */

class INVENTORBASE_API SbBox3s {

 public:
  /**
   * Constructor for a 3D short box.  The box is initially empty.
   */
  SbBox3s()
    { makeEmpty(); }

  /**
   * Constructor for a 3D short box. @B xmin @b, @B ymin @b,
   * @B zmin @b, @B xmax @b, @B ymax @b and @B zmax @b are the bounds of the box.
   */
  SbBox3s(short xmin, short ymin, short zmin,
          short xmax, short ymax, short zmax)
    { m_min.setValue(xmin, ymin, zmin); m_max.setValue(xmax, ymax, zmax); }

  /**
   * Constructor for a 3D short box.
   * @B m_min @b and @B m_max @b are the corners of the diagonal that define the box.
   */
  SbBox3s(const SbVec3s &_min, const SbVec3s &_max)
    { m_min = _min; m_max = _max; }

  /**
   * Constructor given an SbBox3i32 (adapter).
   * Note possible loss of data.
   */
  SbBox3s(const SbBox3i32 &box);

  /**
   * Destructor.
   */
  ~SbBox3s()
    {}

  /**
   * Returns the minimum point of the box. The minimum point is the
   * corner of the box with the lowest X, Y, and Z values.
   * [OIVJAVA-WRAPPER NO_WRAP]
   */
  const SbVec3s &getMin() const
    { return m_min; }

  /**
   * Returns the maximum point of the box. The maximum point is the
   * corner of the box with the highest X, Y, and Z values.
   * [OIVJAVA-WRAPPER NO_WRAP]
   */
  const SbVec3s &getMax() const
    { return m_max; }

  /**
   * Returns the minimum point of the box. The minimum point is the
   * corner of the box with the lowest X, Y, and Z values.
   */
  SbVec3s &getMin()
    { return m_min; }

  /**
   * Returns the maximum point of the box. The maximum point is the
   * corner of the box with the highest X, Y, and Z values.
   */
  SbVec3s &getMax()
    { return m_max; }

  /**
   * Returns the center of the box.
   */
  SbVec3f getCenter() const;

  /**
   * Extends this box (if necessary) to contain the specified point.
   */
  void extendBy(const SbVec3f &pt);

  /**
   * Extends this box (if necessary) to contain the specified box.
   */
  void extendBy(const SbBox3s &bb);

  /**
   * Returns TRUE if the specified point intersects this box.
   */
  SbBool intersect(const SbVec3f &pt) const;

  /**
   * Returns TRUE if the specified box intersects this box.
   */
  SbBool intersect(const SbBox3s &bb) const;

  /**
   * Returns TRUE if bounding box is completely outside the
   * view-volume defined by the model+view+projection matrix given.
   * "cullBits" keeps track of which view-volume clipping planes the
   * box is completely inside of; if a 'parent' bounding box of this
   * bounding box was found to be completely inside the left/right
   * clipping planes, the low bit of cullBits will be set to zero,
   * and this routine will not test this box against those planes.
   * When cullBits is zero, it is a waste of time to call this
   * function!  Before calling this the first time, set cullBits to
   * 7 (SoGLRenderAction and SoSeparator will handle this
   * automatically for render culling).
   */
  SbBool outside(const SbMatrix &MVP, int &cullBits) const;

  /**
   * Sets the corners of the box.
   */
  void setBounds(short xmin, short ymin, short zmin,
                 short xmax, short ymax, short zmax)
    { m_min.setValue(xmin, ymin, zmin); m_max.setValue(xmax, ymax, zmax); }

  /**
   * Sets the corners of the box.
   */
  void setBounds(const SbVec3s &_min, const SbVec3s &_max)
    { m_min = _min; m_max = _max; }

  /**
   * Gets the corners of the box.
   */
  void getBounds(short &xmin, short &ymin, short &zmin,
                 short &xmax, short &ymax, short &zmax) const
    { m_min.getValue(xmin, ymin, zmin); m_max.getValue(xmax, ymax, zmax); }

  /**
   * Gets the corners of the box.
   * [OIVJAVA-WRAPPER NAME{getMinMax}]
   */
  void getBounds(SbVec3s &_min, SbVec3s &_max) const
    { _min = m_min; _max = m_max; }

  /**
   * Returns the closest point on the box to the given point.
   * (Returns the point on the center of the Z face if passed the center.)
   */
  SbVec3f getClosestPoint(const SbVec3f &point) const;

  /**
   * Gets box origin which is the same as the minimum corner of the box.
   */
  void getOrigin(short &originX, short &originY, short &originZ) const
    { originX = m_min[0]; originY = m_min[1]; originZ = m_min[2]; }

  /**
   * Gets box size.
   */
  void getSize(short &sizeX, short &sizeY, short &sizeZ) const {
    if ( m_max[0] < m_min[0] ) {
      sizeX = 0;
      sizeY = 0;
      sizeZ = 0;
    }
    else {
      sizeX = m_max[0] - m_min[0];
      sizeY = m_max[1] - m_min[1];
      sizeZ = m_max[2] - m_min[2];
    }
  }

  /**
   * Makes an empty box.
   */
  void makeEmpty();

  /**
   * Returns TRUE if the box is empty, and FALSE otherwise.
   */
  SbBool isEmpty() const
    { return m_max[0] < m_min[0]; }

  /**
   * Returns TRUE if all three dimensions of the box have positive size, and FALSE
   * otherwise.
   */
  SbBool hasVolume() const
    { return (m_max[0] > m_min[0] && m_max[1] > m_min[1] && m_max[2] > m_min[2]); }

  /**
   * Finds the span of a box along a specified direction. The span is the total
   * distance the box occupies along a given direction. The total distance is
   * returned in the form of a minimum and maximum distance from the origin of each
   * of the corners of the box along the given direction. The difference between
   * these two values is the span.
   */
  void getSpan(const SbVec3f &direction, float &dMin, float &dMax) const;

  /**
   * Transforms box by matrix, enlarging box to contain result.
   */
  void transform(const SbMatrix &m);

  /**
   * Returns the volume of the box.
   */
  float getVolume() const;

  /**
   * Assignment operator given an SbBox3i32 (adapter).
   * Note possible loss of data.
   */
  SbBox3s operator = (const SbBox3i32 &box);

  /**
   * Equality comparison.
   */
  INVENTORBASE_API friend int operator ==(const SbBox3s &b1, const SbBox3s &b2);

  /**
   * Inequality comparison.
   */
  INVENTORBASE_API friend int operator !=(const SbBox3s &b1, const SbBox3s &b2)
  { return !(b1 == b2); }

 private:
  // Minimum and maximum points
  SbVec3s m_min, m_max;
};

/**
 * 3D box class.
 *
 * @ingroup Basics
 *
 * @DESCRIPTION
 *   3D box which has planes parallel to the major axes and is specified by two
 *   points on a diagonal. This class is part of the standard Open Inventor datatype
 *   classes and is used as input and output to geometry operations (see
 *   SoGetBoundingBoxAction).
 *
 * @SEE_ALSO
 *    SbXfBox3f,
 *    SbBox2f,
 *    SbBox2s,
 *    SbVec3f,
 *    SbVec2f,
 *    SbVec2s,
 *    SbMatrix,
 *    SoGetBoundingBoxAction
 *
 * [OIVJAVA-WRAPPER-CLASS BASIC_TYPE{true},LAYOUTED_ARRAY_TYPE{float,6}]
 */

class INVENTORBASE_API SbBox3f {

 public:
  /**
   * Constructor for a 3D float box.  The box is initially empty.
   */
  SbBox3f()
    { makeEmpty(); }

  /**
   * Constructor for a 3D float box. @B xmin @b, @B ymin @b,
   * @B zmin @b, @B xmax @b, @B ymax @b and @B zmax @b are the bounds of the box.
   */
  SbBox3f(float xmin, float ymin, float zmin,
          float xmax, float ymax, float zmax)
    { m_min.setValue(xmin, ymin, zmin); m_max.setValue(xmax, ymax, zmax); }

  /**
   * Constructor for a 3D float box.
   * @B m_min @b and @B m_max @b are the corners of the diagonal that define the box.
   */
  SbBox3f(const SbVec3f &_min, const SbVec3f &_max)
    { m_min = _min; m_max = _max; }

  /**
   * Destructor.
   */
  ~SbBox3f()
    {}

  /**
   * Returns the minimum point of the box. The minimum point is the
   * corner of the box with the lowest X, Y, and Z values.
   * [OIVJAVA-WRAPPER NO_WRAP]
   */
  inline const SbVec3f & getMin() const
    { return m_min; }

  /**
   * Returns the minimum point of the box. The minimum point is the
   * corner of the box with the lowest X, Y, and Z values.
   */
  inline SbVec3f &getMin()
    { return m_min; }

  /**
   * Returns the maximum point of the box. The maximum point is the
   * corner of the box with the highest X, Y, and Z values.
   * [OIVJAVA-WRAPPER NO_WRAP]
   */
  inline const SbVec3f & getMax() const
    { return m_max; }

  /**
   * Returns the maximum point of the box. The maximum point is the
   * corner of the box with the highest X, Y, and Z values.
   */
  inline SbVec3f &getMax()
    { return m_max; }

  /**
   * Returns the center of the box.
   */
  SbVec3f getCenter() const;

  /**
   * Extends this box (if necessary) to contain the specified point.
   */
  inline void extendBy(const SbVec3f &pt)
  {
    if (pt[0] < m_min[0]) m_min[0] = pt[0];
    if (pt[1] < m_min[1]) m_min[1] = pt[1];
    if (pt[2] < m_min[2]) m_min[2] = pt[2];
    if (pt[0] > m_max[0]) m_max[0] = pt[0];
    if (pt[1] > m_max[1]) m_max[1] = pt[1];
    if (pt[2] > m_max[2]) m_max[2] = pt[2];
  }

  /**
   * Extends this box (if necessary) to contain the specified box.
   */
  void extendBy(const SbBox3f &bb);

  /**
   * Returns TRUE if the specified point intersects this box.
   */
  SbBool intersect(const SbVec3f &pt) const;

  /**
   * Returns TRUE if the specified box intersects this box.
   */
  inline SbBool intersect(const SbBox3f &bb) const
  {
    return ((bb.m_max[0] >= m_min[0]) && (bb.m_min[0] <= m_max[0]) &&
	    (bb.m_max[1] >= m_min[1]) && (bb.m_min[1] <= m_max[1]) &&
	    (bb.m_max[2] >= m_min[2]) && (bb.m_min[2] <= m_max[2]));
  }

  /**
   * Returns the intersection of the specified box with this box.
   * Returned box is empty if there is no intersection.
   */
  SbBox3f intersection(const SbBox3f& box) const;

  /**
   * Returns TRUE if the specified box is fully contained
   * inside this box.
   */
  inline SbBool contains(const SbBox3f &bb) const
  {
    SbBool contained = true;
    for( int i = 0; i < 3 && contained; i++ )
    {
      contained &= bb.m_min[i] >= m_min[i] &&
                   bb.m_min[i] <= m_max[i] &&
                   bb.m_max[i] <= m_max[i];
    }

    return contained;
  }


  /**
   * Returns TRUE if bounding box is completely outside the
   * view-volume defined by the model+view+projection matrix given.
   * "cullBits" keeps track of which view-volume clipping planes the
   * box is completely inside of; if a 'parent' bounding box of this
   * bounding box was found to be completely inside the left/right
   * clipping planes, the low bit of cullBits will be set to zero,
   * and this routine will not test this box against those planes.
   * When cullBits is zero, it is a waste of time to call this
   * function!  Before calling this the first time, set cullBits to
   * 7 (SoGLRenderAction and SoSeparator will handle this
   * automatically for render culling).
   */
  SbBool outside(const SbMatrix &MVP, int &cullBits) const;

  /**
   * Sets the corners of the box.
   */
  void setBounds(float xmin, float ymin, float zmin,
                 float xmax, float ymax, float zmax)
    { m_min.setValue(xmin, ymin, zmin); m_max.setValue(xmax, ymax, zmax); }

  /**
   * Sets the corners of the box.
   */
  void setBounds(const SbVec3f &_min, const SbVec3f &_max)
    { m_min = _min; m_max = _max; }

  /**
   * Gets the corners of the box.
   */
  void getBounds(float &xmin, float &ymin, float &zmin,
                 float &xmax, float &ymax, float &zmax) const
    { m_min.getValue(xmin, ymin, zmin); m_max.getValue(xmax, ymax, zmax); }

  /**
   * Gets the corners of the box.
   * [OIVJAVA-WRAPPER NAME{getMinMax}]
   */
  void getBounds(SbVec3f &_min, SbVec3f &_max) const
    { _min = m_min; _max = m_max; }

  /**
   * Returns the closest point on the box to the given point.
   * (Returns the point on the center of the Z face if passed the center.)
   */
  SbVec3f getClosestPoint(const SbVec3f &point) const;

  /**
   * Gets box origin which is the same as the minimum corner of the box.
   */
  void getOrigin(float &originX, float &originY, float &originZ) const
    { originX = m_min[0]; originY = m_min[1]; originZ = m_min[2]; }

  /**
   * Gets box size.
   * [OIVJAVA-WRAPPER NO_WRAP]
   */
  void getSize(float &sizeX, float &sizeY, float &sizeZ) const {
    if ( m_max[0] < m_min[0] ) {
      sizeX = 0.0f;
      sizeY = 0.0f;
      sizeZ = 0.0f;
    }
    else {
      sizeX = m_max[0] - m_min[0];
      sizeY = m_max[1] - m_min[1];
      sizeZ = m_max[2] - m_min[2];
    }
  }

  /**
   * Gets box size.
   */
  SbVec3f getSize() const
  {
    if ( m_max[0] < m_min[0] )
      return SbVec3f(0, 0, 0);

    return m_max-m_min;
  }

  /**
   * Makes an empty box.
   */
  inline void makeEmpty()
  {
    m_min.setValue(FLT_MAX, FLT_MAX, FLT_MAX);
    m_max.setValue(- FLT_MAX, - FLT_MAX, - FLT_MAX);
  }

  /**
   * Returns TRUE if the box is empty, and FALSE otherwise.
   */
  inline SbBool isEmpty() const
    { return m_max[0] < m_min[0]; }

  /**
   * Returns TRUE if all three dimensions of the box have positive size, and FALSE
   * otherwise.
   */
  SbBool hasVolume() const
    { return (m_max[0] > m_min[0] && m_max[1] > m_min[1] && m_max[2] > m_min[2] ); }

  /**
   * Finds the span of a box along a specified direction. The span is the total
   * distance the box occupies along a given direction. The total distance is
   * returned in the form of a minimum and maximum distance from the origin of each
   * of the corners of the box along the given direction. The difference between
   * these two values is the span.
   */
  void getSpan(const SbVec3f &direction, float &dMin, float &dMax) const;

  /**
   * Transforms box by matrix, enlarging box to contain result.
   */
  void transform(const SbMatrix &m);

  /**
   * Returns the volume of the box.
   */
  float getVolume() const;

  /**
   * Equality comparison.
   */
  INVENTORBASE_API friend int operator ==(const SbBox3f &b1, const SbBox3f &b2);

  /**
   * Inequality comparison.
   */
  INVENTORBASE_API friend int operator !=(const SbBox3f &b1, const SbBox3f &b2)
  { return !(b1 == b2); }

  /**
  * Writes the box to the specified output stream.
  */
  INVENTORBASE_API friend inline std::ostream& operator << (std::ostream& os, const SbBox3f& b);

  /**
   * Constructor that converts an arbitrary SbBox3 to an SbBox3f.
   */
  template<typename T>
  explicit SbBox3f(const T& b)
  {
    m_min = SbVec3f(b.getMin());
    m_max = SbVec3f(b.getMax());
  }

  /**
   * Returns the squared maximum distance between a point and the 8 bounding box's vertices
   */
  float computeMaxDistance2(const SbVec3f& p);

  /**
   * Return true if the given triangle intersects the bounding box
   */
  SbBool triangleBoxOverlap(const SbVec3f& u0, const SbVec3f& u1, const SbVec3f& u2) const;

 private:
  // Minimum and maximum points
  SbVec3f m_min, m_max;
};


// P.Vigneras Adding support for double precision bounding box 3
// Feb 15 2000

/**
 * @VSGEXT 3D box class.
 *
 * @ingroup Basics
 *
 * @DESCRIPTION
 *   3D box which has planes parallel to the major axes and is specified by two
 *   points on a diagonal. This class is part of the standard Open Inventor datatype
 *   classes and is used as input and output to geometry operations (see
 *   SoGetBoundingBoxAction).
 *
 * @SEE_ALSO
 *    SbXfBox3f,
 *    SbBox2f,
 *    SbBox2s,
 *    SbVec3d,
 *    SbVec2f,
 *    SbVec2s,
 *    SbMatrix,
 *    SoGetBoundingBoxAction
 *
 * [OIVJAVA-WRAPPER-CLASS BASIC_TYPE{true},LAYOUTED_ARRAY_TYPE{double,6}]
 */

class INVENTORBASE_API SbBox3d {

 public:
  /**
   * Constructor for a 3D double box.  The box is initially empty.
   */
  SbBox3d()
    { makeEmpty(); }

  /**
   * Constructor for a 3D double box. @B xmin @b, @B ymin @b,
   * @B zmin @b, @B xmax @b, @B ymax @b and @B zmax @b are the bounds of the box.
   */
  SbBox3d(double xmin, double ymin, double zmin,
          double xmax, double ymax, double zmax)
    { m_min.setValue(xmin, ymin, zmin); m_max.setValue(xmax, ymax, zmax); }

  /**
   * Constructor for a 3D double box.
   * @B m_min @b and @B m_max @b are the corners of the diagonal that define the box.
   */
  SbBox3d(const SbVec3d &_min, const SbVec3d &_max)
    { m_min = _min; m_max = _max; }

  /**
   * Destructor.
   */
  ~SbBox3d()
    {}

  /**
   * Returns the minimum point of the box. The minimum point is the
   * corner of the box with the lowest X, Y, and Z values.
   * [OIVJAVA-WRAPPER NO_WRAP]
   */
  const SbVec3d & getMin() const
    { return m_min; }

  /**
   * Returns the maximum point of the box. The maximum point is the
   * corner of the box with the highest X, Y, and Z values.
   * [OIVJAVA-WRAPPER NO_WRAP]
   */
  const SbVec3d & getMax() const
    { return m_max; }

  /**
   * Returns the minimum point of the box. The minimum point is the
   * corner of the box with the lowest X, Y, and Z values.
   */
  SbVec3d &getMin()
    { return m_min; }

  /**
   * Returns the maximum point of the box. The maximum point is the
   * corner of the box with the highest X, Y, and Z values.
   */
  SbVec3d &getMax()
    { return m_max; }

  /**
   * Returns the center of the box.
   */
  SbVec3d getCenter() const;

  /**
   * Extends this box (if necessary) to contain the specified point.
   */
  void extendBy(const SbVec3d &pt);

  /**
   * Extends this box (if necessary) to contain the specified box.
   */
  void extendBy(const SbBox3d &bb);

  /**
   * Returns TRUE if the specified point intersects this box.
   */
  SbBool intersect(const SbVec3d &pt) const;

  /**
   * Returns TRUE if the specified box intersects this box.
   */
  SbBool intersect(const SbBox3d &bb) const;

  /**
   * Returns TRUE if bounding box is completely outside the
   * view-volume defined by the model+view+projection matrix given.
   * "cullBits" keeps track of which view-volume clipping planes the
   * box is completely inside of; if a 'parent' bounding box of this
   * bounding box was found to be completely inside the left/right
   * clipping planes, the low bit of cullBits will be set to zero,
   * and this routine will not test this box against those planes.
   * When cullBits is zero, it is a waste of time to call this
   * function!  Before calling this the first time, set cullBits to
   * 7 (SoGLRenderAction and SoSeparator will handle this
   * automatically for render culling).
   */
  SbBool outside(const SbMatrixd &MVP, int &cullBits) const;

  /**
   * Sets the corners of the box.
   */
  void setBounds(double xmin, double ymin, double zmin,
                 double xmax, double ymax, double zmax)
    { m_min.setValue(xmin, ymin, zmin); m_max.setValue(xmax, ymax, zmax); }

  /**
   * Sets the corners of the box.
   */
  void setBounds(const SbVec3d &_min, const SbVec3d &_max)
    { m_min = _min; m_max = _max; }

  /**
   * Gets the corners of the box.
   */
  void getBounds(double &xmin, double &ymin, double &zmin,
                 double &xmax, double &ymax, double &zmax) const
    { m_min.getValue(xmin, ymin, zmin); m_max.getValue(xmax, ymax, zmax); }

  /**
   * Gets the corners of the box.
   * [OIVJAVA-WRAPPER NAME{getMinMax}]
   */
  void getBounds(SbVec3d &_min, SbVec3d &_max) const
    { _min = m_min; _max = m_max; }

  /**
   * Returns the closest point on the box to the given point.
   * (Returns the point on the center of the Z face if passed the center.)
   */
  SbVec3d getClosestPoint(const SbVec3d &point) const;

  /**
   * Gets box origin which is the same as the minimum corner of the box.
   */
  void getOrigin(double &originX, double &originY, double &originZ) const
    { originX = m_min[0]; originY = m_min[1]; originZ = m_min[2]; }

  /**
   * Gets box size.
   */
  void getSize(double &sizeX, double &sizeY, double &sizeZ) const {
    if ( m_max[0] < m_min[0] ) {
      sizeX = 0.0;
      sizeY = 0.0;
      sizeZ = 0.0;
    }
    else {
      sizeX = m_max[0] - m_min[0];
      sizeY = m_max[1] - m_min[1];
      sizeZ = m_max[2] - m_min[2];
    }
  }

  /**
   * Makes an empty box.
   */
  void makeEmpty();

  /**
   * Returns TRUE if the box is empty, and FALSE otherwise.
   */
  SbBool isEmpty() const
    { return m_max[0] < m_min[0]; }

  /**
   * Returns TRUE if all three dimensions of the box have positive size, and FALSE
   * otherwise.
   */
  SbBool hasVolume() const
    { return (m_max[0] > m_min[0] && m_max[1] > m_min[1] && m_max[2] > m_min[2] ); }

  /**
   * Finds the span of a box along a specified direction. The span is the total
   * distance the box occupies along a given direction. The total distance is
   * returned in the form of a minimum and maximum distance from the origin of each
   * of the corners of the box along the given direction. The difference between
   * these two values is the span.
   */
  void getSpan(const SbVec3d &direction, double &dMin, double &dMax) const;

  /**
   * Transforms box by matrix, enlarging box to contain result.
   */
  void transform(const SbMatrixd &m);

  /**
   * Returns the volume of the box.
   */
  double getVolume() const;

  /**
   * Equality comparison.
   */
  INVENTORBASE_API friend int operator ==(const SbBox3d &b1, const SbBox3d &b2);

  /**
   * Inequality comparison.
   */
  INVENTORBASE_API friend int operator !=(const SbBox3d &b1, const SbBox3d &b2)
  { return !(b1 == b2); }

  /**
   * Constructor that converts an arbitrary SbBox3 to an SbBox3f.
   */
  template<typename T>
  explicit SbBox3d(const T& b)
  {
    m_min = SbVec3d(b.getMin());
    m_max = SbVec3d(b.getMax());
  }

 private:
  // Minimum and maximum points
  SbVec3d m_min, m_max;
};

/**
 * 3D box with an associated transformation matrix.
 *
 * @ingroup Basics
 *
 * @DESCRIPTION
 *   A 3D box with an arbitrary transformation applied. This class is useful when a
 *   box will be transformed frequently; if an SbBox3f is used for this purpose it
 *   will expand each time it is transformed in order to keep itself axis-aligned.
 *   Transformations can be accumulated on an SbXfBox3f without expanding the box,
 *   and after all transformations have been done, the box can be expanded to an
 *   axis-aligned box if necessary.
 *
 * @SEE_ALSO
 *    SbBox3f,
 *    SbBox2f,
 *    SbBox2s,
 *    SbVec3f,
 *    SbVec2f,
 *    SbVec2s,
 *    SbMatrix,
 *    SoGetBoundingBoxAction
 *
 * [OIVJAVA-WRAPPER-CLASS BASIC_TYPE{true},LAYOUTED_ARRAY_TYPE{float,38}]
 */

class INVENTORBASE_API SbXfBox3f : public SbBox3f {

 public:
  /**
   * Constructor.  The box is initially empty.
   */
  SbXfBox3f();

  /**
   * Constructor.
   */
  SbXfBox3f(const SbVec3f &_min, const SbVec3f &_max);

  /**
   * Constructor.
   */
  SbXfBox3f(const SbBox3f &box);

  /**
   * Destructor.
   */
  ~SbXfBox3f()
    {}

  /**
   * Sets the transformation on the box.
   */
  void setTransform(const SbMatrix &m);

  /**
   * Gets the transformation on the box.
   */
  const SbMatrix & getTransform() const
    { return xform; }

  /**
   * Gets the inverse of the transformation on the box.
   */
  const SbMatrix & getInverse() const
    { return xformInv; }

  /**
   * Returns the center of the box.
   */
  SbVec3f getCenter() const;

#ifdef OIV_NET_DOC
  /**
  * Extends the box (if necessary) to contain the given 3D point. If the box has had
  * a non-identity transformation applied using the setTransform() method,
  * the point is assumed to be in the transformed space.
  */

#else
  /**
  * Extends the box (if necessary) to contain the given 3D point. If the box has had
  * a non-identity transformation applied using the setTransform() method,
  * the point is assumed to be in the transformed space. For example, the following
  * code sequence:
  *
  * <PRE>
  *  SbXfBox3f bbox;
  *  bbox.extendBy(SbVec3f(0,0,0));
  *  SbMatrix trans;
  *  trans.setTranslate(SbVec3f(1,1,1));
  *  bbox.setTransform(trans);
  *  bbox.extendBy(SbVec3f(0,0,0));
  *  </PRE>
  *  will result in a bounding box extending from (-1,-1,-1) to (0,0,0) in
  *  bbox'es local (untransformed) space.
  */

#endif //OIV_NET_DOC
  void extendBy(const SbVec3f &pt);

  /**
   * Extends the box (if necessary) to contain the given box. If the box has had
   * a non-identity transformation applied using the setTransform() method, the given
   * SbBox3f is assumed to be in the transformed space.
   */
  void extendBy(const SbBox3f &bb)
    { extendBy(SbXfBox3f(bb)); }

  /**
   * Extends the box (if necessary) to contain the given box.
   */
  void extendBy(const SbXfBox3f &bb);

  /**
   * Returns TRUE if intersection of given point and this box is not empty.
   */
  SbBool intersect(const SbVec3f &pt) const;

  /**
   * Returns TRUE if intersection of given box and this box is not empty.
   */
  SbBool intersect(const SbBox3f &bb) const
    { return project().intersect(bb); }

  /**
  * Sets value of the box from a double precision box.
  */
  SbXfBox3f &setValue(const SbXfBox3d &xfbox3d);

  /**
   * Sets the bounds of the box.
   */
  void setBounds(float xmin, float ymin, float zmin,
                 float xmax, float ymax, float zmax)
    { SbBox3f::setBounds(xmin, ymin, zmin, xmax, ymax, zmax); }

  /**
   * Sets the bounds of the box.
   */
  void setBounds(const SbVec3f &_min, const SbVec3f &_max)
    { SbBox3f::setBounds(_min, _max); }

  /**
   * Gets the bounds of the box.
   */
  void getBounds(float &xmin, float &ymin, float &zmin,
                 float &xmax, float &ymax, float &zmax) const
    { SbBox3f::getBounds(xmin, ymin, zmin, xmax, ymax, zmax); }

  /**
   * Gets the bounds of the box.
   * [OIVJAVA-WRAPPER NAME{getMinMax}]
   */
  void getBounds(SbVec3f &_min, SbVec3f &_max) const
    { SbBox3f::getBounds(_min, _max); }

  /**
   * Returns origin (minimum point) of the box.
   */
  void getOrigin(float &originX, float &originY, float &originZ)
    { SbBox3f::getOrigin(originX, originY, originZ); }

  /**
   * Returns size of the box.
   * [OIVJAVA-WRAPPER NO_WRAP]
   */
  void getSize(float &sizeX, float &sizeY, float &sizeZ)
    { SbBox3f::getSize(sizeX, sizeY, sizeZ); }

  /**
   * Gives the volume of the box (0 for an empty box).
   */
  float getVolume() const;

  /**
   * Sets the box to contain nothing.
   */
  void makeEmpty() { SbBox3f::makeEmpty(); }

  /**
   * Checks if the box is empty (degenerate).
   */
  SbBool isEmpty() const { return SbBox3f::isEmpty(); }

  /**
   * Checks if the box has volume; i.e., all three dimensions have positive size.
   */
  SbBool hasVolume() const { return SbBox3f::hasVolume(); }

  /**
   * Finds the extent of the box along a particular direction.
   */
  void getSpan(const SbVec3f &direction, float &dMin, float &dMax) const
    { project().getSpan(direction, dMin, dMax); }

  /**
   * Transforms the box by the given matrix.
   */
  void transform(const SbMatrix &m);

  /**
   * Projects an SbXfBox3f to an SbBox3f
   */
  SbBox3f project() const;

  /**
   * Equality comparison.
   */
  INVENTORBASE_API friend int operator ==(const SbXfBox3f &b1, const SbXfBox3f &b2);

  /**
   * Inequality comparison.
   */
  INVENTORBASE_API friend int operator !=(const SbXfBox3f &b1, const SbXfBox3f &b2)
  { return !(b1 == b2); }

 private:
  // These are incorrect for SbXfBox3f, so we hide them
  const SbVec3f &getMin() const
    { return SbBox3f::getMin(); }

  const SbVec3f &getMax() const
    { return SbBox3f::getMax(); }

  // The box is transformed by this xform
  SbMatrix xform;
  SbMatrix xformInv;
};

/**
 * @VSGEXT 3D box with an associated transformation matrix.
 *
 * @ingroup Basics
 *
 * @DESCRIPTION
 *   A 3D box with an arbitrary transformation applied. This class is useful when a
 *   box will be transformed frequently; if an SbBox3f is used for this purpose it
 *   will expand each time it is transformed in order to keep itself axis-aligned.
 *   Transformations can be accumulated on an SbXfBox3d without expanding the box,
 *   and after all transformations have been done, the box can be expanded to an
 *   axis-aligned box if necessary.
 *
 * @SEE_ALSO
 *    SbBox3f,
 *    SbBox2f,
 *    SbBox2s,
 *    SbVec3d,
 *    SbVec2f,
 *    SbVec2s,
 *    SbMatrix,
 *    SoGetBoundingBoxAction
 *
 * [OIVJAVA-WRAPPER-CLASS BASIC_TYPE{true},LAYOUTED_ARRAY_TYPE{double,38}]
 */

class INVENTORBASE_API SbXfBox3d : public SbBox3d {

 public:
  /**
   * Constructor.  The box is initially empty.
   */
  SbXfBox3d();

  /**
   * Constructor.
   */
  SbXfBox3d(const SbVec3d &_min, const SbVec3d &_max);

  /**
   * Constructor.
   */
  SbXfBox3d(const SbBox3d &box);

  /**
   * Destructor.
   */
  ~SbXfBox3d()
    {}

  /**
   * Sets the transformation on the box.
   */
  void setTransform(const SbMatrixd &m);

  /**
   * Gets the transformation on the box.
   */
  const SbMatrixd & getTransform() const
    { return xform; }

  /**
   * Gets the inverse of the transformation on the box.
   */
  const SbMatrixd & getInverse() const
    { return xformInv; }

  /**
   * Returns the center of the box.
   */
  SbVec3d getCenter() const;

#ifdef OIV_NET_DOC
  /**
  * Extends the box (if necessary) to contain the given 3D point. If the box has had
  * a non-identity transformation applied using the @B setTransform() @b method,
  * the point is assumed to be in the transformed space.
  */

#else
  /**
  * Extends the box (if necessary) to contain the given 3D point. If the box has had
  * a non-identity transformation applied using the @B setTransform() @b method,
  * the point is assumed to be in the transformed space. For example, the following
  * code sequence:
  *
  * <PRE>
  *  SbXfBox3d bbox;
  *  bbox.extendBy(SbVec3d(0,0,0));
  *  SbMatrix trans;
  *  trans.setTranslate(SbVec3d(1,1,1));
  *  bbox.setTransform(trans);
  *  bbox.extendBy(SbVec3d(0,0,0));
  *  </PRE>
  *  will result in a bounding box extending from (-1,-1,-1) to (0,0,0) in
  * bbox'es local (untransformed) space.
  */

#endif //OIV_NET_DOC
  void extendBy(const SbVec3d &pt);

  /**
   * Extends the box (if necessary) to contain the given box.
   */
  void extendBy(const SbBox3d &bb)
    { extendBy(SbXfBox3d(bb)); }

  /**
   * Extends the box (if necessary) to contain the given box.
   */
  void extendBy(const SbXfBox3d &bb);

  /**
   * Returns TRUE if intersection of given point and this box is not empty.
   */
  SbBool intersect(const SbVec3d &pt) const;

  /**
   * Returns TRUE if intersection of this XfBox3d and the given Box3d is not empty
   */
  SbBool intersect(const SbBox3d &bb) const
    { return project().intersect(bb); }

  /**
   * Sets the bounds of the box.
   */
  void setBounds(double xmin, double ymin, double zmin,
                 double xmax, double ymax, double zmax)
    { SbBox3d::setBounds(xmin, ymin, zmin, xmax, ymax, zmax); }

  /**
   * Sets the bounds of the box.
   */
  void setBounds(const SbVec3d &_min, const SbVec3d &_max)
    { SbBox3d::setBounds(_min, _max); }

  /**
   * Gets the bounds of the box.
   */
  void getBounds(double &xmin, double &ymin, double &zmin,
                 double &xmax, double &ymax, double &zmax) const
    { SbBox3d::getBounds(xmin, ymin, zmin, xmax, ymax, zmax); }

  /**
   * Gets the bounds of the box.
   * [OIVJAVA-WRAPPER NAME{getMinMax}]
   */
  void getBounds(SbVec3d &_min, SbVec3d &_max) const
    { SbBox3d::getBounds(_min, _max); }

  /**
   * Returns origin (minimum point) of the box.
   */
  void getOrigin(double &originX, double &originY, double &originZ) const
    { SbBox3d::getOrigin(originX, originY, originZ); }

  /**
   * Returns size of the box.
   */
  void getSize(double &sizeX, double &sizeY, double &sizeZ) const
    { SbBox3d::getSize(sizeX, sizeY, sizeZ); }

  /**
   * Gives the volume of the box (0 for an empty box).
   */
  double getVolume() const;

  /**
   * Sets the box to contain nothing.
   */
  void makeEmpty() { SbBox3d::makeEmpty(); }

  /**
   * Checks if the box is empty (degenerate).
   */
  SbBool isEmpty() const { return SbBox3d::isEmpty(); }

  /**
   * Checks if the box has volume; i.e., all three dimensions have positive size.
   */
  SbBool hasVolume() const { return SbBox3d::hasVolume(); }

  /**
   * Finds the extent of the box along a particular direction.
   */
  void getSpan(const SbVec3d &direction, double &dMin, double &dMax) const
    { project().getSpan(direction, dMin, dMax); }

  /**
   * Transforms the box by the given matrix.
   */
  void transform(const SbMatrixd &m);

  /**
   * Projects an SbXfBox3d to an SbBox3d
   */
  SbBox3d project() const;

  /**
   * Equality comparison.
   */
  INVENTORBASE_API friend int operator ==(const SbXfBox3d &b1, const SbXfBox3d &b2);

  /**
   * Inequality comparison.
   */
  INVENTORBASE_API friend int operator !=(const SbXfBox3d &b1, const SbXfBox3d &b2)
  { return !(b1 == b2); }

 private:
  // These are incorrect for SbXfBox3d, so we hide them
  const SbVec3d & getMin() const
    { return SbBox3d::getMin(); }

  const SbVec3d & getMax() const
    { return SbBox3d::getMax(); }

  // The box is transformed by this xform
  SbMatrixd xform;
  SbMatrixd xformInv;
};

// Note: This implementation must appear after the declaration of SbXfBox3d!
inline SbXfBox3f &SbXfBox3f::setValue(const SbXfBox3d& xfbox3d)
{
  // set float transform
  SbMatrixd dtrans = xfbox3d.getTransform();
  SbMatrix ftrans (
    static_cast<float>(dtrans[0][0]), static_cast<float>(dtrans[0][1]), static_cast<float>(dtrans[0][2]), static_cast<float>(dtrans[0][3]),
    static_cast<float>(dtrans[1][0]), static_cast<float>(dtrans[1][1]), static_cast<float>(dtrans[1][2]), static_cast<float>(dtrans[1][3]),
    static_cast<float>(dtrans[2][0]), static_cast<float>(dtrans[2][1]), static_cast<float>(dtrans[2][2]), static_cast<float>(dtrans[2][3]),
    static_cast<float>(dtrans[3][0]), static_cast<float>(dtrans[3][1]), static_cast<float>(dtrans[3][2]), static_cast<float>(dtrans[3][3])
  );
  setTransform(ftrans);

  // set float bounds
  SbVec3d dmin,dmax;
  xfbox3d.getBounds(dmin,dmax);
  const SbVec3f _min(static_cast<float>(dmin[0]),static_cast<float>(dmin[1]),static_cast<float>(dmin[2]));
  const SbVec3f _max(static_cast<float>(dmax[0]),static_cast<float>(dmax[1]),static_cast<float>(dmax[2]));
  setBounds((_min),(_max));

	return (*this);
}

/**
 * 2D box class.
 *
 * @ingroup Basics
 *
 * @DESCRIPTION
 *   2D box which has planes parallel to the major axes and is specified by two
 *   points (specified as floating point) on a diagonal. This class is part of the
 *   standard Open Inventor datatype classes and is used as input and output to
 *   geometry operations.
 *
 * @SEE_ALSO
 *    SbBox3f,
 *    SbXfBox3f,
 *    SbBox2s,
 *    SbVec3f,
 *    SbVec2f,
 *    SbVec2s,
 *    SbMatrix
 *
 * [OIVJAVA-WRAPPER-CLASS BASIC_TYPE{true},LAYOUTED_ARRAY_TYPE{float,4}]
 */

class INVENTORBASE_API SbBox2f {

 public:
  /**
   * Constructor for a 2D float box.  The box is initially empty.
   */
  SbBox2f()
    { makeEmpty(); };

  /**
   * Constructor for a 2D float box. @B xmin @b, @B ymin @b,
   * @B xmax @b, and @B ymax @b are the bounds of the box.
   */
  SbBox2f(float xmin, float ymin, float xmax, float ymax)
    { m_min.setValue(xmin, ymin); m_max.setValue(xmax, ymax); }

  /**
   * Constructor for a 2D float box. @B m_min @b and @B m_max @b are the
   * corners of the diagonal that defines the box.
   */
  SbBox2f(const SbVec2f &_min, const SbVec2f &_max)
    { m_min = _min; m_max = _max; }

  /**
   * Destructor.
   */
  ~SbBox2f()
    {}

  /**
   * Returns the minimum point of the box.
   */
  const SbVec2f & getMin() const
    { return m_min; }

  /**
   * Returns the maximum point of the box.
   */
  const SbVec2f & getMax() const
    { return m_max; }

  /**
   * Returns the center of the box.
   */
  SbVec2f getCenter() const;

  /**
   * Extends this box (if necessary) to contain the specified point.
   */
  void extendBy(const SbVec2f &pt);

  /**
   * Extends this box (if necessary) to contain the specified box.
   */
  void extendBy(const SbBox2f &r);

  /**
   * Returns TRUE if the specified point intersects this box.
   */
  SbBool intersect(const SbVec2f &pt) const;

  /**
   * Returns TRUE if the specified box intersects this box.
   */
  SbBool intersect(const SbBox2f &bb) const;

  /**
   * Sets the corners of the box.
   */
  void setBounds(float xmin, float ymin, float xmax, float ymax)
    { m_min.setValue(xmin, ymin); m_max.setValue(xmax, ymax); }

  /**
   * Sets the corners of the box.
   */
  void setBounds(const SbVec2f &_min, const SbVec2f &_max)
    { m_min = _min; m_max = _max; }

  /**
   * Gets the corners of the box.
   */
  void getBounds(float &xmin, float &ymin,
                 float &xmax, float &ymax) const
    { m_min.getValue(xmin, ymin); m_max.getValue(xmax, ymax); }

  /**
   * Gets the corners of the box.
   * [OIVJAVA-WRAPPER NAME{getMinMax}]
   */
  void getBounds(SbVec2f &_min, SbVec2f &_max) const
    { _min = m_min; _max = m_max; }

  /**
   * Returns the closest point on the box to the given point.
   * (Returns the point on the center of the Z face if passed the center.)
   */
  SbVec2f getClosestPoint(const SbVec2f &point) const;

  /**
   * Gets box origin.
   */
  void getOrigin(float &originX, float &originY) const
    { originX = m_min[0]; originY = m_min[1]; }

  /**
   * Gets box size.
   */
  void getSize(float &sizeX, float &sizeY) const
    {
    if ( m_max[0] < m_min[0] ) {
      sizeX = 0.0f;
      sizeY = 0.0f;
    }
    else {
      sizeX = m_max[0] - m_min[0];
      sizeY = m_max[1] - m_min[1];
    }
  }

  /**
   * Gets box aspect ratio.
   */
  float getAspectRatio() const
    { return (m_max[0] - m_min[0]) / (m_max[1] - m_min[1]); }

  /**
   * Makes an empty box.
   */
  void makeEmpty();

  /**
   * Returns TRUE if the box is empty, and FALSE otherwise.
   */
  SbBool isEmpty() const { return m_max[0] < m_min[0]; }

  /**
   * Returns TRUE if both dimensions of the box have positive size, and FALSE
   * otherwise.
   */
  SbBool hasArea() const
    { return (m_max[0] > m_min[0] && m_max[1] > m_min[1]); }

  /**
   * Equality comparison.
   */
  INVENTORBASE_API friend int operator ==(const SbBox2f &b1, const SbBox2f &b2);

  /**
   * Inequality comparison.
   */
  INVENTORBASE_API friend int operator !=(const SbBox2f &b1, const SbBox2f &b2)
  { return !(b1 == b2); }

 private:
  // Minimum and maximum points
  SbVec2f m_min, m_max;
};

/**
 * @VSGEXT 2D box class.
 *
 * @ingroup Basics
 *
 * @DESCRIPTION
 *   2D box which has planes parallel to the major axes and is specified by two
 *   points (specified in double precision) on a diagonal. This class is part of the
 *   standard Open Inventor datatype classes and is used as input and output to
 *   geometry operations.
 *
 * @SEE_ALSO
 *    SbBox3f,
 *    SbXfBox3f,
 *    SbBox2s,
 *    SbVec3f,
 *    SbVec2d,
 *    SbVec2s,
 *    SbMatrix
 *
 * [OIVJAVA-WRAPPER-CLASS BASIC_TYPE{true},LAYOUTED_ARRAY_TYPE{double,4}]
 */

class INVENTORBASE_API SbBox2d {

 public:
  /**
   * Constructor for a 2D double box.  The box is initially empty.
   */
  SbBox2d()
    { makeEmpty(); };

  /**
   * Constructor for a 2D double box. @B xmin @b, @B ymin @b,
   * @B xmax @b, and @B ymax @b are the bounds of the box.
   */
  SbBox2d(double xmin, double ymin, double xmax, double ymax)
    { m_min.setValue(xmin, ymin); m_max.setValue(xmax, ymax); }

  /**
   * Constructor for a 2D double box. @B m_min @b and @B m_max @b are the
   * corners of the diagonal that define the box.
   */
  SbBox2d(const SbVec2d &_min, const SbVec2d &_max)
    { m_min = _min; m_max = _max; }

  /**
   * Destructor.
   */
  ~SbBox2d()
    {}

  /**
   * Returns the minimum point of the box.
   */
  const SbVec2d & getMin() const
    { return m_min; }

  /**
   * Returns the maximum point of the box.
   */
  const SbVec2d & getMax() const
    { return m_max; }

  /**
   * Returns the center of the box.
   */
  SbVec2d getCenter() const;

  /**
   * Extends this box (if necessary) to contain the specified point .
   */
  void extendBy(const SbVec2d &pt);

  /**
   * Extends this box (if necessary) to contain the specified box.
   */
  void extendBy(const SbBox2d &r);

  /**
   * Returns TRUE if the specified point intersects this box.
   */
  SbBool intersect(const SbVec2d &pt) const;

  /**
   * Returns TRUE if the specified box intersects this box.
   */
  SbBool intersect(const SbBox2d &bb) const;

  /**
   * Sets the corners of the box.
   */
  void setBounds(double xmin, double ymin, double xmax, double ymax)
    { m_min.setValue(xmin, ymin); m_max.setValue(xmax, ymax); }

  /**
   * Sets the corners of the box.
   */
  void setBounds(const SbVec2d &_min, const SbVec2d &_max)
    { m_min = _min; m_max = _max; }

  /**
   * Gets the corners of the box.
   */
  void getBounds(double &xmin, double &ymin,
                 double &xmax, double &ymax) const
    { m_min.getValue(xmin, ymin); m_max.getValue(xmax, ymax); }

  /**
   * Gets the corners of the box.
   * [OIVJAVA-WRAPPER NAME{getMinMax}]
   */
  void getBounds(SbVec2d &_min, SbVec2d &_max) const
    { _min = m_min; _max = m_max; }

  /**
   * Returns the closest point on the box to the given point.
   * (Returns the point on the center of the Z face if passed the center.)
   */
  SbVec2d getClosestPoint(const SbVec2d &point) const;

  /**
   * Gets box origin.
   */
  void getOrigin(double &originX, double &originY) const
    { originX = m_min[0]; originY = m_min[1]; }

  /**
   * Gets box size.
   */
  void getSize(double &sizeX, double &sizeY) const
    {
    if ( m_max[0] < m_min[0] ) {
      sizeX = 0.0;
      sizeY = 0.0;
    }
    else {
      sizeX = m_max[0] - m_min[0];
      sizeY = m_max[1] - m_min[1];
    }  }

  /**
   * Gets box aspect ratio.
   */
  double getAspectRatio() const
    { return (m_max[0] - m_min[0]) / (m_max[1] - m_min[1]); }

  /**
   * Makes an empty box.
   */
  void makeEmpty();

  /**
   * Returns TRUE if the box is empty, and FALSE otherwise.
   */
  SbBool isEmpty() const { return m_max[0] < m_min[0]; }

  /**
   * Returns TRUE if both dimensions of the box have positive size, and FALSE
   * otherwise.
   */
  SbBool hasArea() const
    { return (m_max[0] > m_min[0] && m_max[1] > m_min[1]); }

  /**
   * Equality comparison.
   */
  INVENTORBASE_API friend int operator ==(const SbBox2d &b1, const SbBox2d &b2);

  /**
   * Inequality comparison.
   */
  INVENTORBASE_API friend int operator !=(const SbBox2d &b1, const SbBox2d &b2)
  { return !(b1 == b2); }

 private:
  // Minimum and maximum points
  SbVec2d m_min, m_max;
};

/**
 * 2D box class.
 *
 * @ingroup Basics
 *
 * @DESCRIPTION
 *   2D box which has planes parallel to the major axes and is specified by two
 *   points (specified with short integers) on a diagonal. This class is part of the
 *   standard Open Inventor datatype classes and is used as input and output to
 *   geometry operations.
 *
 * @SEE_ALSO
 *    SbBox3f,
 *    SbXfBox3f,
 *    SbBox2f,
 *    SbVec3f,
 *    SbVec2f,
 *    SbVec2s,
 *    SbMatrix
 *
 * [OIVJAVA-WRAPPER-CLASS BASIC_TYPE{true},LAYOUTED_ARRAY_TYPE{short,4}]
 */

class INVENTORBASE_API SbBox2s {

 public:
  /**
   * Constructor for a 2D integer box.  The box is initially empty.
   */
  SbBox2s()
    { makeEmpty(); };

  /**
   * Constructor for a 2D integer box. @B xmin @b, @B ymin @b,
   * @B xmax @b, and @B ymax @b are the bounds of the box.
   */
  SbBox2s(short xmin, short ymin, short xmax, short ymax)
    { m_min.setValue(xmin, ymin); m_max.setValue(xmax, ymax); }

  /**
   * Constructor for a 2D integer box. @B m_min @b and
   * @B m_max @b are the corners of the diagonal that defines the box.
   */
  SbBox2s(const SbVec2s &_min, const SbVec2s &_max)
    { m_min = _min; m_max = _max; }

  /**
   * Destructor.
   */
  ~SbBox2s()
    {}

  /**
   * Returns the minimum point of the box.
   */
  const SbVec2s & getMin() const
    { return m_min; }

  /**
   * Returns the maximum point of the box.
   */
  const SbVec2s & getMax() const
    { return m_max; }

  /**
   * Extends this box (if necessary) to contain the specified point.
   */
  void extendBy(const SbVec2s &pt);

  /**
   * Extends this box (if necessary) to contain the specified box.
   */
  void extendBy(const SbBox2s &r);

  /**
   * Returns TRUE if the specified point intersects this box.
   */
  SbBool intersect(const SbVec2s &pt) const;

  /**
   * Returns TRUE if the specified box intersects this box.
   */
  SbBool intersect(const SbBox2s &bb) const;

  /**
   * Sets the corners of the box.
   */
  void setBounds(short xmin, short ymin, short xmax, short ymax)
    { m_min.setValue(xmin, ymin); m_max.setValue(xmax, ymax); }

  /**
   * Sets the corners of the box.
   */
  void setBounds(const SbVec2s &_min, const SbVec2s &_max)
    { m_min = _min; m_max = _max; }

  /**
   * Gets the corners of the box.
   */
  void getBounds(short &xmin, short &ymin,
                 short &xmax, short &ymax) const
    { m_min.getValue(xmin, ymin); m_max.getValue(xmax, ymax); }

  /**
   * Gets the corners of the box.
   * [OIVJAVA-WRAPPER NAME{getMinMax}]
   */
  void getBounds(SbVec2s &_min, SbVec2s &_max) const
    { _min = m_min; _max = m_max; }

  /**
   * Returns origin (minimum point) of box.
   */
  void getOrigin(short &originX, short &originY) const
    { originX = m_min[0]; originY = m_min[1]; }

  /**
   * Returns box size.
   */
  void getSize(short &sizeX, short &sizeY) const
    {
    if ( m_max[0] < m_min[0] ) {
      sizeX = 0;
      sizeY = 0;
    }
    else {
      sizeX = m_max[0] - m_min[0];
      sizeY = m_max[1] - m_min[1];
    }
  }

  /**
   * Returns aspect ratio (ratio of width to height) of box.
   */
  float getAspectRatio() const
    { return float(m_max[0] - m_min[0]) / float(m_max[1] - m_min[1]); }

  /**
   * Makes an empty box.
   */
  void makeEmpty();

  /**
   * Returns TRUE if the box is empty, and FALSE otherwise.
   */
  SbBool isEmpty() const { return m_max[0] < m_min[0]; }

  /**
   * Returns TRUE if both dimensions of the box have positive size, and FALSE
   * otherwise.
   */
  SbBool hasArea() const
    { return (m_max[0] > m_min[0] && m_max[1] > m_min[1]); }


  /**
   * Equality comparison.
   */
  INVENTORBASE_API friend int operator ==(const SbBox2s &b1, const SbBox2s &b2);

  /**
   * Inequality comparison.
   */
  INVENTORBASE_API friend int operator !=(const SbBox2s &b1, const SbBox2s &b2)
  { return !(b1 == b2); }

 private:
  // Minimum and maximum points
  SbVec2s m_min, m_max;
};

/**
 * 2D box class.
 *
 * @ingroup Basics
 *
 * @DESCRIPTION
 *   2D box which has planes parallel to the major axes and is specified by two
 *   points (specified with 32 bits integers) on a diagonal. This class is part of the
 *   standard Open Inventor datatype classes and is used as input and output to
 *   geometry operations.
 *
 * @SEE_ALSO
 *    SbBox3f,
 *    SbXfBox3f,
 *    SbBox2f,
 *    SbBox2s,
 *    SbVec3f,
 *    SbVec2f,
 *    SbVec2i32,
 *    SbMatrix
 *
 * [OIVJAVA-WRAPPER-CLASS BASIC_TYPE{true},LAYOUTED_ARRAY_TYPE{int,4}]
 */

class INVENTORBASE_API SbBox2i32 {

 public:
  /**
   * Constructor for a 2D integer box.  The box is initially empty.
   */
  SbBox2i32()
    { makeEmpty(); };

  /**
   * Constructor for a 2D integer box. @B xmin @b, @B ymin @b,
   * @B xmax @b, and @B ymax @b are the bounds of the box.
   */
  SbBox2i32(int xmin, int ymin, int xmax, int ymax)
    { m_min.setValue(xmin, ymin); m_max.setValue(xmax, ymax); }

  /**
   * Constructor for a 2D integer box. @B m_min @b and
   * @B m_max @b are the corners of the diagonal that defines the box.
   */
  SbBox2i32(const SbVec2i32 &_min, const SbVec2i32 &_max)
    { m_min = _min; m_max = _max; }

  /**
   * Destructor.
   */
  ~SbBox2i32()
    {}

  /**
   * Returns the minimum point of the box.
   */
  const SbVec2i32 & getMin() const
    { return m_min; }

  /**
   * Returns the maximum point of the box.
   */
  const SbVec2i32 & getMax() const
    { return m_max; }

  /**
   * Extends this box (if necessary) to contain the specified point.
   */
  void extendBy(const SbVec2i32 &pt);

  /**
   * Extends this box (if necessary) to contain the specified box.
   */
  void extendBy(const SbBox2i32 &r);

  /**
   * Returns TRUE if the specified point intersects this box.
   */
  SbBool intersect(const SbVec2i32 &pt) const;

  /**
   * Returns TRUE if the specified box intersects this box.
   */
  SbBool intersect(const SbBox2i32 &bb) const;

  /**
   * Sets the corners of the box.
   */
  void setBounds(int xmin, int ymin, int xmax, int ymax)
    { m_min.setValue(xmin, ymin); m_max.setValue(xmax, ymax); }

  /**
   * Sets the corners of the box.
   */
  void setBounds(const SbVec2i32 &_min, const SbVec2i32 &_max)
    { m_min = _min; m_max = _max; }

  /**
   * Gets the corners of the box.
   */
  void getBounds(int &xmin, int &ymin,
                 int &xmax, int &ymax) const
    { m_min.getValue(xmin, ymin); m_max.getValue(xmax, ymax); }

  /**
   * Gets the corners of the box.
   * [OIVJAVA-WRAPPER NAME{getMinMax}]
   */
  void getBounds(SbVec2i32 &_min, SbVec2i32 &_max) const
    { _min = m_min; _max = m_max; }

  /**
   * Returns origin (minimum point) of box.
   */
  void getOrigin(int &originX, int &originY) const
    { originX = m_min[0]; originY = m_min[1]; }

  /**
   * Returns box size.
   */
  void getSize(int &sizeX, int &sizeY) const
    {
    if ( m_max[0] < m_min[0] ) {
      sizeX = 0;
      sizeY = 0;
    }
    else {
      sizeX = m_max[0] - m_min[0];
      sizeY = m_max[1] - m_min[1];
    }
  }

  /**
   * Returns aspect ratio (ratio of width to height) of box.
   */
  float getAspectRatio() const
    { return float(m_max[0] - m_min[0]) / float(m_max[1] - m_min[1]); }

  /**
   * Makes an empty box.
   */
  void makeEmpty();

  /**
   * Equality comparison.
   */
  INVENTORBASE_API friend int operator ==(const SbBox2i32 &b1, const SbBox2i32 &b2);

  /**
   * Inequality comparison.
   */
  INVENTORBASE_API friend int operator !=(const SbBox2i32 &b1, const SbBox2i32 &b2)
  { return !(b1 == b2); }

 private:
  // Minimum and maximum points
  SbVec2i32 m_min, m_max;
};

/**
 * Writes the box to the specified output stream.
 */
inline std::ostream& operator << (std::ostream& os, const SbBox3f& b)
{
  return os << b.getMin() << " - " << b.getMax();
}

/**
 * Writes the box to the specified output stream.
 */
inline std::ostream& operator << (std::ostream& os, const SbBox3i32& b)
{
  return os << b.getMin() << " - " << b.getMax();
}

/**
 * Writes the box to the specified output stream.
 */
inline std::ostream& operator << (std::ostream& os, const SbBox2f& b)
{
  return os << b.getMin() << " - " << b.getMax();
}

#endif /* _SB_BOX_ */
