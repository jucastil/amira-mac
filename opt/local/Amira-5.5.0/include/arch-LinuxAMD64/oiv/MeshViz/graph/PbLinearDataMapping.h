/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PB_LINEAR_DATA_MAPPING_
#define  _PB_LINEAR_DATA_MAPPING_

#include <MeshViz/graph/PbDataMapping.h>

/**
 * @DTEXT  Class to define linear data mapping.
 * 
 * @ingroup MeshVizMisc
 * 
 * @DESCRIPTION
 *    This class is used to define linear data mapping. This object defines a linear 
 *    association between colors, transparencies and floating-point values. In 
 *    other words, this association is defined by 2 functions F(c,v) and F(c,t):
 * <PRE>
 *       F(c,v)(V) = C (with c being a color and v being a value).
 *       F(t,v)(V) = T (with t being a transparency and v being a value).
 * </PRE>
 *    F(c,v) and F(t,v) are linear, so only two values (v1 and v2), two associated
 *    transparencies(t1,t2) and two associated colors (c1 and c2) define these
 *    functions. For a given value vi, its color ci is determined by linear 
 *    interpolation between (v1,c1) and (v2,c2). Idem for the transparencies.
 *    By default v1=0, v2=0, c1=(0,0,0) (black), c2=(1,1,1) (white), t1=t2=0.0 
 *    (opaque).
 * 
 */
class MESHVIZ_API PbLinearDataMapping : public PbDataMapping {

 public:

  /**
   * Default constructor.
   */
  PbLinearDataMapping() ;

  /**
   * Copy constructor.
   */
  PbLinearDataMapping(const PbLinearDataMapping &linearDataMap) ;

  /**
   * Assignment operator.
   */
  PbLinearDataMapping& operator=(const PbLinearDataMapping  &linearDataMap) ;

  /**
   * Sets values v1,v2 and the associated RGB colors c1, c2.
   */
  void setValues(float v1, const SbColor &c1, float v2, const SbColor &c2) ;

  /**
   * Sets values v1,v2, the associated transparecny t1,t2, and the associated RGB colors c1, c2.
   */
  void setValues(float v1, const SbColor &c1, float t1, float v2, const SbColor &c2, float t2) ;

  /**
   * Sets values v1,v2 and the associated HLS colors c1, c2.
   * [OIV-WRAPPER-ARG IN,WRAP_AS{const float *}&ARRAY{3},IN,WRAP_AS{const float *}&ARRAY{3}]
   */
  void setValues(float v1, const PbHLSColor c1, float v2, const PbHLSColor c2) ;

  /**
   * Sets values v1,v2, the associated transparecny t1,t2, and the associated HLS colors c1, c2.
   * [OIV-WRAPPER-ARG IN,WRAP_AS{const float *}&ARRAY{3},IN,IN,WRAP_AS{const float *}&ARRAY{3},IN]
   */
  void setValues(float v1, const PbHLSColor c1, float t1, float v2, const PbHLSColor c2, float t2) ;

  /**
   * Gets the current values v1,v2 and the associated RGB colors c1, c2.
   * [OIVJAVA-WRAPPER NAME{getRGBValues},PACK{RGBMapping}]
   */
  void getValues(float &v1, SbColor &c1, float &v2, SbColor &c2) const ;

  /**
   * Gets the current values v1,v2, the associated transparecny t1,t2, and the associated RGB colors c1, c2.
   * [OIVJAVA-WRAPPER NAME{getRGBAValues},PACK{RGBTransparencyMapping}]
   */
  void getValues(float &v1, SbColor &c1, float &t1, float &v2, SbColor &c2, float &t2) const ;

  /**
   * Gets the current values v1,v2 and the associated HLS colors c1, c2.
   * [OIV-WRAPPER-ARG OUT,WRAP_AS{float *}&ARRAY{3},OUT,WRAP_AS{float *}&ARRAY{3}]
   * [OIVJAVA-WRAPPER NAME{getHLSValues},PACK{HLSMapping}]
   */
  void getValues(float &v1, PbHLSColor c1, float &v2, PbHLSColor c2) const ;

  /**
   * Gets the current values v1,v2, the associated transparecny t1,t2, and the associated HLS colors c1, c2.
   * [OIV-WRAPPER-ARG OUT,WRAP_AS{float *}&ARRAY{3},OUT,OUT,WRAP_AS{float *}&ARRAY{3},OUT]
   * [OIVJAVA-WRAPPER NAME{getHLSAValues},PACK{HLSTransparencyMapping}]
   */
  void getValues(float &v1, PbHLSColor c1, float &t1, float &v2, PbHLSColor c2, float &t2) const ;

  /*---------------------------------------------------------------------------*/
 PoINTERNAL public:
  virtual ClassType getClassType() const
    { return LINEAR_DATA_MAPPING ;}

 private:
  // Used by constructor per copy and affectation operator
  void copy(const PbLinearDataMapping &linearDataMap, SbBool isConstructorPerCopy) ;

  const SbColor* computeColor(float value) const;
  const SbColor* computeColor(float value, float &transparency) const;

  float   m_val1, m_val2, m_transparency1, m_transparency2;
  SbColor m_color1, m_color2  ;
} ;
/*----------------------------------------------------------------------------*/

#endif /* _PB_LINEAR_DATA_MAPPING_ */

