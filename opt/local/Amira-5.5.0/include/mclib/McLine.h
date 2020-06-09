/*
Copyright 1999-2013 Visualization Sciences Group, SAS
Copyright 1995-2013, ZIB Berlin
ALL RIGHTS RESERVED.

amira(R) is a registered trademark of ZIB.

amira(R) is being jointly developed by Zuse Institute Berlin and
Visualization Sciences Group, SAS.
Avizo® is a registered trademark of Visualization Sciences Group, SAS
HardCopy, MeshViz, VolumeViz, TerrainViz are marks of Visualization
Sciences Group, SAS 
Visualization Sciences Group, SAS is a source licensee of OpenGL®, Open Inventor® 
from Silicon Graphics, Inc. OpenGL® and Open Inventor® are 
registered trademark of Silicon Graphics, Inc. All other products and 
company names are trademarks or registered trademarks of 
their respective companies. 

FEI Visualization Sciences Group accepts no liability to any 
party for loss or damage caused by errors or omissions or by 
statements of any kind in this publication, whether such errors 
result from accident, negligence or any other cause. FEI Visualization
Sciences Group assumes  no liability for incidental or consequential
damages arising from the use of information in this publication.
FEI Visualization Sciences Group provides no 
warranties regarding the information contained in this 
publication, whether expressed, implied, or statutory, including 
implied warranties of merchantability or fitness for a 
particular purpose. 

FEI Visualization Sciences Group also does not assume any liability
for links from this publication to publications from other companies,
organizations or individuals. FEI Visualization Sciences Group does not
imply endorsement of any specific  company, organization or individual
through offering links to this content.
All information provided within this publication 
is subject to change at any time and is provided for 
informational purposes only by FEI Visualization Sciences Group.
Copyright 1994-2012 by Visualization Sciences Group, SAS Merignac, France.

*/

/// @addtogroup mclib mclib
/// @{
#ifndef MC_LINE_H
#define MC_LINE_H

#include "McVec3f.h"
#include "McWinDLLApi.h"

#pragma warning(push)

// 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
#pragma warning(disable:4251)

class McBox3f;

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
 *    McVec3f,
 *    SbPlane
 *
 */
class MCLIB_API McLine {
 public:
  /**
   * Constructor.
   */
  McLine()  {}

  /**
   * Constructor. To construct a line from a position and direction, use: McLine(p0,
   * p0 + dir). The line is directed from @B p0 @b to @B p1@b.
   */
  McLine(const McVec3f &p0, const McVec3f &p1);

  /**
   * Sets line to pass through points @B p0 @b and @B p1@b.
   */
  void    setValue(const McVec3f &p0, const McVec3f &p1);

  // @TOBEREVIEWED
  /**
   * Sets line using a position and a direction vector.
   * The direction vector will be normalized automatically.
   * This method is preferred over setValue when the point has very
   * large magnitude, for example 1e6, because adding a normalized
   * direction vector to such a point may not be significant.
   */
  void    setPosDir( const McVec3f &position, const McVec3f &direction );

  /**
   * Finds the two closest points between this line and @B line2@b, and loads them
   * into @B ptOnThis @b and @B ptOnLine2@b. Returns FALSE if the lines are
   * parallel (results undefined), and returns TRUE otherwise.
   */
  bool    getClosestPoints(const McLine  &line2,
                             McVec3f &ptOnThis,
                             McVec3f &ptOnLine2 ) const;

  /**
   *  Same as above, but this version also returns the value of the parameters (of the parametric representation of the lines) at the closest point.
   *  @B paramOnThis @b is the parameter value of this line at the closest point: ptOnThis = p0 + paramOnThis * dir (where dir is normalized).
   *  @B paramOnLine2 @b is the parameter value of @B line2 @b at the closest point.
   */
  bool    getClosestPoints(const McLine  &line2,
                             McVec3f &ptOnThis,
                             McVec3f &ptOnLine2,
                             float &paramOnThis,
                             float &paramOnLine2) const;

  /**
   * Returns the closest point on the line to the given point.
   */
  McVec3f    getClosestPoint(const McVec3f &point) const;


  /**
   * Returns position of line origin point and direction vector of line.
   */
  const McVec3f &getPosition() const  { return pos; }
  /**
   * Returns position of line origin point and direction vector of line.
   */
  const McVec3f &getDirection() const  { return dir; }

 public:
  // Intersect the line with a box, point, line, and triangle.
  bool intersect(const McBox3f &box, McVec3f &enter, McVec3f &exit, float Eps = 1e-6) const;
  bool intersect(float angle, const McBox3f &box) const;
  bool intersect(float angle, const McVec3f &point) const;
  bool intersect(float angle, const McVec3f &v0, const McVec3f &v1, McVec3f &pt) const;
  bool intersect(const McVec3f &v0, const McVec3f &v1, const McVec3f &v2,
                   McVec3f &pt, McVec3f &barycentric, bool &front) const;

 private:
  // Parametric description:
  //  l(t) = pos + t * dir
  McVec3f  pos;
  McVec3f  dir;
};

#pragma warning(pop)

#endif

/// @}
