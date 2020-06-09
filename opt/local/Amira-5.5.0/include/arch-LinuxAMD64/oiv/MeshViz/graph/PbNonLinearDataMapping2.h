/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PB_NON_LINEAR_DATA_MAPPING2_
#define  _PB_NON_LINEAR_DATA_MAPPING2_

#include <MeshViz/graph/PbDataMapping.h>

/**
 * @DTEXT  Class to define non linear data mapping.
 * 
 * @ingroup MeshVizMisc
 * 
 * @DESCRIPTION
 *    This object defines a non linear association between colors, transparencies
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
 *    associated colors also). By default, F(c,v)(V) is linear by level 
 *    (LINEAR_PER_LEVEL), the number of colors and values is 2 with V1=0, V2=0, 
 *    C1=(0,0,0) (black) and C2=(1,1,1) (white).
 * 
 *    There are as well, two ways to express F(t,v)(V)
 * 
 */
class MESHVIZ_API PbNonLinearDataMapping2 : public PbDataMapping {

 public:

  /**
   *  Type of data mapping.
   */
  enum Type {
    NON_LINEAR_PER_LEVEL,
    LINEAR_PER_LEVEL
  } ;



  /**
   * Default constructor.
   */
  PbNonLinearDataMapping2() ;

  /**
   * Copy constructor.
   */
  PbNonLinearDataMapping2(const PbNonLinearDataMapping2 &nonLinearDataMap2) ;

  /**
   * Destructor.
   */
  ~PbNonLinearDataMapping2() ;

  /**
   * Assignment operator.
   */
  PbNonLinearDataMapping2& operator=(const PbNonLinearDataMapping2 &nonLinearDataMap2) ;

  /**
   * Sets non linear function for data mapping, with RGB color.
   * If type = NON_LINEAR_PER_LEVEL, the number of colors must be equal to numValues + 1, 
   * otherwise it must be equal to numValues.
   * [OIV-WRAPPER-ARG IN,NO_WRAP{type == Types::NON_LINEAR_PER_LEVEL? c->Length-1: c->Length},ARRAY,ARRAY]
   */
  void setValues(Type type, int numValues, const float *v, const SbColor *c) ;

  /**
   * Sets non linear function for data mapping, with RGB color and transparencies.
   * If type = NON_LINEAR_PER_LEVEL, the number of colors and transparencies must be equal to numValues + 1, 
   * otherwise it must be equal to numValues.
   * [OIV-WRAPPER-ARG IN,NO_WRAP{type == Types::NON_LINEAR_PER_LEVEL? c->Length-1: c->Length},ARRAY,ARRAY,ARRAY]
   */
  void setValues(Type type, int numValues, const float *v, const SbColor *c, const float *t) ;

  /**
   * Sets non linear function for data mapping, with HLS color.
   * If type = NON_LINEAR_PER_LEVEL, the number of colors must be equal to numValues + 1, 
   * otherwise it must be equal to numValues.
   * [OIV-WRAPPER-CUSTOM-CODE]
   */
  void setValues(Type type, int numValues, const float *v, const PbHLSColor *c) ;

  /**
   * Sets non linear function for data mapping, with HLS color and transparencies.
   * If type = NON_LINEAR_PER_LEVEL, the number of colors and transparencies must be equal to numValues + 1, 
   * otherwise it must be equal to numValues.
   * [OIV-WRAPPER-CUSTOM-CODE]
   */
  void setValues(Type type, int numValues, const float *v, const PbHLSColor *c, const float *t) ;

  /**
   * Gets the list of values defining the current non linear data mapping.
   * [OIV-WRAPPER-ARG NO_WRAP]
   * [OIV-WRAPPER-RETURN-TYPE ARRAY{numValues}]
   */
  const float*      getValuesList(int &numValues) const  { numValues = m_nbValues ; return m_valuesList ; }

  /**
   * Gets the list of RGB colors defining the current non linear data mapping.
   * [OIV-WRAPPER-ARG NO_WRAP]
   * [OIV-WRAPPER-RETURN-TYPE ARRAY{numColors}]
   */
  const SbColor*    getRGBColorsList(int &numColors) const  { numColors = m_nbColors ; return m_colorsList ;}

  /**
   * Gets the list of HLS colors defining the current non linear data mapping.
   * [OIV-WRAPPER-CUSTOM-CODE]
   */
  const PbHLSColor* getHLSColorsList(int &numColors) ;

  /**
   * Gets the list of transparencies defining the current non linear data mapping.
   * [OIV-WRAPPER-ARG NO_WRAP]
   * [OIV-WRAPPER-RETURN-TYPE ARRAY{num_transparency}]
   */
  const float *     getTransparencyList(int &num_transparency) const  { num_transparency = m_nbColors ; return m_transparencyList ;}

  /**
   * Returns the data mapping type.
   */
  Type getType() const
    { return m_typeMapping ; }

  /*---------------------------------------------------------------------------*/
 PoINTERNAL public:
  virtual ClassType getClassType() const
    { return NON_LINEAR_DATA_MAPPING2 ;}

 private:
  // Used by constructor per copy and affectation operator
  void copy(const PbNonLinearDataMapping2 &nonLinearDataMap2, SbBool isConstructorPerCopy) ;

  const SbColor* computeColor(float value) const;
  const SbColor* computeColor(float value, float &transparency) const;

  void sortColorsValues() ;
  void sortColorsTransparenciesValues();

  SbColor    *m_colorsList ;
  float      *m_valuesList ;
  float      *m_transparencyList;
  PbHLSColor *m_hlsList ;
  int        m_nbColors, m_nbValues ; 
  Type       m_typeMapping ;
} ;

/*----------------------------------------------------------------------------*/

#endif /* _PB_NON_LINEAR_DATA_MAPPING2_  */

