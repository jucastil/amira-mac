/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_DATA_MAPPING_
#define  _PO_DATA_MAPPING_

#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFColor.h>

#include <MeshViz/nodes/PoNode.h>

class PbDataMapping ;
class SoFieldSensor ;

/**
 * @DTEXT  Abstract base class for all data mapping nodes.
 * 
 * @ingroup MeshVizMisc
 * 
 * @DESCRIPTION
 *    This node is the abstract base class for all data mapping nodes.
 *    Data mapping defines an association between 
 *    colors, transparencies and floating-point values. Giving transparencies is
 *    not compulsory. When they are not given, they are supposed to be equal to 0
 *    , i.e. each color is opaque.
 *    
 *    Whatever data mapping, two threshold values can be defined, minThreshold 
 *    and maxThreshold. One color (minThresholdColor) and one transparency 
 *    (minThresholdTransparency) are associated to minThreshold. 
 *    As well, maxThresholdColor and maxThresholdTransparency are associated to 
 *    maxThreshold. 
 *    For a given value vi <= minThreshold, the associated color
 *    ci is minThresholdColor and the associated transparency ti is 
 *    minThresholdTransparency. 
 *    As well, for a given value vi >= maxThreshold, the associated color ci is 
 *    maxThresholdColor and the associated transparency ti is 
 *    maxThresholdTransparency.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoDataMapping {
 *    @TABLE_FILE_FORMAT
 *       @TR minThresholdEnabled @TD FALSE
 *       @TR minThreshold @TD 0
 *       @TR minThresholdColor @TD 0 0 0
 *       @TR minThresholdTransparency @TD 0.0
 *       @TR maxThresholdEnabled @TD FALSE
 *       @TR maxThreshold @TD 1
 *       @TR maxThresholdColor @TD 0 0 0
 *       @TR maxThresholdTransparency @TD 0.0
 *       @TR transparencyEnabled @TD FALSE
 *       @TR transparencyValueDeletedParts @TD 0.95
 *    @TABLE_END
 *    }
 * 
 * 
 */

class MESHVIZ_API PoDataMapping : public PoNode {
  SO_NODE_ABSTRACT_HEADER(PoDataMapping) ;


 public:

  /* Fields */

  /**
   * Defines if the minimum threshold is enable.
   */
  SoSFBool  minThresholdEnabled ;

  /**
   * Minimum threshold value.
   */
  SoSFFloat minThreshold ;

  /**
   * Color associated to values <= minThreshold.
   */
  SoSFColor minThresholdColor ;

  /**
   * Transparency associated to values <= minThreshold.
   */
  SoSFFloat minThresholdTransparency ;



  /**
   * Defines if the maximum threshold is enable.
   */
  SoSFBool  maxThresholdEnabled ;

  /**
   * Maximum threshold value.
   */
  SoSFFloat maxThreshold ;

  /**
   * Color associated to values >= maxThreshold.
   */
  SoSFColor maxThresholdColor ;

  /**
   * Transparency associated to values >= maxThreshold.
   */
  SoSFFloat maxThresholdTransparency ;

  /**
   * Enable/Disable the taking into account of transparency. If it is disable,
   * the different shape are always opaque.
   */
  SoSFBool  transparencyEnabled ;

  /**
   * Each primitive part of which transparency >= transparencyValueDeletedParts, 
   * is deleted.
   */
  SoSFFloat transparencyValueDeletedParts ;

  /* Methods */

  /**
   * Returns the color associated to a value.
   * [OIV-WRAPPER-RETURN-TYPE-VALUE]
   */
  virtual const SbColor* getColor(float value)=0 ;

  /**
   * Returns the color and the transparency associated to a value.
   * [OIV-WRAPPER-RETURN-TYPE-VALUE]
   * [OIVJAVA-WRAPPER NAME{getColorTransparency},PACK{ColorTransparency}]
   */
  virtual const SbColor* getColor(float value, float &transparency)=0 ;

  /*----------------------------------------------------------------------------*/
 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  const PbDataMapping *getDataMapping() { updateDataMapping(); return m_dataMapping;};

 protected:
  PbDataMapping *m_dataMapping ;

  PoDataMapping() ;
  // Constructor.

  virtual ~PoDataMapping() ;
  virtual void updateDataMapping() ;

 private:
  static void minThresholdChangedCB(void *data, SoSensor *) ;
  static void maxThresholdChangedCB(void *data, SoSensor *) ;
  static void transparencyChangedCB(void *data, SoSensor *) ;

  SbBool        m_minThresholdChanged ;
  SoFieldSensor *m_minThresholdEnabledSensor ;
  SoFieldSensor *m_minThresholdSensor ;
  SoFieldSensor *m_minThresholdColorSensor ;
  SoFieldSensor *m_minThresholdTransSensor ;

  SbBool        m_maxThresholdChanged ;
  SoFieldSensor *m_maxThresholdEnabledSensor ;
  SoFieldSensor *m_maxThresholdSensor ;
  SoFieldSensor *m_maxThresholdColorSensor ;
  SoFieldSensor *m_maxThresholdTransSensor ;

  SbBool        m_transparencyChanged ;
  SoFieldSensor *m_transEnabledSensor ;
  SoFieldSensor *m_transValueDeletedPartsSensor ;
} ;
/*----------------------------------------------------------------------------*/

#endif /* _PO_DATA_MAPPING_  */

