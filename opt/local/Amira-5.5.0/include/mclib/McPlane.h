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
#ifndef MC_PLANE_H
#define MC_PLANE_H

#include "McVec3f.h"
#include "McLine.h"
#include "McWinDLLApi.h"

#pragma warning(push)

// 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
#pragma warning(disable:4251)

class McMat4f;

/**
 * Oriented plane in 3D.
 *
 * @ingroup Basics
 *
 * @DESCRIPTION
 *   Represents an oriented plane in 3D. This is a lightweight class/datatype that is
 *   used for arguments to some Open Inventor objects.
 *
 * @SEE_ALSO
 *    McVec3f,
 *    McLine
 *
 */

class MCLIB_API McPlane {
 public:
  /**
   * Constructor.
   */
  McPlane()  {}

  /**
   * Constructor. @B p0@b, @B p1@b, and @B p2@b represent three points in the
   * plane.
   */
  McPlane(const McVec3f &p0, const McVec3f &p1, const McVec3f &p2);

  /**
   * Constructor. @B normal@b is a normal vector and @B distance @b is distance
   * from origin to
   * plane along normal vector.
   */
  McPlane(const McVec3f &normal, float distance);

  /**
   * Constructors. @B normal@b is a normal vector and @B point @b is a point
   * in 3-space for the plane
   * to pass through.
   */
  McPlane(const McVec3f &normal, const McVec3f &point);


  /** flip sign of normal */
  void revertOrientation() {
    normalVec *= -1;
    distance *= -1;
  }

  /**
   * Offset a plane by a given distance.
   */
  void    offset(float d);

  /**
   * Intersect line and plane, returning TRUE if there is an intersection, FALSE if
   * line is parallel to plane.
   */
  bool intersect(const McLine &l,
                   McVec3f &intersection) const;

  /**
   * Intersect two planes, returning TRUE if there is an intersection, FALSE if
   * both planes are parallel.
   */
  bool intersect(const McPlane &p,
                   McLine &intersection) const;

  /**
    * Returns signed distance between the plane and pnt.
    */
  float getDistance(const McVec3f& pnt) const
  {
      return normalVec.dot(pnt) - distance;
  }

  /**
   * Transforms the plane by the given matrix.
   */
  void    transform(const McMat4f &matrix);

  /**
   * Returns TRUE if the given point is within the half-space defined by the plane.
   */
  bool    isInHalfSpace(const McVec3f &point) const;


  /**
   * Returns normal vector to plane.
   */
  const McVec3f &getNormal() const    { return normalVec; }
  /**
   * Returns distance from origin to plane.
   */
  float    getDistanceFromOrigin() const  { return distance; }

  /**
   * Equality comparison operator.
   */
  friend int MCLIB_API operator ==(const McPlane &p1, const McPlane &p2);
  /**
   * Inequality comparison operator.
   */
  friend int operator !=(const McPlane &p1, const McPlane &p2)
  { return !(p1 == p2); }

 private:
  // Plane is all p such that normalVec . p - distance = 0

  // Normal to the plane
  McVec3f  normalVec;

  // Distance from origin to plane: distance * normalVec is on the plane
  float  distance;
};

int MCLIB_API operator ==(const McPlane &p1, const McPlane &p2);

#pragma warning(pop)

#endif

/// @}
