/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined SODATAEXTRACT_H
#define SODATAEXTRACT_H

#include <Inventor/SbDataType.h>

#include <Inventor/STL/vector>

#include <Inventor/algorithms/SoAlgorithmsDefs.h>

class SoBufferObject;
class SoCpuBufferObject;

/**
* @VSGEXT Data extraction algorithms for buffers
*
* @ingroup CpuAlgorithms
*
* @DESCRIPTION
*
* The Data extract module provides basic algorithms for extracting a
* specific subset of the data from a buffer.  For example, extracting
* an axis aligned slice from a buffer that contains an LDM volume
* data tile.
*
* Examples:
*
* @SEE_ALSO
*   SoAlgorithms, SoArithmetic, SoConversion, SoConvolution, SoSeismic
*
*/

class INVENTORALGORITHMS_API  SoDataExtract
{
public:

  /** Constructor */
  SoDataExtract();

SoINTERNAL public:
  /** Virtual destructor */
  virtual ~SoDataExtract();

  /** Static initClass function to initialize the data extraction module. */
  static void initClass();

  /** Static exitClass function to free the memory allocated by the data extraction module. */
  static void exitClass();

public:
  /**
   * Extract an X axis slice @BR
   * Given a buffer containing an LDM volume data tile, extract the Nth slice of data
   * along the X axis, where slices are numbered 0 to dimx-1.
   */
  virtual int getXSliceFromTile( SoBufferObject* inputTile, int dimx,int dimy,int dimz, int datumSize, int slice, SoBufferObject* outputSlice);

  /**
   * Extract an X axis slice @BR
   * Given a buffer containing an LDM volume data tile, extract the Nth slice of data
   * along the X axis, where slices are numbered 0 to dimx-1.
   */
  virtual int getYSliceFromTile( SoBufferObject* inputTile, int dimx,int dimy,int dimz, int datumSize, int slice, SoBufferObject* outputSlice);

  /**
   * Extract an X axis slice @BR
   * Given a buffer containing an LDM volume data tile, extract the Nth slice of data
   * along the X axis, where slices are numbered 0 to dimx-1.
   */
  virtual int getZSliceFromTile( SoBufferObject* inputTile, int dimx,int dimy,int dimz, int datumSize, int slice, SoBufferObject* outputSlice);

  /**
   * Copy a tile
   */
  virtual int copyTile( SoBufferObject* inputTile,int tileDimx, int tileDimy, int tileDimz, int originX, int originY, int originZ, int datumSize,
                       int bufDimX, int bufDimY, int bufDimZ,int vMinX, int vMinY, int vMinZ, int vMaxX, int vMaxY, int vMaxZ,
                       SoBufferObject* outputBuffer );

  /**
   * Copy a plane
   */
  virtual int copyPlane( SoBufferObject* inputTile, int tileDimX, int tileDimY, int tileDimZ, int originX, int originY, int originZ,
                         int datumSize, int bufDimX, int qminX, int qminY, int qminZ,
                         int qmaxX, int qmaxY, int qmaxZ, float normI, float normJ, float normK,
                         float distance, int xAxis, int yAxis, int zAxis, SoBufferObject* outputBuffer );

};

#endif //SODATAEXTRACT_H

