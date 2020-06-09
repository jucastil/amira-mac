/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PB_NON_LINEAR_DATA_MAPPING_
#define  _PB_NON_LINEAR_DATA_MAPPING_

#include <MeshViz/graph/PbDataMapping.h>

/**
 * @DTEXT  Class to define non linear data mapping.
 * 
 * @ingroup MeshVizMisc
 * 
 * @DESCRIPTION
 *    This class is used to define non linear data mapping. This object defines a non 
 *    linear association between colors, transparencies and floating-point values. 
 *    In other words, this association is defined by 2 functions F(c,v) and F(c,t):
 * <PRE>
 *       F(c,v)(V) = C (with c being a color and v being a value).
 *       F(t,v)(V) = T (with t being a transparency and v being a value).
 * </PRE>
 *    F(c,v) and F(t,v) are given by the user. If they are not given by the user, 
 *    default one are used. The default F(c,v) computes a linear data mapping 
 *    between black and white. The default F(c,t) returns always 0.
 * 
 */
class MESHVIZ_API PbNonLinearDataMapping : public PbDataMapping {

 public:

  /**
  * [OIV-WRAPPER-RETURN-TYPE VALUE]
  */
  typedef const SbColor* RGBFunction(void* userData, float);

  /**
   * [OIV-WRAPPER-RETURN-TYPE ARRAY{3},COPY]
   */
  typedef const float* HLSFunction(void* userData, float);

  typedef float TransparencyFunction(void* userData, float);

  /**
   * Default constructor.
   */
  PbNonLinearDataMapping() ;

  /**
   * Sets a non linear function for data mapping. This function returns a RGB color.
   * [OIV-WRAPPER EVENT_NAME{RGBMapping}]
   */
  void setRGBFunction(RGBFunction* func, void* userData) ;

  /**
   * deprecated.
   * [OIV-WRAPPER-NO-WRAP]
   */
  void setRGBFunction(const SbColor* (*func)(float)) ;

  /**
   * Sets a non linear function for data mapping. This function returns a HLS color.
   * [OIV-WRAPPER EVENT_NAME{HLSMapping}]
   */
  void setHLSFunction(HLSFunction* func, void* userData) ;

  /**
   * deprecated.
   * [OIV-WRAPPER-NO-WRAP]
   */
  void setHLSFunction(const float* (*func)(float)) ;

  /**
   * Sets a function returning a transparency value. If no function is set, a 
   * default function is used (returning always 0.0).
   * [OIV-WRAPPER EVENT_NAME{TransparencyMapping}]
   */
  void setTransparencyFunction(TransparencyFunction* func, void* userData) ;

  /**
   * deprecated.
   * [OIV-WRAPPER-NO-WRAP]
   */
  void setTransparencyFunction(float (*func)(float));

  /*---------------------------------------------------------------------------*/
 PoINTERNAL public:
  virtual ClassType getClassType() const
    { return NON_LINEAR_DATA_MAPPING1 ;}

 private:

  const SbColor* computeColor(float value) const;
  const SbColor* computeColor(float value, float &transparency) const;
  
  static const SbColor* defaultColorFunc(float value) ;
  // Default color function

  static float defaultTransparencyFunction(float value) ;
  // Default transp. function

  const   SbColor* (*m_RGBFunc)(float) ;
  const   float* (*m_HLSFunc)(float) ;
  float (*m_TransparencyFunc)(float) ;
  
  const   SbColor* (*m_RGBFunc2)(void*, float) ;
  const   float* (*m_HLSFunc2)(void*, float) ;
  float (*m_TransparencyFunc2)(void*, float) ;
  
  void * m_RGBUserData;
  void * m_HLSUserData;
  void * m_TransparencyUserData;
} ;

/*----------------------------------------------------------------------------*/

#endif /* _PB_NON_LINEAR_DATA_MAPPING_  */

