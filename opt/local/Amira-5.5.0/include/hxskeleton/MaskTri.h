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

/// @addtogroup hxskeleton hxskeleton
/// @{
#ifndef MASKTRI_H
#define MASKTRI_H

#include <vector>
#ifdef _YAV_
#include "chamferTriangleStruct.h"
namespace yav {
#else
#include "hxskeleton/chamferTriangleStruct.h"
#endif // _YAV_


  /** MaskTri class : virtual class to compute chamfer triangulations
      used for chamfer mask coefficients determination */
class MaskTri
{
  friend class MaskCalculation;
  friend class MaskCalc;
  friend class MaskCalcAnisotropZ;
  friend class MaskCalcAnisotropYZ;

public :

  /** @name Constructors */
  //@{
  ///
  MaskTri(int _order);
  ///@}

  /** @name Destructor */
  //@{
  ///
  virtual ~MaskTri();
  //@}

  /** @name accessors */
  ///
  int getNbPts();
  ///
  int getNbTri();
  ///
  void deleteTri(int index);

  /** @name Other methods */

  ///
  virtual unsigned char *** editFinalMask();

  ///
  virtual void printTriangulation() = 0;


protected :
  /** returns the index of elmt in fareyElmts,
      returns -1 if elmt is not in fareyElmts.
  **/
  int isInSet(chamferTriElmt elmt);

  //  void initNC();

  /// vector where triangulation triangles are stored
  std::vector < chamferTriangle > myTris;
  /// vector where points of the triangulation are stored
  std::vector < chamferTriElmt >  myElmts;

  /** The nbPts first points of myElmts are the points of the chamfer mask generator.
      After nbPts, myElmts' points are possible symmetric points of the mask generator
      used to compute local convexity conditions.
  **/
  int nbPts;
  /// Iterator of myElmts
  int elmtIt;
  /// fareyTris iterator
  int triIt;

  /// Order of the triangulation (i.e. width of the mask)
  int order;
  /// Size of the final mask
  int maskSize;
  /// Final mask
  unsigned char *** finalMask;
};

#ifdef _YAV_
} //namespace yav
#endif

#endif // FAREYTRI_H

/// @}
