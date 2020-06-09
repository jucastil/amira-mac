/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef __SO_VECTORIZE_ACTION_
#define __SO_VECTORIZE_ACTION_


#include <inttypes.h>
#include <stdio.h>
#include <Inventor/SbBasic.h>
#include <Inventor/SbColor.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/actions/SoAction.h>
#include <Inventor/actions/SoSubAction.h>
#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/elements/SoAnnoText3RenderPrintElement.h>
#ifndef NO_TGS_OIV
#  include <Inventor/nodes/SoImage.h>
#endif
#include <HardCopy/SoHardCopy.h>


#define POINT_TO_MM 0.3527777778F

#ifndef NO_TGS_OIV
class SoMarkerSet;
#endif

class SoNode;
class SoPath;
class SoPathList;
class SoCallbackAction;
class SoPrimitiveVertex;
class SoHLHSRVectorize;

class SoVectorOutput;

/**
 * @HCEXT Abstract class for vectorizing a scene graph to a file.
 * 
 * @ingroup HardCopy
 * 
 * @DESCRIPTION
 *   This class is an abstract class for all vectorize actions. The supported 
 *   subclasses are SoVectorizeCGMAction, SoVectorizeGDIAction (Win32 only),
 *   SoVectorizeHPGLAction, and 
 *   SoVectorizePSAction. 
 *   As with SoWriteAction, these subclasses contain an SoVectorOutput instance (or 
 *   derived) which writes by default to standard output. Methods on
 *   SoVectorOutput can be called to specify what file to write to.
 * 
 * Default values:
 *       - Orientation: #PORTRAIT
 *       - Start position: X=10.0 mm and Y=10.0 mm
 *       - Dimensions: Width=190.0 mm and Height=277.0 mm
 *       - Border width: 2.0 mm
 *       - Border color: (1.,1.,1.)
 *       - Background: no background
 *       - Nominal width: 0.35 mm
 *       - Pixel image size: 0.35mm
 *       - Color Translation method: #REVERSE_ONLY_BLACK_AND_WHITE
 *       - Number of pens: 0
 *       - Color priority: TRUE
 *       - Line End Style: #BUTT_END
 *       - Line Join Style: #NO_JOIN
 *       - Miter limit: 1.5 (Miter Length / Line Width)
 *       - HLHSR mode: #NO_HLHSR
 *       - Lighting enabled: FALSE
 *       - Polygon/Line/Marker offset: 0
 *       - Shade model: #FLAT
 *       - HLHSR raster quality: 0.5
 * 
 *  Line end styles description:
 * 
 * @IMAGE SoVectorizeAction.gif
 *
 * Force black and white rendering: @BR
 * It is possible to force black and white rendering by setting the
 * environment variable OIV_HC_BLACK_AND_WHITE (see SoPreferences).
 * In this mode all non-white colors are set to full black.
 * This is useful because selecting "black & white" in the printer
 * setup dialog normally produces gray scale rendering and some
 * colors may be difficult to see.  This option is applied after
 * color translation (e.g. REVERSE_ONLY_BLACK_AND_WHITE). The variable
 * must be set before creating an instance of the class.
 * 
 * Performance:@BR
 * The HLHSR modes #NO_HLHSR and #HLHSR_SIMPLE_PAINTER are generally quite
 * fast and should be used whenever possible (when the resulting image
 * quality is acceptable or when a quick preview is desired).  The other
 * HLHSR modes involve computations that are very CPU intensive. In other
 * words, the time required to produce an image depends almost entirely on
 * the machine's processor speed. #HLHSR_PAINTER_SURFACE_REMOVAL has a
 * very small dependency on the graphics board (because it does one
 * offscreen render) whereas #HLHSR_RASTER performance is completely linked
 * to the graphics board performance. The other modes are not affected by 
 * the graphics board performance. One implication of the CPU dependency is that the
 * release libraries will generally be much faster than the debug libraries
 * (because of compiler optimizations). Benchmarking should always be done
 * using the release libraries. 
 *
 * Performance is directly related to the
 * number of primitives (individual faces and line segments, not the number
 * of nodes in the scene graph) and the number of intersecting or 
 * difficult-to-sort primitives. Performance decreases rapidly (worse than linear)
 * for large numbers of primitives. Therefore algorithms that can reduce
 * the number of primitives may be needed for large scenes (see, for example,
 * SoSimplifyAction). 
 *
 * In some cases setting a small polygon offset can
 * improve performance by reducing interference between faces and lines 
 * (used only with the Painter's algorithm HLHSR modes).
 *
 * #HIDDEN_LINES_REMOVAL mode is very slow and should not be used unless
 * very precise output is required.
 *
 * Generally #HLHSR_RASTER mode gives the best combination of performance and 
 * image quality.
 * 
 * @B Limitations @b
 *  - Modeling clipping (SoClipPlane) is ignored.
 *  - Textures are ignored (polygons are drawn as if no texture is applied).
 *  - Transparency is ignored.
 *  - SoAnnotation nodes are handled like SoSeparator nodes.
 *  - Smooth shading is only supported with PostScript Level 3.
 *  - VolumeViz representations are not supported (because texturing is not possible).
 *  - FXViz representations are not supported.
 *
 */

class HARDCOPY_API SoVectorizeAction : public SoAction {
  
  SO_ACTION_HEADER_WITH_DEF(SoVectorizeAction);

 public:
   /*
    * Destructor
    */
   virtual ~SoVectorizeAction();

  /**
   *  Dimension unit.
   */
  enum DimensionUnit {
    /**
     *  Inch.
     */
    INCH,  
    /**
     *  Millimeter.
     */
    MM,    
    /**
     *  Meter.
     */
    METER  
  };

  /**
   * Shading models.
   */
  enum ShadeModel {
  /**
   * Flat shading model.
   * Each polygon is filled with a unique color which is the average
   * of the colors associated with each vertex of the original polygon.
   */
    FLAT,

  /**
   * Smooth shading model.
   * Each polygon is filled with shaded colors which are interpolations of
   * of the colors associated with each vertex of the original polygon.
   * NOTE: Only supported with PostScript Level 3 format.
   */
    SMOOTH
  };

  /**
   *  Orientation type.
   */
  enum Orientation {
    /**
     *  The orientation is PORTRAIT.
     */
    PORTRAIT,   
    /**
     *  The orientation is LANDSCAPE.
     */
    LANDSCAPE   
  };

  /**
   *  Color translation methods.
   */
  enum ColorTranslationMethod {
    /**
     *  Only black and white are reversed (default).
     */
    REVERSE_ONLY_BLACK_AND_WHITE,  
    /**
     *  Colors stay as is.
     */
    AS_IS,                         
    /**
     *  All colors are reversed.
     */
    REVERSE                        
  };

  /**
   *  Join line style.
   */
  enum JoinLineStyle {
    /**
     *  There is no line join style.
     */
    NO_JOIN,                
    /**
     *  The line join style is mitered.
     */
    MITERED_JOIN,           
    /**
     *  The line join style is mitered and beveled.     
     */
    MITERED_BEVELED_JOIN,   
    /**
     *  The line join style is beveled.
     */
    BEVELED_JOIN,           
    /**
     *  The line join style is triangular.
     */
    TRIANGULAR_JOIN,        
    /**
     *  The line join style is rounded.
     */
    ROUNDED_JOIN            
  };

  /**
   *  End line style.
   */
  enum EndLineStyle {
    BUTT_END,
    SQUARE_END,
    TRIANGULAR_END,
    ROUND_END
  };


  /**
   *  HLHSR (Hidden Line and Hidden Surface Removal) mode.
   *  For additional info, see #setHLHSRMode.
   */
  enum HLHSRMode {
    /**
     *  No HLHSR is done.
     */
    NO_HLHSR,             
    /**
     *  Simple painter's algorithm is used.
     */
    HLHSR_SIMPLE_PAINTER, 
    /**
     *  Painter's algorithm is used. Interpenetrating primitives are split
     * to provide more correct visual results.
     */
    HLHSR_PAINTER,        
    /**
     *  Surfaces that are completely hidden are removed prior to
     *  application of the painter's algorithm.
     */
    HLHSR_PAINTER_SURFACE_REMOVAL,
    /**
     * A raster-based algorithm is used.
     */
    HLHSR_RASTER,
    /**
     *  The output is rendered with
     *  lines (regardless of the on-screen render style) and hidden
     *  lines are removed.
     */
    HIDDEN_LINES_REMOVAL  
  };
  /*----------------------------------------------------------------------------*/

  /**
   * Output access method
   */

#ifdef OIV_NET_DOC
  /**
  * Returns reference to SoOutput instance in action.
  */

#else
  /**
  * Returns pointer to SoOutput instance in action.
  */

#endif //OIV_NET_DOC
  virtual SoVectorOutput *getVectorOutput() const;

  /**
   * @deprecated use getVectorOutput().
   * @DEPRECATED_SINCE_OIV 6.0
   */
  SoVectorOutput *getOutput() const;

  // Apply methods

  /**
   * Initiates an action on the graph specified by a node.
   */
  virtual void apply(SoNode *node);

  /**
   * Initiates an action on the graph specified by a path.
   */
  virtual void apply(SoPath *path);

  /**
   * Initiates an action on the graph specified by list of paths.
   * TRUE can be passed for the @B obeysRules @b flag if the given path list has the 
   * following four properties:
   *   - All paths have the same head node,
   *   - Paths are sorted in traversal order,
   *   - If one path ends at node A, no other path continues through A,
   *   - No two paths are the same.
   *
   * These rules will be obeyed by path lists returned by picking and by searches 
   * for non-group nodes.
   */
  virtual void apply(const SoPathList &pathList, SbBool obeysRules = FALSE);

#ifdef OIV_NET_DOC
  /**
  * Begin a new page.
  * Allows the user to generate multiple plots per page.  
  */
#else
  /**
  * Begin a new page.
  * Allows the user to generate multiple plots per page.
  * 
  * A typical use is:
  * <PRE> 
  *   SoVectorizePSAction vectPS;
  *   vectPS.beginPage(startPos, pageSize);
  *
  *   Draw the scene graph root1 from the start point
  *   (x1, y1) to the end point(x1+width1, y1+height1)
  *   vectPS.setStartPosition(x1, y1);
  *   vectPS.setDrawingDimensions(width1, height1);
  *   vectPS.setBorder(2.0);
  *   vectPS.apply(root1);
  *
  *   vectPS.setStartPosition(x2, y2);
  *   vectPS.setDrawingDimensions(width2, height2);
  *   vectPS.apply(root2);
  *
  * ,..
  *
  *   vectPS.setStartPosition(xi, yi);
  *   vectPS.setDrawingDimensions(widthi, heighti);
  *   vectPS.apply(rooti);
  *
  *   vectPS.endPage();
  * </PRE>
  */

#endif //OIV_NET_DOC
  virtual void beginPage(const SbVec2f &startPagePosition, 
                         const SbVec2f &pageSize, 
                         DimensionUnit u = MM);

  /**
   * Ends a page.
   * Allows the user to generate multiple plots per page.
   */
  virtual void endPage();

  // Drawing parameters initialisation methods

  /**
   * Sets the dimensions of the drawing on the sheet of paper.
   */
  virtual void setDrawingDimensions(float w, float h, DimensionUnit u = MM);

  /**
   * Sets the dimensions of the drawing on the sheet of paper.
   */
  virtual void setDrawingDimensions(const SbVec2f &d, DimensionUnit u = MM);

  /**
   * Returns the dimensions of the drawing on the sheet of paper.
   */
  virtual SbVec2f getDrawingDimensions(DimensionUnit u = MM) const;

  /**
   * Sets the start position of the drawing on the sheet of paper.
   */
  virtual void setStartPosition(float x, float y, DimensionUnit u = MM);

  /**
   * Sets the start position of the drawing on the sheet of paper.
   */
  virtual void setStartPosition(const SbVec2f &p, DimensionUnit u = MM);

  /**
   * Returns the start position of the drawing on the sheet of paper.
   */
  virtual SbVec2f getStartPosition(DimensionUnit u = MM) const;

  /**
   * Sets the orientation of the drawing on the sheet of paper.
   */
  virtual void setOrientation(Orientation o);

  /**
   * Returns the orientation of the drawing on the sheet of paper.
   */
  virtual Orientation getOrientation() const;

  /**
   * Sets the width of the border of the clipping limits.
   * The color of the border is set to white.
   * If width = 0, there is no border. 
   */
  virtual void setBorder(float width) {
    SbColor color = SbVec3f(1.,1.,1.);
    setBorder(width, color);
  }

  /**
   * Sets the color and the width of the border of the clipping limits. 
   * If width = 0, there is no border.
   */
  virtual void setBorder(float width, SbColor color);

  /**
   * Returns the color and the width of the border of the clipping limits. 
   * If width = 0, there is no border. 
   * [OIV-WRAPPER-ARG OUT,OUT]
   */
  virtual void getBorder(float *w, SbColor *color) const;

  /**
   * Enables or disables the background and sets its color to white.
   * If bg = FALSE, there is no background.
   */
  virtual void setBackgroundColor(SbBool bg) {
    SbColor color = SbVec3f(0.,0.,0.);
    setBackgroundColor(bg, color);
  }

  /**
   * Sets the color of the background. 
   * If bg = FALSE, there is no background.
   */
  virtual void setBackgroundColor(SbBool bg, SbColor color);

  /**
   * Returns the color of the background. 
   * [OIV-WRAPPER-ARG OUT]
   */
  virtual SbBool getBackgroundColor(SbColor *color) const;

  /**
   * Sets the nominal width.
   * For sizes specified in "points" (equals 1/72 inch), 
   * specifies the physical size of the "point" on the hard copy output.
   * One printer point is equal to w units where units are
   * millimeters, meters, inches.
   * By default 1 printer point equals approximately 0.3527 millimeters.
   * Used for the following attributes: line width, point size, text size,
   * and text space.
   */
  virtual void  setNominalWidth(float w, DimensionUnit u = MM);

  /**
   * Returns the nominal width.
   */
  virtual float getNominalWidth(DimensionUnit u = MM) const;

  /** 
   * Sets the line pattern size, i.e.,
   * the association between printer pattern (16 printer "points") 
   * and the size of the line pattern on the hard copy output.
   * One printer pattern is equal to
   *   SoDrawStyleElement::linePatternScaleFactor * w units
   * where units are millimeters, meters, inches.
   * By default one printer pattern equals 5.6444 millimeters (16 * .3527 mm/point).
   * Used for the following attributes: line pattern length.
   */
  virtual void setLinePatternSize(float w, DimensionUnit u = MM);

  /** 
   * Returns the line pattern scale factor.
   */
  virtual float getLinePatternSize(DimensionUnit u = MM) const;

  /**
   * Sets the size of a pixel for image primitives.
   * For sizes specified in pixels, specifies the physical size 
   * of a "pixel" on the hard copy output.
   * One pixel is equal to w units   
   * where units are millimeters, meters, inches.
   * By default 1 pixel equals 0.35 millimeters.
   * Used for the following attributes: images.
   */
  virtual void  setPixelImageSize(float w, DimensionUnit u = MM);

  /**
   * Returns the size of a pixel.
   */
  virtual float getPixelImageSize(DimensionUnit u = MM) const;

  /**
   * Sets the method for choosing the color of the drawing 
   * on the sheet of paper. The default value is 
   * REVERSE_ONLY_BLACK_AND_WHITE.
   * This method is applied for all colors.
   */
  virtual void setColorTranslationMethod(ColorTranslationMethod method);

  /**
   * Returns the method for choosing the color of the drawing on the sheet 
   * of paper.
   */
  virtual ColorTranslationMethod getColorTranslationMethod() const;

  /**
   * Sets the style for line ends.
   */
  virtual void setLineEndStyle(EndLineStyle style); 

  /**
   * Returns the style for line ends.
   */
  virtual EndLineStyle getLineEndStyle() const; 

  /**
   * Sets the style for line joins.
   */
  virtual void setLineJoinsStyle(JoinLineStyle style); 

  /**
   * Returns the style for line joins.
   */
  virtual JoinLineStyle getLineJoinsStyle() const;  

  /**
   * Sets the miter limit.
   */
  virtual void setMiterLimit(float limit);

  /**
   * Returns the miter limit.
   */
  virtual float getMiterLimit() const;

  /**
   * Sets the description of the color and the width of each pen. The function is 
   * useful for pen plotters, but can also be used for raster plotters. 
   * For raster plotters, 
   * the drawing color is the color of the chosen pen. This is useful to force the 
   * plotter to use a set of colors. If the width parameter is not specified, a 0.35 mm 
   * value is assumed.
   * [OIV-WRAPPER-ARG NO_WRAP{(colors != NULL? colors->Length: 0)},ARRAY,ARRAY,IN]
   */
  virtual void setPenDescription(int num_pens, 
                                 const SbColor *colors = 0, 
                                 const float *widths = 0, 
                                 DimensionUnit u = MM);

  /**
   * Returns the description of the color and the width of each pen.
   * [OIV-WRAPPER-ARG ARRAY,ARRAY,IN]
   */
  virtual void getPenDescription(SbColor *colors, 
                                 float *widths, 
                                 DimensionUnit u = MM) const;

  /**
   * Returns the number of pens.
   */
  virtual int getPenNum() const;

  /**
   * Sets the color priority flag. If priority = TRUE, a pen will be chosen 
   * according to its color. Otherwise, it will be chosen according to 
   * its width.
   */
  virtual void   setColorPriority(SbBool priority);

  /**
   * Returns the color priority. 
   */
  virtual SbBool getColorPriority(void) const;

  /**
   * Sets the Hidden Line and Hidden Surface Removal mode. 
   * Possible values of mode:
   *   - #NO_HLHSR. Hidden lines and hidden surfaces are not removed. 
   *
   *   - #HLHSR_SIMPLE_PAINTER. Simple painter's algorithm is used for HLHSR. 
   *     Lines and surfaces are sorted by their maximum Z depth
   *     and displayed in order from front to back
   *     so lines and surfaces that are in the foreground are drawn last.
   *     If the scene contains interpenetrating primitives,
   *     there may be visibility errors in the resulting output.
   *
   *   - #HLHSR_PAINTER. Like the simple painter's algorithm, the primitives
   *     are depth sorted and displayed from front to back.
   *     In addition, some ambiguities where the polygons' Z extents
   *     overlap are resolved. 
   *     Primitives that intersect other primitives are
   *     split and the new pieces sorted to provide more correct
   *     visual results.
   *     This mode is slower than the HLHSR_SIMPLE_PAINTER mode.
   *
   *   - #HLHSR_PAINTER_SURFACE_REMOVAL. This mode is the same as the previous,
   *     but a first pass removes surfaces that are completely hidden. The method 
   *     used to remove
   *     hidden surfaces is a pixel rendering method, so for very small surfaces, some 
   *     accuracy errors can occur. Because some surfaces are removed before the
   *     painter's algorithm is applied, this method can be significantly faster than
   *     the previous one. Generally output files are smaller than using the previous
   *     method.
   *
   *   - #HLHSR_RASTER. A raster image is generated and vectorized to
   *     determine visible primitives.
   *
   *   - #HIDDEN_LINES_REMOVAL. This mode removes all hidden lines.
   *     Whether the screen render style is FILLED or LINES, the output render
   *     style will be lines.
   *     This mode is very slow but gives correct results.
   */
  virtual void setHLHSRMode(HLHSRMode mode)
    { m_HLHSRMode = mode; }

  /**
   * Returns the Hidden Line and Hidden Surface Removal mode. 
   */
  HLHSRMode getHLHSRMode() const 
    { return m_HLHSRMode; }


  //@{
  /**
   * Sets the quality of the raster image generated to vectorize visible 
   * primitives with the #HLHSR_RASTER algorithm.
   * 0 is the worst quality, 1 is the best.
   */
  void setHLHSRRasterQuality(float quality) 
  { m_HLHSRRasterQuality = quality ; }

  /**
   * Returns the raster image quality value. See setHLHSRRasterQuality().
   */

  float getHLHSRRasterQuality() const
  { return m_HLHSRRasterQuality ; }
  //@}

  //@{
  /**
   * Enables/disables the use of OpenGL display lists to generate the raster image
   * with the #HLHSR_RASTER algorithm.
   * Enabled by default.
   */
  void setHLHSRRasterCaching(SbBool enable)
  { m_HLHSRRasterCaching = enable ; }

  /**
   * Returns the raster caching flag. See setHLHSRRasterCaching().
   */

  SbBool getHLHSRRasterCaching() const
  { return m_HLHSRRasterCaching ; }
  //@}

  /**
   * Allows the user to enable/disable the taking into account of lights in the scene 
   * graph during the computation of the vectorized file. 
   * If ...
   *  - flag = FALSE, whatever the light model,  the color of an object is its diffuse 
   *    color.
   *  - flag = TRUE and the light model is PHONG, the color of an object depends 
   *    on its orientation, its material (ambient, diffuse, ..., specular color) and
   *    the lights illuminating the object.
   */
  virtual void enableLighting(SbBool flag)    
    { m_isLightingEnabled = flag; }  

  /**
   * Returns TRUE if lighting is enabled.
   */
  SbBool isLightingEnabled() const
    { return m_isLightingEnabled; }

  /**
   * Selects #FLAT or #SMOOTH shading.
   */
  void setShadeModel(ShadeModel model) 
  { m_shadeModel = model ; }

  /**
   * Returns the shade model.
   */
  ShadeModel getShadeModel() 
  { return m_shadeModel ; }

  /**
   * Method to set the Z offset to be applied to polygons in normalized
   * device coordinates (-1 to 1 space). This is useful for separating coplanar 
   * lines and polygons. Similar to SoPolygonOffset, a positive offset value moves
   * the primitives away from the camera and a negative value pulls them closer.
   * There are separate methods for lines (#setLineOffset) and markers (#setMarkerOffset).
   * The default value for the offset methods is zero. @BR
   * @BR
   * Generally applications should avoid using lines and polygons that
   * are exactly coplanar. Correct results cannot be guaranteed for normal or
   * vectorized rendering. SoPolygonOffset can significantly reduce the problem
   * for normal rendering, but has no effect on vectorized rendering. However a Z
   * offset of approximately 0.01 applied to polygons will usually improve the 
   * appearance of vectorized coplanar primitives. Applying too large an offset
   * may cause the converse visual artifact where lines that should be hidden
   * become visible.
   */
  void setPolygonOffset( float offset )
    { m_polyOffset = offset; }
  /**
   * Sets line offset. See #setPolygonOffset.
   */
  void setLineOffset( float offset )
    { m_lineOffset = offset; }
  /**
   * Sets marker offset. See #setPolygonOffset.
   */
  void setMarkerOffset( float offset )
    { m_markOffset = offset; }
  /**
   * Returns polygon offset. See #setPolygonOffset.
   */
  float getPolygonOffset() const
    { return m_polyOffset; }
  /**
   * Returns line offset. See #setPolygonOffset.
   */
  float getLineOffset() const
    { return m_lineOffset; }
  /**
   * Returns marker offset. See #setPolygonOffset.
   */
  float getMarkerOffset() const
    { return m_markOffset; }

 SoINTERNAL public:

  //@{
  /**
   * Sets the tile size of the raster image generated to vectorize 
   * visible primitives with the #HLHSR_RASTER algorithm.
   * Default is 2048, because standard OpenGL texture is 2048x2048.
   * On several system, it could interesting to decrease tile size to 
   * increase offscreen rendering speed. But the smaller the tile size, 
   * the bigger the vector output.
   */
  void setHLHSRRasterTileSize(unsigned short tileSize) 
  { m_HLHSRRasterTileSize = tileSize ; }

  /**
   * Returns the tile size of the raster image generated to vectorize 
   * visible primitives with the #HLHSR_RASTER algorithm.
   */

  unsigned short getHLHSRRasterTileSize() const
  { return m_HLHSRRasterTileSize ; }
  //@}

  /**
   * Internally used to initialize the class.
   */
  static void initClass();
  static void exitClass();

  /*----------------------------------------------------------------------------*/
 protected:
  SoVectorizeAction();

  // Output data
  SoVectorOutput *m_output;

  // Begin and end of traversal
  virtual void beginTraversal();
  virtual void beginTraversal(SoNode *)
    { beginTraversal(); }
  virtual void endTraversal();
  virtual void endTraversal(SoNode *)
    { endTraversal(); }

  virtual void writeHeader() = 0;
  virtual void writeFooter() = 0;
  
  virtual void setHardwareClip() = 0;

  // Compute clipping limits
  virtual SbBox2f getClippingLimits() const;

  // Printing methods
  virtual void printPolyMark(const SbVec4f *points, 
                             int num_points, 
                             const SbColor *colors, 
                             SbBool color_flag, 
                             float size);
#ifndef NO_TGS_OIV
  virtual void printPolyMark(const SbVec4f *points, 
                             int num_points, 
                             const SbColor *colors, 
                             SbBool color_flag,
                             SoMarkerSet *markerSet);
  virtual void printImage(const SbVec4f &origin, 
                          const unsigned char *imagePixels, 
                          SbVec2s &sourceSize, 
                          SbVec2s &requestedSize, 
                          int numComponents,
                          SoImage::HorAlignment horAlign,
                          SoImage::VertAlignment vertAlign);
#endif

  virtual void printPolyLine(const SbVec4f *points, 
                             int num_points, 
                             const SbColor *colors, 
                             SbBool color_flag,
                             float thickness, 
                             u_short linePattern, 
                             int linePatternScaleFactor = 1);
  virtual void printPolygon(const SbVec4f *points, 
                            int num_points, 
                            const SbColor *colors,
                            SbBool color_flag,
                            const SbString &category, 
                            const SbString &name, 
                            const unsigned char *pattern);
  virtual void printText2(const SbVec4f point, 
                          const SbColor colors,
                          const SbString& font_name, 
                          float font_size, 
                          const SbString& string, 
                          int justif, 
                          float angle);

  // Print the border and the background
  virtual void printBorder() = 0;
  virtual void printBackground() = 0;

  // To choice the good pen and the good associated width.
  virtual void penAssignment(SbColor color, float width, 
                             int *ret_ind, float *ret_width);
  // Viewport methods  
  float getViewportWidth()  const;
  float getViewportHeight() const;
  const SbViewportRegion &getViewportRegion() const;

  // Translate color method(depends on setColorTranslationMethod())
  SbColor translateColor(SbColor color);

  // Access methods in mm
  float getShiftX() const;
  float getShiftY() const;
  float getWidth()  const;
  float getHeight() const;

  // Get offset - Indicate the offset(x,y) to draw a primitive.
  float getOffsetX() const;
  float getOffsetY() const;

  // Miscellaneous methods.
  virtual void prepareAction(SoCallbackAction &action, 
                             SbBool activateSoAnnotationCB = TRUE);
  
  // Data
  // Border and background attributes
  float m_border_width;
  SbColor m_border_color;
  SbBool m_background_flag;
  SbColor m_background_color;
  
  // Nominal width(in millimeters)
  float m_nominal_width;
  // Line pattern scale factor(in millimeters)
  float m_linePatternSize;
  // Pixel image size(in millimeters)
  float m_pixelImageSize;
  
  // Pen description
  int m_num_pens;
  // Array for color in LUT.
  SbColor *m_color_tab;
  
  // End line style
  EndLineStyle m_line_ends_style;
  JoinLineStyle m_line_joins_style;
  float m_miter_limit;
  
  // Existance of a viewport
  SbBool m_isViewportRegionExist;
  
  // Page size(in millimeters)
  SbVec2f m_pageSize;
  
  // Start page position(in millimeters)
  SbVec2f m_startPagePosition;
  
  // Multiplot per page data
  SbBool m_isMultiPlotPerPage;
  SbBool m_isFirstPlotPage;
  
  /*----------------------------------------------------------------------------*/
  
 private:
  // Drawing methods
  void drawTriangle(SoCallbackAction *action,
                    SoPrimitiveVertex *v1,
                    SoPrimitiveVertex *v2,
                    SoPrimitiveVertex *v3);
  void drawLineSegment(SoCallbackAction *action,
                       SoPrimitiveVertex *v1,
                       SoPrimitiveVertex *v2);
  SoCallbackAction::Response sendPoints(SoCallbackAction *action);
  void drawPoint(SoCallbackAction *action,
                 SoPrimitiveVertex *v);
  SoCallbackAction::Response drawText2(SoCallbackAction *action,
                                       const SoNode *node, 
                                       SbBool isAnnoText3 = FALSE);
  SoCallbackAction::Response drawText3(SoCallbackAction *action,
                                       const SoNode *node, 
                                       SbBool isAnnoText3 = FALSE);
  SoCallbackAction::Response drawMarkerSet(SoCallbackAction *action, 
                                           const SoNode *node);
  SoCallbackAction::Response drawImage(SoCallbackAction *action, 
                                       const SoNode *node);

  // Clipping methods
  void clipImage(SoCallbackAction *action, 
                 SbVec4f *points, 
                 const SoNode *node);
  void clipText(SoCallbackAction *action, 
                SbVec4f *points, 
                SbColor color,
                SoNode *node,  
                SbBool isAnnoText3 = FALSE);
  void clipPolygon(SoCallbackAction *action,
                   SbVec4f *points, 
                   int num_points, 
                   SbColor *colors);
  void clipPolyLine(SoCallbackAction *action,
                    SbVec4f *points, 
                    int num_points, 
                    SbColor *colors);
  void clipPolyLineFar(SoCallbackAction *action,
                       SbVec4f *points, 
                       int num_points, 
                       SbColor *colors,
                       int color_flag);
  void clipPolyLineXMin(SoCallbackAction *action,
                        SbVec4f *points, 
                        int num_points, 
                        SbColor *colors,
                        int color_flag);
  void clipPolyLineXMax(SoCallbackAction *action,
                        SbVec4f *points, 
                        int num_points, 
                        SbColor *colors,
                        int color_flag);
  void clipPolyLineYMin(SoCallbackAction *action,
                        SbVec4f *points, 
                        int num_points, 
                        SbColor *colors,
                        int color_flag);
  void clipPolyLineYMax(SoCallbackAction *action,
                        SbVec4f *points, 
                        int num_points, 
                        SbColor *colors,
                        int color_flag);
  void clipPolyMark(SoCallbackAction *action,
                    SbVec4f *points, 
                    int num_points, 
                    SbColor *colors 
#ifndef NO_TGS_OIV
                    , SoMarkerSet *markerSet = NULL
#endif
                    );

  // HLHSR vectorize methods and members
  SoHLHSRVectorize *getHLHSRVectorize() const 
    { return m_HLHSRVectorize; }
  SoHLHSRVectorize *m_HLHSRVectorize;

  // Projects points on the sheet space.
  void projectPoints(SbVec4f *points, int n);

  // Defines the projection source used by projectPoints which defines the 2D space 
  // source used to project points on the sheet space.
  void setProjectionSource(const SbBox2f &projSrc) ;
  void setDefaultProjectionSource() ;

  void transformPoints(SoCallbackAction *action, SbVec4f *points, int n);
  void transformVecMCToVRC(SoCallbackAction *action, SbVec3f &point);
  void transformPointsMCToVRC(SoCallbackAction *action, 
                              SbVec4f *points, int n);
  void transformPointsVRCToNPC(SoCallbackAction *action, 
                               SbVec4f *points, int n);
  SbColor getColor(SoCallbackAction *action, 
                   int index, 
                   SbBool &isFullyTransparent);
  SbColor getLightingColor(SoCallbackAction *action, 
                           const SoPrimitiveVertex *vertex,
                           const SbVec4f &point, 
                           SbBool &isFullyTransparent);
  void  computeLightList(SoState *state);
  void  deleteLightsList();
  float getAttenuationFactor(const SoCallbackAction *action, 
                             const SbVec3f &lightLocation, 
                             const SbVec3f &vertexPoint);
  
  float getNormalizedWidth();
  float getNormalizedHeight();
  float computeFontSizeAngleViewing(SoCallbackAction *action, 
                                    float fontSize, float &angle);

  // Viewport methods    
  void  setViewportRegion(SoCallbackAction *action);
  void  setViewportRegion(const SbViewportRegion &vp) 
  { m_viewportRegion = vp ; }

  // Conversion methods
  static float unitsToMillimeters(float w, DimensionUnit u);
  static float millimetersToUnits(float w, DimensionUnit u);

  // Callbacks
  static void drawTriangleCB(void *object, 
                             SoCallbackAction *action, 
                             SoPrimitiveVertex *v1,
                             SoPrimitiveVertex *v2, 
                             SoPrimitiveVertex *v3);
  static void drawLineSegmentCB(void *object, 
                                SoCallbackAction *action, 
                                SoPrimitiveVertex *v1, 
                                SoPrimitiveVertex *v2);
  static void drawPointCB(void *object, 
                          SoCallbackAction *action, 
                          SoPrimitiveVertex *v);
  static SoCallbackAction::Response drawText2CB(void *object, 
                                                SoCallbackAction *action, 
                                                const SoNode *node);
  static SoCallbackAction::Response drawText3CB(void *object, 
                                                SoCallbackAction *action, 
                                                const SoNode *node);
  static SoCallbackAction::Response drawImageCB(void *object, 
                                                SoCallbackAction *action, 
                                                const SoNode *node);
  static SoCallbackAction::Response sendPointsCB(void *object, 
                                                 SoCallbackAction *action, 
                                                 const SoNode *node);
  static SoCallbackAction::Response drawAnnoText3CB(void *object, 
                                                    SoCallbackAction *action, 
                                                    const SoNode *node);
  static SoCallbackAction::Response endDrawAnnoText3CB(void *, 
                                                       SoCallbackAction *, 
                                                       const SoNode *);
  static SoCallbackAction::Response cameraCB(void *object, 
                                             SoCallbackAction *action, 
                                             const SoNode *node);
  static SoCallbackAction::Response storeAnnotationCB(void *object, 
                                                      SoCallbackAction *action, 
                                                      const SoNode *node);
  
  // Method needed to implement rendering of delayed paths
  void addDelayedPath(SoPath *path);
  void renderDelayedPaths();

  // Data
  // Start position(in millimeters)
  float m_shiftX, m_shiftY;
  Orientation m_orientation;  
  // Drawing dimensions(in millimeters)
  float m_width, m_height;

  // Viewport region
  SbViewportRegion m_viewportRegion;
  
  ColorTranslationMethod m_colorTranslationMethod;
  // Array for line width.
  float *m_pensWidth;
  SbBool m_priority;

  int m_numAlloc;
  int m_numVertices;
  SbVec4f *m_pointList;
  SbColor *m_colorList;
  HLHSRMode m_HLHSRMode;
  float m_HLHSRRasterQuality ;
  SbBool m_HLHSRRasterCaching ;
  unsigned short m_HLHSRRasterTileSize ;
  SbBool m_isAnnoText3Drawn;

  // Lighting data
  SoNodeList m_lightNodesList;
  SbPList m_lightsList;  
  SbBool m_isLightingEnabled;

  // Shading model
  ShadeModel m_shadeModel ;

  // Offset Z value (allows separating coplanar lines and polys)
  float m_polyOffset;
  float m_lineOffset;
  float m_markOffset;

  // Defines the projection source used by projectPoints which defines the 2D space 
  // source used to project points on the sheet space.
  SbBox2f m_projSrc ;

  // Stuff needed to implement rendering of delayed paths
  SoPathList m_delayedPaths; // List of paths to render

  // Friend classes
  friend class SoHLHSRVectorize;
  friend class SoHLHSRImageVectorizer;
};

/**
 * @HCEXT Abstract class used to write vector formatted files.
 * 
 * @ingroup HardCopy
 * 
 * @DESCRIPTION
 *  This is an abstract class for all vectorized outputs.
 * 
 */

class HARDCOPY_API SoVectorOutput
{

 public:

  /**
   * Constructor.
   */
  SoVectorOutput();

  /**
   * Destructor.
   */
  virtual ~SoVectorOutput();

 public:

  /**
   * Sets file pointer to write to.
   */
  virtual void setFilePointer(FILE *newFP);

  /**
   * Returns the file pointer in use.
   */

  virtual FILE *getFilePointer();

#ifdef OIV_NET_DOC
  /**
  * Opens named file and returns false on error.
  *
  * @UNICODE_WARNING
  */

#else
  /**
  * Opens named file, sets file pointer to result. 
  * It returns FALSE on error.
  *
  * @UNICODE_WARNING
  */

#endif //OIV_NET_DOC

  SoNONUNICODE virtual SbBool openFile(const char *file_name);

#ifdef OIV_NET_DOC
  /**
  * Opens named file and returns false on error.
  */

#else
  /**
  * Opens named file, sets file pointer to result. 
  * It returns FALSE on error.
  */

#endif //OIV_NET_DOC

  virtual SbBool openFile( const SbString& file_name );

  /**
   * Closes the current file opened with #openFile().
   */
  virtual void closeFile();

 protected:

  FILE *m_out_file;
};

#endif //__SO_VECTORIZE_ACTION_

