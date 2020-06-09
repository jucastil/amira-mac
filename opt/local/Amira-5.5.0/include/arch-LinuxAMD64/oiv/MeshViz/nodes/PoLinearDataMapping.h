/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_LINEAR_DATA_MAPPING_
#define  _PO_LINEAR_DATA_MAPPING_

#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFColor.h>

#include <MeshViz/nodes/PoDataMapping.h>

class SoFieldSensor ;

/**
 * @DTEXT  Node class to define a linear data mapping.
 * 
 * @ingroup MeshVizMisc
 * 
 * @DESCRIPTION
 *   This node defines the current data mapping for all subsequent MeshViz
 *   representations which use it.
 *   There is no data mapping until a PoDataMapping node is traversed.
 * 
 *   This node defines a linear association between colors, transparencies and 
 *   floating-point values. In other words, this association is defined by 2 
 *   functions F(c,v) and F(c,t):
 * <PRE>
 *       F(c,v)(V) = C (with c being a color and v being a value).
 *       F(t,v)(V) = T (with t being a transparency and v being a value).
 * </PRE>
 *    F(c,v) and F(t,v) are linear, so only two values (value1 and value2), 
 *    two associated transparencies (transparency1,transparency2) and two associated 
 *    colors (color1 and color2) define these functions. 
 *    For a given value vi, its color ci is determined by linear 
 *    interpolation between (value1,color1) and (value2,color2). Idem for the 
 *    transparencies.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoLinearDataMapping {
 *    @TABLE_FILE_FORMAT
 *       @TR value1 @TD 0
 *       @TR color1 @TD 0 0 0
 *       @TR transparency1 @TD 0
 *       @TR value2 @TD 1
 *       @TR color2 @TD 1 1 1
 *       @TR transparency2 @TD 0
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

class MESHVIZ_API PoLinearDataMapping : public PoDataMapping {
  SO_NODE_HEADER(PoLinearDataMapping) ;


 public:

  /* Fields */

  /**
   * Defines the first value of the linear data mapping.
   */
  SoSFFloat value1 ;

  /**
   * Defines the first color of the linear data mapping.
   */
  SoSFColor color1 ;

  /**
   * Defines the first transparency of the linear data mapping.
   */
  SoSFFloat transparency1 ;

  /**
   * Defines the second value of the linear data mapping.
   */
  SoSFFloat value2 ;

  /**
   * Defines the second color of the linear data mapping.
   */
  SoSFColor color2 ;

  /**
   * Defines the second transparency of the linear data mapping.
   */
  SoSFFloat transparency2 ;

  /* Methods */

  /**
   * Constructor.
   */
  PoLinearDataMapping() ;

  /**
   * Returns the color associated to a value.
   */
  virtual const SbColor* getColor(float value) ;

  /**
   * Returns the color and transparency associated to a value.
   */
  virtual const SbColor* getColor(float value, float &transparency) ;

  /*----------------------------------------------------------------------------*/
 SoEXTENDER public:
  virtual void  doAction(SoAction *action) ;

 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  virtual ~PoLinearDataMapping() ;
  virtual void updateDataMapping() ;

 private:
  static void fieldChangedCB(void *data, SoSensor *) ;

  SbBool        m_isFieldChanged ;
  SoFieldSensor *value1Sensor ;
  SoFieldSensor *color1Sensor ;
  SoFieldSensor *transparency1Sensor ;
  SoFieldSensor *value2Sensor ;
  SoFieldSensor *color2Sensor ;
  SoFieldSensor *transparency2Sensor ;
  
} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_LINEAR_DATA_MAPPING_  */

