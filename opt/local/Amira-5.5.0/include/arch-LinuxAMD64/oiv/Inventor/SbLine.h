/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _SB_LINE_
#define _SB_LINE_

#include <Inventor/SbBase.h>
#include <Inventor/SbVec.h>
#include <Inventor/SbBox.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbLine
//
//  Represents a directed line in 3D space.
//
//////////////////////////////////////////////////////////////////////////////

class SbLined;

/**
* Directed line in 3D.
*
* @ingroup Basics
*
* @DESCRIPTION
*   Represents a directed line in 3D. This is a basic Open Inventor datatype that is
*   used for representing a 3D line. It is used as input and output by a variety of
*   Open Inventor classes.
*
* @SEE_ALSO
*    SbVec3f,
*    SbPlane
*
* [OIVJAVA-WRAPPER-CLASS BASIC_TYPE{true},LAYOUTED_ARRAY_TYPE{float,6}]
*/

class INVENTORBASE_API SbLine {
public:
  /**
  * Default constructor.  The line is not initialized.
  */
  SbLine()  {}

  /**
  * Constructor. The line is directed from @B p0 @b to @B p1@b. @BR
  * To construct a line from a position and direction you can use: SbLine(p0,
  * p0 + dir), but using the default constructor followed by the setPosDir()
  * method is recommended to avoid floating point precision problems.
  */
  SbLine(const SbVec3f &p0, const SbVec3f &p1);

  /**
  * Sets line to pass through points @B p0 @b and @B p1@b.
  */
  void    setValue(const SbVec3f &p0, const SbVec3f &p1);

  /**
  * Sets line using a position and a direction vector.
  * The direction vector will be normalized automatically.
  * This method is preferred over setValue when the point has very
  * large magnitude, for example 1e6, because adding a normalized
  * direction vector to such a point may not be significant.
  */
  void    setPosDir( const SbVec3f &position, const SbVec3f &direction );

  /**
  * Sets line from a double precision line.
  */
  void    setValue( SbLined line );

  /**
  * Finds the two closest points between this line and @B line2@b, and loads them
  * into @B ptOnThis @b and @B ptOnLine2@b. Returns FALSE if the lines are
  * parallel (results undefined), and returns TRUE otherwise.
  */
  SbBool    getClosestPoints(const SbLine  &line2,
    SbVec3f &ptOnThis,
    SbVec3f &ptOnLine2 ) const;

  /**
  * Returns the closest point on the line to the given point.
  */
  SbVec3f    getClosestPoint(const SbVec3f &point) const;

  /**
  * Returns position of line origin point.
  */
  inline const SbVec3f &getPosition() const  { return pos; }

  /**
  * Returns direction vector of line.
  */
  inline const SbVec3f &getDirection() const  { return dir; }

  /**
  * Setup epsilon to detect intersection of very small geometry.
  */
  static void setIntersectEpsilon(const float epsilon);

  SoINTERNAL public:

  /**
   * Intersect the line with a box.
   */
  SbBool intersect(const SbBox3f &box, SbVec3f &enter, SbVec3f &exit) const;

  /**
   * Intersect the line with a box.
   */
  SbBool intersect(const SbXfBox3f &xbox, SbVec3f &enter, SbVec3f &exit) const;

  /**
   * Intersect the line with a box.
   */
  SbBool intersect(float angle, const SbBox3f &box) const;

  /**
   * Intersect the line with a point.
   */
  SbBool intersect(float angle, const SbVec3f &point) const;

  /**
   * Intersect the line with a triangle.
   */
  SbBool intersect(float angle, const SbVec3f &v0, const SbVec3f &v1, SbVec3f &pt) const;

  /**
   * Intersect the line with a triangle.
   */
  SbBool intersect(
    const SbVec3f &v0, const SbVec3f &v1, const SbVec3f &v2, 
    SbVec3f &pt, SbVec3f &barycentric, SbBool &front
    ) const;

private:
  // Parametric description:
  //  l(t) = pos + t * dir
  SbVec3f  pos;
  SbVec3f  dir;

  static float s_epsilon;
  static bool s_userEpsilon;
  static int s_reportZeroVectors;
};

//======================================================================

/**
* Directed line in 3D (double precision).
*
* @ingroup Basics
*
* @DESCRIPTION
*   Represents a (double precision) directed line in 3D. 
*   This is a basic Open Inventor datatype that is
*   used for representing a 3D line. It is used as input and output by a variety of
*   Open Inventor classes.
*
* @SEE_ALSO
*    SbVec3d,
*    SbLine,
*    SbPlane
*
* [OIVJAVA-WRAPPER-CLASS BASIC_TYPE{true},LAYOUTED_ARRAY_TYPE{double,6}]
*/

class INVENTORBASE_API SbLined {
public:
  /**
  * Default constructor.  The line is not initialized.
  */
  SbLined()  {}

  /**
  * Constructor. The line is directed from @B p0 @b to @B p1@b. @BR
  * To construct a line from a position and direction you can use: SbLine(p0,
  * p0 + dir), but using the default constructor followed by the setPosDir()
  * method is recommended to avoid floating point precision problems.
  */
  SbLined(const SbVec3d &p0, const SbVec3d &p1);

  /**
  * Sets line to pass through points @B p0 @b and @B p1@b.
  */
  void    setValue(const SbVec3d &p0, const SbVec3d &p1);

  /**
  * Sets line using a position and a direction vector.
  * The direction vector will be normalized automatically.
  * This method is preferred over setValue when the point has very
  * large magnitude, for example 1e6, because adding a normalized
  * direction vector to such a point may not be significant.
  */
  void    setPosDir( const SbVec3d &position, const SbVec3d &direction );

  /**
  * Set value from single precision line
  */
  void    setValue( SbLine line );

  /**
  * Finds the two closest points between this line and @B line2@b, and loads them
  * into @B ptOnThis @b and @B ptOnLine2@b. Returns FALSE if the lines are
  * parallel (results undefined), and returns TRUE otherwise.
  */
  SbBool    getClosestPoints(const SbLined  &line2,
    SbVec3d &ptOnThis,
    SbVec3d &ptOnLine2 ) const;

  /**
  * Returns the closest point on the line to the given point.
  */
  SbVec3d    getClosestPoint(const SbVec3d &point) const;


  /**
  * Returns position of line origin point.
  */
  inline const SbVec3d &getPosition() const  { return pos; }

  /**
  * Returns direction vector of line.
  */
  inline const SbVec3d &getDirection() const  { return dir; }

  /**
  * Setup epsilon to detect intersection of very small geometry.
  */
  static void setIntersectEpsilon(const double epsilon);

  SoINTERNAL public:
  // Intersect the line with a box, point, line, and triangle.
  SbBool intersect(const SbBox3d &box,
    SbVec3d &enter, SbVec3d &exit) const;
  SbBool intersect(double angle, const SbBox3d &box) const;
  SbBool intersect(double angle, const SbVec3d &point) const;
  SbBool intersect(double angle, const SbVec3d &v0,
    const SbVec3d &v1, SbVec3d &pt) const;
  SbBool intersect(const SbVec3d &v0,
    const SbVec3d &v1,
    const SbVec3d &v2,
    SbVec3d &pt, SbVec3d &barycentric,
    SbBool &front) const;

private:
  // Parametric description:
  //  l(t) = pos + t * dir
  SbVec3d  pos;
  SbVec3d  dir;

  static double s_epsilon;
  static bool s_userEpsilon;
  static int s_reportZeroVectors;
};

// Inline methods

inline void SbLine::setValue( SbLined line )
{
  pos.setValue( line.getPosition() );
  dir.setValue( line.getDirection() );
}

inline void SbLined::setValue( SbLine line )
{
  pos.setValue( line.getPosition() );
  dir.setValue( line.getDirection() );
}

#endif /* _SB_LINE_ */
