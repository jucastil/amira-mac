/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_NON_LINEAR_DATA_MAPPING_
#define  _PO_NON_LINEAR_DATA_MAPPING_

#include <MeshViz/nodes/PoDataMapping.h>

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
 *   and floating-point values. 
 *   In other words, this association is defined by 2 functions F(c,v) and F(c,t):
 * <PRE>
 *       F(c,v)(V) = C (with c being a color and v being a value).
 *       F(t,v)(V) = T (with t being a transparency and v being a value).
 * </PRE>
 *    F(c,v) and F(t,v) are given by the user. If they are not given by the user, 
 *    default one are used. The default F(c,v) computes a linear data mapping 
 *    between black and white. The default F(c,t) returns always 0.
 * 
 */

class MESHVIZ_API PoNonLinearDataMapping : public PoDataMapping {
  SO_NODE_HEADER(PoLinearDataMapping) ;


 public:

  /**
   * Color callback prototype.
   * [OIV-WRAPPER-NO-WRAP]
   */
  typedef const SbColor* PoDataMappingColorCB(float value) ;

  /**
   * Color callback prototype.
   * [OIV-WRAPPER NAME{ColorFunction}]
   * [OIV-WRAPPER-RETURN-TYPE VALUE]
   */
  typedef const SbColor* PoDataMappingColorCB2(void* userData, float value) ;

  /**
   * Transparency callback prototype.
   * [OIV-WRAPPER-NO-WRAP]
   */
  typedef          float PoDataMappingTransparencyCB(float value) ;

  /**
   * Transparency callback prototype.
   * [OIV-WRAPPER NAME{TransparencyFunction}]
   */
  typedef          float PoDataMappingTransparencyCB2(void* userData, float value) ;

  /**
   * Constructor.
   */
  PoNonLinearDataMapping() ;

  /**
   * Sets pointer to a callback function which computes a color from a real
   * value.
   * [OIV-WRAPPER EVENT_NAME{ColorMapping}]
   */
  void setColorFunction(PoDataMappingColorCB2 *func, void* userData) ;

  /**
   * Deprecated.
   * [OIV-WRAPPER-NO-WRAP]
   */
  void setColorFunction(PoDataMappingColorCB *func) ;

  /**
   * Sets pointer to a callback function which computes a transparency from
   * a real value.
   * [OIV-WRAPPER EVENT_NAME{TransparencyMapping}]
   */
  void setTransparencyFunction(PoDataMappingTransparencyCB2 *func, void* userData) ;

  /**
   * Deprecated.
   * [OIV-WRAPPER-NO-WRAP]
   */
  void setTransparencyFunction(PoDataMappingTransparencyCB *func) ;

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
  virtual ~PoNonLinearDataMapping() ;
} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_NON_LINEAR_DATA_MAPPING_  */


