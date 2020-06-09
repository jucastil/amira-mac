/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef LDM_DATA_TRANSFROM_H
#define LDM_DATA_TRANSFROM_H

#include <LDM/SoLDMLargeDataManagement.h>

#include <Inventor/fields/SoFieldContainer.h>
#include <Inventor/SbLinear.h>
#include <Inventor/SbBox.h>

class SoDataSet;
class SoBufferObject;

/**
 * @LDMEXT LDM data transform object.
 *
 * @ingroup LDMMisc
 *
 * @DESCRIPTION
 * This object defines a transform function to be applied to each LDM tile
 * after it is loaded (returned from the volume reader) but before it is
 * stored in system memory (LDM data cache).
 * This allows you to modify the original data (for example, scaling or
 * filtering) before it is displayed.  It can also be used to create
 * multiple data sets in memory from a single data set on disk.
 *
 * Derive a new class from this one and implement the #transformFunction method.
 * Create an instance of the new class and set in the dataTransform field of
 * the SoDataSet node.
 *
 * Note that for volume data, the SoVolumeTransform node also allows a
 * transform function to be applied to each LDM tile, but the transform
 * is applied immediately before the tile is loaded onto the graphics board.
 * SoVolumeTransform does allow the Data Access API to be used in the
 * transform function.
 *
 * Also note that the SoDataCompositor node allows a transform function
 * to be applied in the special case where multiple volumes should be
 * combined into a single volume.
 *
 * @SEE_ALSO
 * SoDataSet, SoVolumeData, SoVolumeTransform
 *
 */
class LDM_API SoLDMDataTransform : public SoFieldContainer
{
  SO_FIELDCONTAINER_ABSTRACT_HEADER(SoLDMDataTransform);
public:

  /**
   * Default constructor.
   */
  SoLDMDataTransform();

  /**
  * Data transform function. @BR
  * This function allows a tile of data to be transformed after it is loaded, but before
  * it is stored in main memory.  It is not currently possible to access other tiles of
  * data (for example using the data access API) from this function.  Note that the
  * function will be called from LDM data loader threads, so multiple threads may be
  * executing in this function at the same time (on different tiles).
  * Inputs are:
  *  - The associated data set object the function is calling for.
  *    This allows retrieving information such as data type (ds->getDataType()).
  *  - The dimensions of the tile to transform.
  *    This defines the size of the buffer and is the same for every tile in a dataset.
  *    However tiles on the "outside" of the dataset may be partial tiles and contain
  *    less than the full number of actual data values.
  *  - A buffer containing the tile data to transform.
  *    The data should be modified "in place" in this buffer.
  *  - The position and extent of the tile in data space (voxel coordinates).
  *    For lower resolution tiles (level > 0) the extent of the tile will be larger
  *    than the dimensions of the tile (number of values in the tile).
  *  - The tile resolution level.  Level 0 is full resolution data.
  *  - Optional user data specified with setLDMDataTransformFunction.
  *
  * @NOTES: This method must be thread safe, and must not make any OpenInventor database
  *   modification or notification.
  */
  virtual void transformFunction(
    SoDataSet* ds,                      // current dataset
    const SbVec3i32& bufferDimension,   // tile dim
    SoBufferObject* bufferToTransform,  // buffer to transform
    const SbBox3i32& dataBox,           // position of tile in data space
    int resolutionLevel	                // resolution level of the tile
  )=0;

protected:

  /**
   * Destructor.
   */
  virtual ~SoLDMDataTransform();

};

#endif /* LDM_DATA_TRANSFROM_H */
