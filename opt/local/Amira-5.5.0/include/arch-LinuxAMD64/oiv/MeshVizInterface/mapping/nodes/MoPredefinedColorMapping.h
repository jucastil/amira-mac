/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _MO_PREDEFINEDCOLORMAPPING_
#define  _MO_PREDEFINEDCOLORMAPPING_

#include <Inventor/fields/SoMFVec4f.h>

#include <MeshVizInterface/mapping/MoMeshVizDataMapping.h>
#include <MeshVizInterface/mapping/nodes/MoColorMapping.h>
#include <MeshVizInterface/mapping/interfaces/MiColorMapping.h>

class MbPredefinedColorMapping;

/**
* @DTEXT  Property node that selects a predefined color mapping.
* 
* @ingroup MeshIViz_Mapping_Attributes
* 
* @DESCRIPTION
* The range of the scalar values must be given to adjust the color map to the scalar set. 
* If a value is less than #minValue, the first color in the map is used.
* If a value is greater than #maxValue, the last color in the map is used.
* If a value is between #minValue and #maxValue, linear interpolation is used
* to determine the color.
*
* @FILE_FORMAT_DEFAULT
*    PredefinedColorMapping {
*    @TABLE_FILE_FORMAT
*       @TR minValue           @TD 0
*       @TR maxValue           @TD 1
*       @TR predefColorMap     @TD NONE
*    @TABLE_END
*    }
*
* @ACTION_BEHAVIOR
*   Sets the current color mapping.  See MoColorMappingElement.
*
* @SEE_ALSO
*   MoCustomColorMapping, MoLevelColorMapping, MoLinearColorMapping
* 
*/
class MESHIVIZDM_API MoPredefinedColorMapping : public MoColorMapping {

  SO_NODE_HEADER(MoPredefinedColorMapping) ;

public:

  /**
  * Constructor.  The initial color map is NONE (node has no effect).
  */
  MoPredefinedColorMapping() ;

  //@{
  /**
  * The min and max values defining the range of scalar values.
  * Default values are 0 and 1.
  */
  SoSFFloat minValue;
  SoSFFloat maxValue;
  //@}

  /**
  * Predefined colormaps.
  */
  enum PredefColorMapping{
    NONE,           /**< Turn off color mapping (Default value)*/
    GREY,           /**< Greyscale color map */
    TEMPERATURE,    /**< Temperature color map */
    PHYSICS,        /**< Physics color map */
    STANDARD,       /**< Standard color map */
    GLOW,           /**< Glow color map */
    BLUE_RED,       /**< Blue to Red color map */
    SEISMIC,        /**< Seismic color map */
    BLUE_WHITE_RED, /**< Blue to White to Red color map */
    INTENSITY       /**< Intensity color map */
   } ;

  /**
   * Predefined color map to use.
   * Use enum #PredefColorMapping. Default is NONE.
   *
   *    @TABLE_0B
   *       @TR NONE           @TD Default (node is ignored)
   *       @TR GREY or GRAY   @TD @IMAGE grayColorMap.jpg
   *       @TR TEMPERATURE    @TD @IMAGE temperatureColorMap.jpg
   *       @TR PHYSICS        @TD @IMAGE physicsColorMap.jpg
   *       @TR STANDARD       @TD @IMAGE standardColorMap.jpg
   *       @TR GLOW           @TD @IMAGE glowColorMap.jpg
   *       @TR BLUE_RED       @TD @IMAGE blue_redcolormap.jpg
   *       @TR SEISMIC        @TD @IMAGE seismicColorMap.jpg
   *       @TR BLUE_WHITE_RED @TD @IMAGE blue_white_redcolormap.jpg
   *       @TR INTENSITY      @TD @IMAGE intensityColorMap.jpg
   *    @TABLE_END
   *
   * NOTE: The checkerboard pattern shows through where the color map alpha (opacity)
   * value is less than 1.0.
  */
  SoSFEnum predefColorMap;

  /**
  * Retrieves the interface to the color mapping object. 
  */
  const MiColorMapping<double,SbColorRGBA>* getColorMapping();

  /*----------------------------------------------------------------------------*/
  SoINTERNAL public:
  static void initClass() ;
  static void exitClass() ;

  typedef std::map<MoPredefinedColorMapping::PredefColorMapping,MbPredefinedColorMapping*>  PredefColorMappingMap;


  SoEXTENDER public:
  virtual void  doAction(SoAction *action) ;

protected:
  virtual ~MoPredefinedColorMapping() ;


  PredefColorMappingMap* m_predefColorMapping;

} ; 

#endif /* _MO_PREDEFINEDCOLORMAPPING_  */

