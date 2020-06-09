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
#ifndef LDCOORDS_H
#define LDCOORDS_H

#include <stdlib.h>
#include <stdio.h>

#ifdef _YAV_
namespace yav {
#endif


typedef struct {
  int origin[3];
  int size[3];
} blockCoords;

/** class LDCoords : creates a partition of a LDA image with blocks 
    of a given size and with a given overlap between them. */
class LDCoords
{
public :

  enum {
    LITTLE_LAST,
    LITTLE_FIRST,
    BIG_LAST,
    BIG_FIRST,
    BIG_F_L,
    IMAGE_TRUNC
  };

  /****************************************************************************/
  /*                               CONSTRUCTORS                               */
  /****************************************************************************/
  /**  @name Constructors */
  //@{
  
  /**
     Tries to divide the image into regular blocs.
     If the image size is not a multiple of the block size, there are different
     choices according to the parameter flag : 
     @param flag LDCoords::LITTLE_LAST..: a littler block is done at the end of the line/column/plane
     @param flag LDCoords::LITTLE_FIRST.: a littler block is done at the beginning of the line/column/plane
     @param flag LDCoords::BIG_LAST.....: a bigger  block is done at the end of the line/column/plane
     @param flag LDCoords::BIG_FIRST....: a bigger  block is done at the beginning of the line/column/plane
     @param flag LDCoords::BIG_F_L......: 2 bigger  blocks are done at the beginning and at the end of the line/column/plane
     @param flag LDCoords::IMAGE_TRUNC..: the image is truncated
  */
  LDCoords(const int imageOrigin[3], const int imageSize[3], 
	   const int blockSize[3],   const int blockOverlap[3], int flag); 
  //@}
  

  /****************************************************************************/
  /*                               ACCESSORS                                  */
  /****************************************************************************/
  /**  @name Accessors */
  //@{
  /// return the number of blocs in line/column/plane
  int * getNbBlocks();
  /// return the origin of the block of the i*line, j*column, and k*plane
  int * getOrigin(int i, int j, int k);
  /// p[0] = i, p[1] = j, p[2] = k
  int * getOrigin(int * p);
  /// return the size   of the block of the i*line, j*column, and k*plane
  int * getSize(int i, int j, int k);
  /// p[0] = i, p[1] = j, p[2] = k
  int * getSize(int *p);
  //@}
  
  void printTable();

  /****************************************************************************/
  /*                               FIELDS                                     */
  /****************************************************************************/
protected :
  /** @name Fields */
  //@{
  ///
  blockCoords *** blockTable;
  ///
  int nbBlocks[3];
 //@}

};

#ifdef _YAV_
} // namespace yav
#endif

#endif // LDCOORDS_H


/// @}
