/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  SO_HEIGHTFIELD_GEOMETRY_H
#define  SO_HEIGHTFIELD_GEOMETRY_H

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#pragma warning(disable:4996)
#endif

#include <VolumeViz/nodes/SoVolumeData.h>
#include <Inventor/fields/SoSFDouble.h>
#include <Inventor/fields/SoSFFloat.h>

/**
* @VREXT Height field data node
*
* @ingroup VolumeVizNodes
*
* @DESCRIPTION
* SoHeightFieldGeometry defines a uniform grid in the XY plane whose vertices are
* height (Z) values stored in 2D LDM format (any LDM data set with the Z dimension
* equal to 1).  Storing only height values is a very efficient way to represent a
* surface and LDM supports 8 and 16 bit integer data in addition to float (and other
* types). Adding the combination of LDM data management with advanced GPU features
* provides a way to handle extremely large surfaces. Just as with volume data, LDM
* uses tiles of data and multiple levels of resolution to enable interactive frame
* rates even for data sets that cannot fit in system memory. Using an advanced GPU
* feature called a "geometry shader", SoHeightFieldRender generates triangles for
* the surface on the graphics board, so no additional system memory is needed for
* the triangle representation.
*
* SoHeightFieldGeometry is derived from SoVolumeData and serves a similar purpose
* in the scene graph, providing a reference to an LDM data set which will be
* loaded as needed by rendering nodes, specifically SoHeightFieldRender in this case.
* It also supports an "undefined" value which will be rendered as holes in the grid.
* The geometry is given by the inherited field #fileName. The given file must be
* an LDM file built by the LDM converter (see SoConverter). For use with
* SoHeightFieldRender the data set must have a depth (Z dimension) of exactly 1.
* The undefined value can be specified with the @I -u @i option of the converter or
* explicitly by setting the #undefinedValue field.
*
* Data set values are converted to height values in 3D space in two ways depending
* on the data type:
* - Integer values are normalized between [0,1]  ([-1,1] for signed types)
*   based on the range of values for the specific data type.  For example, for
*   UNSIGNED BYTE values the range 0..255 is mapped to 0..1.
* - Floating point values are not normalized (are used "as is").
*
* In order to avoid holes between tiles when rendering with SoHeightFieldRender,
* the volume must have been converted with a border of at least 1.
*
* Extent in 3D space
*
* A standard SoVolumeData node has no intrinsic "extent" in 3D.  The extent of
* the volume is initially defined by the values returned from the volume reader
* (normally from the extent tag in the LDM file header).  The extent field is
* initialized with these values from the reader and always contains the current
* extent values. The application can modify the extent of the volume by changing
* the values in the extent field. (Note that the actual bounding box of the volume
* in 3D is the volume extent modified by any transform nodes in the scene graph.)
*
* SoHeightFieldGeometry only uses the X and Y parts of the extent field. The Z
* extent of the surface in 3D is completely defined by the values in the data set.
* So the X and Y values in the extent field are the actual extent, but the Z values
* are not meaningful and changing the Z values in the extent field has no effect.
* Note that you can always get the current bounding box (X, Y and Z) using an
* SoGetBoundingBoxAction and you can still control the bounding box using an
* SoTransform (or similar) node. To scale or offset the height values, put a
* transform node in the scene graph before the SoHeightFieldGeometry node.
* For example, to scale the height values by a factor of 2, you could use an
* SoScale node with the scaleFactor field set to (0,0,2).
*
* @FILE_FORMAT_DEFAULT
*    HeightFieldGeometry {
*    @TABLE_FILE_FORMAT
*       @TR undefinedValue             @TD NaN
*       @TR fileName                   @TD ""
*       @TR storageHint                @TD AUTO
*       @TR usePalettedTexture         @TD TRUE
*       @TR texturePrecision           @TD 8
*       @TR useSharedPalettedTexture   @TD TRUE
*       @TR useCompressedTexture       @TD TRUE
*       @TR useExtendedData            @TD FALSE
*       @TR dataSetId                  @TD 1
*       @TR data                       @TD NODATA 0 0 0 UBYTE 8
*    @TABLE_END
*    }
*
* @SEE_ALSO
*    SoHeightFieldRender,
*    SoHeightFieldProperty,
*    SoMultiDataSeparator,
*    SoConverter
*
*/

class VOLUMEVIZ_API SoHeightFieldGeometry : public SoVolumeData
{
  SO_NODE_HEADER( SoHeightFieldGeometry );

public:
  /** Constructor */
  SoHeightFieldGeometry();

  /**
   * Vertices with this value won't be rendered by the SoHeightFieldRender. @BR
   * Default is NaN (Not a Number).
   */
  SoSFDouble undefinedValue;

SoINTERNAL public:
  static void initClass();
  static void exitClass();

  /**
  * Handle field change
  */
  virtual void notify(SoNotList *list);

  /**
   * Return bbox of given tile id.
   * Return false if not available
   */
  virtual bool getBbox(SoLDMTileID tileId, SbBox3f& box);

  /**
   * Apply normalization to given value
   */
  inline double transformHeightValue(double val) const;

  /** Return value at given pos in given data
   * Avoid querying for the tile's data when doing rayPick in SoVolumeStateHeightField
   */
  double getValueD(const SbVec3i32 &pos,
                   SoBufferObject *dataBufferObject,
                   SbBool realValue);

  /** Return true if per tile min/max is available */
  bool hasPerTileMinMax() const;

protected:
  virtual ~SoHeightFieldGeometry();

  /** Fetch undefined value */
  virtual void readChar();

  /** return ((T*)dataPtr)[address] */
  template<typename T> double
  getValue(void* dataPtr, int64_t address);

  //Set if an undefinedValue was defined
  virtual void setUseUserUndefinedValue(bool useUserUndefinedValue);

private:
  /**
  * If user set its own undefined value, use it until a filename change
  * happens
  */
  bool m_useUserUndefinedValue;
};


/*******************************************************************************/
double
SoHeightFieldGeometry::transformHeightValue(double val) const
{
  return m_type.normalize(val);
}

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif // SO_HEIGHTFIELD_GEOMETRY_H
