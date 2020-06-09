/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PB_DATA_MAPPING_
#define  _PB_DATA_MAPPING_

#include <MeshViz/graph/PbBase.h>

#include <Inventor/SbColor.h>

/**
 * @DTEXT  Abstract class for data mapping.
 * 
 * @ingroup MeshVizMisc
 * 
 * @DESCRIPTION
 *    Data mapping defines an association between 
 *    colors, transparencies and floating-point values. Giving transparencies is
 *    not compulsory. When they are not given, they are supposed to be equal to 0
 *    , i.e. each color is opaque.
 *    
 *    Whichever data mapping, two threshold values can be defined, threshold_min 
 *    and threshold_max. One color (cmin) and one transparency (transp_min) are 
 *    associated to threshold_min . As well, cmax and transp_max are associated 
 *    to threshold_max. For a given value vi <= threshold_min, the associated color
 *    ci is cmin and the associated transparency ti is transp_min. As well, for 
 *    a given value vi >= threshold_max, the associated color ci is cmax and the
 *    associated transparency ti is transp_max.
 *    
 *    By default min and max thresholds are disabled, threshold_min = 0 and 
 *    threshold_max = 1 and no color is associated to threshold_min and 
 *    threshold_max. Each part of primitive of which transparency is greater or
 *    equal 0.95 is deleted. This default value can be changed by the method
 *    setTransparencyValueDeletedParts().
 * 
 */

class MESHVIZ_API PbDataMapping : public PbBase {

 public:

  typedef float PbHLSColor[3] ;



  /**
   * Default constructor.
   */
  PbDataMapping() ;

  /**
   * Destructor.
   */
  ~PbDataMapping() ;

  /**
   * Copy constructor.
   */
  PbDataMapping(const PbDataMapping  &dataMapping) ;

  /**
   * Assignment operator.
   */
  PbDataMapping& operator=(const PbDataMapping &dataMapping) ;

  /**
  * Gets RGB color associated to a value. If the returned value is NULL, 
  * this means that there is no color associated to this value.
  * [OIV-WRAPPER-RETURN-TYPE VALUE]
  */
  const SbColor *getRGBColor(float value) const;

  /**
  * Gets HLS color associated with a value. If the returned value is NULL, 
  * this means that there is no color associated with this value.
  * [OIV-WRAPPER-RETURN-TYPE ARRAY{3},COPY]
  */
  const float   *getHLSColor(float value) const;

  /**
  * Gets the RGB color and the transparency associated with a value. 
  * If the returned value is NULL, this means that there is no color 
  * associated to this value.
  * [OIV-WRAPPER-RETURN-TYPE-VALUE]
  */
  const SbColor *getRGBColor(float value, float &transparency) const;

  /**
  * Gets the HLS color and the transparency associated to a value.
  * If the returned value is NULL, this means that there is no color 
  * associated to this value.
  * [OIV-WRAPPER-RETURN-TYPE ARRAY{3},COPY]
  */
  const float   *getHLSColor(float value, float &transparency) const;

  

  /**
   * Sets a minimum threshold. No color is associated to this threshold.
   */
  void setMinThreshold(float threshold_min) ;

  /**
   * Sets a minimum threshold, associated to a RGB color and a transparency value.
   */
  void setMinThreshold(float threshold_min, const SbColor &cmin, float transp_min=0.0) ;

  /**
   * Sets a minimum threshold, associated to a HLS color and a transparency value.
   * [OIV-WRAPPER-ARG IN,WRAP_AS{const float *}&ARRAY{3},IN]
   */
  void setMinThreshold(float threshold_min, PbHLSColor cmin, float transp_min=0.0) ;

  /**
   * Sets a maximum threshold. No color is associated to this threshold.
   */
  void setMaxThreshold(float threshold_max) ;

  /**
   * Sets a maximum threshold, associated to a RGB color and a transparency value.
   */
  void setMaxThreshold(float threshold_max, const SbColor &cmax, float transp_max=0.0) ;

  /**
   * Sets a maximum threshold, associated to a HLS color and a transparency value.
   * [OIV-WRAPPER-ARG IN,WRAP_AS{const float *}&ARRAY{3},IN]
   */
  void setMaxThreshold(float threshold_max, PbHLSColor cmax, float transp_max=0.0) ;

  /**
   * Gets the minimum threshold and its associated RGB color. 
   * NULL is returned if no color is associated to this threshold.
   * [OIV-WRAPPER-RETURN-TYPE-VALUE]
   * [OIVJAVA-WRAPPER PACK{RGBThreshold}]
   */
  const SbColor* getMinRGBThreshold(float &threshold_min) const ;

  /**
   * Gets the minimum threshold and its associated HLS color. 
   * NULL is returned if no color is associated to this threshold.
   * [OIV-WRAPPER-RETURN-TYPE ARRAY{3},COPY]
   */
  const float*   getMinHLSThreshold(float &threshold_min) const ;

  /**
   * Gets the minimum threshold, its associated RGB color and transparency.
   * NULL is returned if no color is associated to this threshold.
   * [OIV-WRAPPER-RETURN-TYPE-VALUE]
   */
  const SbColor* getMinRGBThreshold(float &threshold_min, float &transp_min) const ;

  /**
   * Gets the minimum threshold, its associated HLS color and transparency.
   * NULL is returned if no color is associated to this threshold.
   * [OIV-WRAPPER-RETURN-TYPE ARRAY{3},COPY]
   */
  const float*   getMinHLSThreshold(float &threshold_min, float &transp_min) const ;

  /**
   * Gets the maximum threshold and its associated RGB color. 
   * NULL is returned if no color is associated to this threshold.
   * [OIV-WRAPPER-RETURN-TYPE-VALUE]
   * [OIVJAVA-WRAPPER PACK{RGBThreshold}]
   */
  const SbColor* getMaxRGBThreshold(float &threshold_max) const ;

  /**
   * Gets the maximum threshold and its associated HLS color. 
   * NULL is returned if no color is associated to this threshold.
   * [OIV-WRAPPER-RETURN-TYPE ARRAY{3},COPY]
   */
  const float*   getMaxHLSThreshold(float &threshold_max) const ;

  /**
   * Gets the maximum threshold, its associated RGB color and transparency.
   * NULL is returned if no color is associated to this threshold.
   * [OIV-WRAPPER-RETURN-TYPE-VALUE]
   */
  const SbColor* getMaxRGBThreshold(float &threshold_max, float &transp_max) const ;

  /**
   * Gets the maximum threshold, its associated HLS color and transparency.
   * NULL is returned if no color is associated to this threshold.
   * [OIV-WRAPPER-RETURN-TYPE ARRAY{3},COPY]
   */
  const float*   getMaxHLSThreshold(float &threshold_max, float &transp_max) const ;

  /**
   * Enable/Disable the taking into account of threshold values.
   */
  void enableThresholds(SbBool min, SbBool max) ;

  /**
   * Returns min=TRUE if the minimum threshold is enabled, otherwise FALSE. Idem with max.
   */
  void thresholdsEnabled(SbBool &min, SbBool &max) const
    { min = m_minEnabled ; max = m_maxEnabled ;}

  /**
   * Enable/Disable the taking into account of transparency. If it is disable,
   *  the different shape are always opaque.
   */
  void enableTransparency(SbBool flag);

  /**
   * Returns TRUE if transparency is enabled, otherwise FALSE
   */
  SbBool isTransparencyEnabled() const
    { return m_transparencyEnabled ; }

  /**
   * Sets a value that defines the following property : each primitive part 
   * of which transparency >= value, is deleted. value = 0.95 by default.
   */
  void setTransparencyValueDeletedParts(float value);

  /**
   * Gets a value that defines the following property : each primitive part 
   * of which transparency >= value, is deleted.
   */
  float getTransparencyValueDeletedParts() const; 

  /*---------------------------------------------------------------------------*/


 PoINTERNAL public:
  // Data mapping type
  enum ClassType {
    DATA_MAPPING,
    LINEAR_DATA_MAPPING,
    NON_LINEAR_DATA_MAPPING1,
    NON_LINEAR_DATA_MAPPING2
  } ;

  virtual ClassType getClassType() const 
    { return DATA_MAPPING ; }

  uint32_t getId() const { return m_uniqueId; }

 protected:
  // Notify a change to all connected objects 
  void notifyChange();
  
  // Compute a color interpolation 
  // Interpolation between (c1, v1) and (c2, v2) for a vi value
  // vi is updated.
  static void  colorInterpolation(const SbColor &c1, float v1, 
                                  const SbColor &c2, float v2, 
                                  float vi, SbColor *ci) ;
  static void  colorInterpolation(const SbColor &c1, float t1, float v1, 
                                  const SbColor &c2, float t2, float v2, 
                                  float vi, SbColor *ci, float &ti) ;
  static void transparencyInterpolation(float t1, float v1, 
                                        float t2, float v2, 
                                        float vi, float ti) ;

  float   m_transparencyValueDeletedParts;
  SbColor *m_colorValue ;
  virtual const SbColor* computeColor(float value) const=0;
  virtual const SbColor* computeColor(float value, float &transparency) const=0;
  SbBool  m_transparencyEnabled;

  // Unique id for this node.
  uint32_t    m_uniqueId;

 private:
  static  uint32_t sm_nextUniqueId;

  // Used by constructor per copy and affectation operator
  void copy(const PbDataMapping &dataMapping, SbBool isConstructorPerCopy) ;

  float   m_thresholdMin, m_thresholdMax, m_transparencyMin, m_transparencyMax;
  SbColor m_colorMin, m_colorMax ;
  SbBool  m_minEnabled, m_maxEnabled, m_isMinColor, m_isMaxColor;
} ;

/*----------------------------------------------------------------------------*/

#endif /* _PB_DATA_MAPPING_ */



