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
#ifndef ALIGNBLOCKS_H
#define ALIGNBLOCKS_H

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortFilename.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxfield/HxUniformScalarField3.h>

#include <hxskeleton/HxSkeletonWinDLLApi.h>

/** types of projection view */
#define _Z_     0
#define _COLOR_ 1
#define _ZMAX_  2
#define _MAX_   3

enum SIM_TYPE
{
  UNKNOWN,
  SSD,
  CORREL
};

class HXSKELETON_API HxAlignBlocks : public HxCompModule {

  HX_HEADER(HxAlignBlocks);

public:
  HxAlignBlocks();

  ~HxAlignBlocks();

  HxPortFilename   portFilename;
  HxPortIntSlider  portSearchAreaX;
  HxPortInfo       portInfoX;
  HxPortIntSlider  portSearchAreaY;
  HxPortInfo       portInfoY;
  HxPortIntSlider  portSearchAreaZ;
  HxPortInfo       portInfoZ;
  HxPortToggleList portWhilAlignment;
  HxPortRadioBox   portSimilarity;
  HxPortDoIt       portAction;


  virtual void update();
  virtual void compute();


  /** Align mosaic blocks
   * The mosaic must contain overlapping blocks.
   * For each bloc of the mosaic, finds the best translation,
   * i.e. the translation minimizing the difference of intensity in
   * the overlapping regions between the considered block and all its neighbours.
   *@param aMosaic mosaic
   *@param filename where to store the mosaic and tmp files
   * (the 2D projection vues of the blocks will be saved as
   *  filename_nb.mip.am where nb represents the number of the block
   *@param searchAreaX max value of the translation to apply in x direction
   *@param searchAreaY max value of the translation to apply in y direction
   *@param searchAreaZ max value of the translation to apply in z direction
   *@param alignXY if true, performs alignment in the plan XY
   *@param alignZ  if ture, performs alignment in the z direction
   *@param coef similarity coefficient.
   * Can be equal to SSD (Sum of Squared Differences) or CORREL (Correlation Coefficient)
   */
/*
  static void alignBlocks(HxMosaic * aMosaic,
			  McFilename filename = NULL,
			  int searchAreaX = 50,
			  int searchAreaY = 50,
			  int searchAreaZ = 10,
			  bool alignXY = true,
			  bool alignZ  = true,
			  SIM_TYPE coef = CORREL);

  static void alignBlocksXY(HxMosaic * aMosaic,
			    int searchAreaX = 50,
			    int searchAreaY = 50,
			    SIM_TYPE coef = CORREL,
			    float vx = 1.0,
			    float vy = 1.0,
			    float vz = 1.0,
			    McFilename base = NULL,
			    FILE * fp = NULL);

  static void alignBlocksZ(HxMosaic * aMosaic,
			   int searchAreaZ = 10,
			   SIM_TYPE coef = CORREL,
			   float vx = 1.0,
			   float vy = 1.0,
			   float vz = 1.0,
			   McFilename base = NULL,
			   FILE * fp = NULL);
*/
  static void alignBlocks(HxMosaic * aMosaic,
			  McFilename filename,
			  int searchAreaX = 50,
			  int searchAreaY = 50,
			  int searchAreaZ = 10,
			  bool alignXY = true,
			  bool alignZ  = true,
			  SIM_TYPE coef = CORREL);

  static void alignBlocksXY(HxMosaic * aMosaic,
			    int searchAreaX,
			    int searchAreaY,
			    SIM_TYPE coef,
			    float vx,
			    float vy,
			    float vz,
			    McFilename base,
			    FILE * fp = NULL);

  static void alignBlocksZ(HxMosaic * aMosaic,
			   int searchAreaZ,
			   SIM_TYPE coef,
			   float vx,
			   float vy,
			   float vz,
			   McFilename base,
			   FILE * fp = NULL);

/** Computes the projection on the XY plane
 *@param src image to project
 *param type
 _Z_     -> projects the z-coordinate of the last non zero point
 _COLOR_ -> projects the clorl        of the last non zero point
 _ZMAX_  -> projects the z-coordinate of the maximum intensity point
 _MAX_   -> projects the intensity    of the maximum intensity point
 */
  static HxUniformScalarField3* upView(HxUniformScalarField3 * src, int type);

private:

  typedef struct {
    int imageNumber;
    McString originalName;
    int dims[3];
    float bbox[6];
    float translation[3];
    McDArray<int> neighbours;
    McDArray<int> commonSurfaces;
    int maxSurface;
    HxUniformScalarField3 * mip;
  } alignMip;

  static int commonSurface(int srcDimX, int srcDimY,
			   int i2rDimX, int i2rDimY,
			   int relativePosX, int relativePosY);

  static int commonVolume(int srcDimX, int srcDimY, int srcDimZ,
			  int i2rDimX, int i2rDimY, int i2rDimZ,
			  int relativePosX, int relativePosY, int relativePosZ);

  static void blocsSSD(int srcDimX, int srcDimY,
		       int i2rDimX, int i2rDimY,
		       unsigned char * src,
		       unsigned char * i2r,
		       int relativePosX, int relativePosY,
		       int * overlapSurface, double * overlapError);

  static void blocsSSD(int srcDimX, int srcDimY, int srcDimZ,
		       int i2rDimX, int i2rDimY, int i2rDimZ,
		       unsigned char * src,
		       unsigned char * i2r,
		       int relativePosX, int relativePosY, int relativePosZ,
		       int * overlapVolume, double * overlapError);

  static void blocsCorrelation(int srcDimX, int srcDimY,
			       int i2rDimX, int i2rDimY,
			       unsigned char * src,
			       unsigned char * i2r,
			       int relativePosX, int relativePosY,
			       int * overlapSurface, double * overlapError);


  static void blocsCorrelation(int srcDimX, int srcDimY, int srcDimZ,
			       int i2rDimX, int i2rDimY, int i2rDimZ,
			       unsigned char * src,
			       unsigned char * i2r,
			       int relativePosX, int relativePosY, int relativePosZ,
			       int * overlapVolume, double * overlapError);

  // Voxel size of mosaic images
  McVec3f vSize;

};

#endif




/// @}
