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
#ifndef CHAMFERMASK_H
#define CHAMFERMASK_H


#ifdef _YAV_
namespace yav {
#else
#include <hxskeleton/HxSkeletonWinDLLApi.h>
#endif


typedef struct {
  bool exist;
  int offset;
  unsigned char value;
} chamferElmt;


  /**  ChamferMask class, contains the geometry and the coefficients of a chamfer mask */
class ChamferMask
{
public :

  /** @name Constructors */
  //@{
  /** Default constructor (uses default coefficients)
      @param size : size of the chamfer mask, (must be odd), e.g. : 5 ->  5x5(x5) mask
      @param        Only 3x3(x3), 5x5(x5) and 7x7(x7) default mask coefficients are implemented
      @param dim  : dimension of the chamfer mask. 
      @param        By default, equals 3 but can be set to 2 if the image to process is 2D or if 
      @param        you want to process the distance calculation slice by slice.
      @param flag : 0 -> default mask for distance map calculation
      @param        1 -> corresponding default initialisation mask 
  */
  ChamferMask(int size = 3, int dim = 3, int flag = 0);
  /** 
      @param size : size of the chamfer (e.g. : 5 -> chamfer mask 5x5(x5))
      @param coeffs : table of the coefficients of the mask, (1/8th)Z^3
      @param e.g. for 3x3x3 chamfer mask :
      @param coeffs[1][0][0] (a1) : coefficient for horizontal displacement\n
      @param coeffs[0][1][0] (a2) : coefficient for vertical   displacement\n
      @param coeffs[0][0][1] (a3) : coefficient for depth displacement\n
      @param coeffs[1][1][0] (b1) : coefficient for planar diagonnal displacement between a1 and a2\n
      @param coeffs[0][1][1] (b2) : coefficient for planar diagonnal displacement between a2 and a3\n
      @param coeffs[1][0][1] (b3) : coefficient for planar diagonnal displacement between a3 and a1\n
      @param coeffs[1][1][1] (c)  : coefficient for diagonnal displacement\n
      @param coeffs[x][y][z] = 0 if the xyz position is not relevant, e.g.\n
      @param coeffs[2][0][0] = 0 for the chamfer 5x5x5\n
      @param epsilon : scale coefficient of the distance map. If epsilon = -1.0 (default value),\n 
                       then scale coefficient is set to coeffs[1][0][0] (a1)\n
      @param maxRelError : Maximum relative error with the euclidian distance (default is -1)
  */
  /// 3D constructor 
  ChamferMask(int size, unsigned char *** coeffs, float epsilon = -1.0, float maxRelError = -1.0);
  /// 2D constructor
  ChamferMask(int size, unsigned char ** coeffs,  float epsilon = -1.0, float maxRelError = -1.0); 

  //@}

  /** @name Destructor */
  //@{
  /// destructor
  ~ChamferMask();
  //@}
  
  
  /** @name Accessors */
  //@{

  /// Returns the length of the table where chamfer mask coefficients are stored
  int getMaskSize();
  /// Returns the table where where chamfer mask coefficients are stored
  unsigned char * getChamferMask();
  /// Returns the table containing the offsets corresponding to the table of coefficients (chamfermask)
  int * getNeighborhood();
  /// Returns the size of the chamfer mask (e.g. 5 for a 5x5x5 chamfer mask)
  int getChamferSize();
  /** Returns the number of line(s) from when you can consider you are 
      in the middle of the image (i.e. mask borders are no longer outside the image) */
  int getIBegin();
  /** Returns the number of collumns(s) from when you can consider you are 
      in the middle of the image (i.e. mask borders are no longer outside the image) */
  int getJBegin();
  /** Returns the number of plane(s) from when you can consider you are 
      in the middle of the image (i.e. mask borders are no longer outside the image) */
  int getKBegin();
  /// Returns false if offsets (in neighborhood table, for exemple) have never been initialized
  bool getIsSetOffsets();

  /** Set in elmt the private mask element corresponding to (x, y, z) coordinates 
      relatively to the central point of the mask, i.e. : 
      @param z :     0    <=  z  <= kBegin
      @param y : - jBegin <=  y  <= jBegin
      @param x : - iBegin <=  x  <= iBegin
  */
  void getPrivatMask(int x, int y, int z, chamferElmt * elmt);

  /// Returns the distance map scale value
  float getEpsilon();
  /// Returns the maximum relative error with the euclidian distance
  float getMaxRelativeError();

  //@}

  /** @name Public methods */
  //@{

  /// Initialization of the image dimensions -> sets the offsets of the neighborhood for mask values
  void initOffsets(int dimX, int dimY, int dimZ);

  //@}

protected : 

  /** @name Protected methods */
  //@{
  ///
  void initMask2D(int size, unsigned char **  coeffs, float epsilon);
  ///
  void initMask3D(int size, unsigned char *** coeffs, float epsilon);
  //@}

  /** @name Fields */
  //@{

  /// Scale factor of the distance map
  float epsilon;

  /// Maximum relative error
  float maxRelError;

  /** @name For general algorithms */
  //@{
  /// size of the table containing mask coefficients
  int maskSize;
  /// table of size maskSize, containing only existing chamfer coefficients
  unsigned char * chamferMask;   
  /// table of size maskSize, containing the offsets of the neighbors corresponding to the chamferMask.
  int * neighborhood ;
  
  // Fields corresponding to the size of the mask 
  /// size of the chamfer mask : if size == 3 -> mask 3x3(x3), 5 -> mask 5x5(x5)
  int chamferSize;      
  
  /// indice of line where you can consider you are no longer on the borders of the image
  int iBegin;
  /// 
  int jBegin;
  /// 
  int kBegin;
  
  /// set to true if offsets have been initialized at least once
  bool isSetOffsets;
  //@}

  /** @name For the treatment of the borders */
  //@{
  /** 3 dimensionnal table representing the half cube within the point of 
      interest where the mask will be applied : 
      @param z :            0      <=  z  <= chamferSize / 2
      @param y : - chamferSize / 2 <=  y  <= chamferSize / 2
      @param x : - chamferSize / 2 <=  x  <= chamferSize / 2
      @param elmt.exist is set to false when it is null or when 
      k >= 0 and for k = 0 { j >= 0, and for j = 0, {i > 0}} 
      (only the half of the neighbooring cube)
  */ 
  chamferElmt *** privateMask; 
  //@}

  //@}
};

#ifdef _YAV_
} // namespace yav
#endif


#endif //CHAMFERMASK_H

/// @}
