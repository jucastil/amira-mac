/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  SO_HEIGHTFIELD_PROPERTY_H
#define  SO_HEIGHTFIELD_PROPERTY_H

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#pragma warning(disable:4996)
#endif

#include <VolumeViz/nodes/SoVolumeData.h>

#include <Inventor/fields/SoMFDouble.h>
#include <Inventor/fields/SoSFFloat.h>

/**
* @VREXT Height field property node.
*
* @ingroup VolumeVizNodes
*
* @DESCRIPTION
* SoHeightFieldProperty defines a set of values on a uniform grid in the XY plane
* that can be used to color an SoHeightFieldGeometry when rendered using an
* SoHeightFieldRender node.
*
* SoHeightFieldProperty is derived from SoVolumeData and serves a similar purpose
* in the scene graph, providing a reference to an LDM data set which will be
* loaded as needed by rendering nodes, specifically SoHeightFieldRender in this case.
* The property data is given using the inherited field #fileName.
* The given file must be an LDM file built by the LDM converter (see SoConverter).
*
* Multiple SoHeightFieldProperty nodes can be inserted in a scene graph and combined
* together in the GPU to do render compositing. However the default fragment shader 
* only handles one property (the first one).  To combine multiple properties use a 
* custom shader program (see SoVolumeShader and the example program).
*
* Note that it is not necessary (or useful) to set the inherited extent field.
* SoHeightFieldRender will use the extent associated with the SoHeightFieldGeometry node.
*
* @FILE_FORMAT_DEFAULT
*    HeightFieldProperty {
*    @TABLE_FILE_FORMAT
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
*    SoHeightFieldGeometry,
*    SoMultiDataSeparator,
*    SoConverter
*
*
*/

class VOLUMEVIZ_API SoHeightFieldProperty : public SoVolumeData
{
  SO_NODE_HEADER( SoHeightFieldProperty );

public:
  SoHeightFieldProperty();

SoINTERNAL public:
  static void initClass();
  static void exitClass();

  /**
   * Returns bbox of given tile id.
   * Returns false if not available
   */
  virtual bool getBbox(SoLDMTileID tileId, SbBox3f& box);

protected:
  virtual ~SoHeightFieldProperty();

private:
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif // SO_HEIGHTFIELD_PROPERTY_H
