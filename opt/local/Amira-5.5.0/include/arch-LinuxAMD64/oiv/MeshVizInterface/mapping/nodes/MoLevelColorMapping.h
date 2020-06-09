/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _MO_LEVELCOLORMAPPING_
#define  _MO_LEVELCOLORMAPPING_

#include <Inventor/fields/SoMFVec4f.h>
#include <Inventor/fields/SoMFFloat.h>

#include <MeshVizInterface/mapping/MoMeshVizDataMapping.h>
#include <MeshVizInterface/mapping/nodes/MoColorMapping.h>
#include <MeshVizInterface/mapping/interfaces/MiColorMapping.h>

#include <MeshVizInterface/implement/colormapping/MbLevelColorMapping.h>

/**
 * @DTEXT  Property node that defines a color mapping with constant color in each interval.
 * 
 * @ingroup MeshIViz_Mapping_Attributes
 * 
 * @DESCRIPTION   
 *   This node specifies a color mapping defined by a set of N  
 *   scalar #values (thus N-1 intervals) and N-1 #colors representing the constant 
 *   color used for values located in each interval.
 *   Thus, for a given value v, Vk <= v <= Vk+1, the associated color is Ck.
 *
 *   Notes:
 *   - The number of colors must be exactly one less than the number of scalars. @n
 *   - If either the number of scalars or the number of colors is zero, the color
 *     mapping is ignored.
 *   - Values less than the first scalar are assigned the first color.
 *   - Values greater than the last value are assigned the last color.
 *
 * @FILE_FORMAT_DEFAULT
 *    LevelColorMapping {
 *    @TABLE_FILE_FORMAT
 *       @TR values             @TD 0
 *       @TR colors             @TD 0,0,0,0
 *       @TR minThresholdEnable @TD FALSE
 *       @TR minThresholdValue  @TD 0
 *       @TR minThresholdColor  @TD 0,0,0,0
 *       @TR maxThresholdEnable @TD FALSE
 *       @TR maxThresholdValue  @TD 0
 *       @TR maxThresholdColor  @TD 0,0,0,0
 *    @TABLE_END
 *    }
 *
 * @ACTION_BEHAVIOR
 *   Sets the current color mapping.  See MoColorMappingElement.
 *
 * @SEE_ALSO
 *    MoCustomColorMapping, MoLinearColorMapping, MoPredefinedColorMapping
 * 
 */
class MESHIVIZDM_API MoLevelColorMapping : public MoColorMapping {

  SO_NODE_HEADER(MoLevelColorMapping) ;
  
 public:

  /**
   * Constructor.  Initially the color mapping is empty and has no effect.
   */
  MoLevelColorMapping() ;

  /** 
   * Contains a set of N scalar values defining the levels of the colormap. Default is empty.
   */
  SoMFFloat values;
   
  /** 
   * Contains a set of N-1 color values defining the constant color of each level. @n
   * Each color consists of R, G, B and A values in the range 0..1. Default is empty.
  */
  SoMFVec4f colors;

  /** 
  * Min Threshold enable flag. @BR
  * When TRUE, values lower than minThresholdValue are displayed using the minThresholdColor.
  * Default is FALSE.
  */
  SoSFBool minThresholdEnable;

  /** 
  * Min Threshold value. Default is 0.
  */
  SoSFFloat minThresholdValue;
  
  /** 
  * Min Threshold color (R, G, B and A values in the range 0..1). Default is transparent black (0,0,0,0).
  */
  SoSFVec4f minThresholdColor;

  /** 
  * Max Threshold enable flag. @BR
  * When TRUE, values higher than maxThresholdValue are displayed using the maxThresholdColor.
  * Default is FALSE.
  */
  SoSFBool maxThresholdEnable;

  /** 
  * Max Threshold value. Default is 0.
  */
  SoSFFloat maxThresholdValue;
  
  /** 
  * Max Threshold color (R, G, B and A values in the range 0..1). Default is transparent black (0,0,0,0).
  */
  SoSFVec4f maxThresholdColor;

  /** 
  * Returns the internal MbLevelColorMapping color mapper
  */
  const MbLevelColorMapping<double,SbColorRGBA>& getColorMapper() const { return m_levelCM ;};

 /*----------------------------------------------------------------------------*/
  SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  
  SoEXTENDER public:
  virtual void  doAction(SoAction *action) ;

 protected:
  virtual ~MoLevelColorMapping() ;

  MbLevelColorMapping<double,SbColorRGBA> m_levelCM;

} ; 

#endif /* _MO_LEVELCOLORMAPPING_  */

