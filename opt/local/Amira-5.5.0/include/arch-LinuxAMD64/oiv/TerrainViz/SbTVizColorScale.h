/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : C. OGNIER (Feb 2001)
**=======================================================================*/

#ifndef SBTVIZCOLORSCALE_H
#define SBTVIZCOLORSCALE_H

#include <Inventor/SbLinear.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/SbColor.h>


/**
 *
 * @TVEXT Class to manage colorscales
 * 
 * @ingroup TerrainViz
 * 
 * @DESCRIPTION
 *   This class manages a list of altitudes and a corresponding color list.
 *   
 *   Colors are mapped onto the terrain using the altitude scale.
 *   For N colors, N+1 altitudes must be supplied.
 *   Extreme colors are mapped for data outside the given limits (high and low).
 *
 *   @IMAGE DTM_colorscale.jpg
 *
 *  
 *   If no colors are supplied, white is used.
 *  
 *   Two modes are available: 
 *    - TVIZ_SHADING (default) uses OpenGL shading on every vertex.
 *    - TVIZ_CONTOURING maps colors by contouring.
 * 
 * @SEE_ALSO
 *    SbTVizRegularGridData,
 *    SoTViz,
 *    SoTVizRender
 * 
 * 
 */ 



class TERRAINVIZ_API SbTVizColorScale {

  public :

    enum ColorMode {
      /**
       * Colorscale is smoothed.
       */    
      TVIZ_SHADING = 0,
      /**
       * Colorscale is applied by contouring.
       */    
      TVIZ_CONTOURING
    };


  /**
   * Constructor.
   */
  SbTVizColorScale();


  /**
   * 
   * Constructor by copy.
   */
  SbTVizColorScale(const SbTVizColorScale& colorScale);


  /**
   * Destructor.
   */
  virtual ~SbTVizColorScale();


  /**
   * Sets the color array. This array should be one element shorter
   * than the altitudes array.
   */
  void setColors(int numColors, const SbColor* colors);

  
  /**
   * Returns the color array.
   */
  const SbColor* getColors() const;


  /**
   * Returns the color array length.
   */
  int  getNumColors() const;

  /**
   * Sets the altitude array. This array should be one element longer than the colors array.
   * The array must be sorted by increasing values.
   */
  void setAltitudes(int numAltitudes, const float* altitudes);

  /**
   * Returns the altitude array.
   */
  const float* getAltitudes() const;
        
  /**
   * Returns the altitude array length.
   */
  int  getNumAltitudes() const;
        
  /**
   * Sets the lower and upper colors used for the extreme low and high values.
   * The default upper extreme color is white, the default lower extreme color
   * is black.
   */
  void setExtremeColors(SbColor& lowerColor, SbColor& upperColor);

  /**
   * Returns the lower and upper colors used for extreme values.
   */
  void getExtremeColors(SbColor& lowerColor, SbColor& upperColor) const;

  /**
   * Returns the color at the specified height.
   */
  void getColor(float altitude, SbColor& color) const;


  /**
   * Sets the color mode.
   */
  void setColorMode(ColorMode colorMode);

  /**
   * Returns the color mode.
   */
  ColorMode getColorMode() const;
    



 SoINTERNAL public:
  void rotate(double angle);
  void resetChangeFlag() {m_changeFlag = FALSE;};
  SbBool hasChanged() {return m_changeFlag;};

  private :
  SbBool    m_changeFlag;
  ColorMode m_colorMode;
  int       m_numColors;
  int       m_numAltitudes;
  float*    m_altitudes;
  SbColor*  m_colors;
  SbColor   m_defaultUpperColor;
  SbColor   m_defaultLowerColor;  
};

#endif
