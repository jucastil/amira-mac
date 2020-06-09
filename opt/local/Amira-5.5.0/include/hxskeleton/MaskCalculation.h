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
#ifndef MASKCALCULATION_H
#define MASKCALCULATION_H

#ifdef _YAV_ // namespace for INRIA
#include "chamferTriangleStruct.h"
#include "MaskTri.h"
namespace yav {
#else
#include "hxskeleton/chamferTriangleStruct.h"
#include "hxskeleton/MaskTri.h"
#endif //_YAV_


class MaskCalculation
{
public :
  // Constructor
  MaskCalculation();

  // Destructor
  virtual ~MaskCalculation();

  void printMask(const char * filename);

  void wheightsCalc(const char * filename, int maxWheight, int minWheight = 1);
  void initLCC();

  unsigned char *** getFinalMask();
  float getEpsilon();
  float getMaxRelativeError();

  void printInitialisation(char * filename);

protected :

  bool localConvexityCond(int k);
  void preCalcError();
  int delta(chamferTriangle tri);


  virtual float normeInf(chamferTriElmt elmt) = 0;
  virtual float norme1(chamferTriElmt elmt) = 0;


  void wheightsCalcRec(int k);
  virtual void relativeErrorCalc(chamferTriangle tri, RelErrorElmt * errElmt)=0;

  /// Fields
  MaskTri * myTriangulation;

  unsigned int etIt;
  std::vector < int * > wheightsTable;
  std::vector < RelErrorElmt > errorsTable;


  std::vector < LCCElmt > LCCTable;
  /// vector where triangulation triangles are stored
  std::vector < chamferTriangle > * myTris;
  /// vector where points of the triangulation are stored
  std::vector < chamferTriElmt > *  myElmts;

  int nbPts;

  int a;


};

#ifdef _YAV_
} // end namespace yav
#endif

#endif // MASKCALCULATION_H

/// @}
