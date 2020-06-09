/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_NON_LINEAR_DATA_MAPPING2_
#define  _PO_NON_LINEAR_DATA_MAPPING2_

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoMFColor.h>

#include <MeshViz/nodes/PoDataMapping.h>

class SoFieldSensor ;

/**
 * @DTEXT  Node class to define a non linear data mapping.
 * 
 * @ingroup MeshVizMisc
 * 
 * @DESCRIPTION
 *   This node defines the current data mapping for all subsequent MeshViz
 *   representations which use it.
 *   There is no data mapping until a PoDataMapping node is traversed.
 * 
 *   This node defines a non linear association between colors, transparencies
 *    and floating-point values. In other words, this association is defined by 2 
 *    functions F(c,v) and F(c,t):
 * <PRE>
 *       F(c,v)(V) = C (with c being a color and v being a value).
 *       F(t,v)(V) = T (with t being a transparency and v being a value).
 * </PRE>
 *    There are two ways to express F(c,v)(V):
 * 
 *    - F(c,v)(V) is non linear, but linear per level, so a list of values sorted in 
 *    increasing order and a list of colors associated define this function. Thus, the 
 *    association is (V1,C1), (V2,C2),...,(Vn,Cn) with V1 < V2 <...< Vn.
 *    For a given value vi, Vk <= vi <= Vk+1, the associated color ci is determined by a 
 *    linear interpolation between (Vk,Ck) and (Vk+1,Ck+1).
 *    
 *    - F(c,v)(V) is defined by level, so a list of n values sorted in increasing order and 
 *    a list of n+1 colors associated define this function. Thus, the association is C1, 
 *    (V1,C2), (V2,C3),...,(Vn,Cn+1) with V1 < V2 <...< Vn. For a given value vi, Vk <= vi 
 *    < Vk+1, the associated color ci is Ck+1. If vi < V1, the associated color ci is C1.
 *    In the two methods, the list of values is sorted in increasing order (and the 
 *    associated colors also). 
 * 
 *    There are as well, two ways to express F(t,v)(V)
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoNonLinearDataMapping2 {
 *    @TABLE_FILE_FORMAT
 *       @TR type @TD LINEAR_PER_LEVEL
 *       @TR value @TD 0
 *       @TR color @TD 0 0 0
 *       @TR transparency @TD 0
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

class MESHVIZ_API PoNonLinearDataMapping2 : public PoDataMapping {
  SO_NODE_HEADER(PoLinearDataMapping2) ;


 public:

  /**
   *  Data mapping type
   */
  enum Type {
    /**
     *  The data mapping is non linear per level.
     */
    NON_LINEAR_PER_LEVEL, 
    /**
     *  The data mapping is non linear but linear per level.
     */
    LINEAR_PER_LEVEL      
  } ;

  /* Fields */

  /**
   * Defines the type of data mapping.
   */
  SoSFEnum  type ;

  /**
   * Defines the list of values for the data mapping
   */
  SoMFFloat value ;

  /**
   * Defines the list of colors for the data mapping.
   * The number of colors must be >= the number of values + 1 if
   * the type is NON_LINEAR_PER_LEVEL and >= the number of values
   * otherwise.
   */
  SoMFColor color ;

  /**
   * Defines the list of transparencies for the data mapping.
   * To be taken into account the number of transparencies must be
   * equal to the number of colors, otherwise transparencies are ignored.
   */
  SoMFFloat transparency ;

  /* Methods */

  /**
   * Constructor.
   */
  PoNonLinearDataMapping2() ;

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
  virtual ~PoNonLinearDataMapping2() ;
  virtual void updateDataMapping() ;

 private:
  static void fieldChangedCB(void *data, SoSensor *) ;

  SbBool        m_isFieldChanged ;
  SoFieldSensor *m_typeSensor ;
  SoFieldSensor *m_valueSensor ;
  SoFieldSensor *m_colorSensor ;
  SoFieldSensor *m_transparencySensor ;
  
} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_NON_LINEAR_DATA_MAPPING2_ */

