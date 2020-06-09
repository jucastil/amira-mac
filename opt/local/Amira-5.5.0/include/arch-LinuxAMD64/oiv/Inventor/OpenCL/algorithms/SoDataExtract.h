/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined SOOPENCLDATAEXTRACT_H
#define SOOPENCLDATAEXTRACT_H

#include <Inventor/SbString.h>

#include <Inventor/STL/vector>

#include <Inventor/algorithms/SoDataExtract.h>

#include <Inventor/OpenCL/algorithms/SoOpenCLAlgorithmsDefs.h>

class SoOpenCLHandle;
class SoOpenCLBufferObject;

/**
* @VSGEXT Data extraction algorithms for OpenCL buffers
*
* @ingroup OpenCLAlgorithms
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
*
* [OIVJAVA-WRAPPER-CLASS NO_WRAP]
* 
*/

class INVENTOROPENCLALGORITHMS_API  SoOpenCLDataExtract : public SoDataExtract
{
public:

  /** Constructor */
  SoOpenCLDataExtract();

SoINTERNAL public:
  /** Virtual destructor */
  virtual ~SoOpenCLDataExtract();


  /** Static initClass function to initialize the data extraction module. */
  static void initClass();

  /** Static exitClass function to free the memory allocated by the data extraction module. */
  static void exitClass();

public:
  /**
   * Extract X axis slice
   */
  virtual int getXSliceFromTile( SoBufferObject* inputTile, int dimx,int dimy,int dimz, int datumSize, int slice, SoBufferObject* outputSlice);

  /**
   * Extract Y axis slice
   */
  virtual int getYSliceFromTile( SoBufferObject* inputTile, int dimx,int dimy,int dimz, int datumSize, int slice, SoBufferObject* outputSlice);

  /**
   * Extract Z axis slice
   */
  virtual int getZSliceFromTile( SoBufferObject* inputTile, int dimx,int dimy,int dimz, int datumSize, int slice, SoBufferObject* outputSlice);

  /**
   * Copy tile
   */
  virtual int copyTile( SoBufferObject* inputTile,int tileDimx, int tileDimy, int tileDimz, int originX, int originY, int originZ, int datumSize,
                       int bufDimX, int bufDimY, int bufDimZ,int vMinX, int vMinY, int vMinZ, int vMaxX, int vMaxY, int vMaxZ,
                       SoBufferObject* outputBuffer );

  /**
   * Copy plane
   */
  virtual int copyPlane( SoBufferObject* inputTile, int tileDimX, int tileDimY, int tileDimZ, int originX, int originY, int originZ,
                         int datumSize, int bufDimX, int qminX, int qminY, int qminZ,
                         int qmaxX, int qmaxY, int qmaxZ, float normI, float normJ, float normK,
                         float distance, int xAxis, int yAxis, int zAxis, SoBufferObject* outputBuffer );

  // OPENCL

  /**
   * Extract X axis slice from OPENCL buffer
   */
  int getXSliceFromTile( SoOpenCLBufferObject* inputTile, int dimx,int dimy,int dimz, int datumSize, int slice, SoOpenCLBufferObject* outputSlice);

  /**
   * Extract Y axis slice from OPENCL buffer
   */
  int getYSliceFromTile( SoOpenCLBufferObject* inputTile, int dimx,int dimy,int dimz, int datumSize, int slice, SoOpenCLBufferObject* outputSlice);

  /**
   * Extract Z axis slice from OPENCL buffer
   */
  int getZSliceFromTile( SoOpenCLBufferObject* inputTile, int dimx,int dimy,int dimz, int datumSize, int slice, SoOpenCLBufferObject* outputSlice);

  /**
   * Copy tile from OPENCL buffer
   */
  int copyTile( SoOpenCLBufferObject* inputTile,int tileDimx, int tileDimy, int tileDimz, int originX, int originY, int originZ, int datumSize,
                       int bufDimX, int bufDimY, int bufDimZ,int vMinX, int vMinY, int vMinZ, int vMaxX, int vMaxY, int vMaxZ, 
                       SoOpenCLBufferObject* outputBuffer );

  /**
   * Copy plane from OPENCL buffer
   */
  int copyPlane( SoOpenCLBufferObject* inputTile, int tileDimX, int tileDimY, int tileDimZ, int originX, int originY, int originZ,
                         int datumSize, int bufDimX, int qminX, int qminY, int qminZ, 
                         int qmaxX, int qmaxY, int qmaxZ, float normI, float normJ, float normK, 
                         float distance, int xAxis, int yAxis, int zAxis, SoOpenCLBufferObject* outputBuffer );

private:

  SoOpenCLHandle* m_getXSliceFromTileHandle;
  SoOpenCLHandle* m_getYSliceFromTileHandle;
  SoOpenCLHandle* m_getZSliceFromTileHandle;

  SoOpenCLHandle* m_copyTileHandle;
  SoOpenCLHandle* m_copyPlaneHandle;

};

#endif //SODATAEXTRACT_H

