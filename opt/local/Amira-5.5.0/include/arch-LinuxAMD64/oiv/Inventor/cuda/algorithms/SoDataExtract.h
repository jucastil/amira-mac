/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined SOCUDADATAEXTRACT_H
#define SOCUDADATAEXTRACT_H

#include <Inventor/SbString.h>

#include <Inventor/STL/vector>

#include <Inventor/algorithms/SoDataExtract.h>

#include <Inventor/cuda/algorithms/SoCudaAlgorithmsDefs.h>

class SoCudaHandle;
class SoCudaBufferObject;

/**
* @VSGEXT Data extraction algorithms for CUDA buffers
*
* @ingroup CudaAlgorithms
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

class INVENTORCUDAALGORITHMS_API  SoCudaDataExtract : public SoDataExtract
{
public:

  /** Constructor */
  SoCudaDataExtract();

SoINTERNAL public:
  /** Virtual destructor */
  virtual ~SoCudaDataExtract();


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

  // CUDA

  /**
   * Extract X axis slice from CUDA buffer
   */
  int getXSliceFromTile( SoCudaBufferObject* inputTile, int dimx,int dimy,int dimz, int datumSize, int slice, SoCudaBufferObject* outputSlice);

  /**
   * Extract Y axis slice from CUDA buffer
   */
  int getYSliceFromTile( SoCudaBufferObject* inputTile, int dimx,int dimy,int dimz, int datumSize, int slice, SoCudaBufferObject* outputSlice);

  /**
   * Extract Z axis slice from CUDA buffer
   */
  int getZSliceFromTile( SoCudaBufferObject* inputTile, int dimx,int dimy,int dimz, int datumSize, int slice, SoCudaBufferObject* outputSlice);

  /**
   * Copy tile from CUDA buffer
   */
  int copyTile( SoCudaBufferObject* inputTile,int tileDimx, int tileDimy, int tileDimz, int originX, int originY, int originZ, int datumSize,
                       int bufDimX, int bufDimY, int bufDimZ,int vMinX, int vMinY, int vMinZ, int vMaxX, int vMaxY, int vMaxZ, 
                       SoCudaBufferObject* outputBuffer );

  /**
   * Copy plane from CUDA buffer
   */
  int copyPlane( SoCudaBufferObject* inputTile, int tileDimX, int tileDimY, int tileDimZ, int originX, int originY, int originZ,
                         int datumSize, int bufDimX, int qminX, int qminY, int qminZ, 
                         int qmaxX, int qmaxY, int qmaxZ, float normI, float normJ, float normK, 
                         float distance, int xAxis, int yAxis, int zAxis, SoCudaBufferObject* outputBuffer );

private:

  SoCudaHandle* m_getSliceFromTileHandle;
  SoCudaHandle* m_copyTileHandle;
  SoCudaHandle* m_copyPlaneHandle;

};

#endif //SODATAEXTRACT_H

