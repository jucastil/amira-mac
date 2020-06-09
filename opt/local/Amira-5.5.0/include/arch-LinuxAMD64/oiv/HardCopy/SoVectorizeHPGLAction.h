/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef __SO_VECTORIZE_HPGL_ACTION_
#define __SO_VECTORIZE_HPGL_ACTION_

#include <HardCopy/SoVectorizeAction.h>

/**
 * @HCEXT Class used to write vector formatted files in HPGL/2 format.
 * 
 * @ingroup HardCopy
 * 
 * @DESCRIPTION
 *   This class is used for writing vector formatted files in HPGL/2 language 
 *   format. 
 *   It provides some convenience functions for handling files. An instance of 
 *   SoHPGLVectorOutput is contained in an SoVectorizeHPGLAction; this is 
 *   typically the only instance needed.
 * 
 */

class HARDCOPY_API SoHPGLVectorOutput : public SoVectorOutput
{

 public:

  /**
   * Constructor. The default constructor writes to stdout. 
   */
  SoHPGLVectorOutput();

  /**
   * Destructor. 
   * The destructor closes any files opened by the SoHPGLVectorOutput.
   */
  virtual ~SoHPGLVectorOutput();
};

/**
 * @HCEXT Realizes the vectorization of a scene graph to a file in HPGL/2 format.
 * 
 * @ingroup HardCopy
 * 
 * @DESCRIPTION
 *   This class is used for vectorizing scene graphs to HPGL/2 format files. 
 *   It contains an SoHPGLVectorOutput instance which writes by default to 
 *   standard output. 
 *   Methods on SoHPGLVectorOutput can be called to specify what file to 
 *   write to.
 * 
 */

class HARDCOPY_API SoVectorizeHPGLAction : public SoVectorizeAction {

  SO_ACTION_HEADER(SoVectorizeHPGLAction);

 public:

  /**
   * Constructor.
   */
  SoVectorizeHPGLAction();

  /**
   * Destructor.
   */
  virtual ~SoVectorizeHPGLAction();

#ifdef OIV_NET_DOC
  /**
  * Returns the reference to SoHPGLVectorOutput instance in action.
  */

#else
  /**
  * Returns the pointer to SoHPGLVectorOutput instance in action.
  */

#endif //OIV_NET_DOC
  SoHPGLVectorOutput *getHPGLVectorOutput() const;

  /**
   * @deprecated use getHPGLVectorOutput().
   * @DEPRECATED_SINCE_OIV 6.0
   */
  SoHPGLVectorOutput *getOutput() const;

SoINTERNAL public:
  /**
   * Internally used to initialize the class.
   */
  static void initClass();
  static void exitClass();

 protected:
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
                          const SbColor color,
                          const SbString& font_name, 
                          float font_size, 
                          const SbString& string, 
                          int justif, 
                          float angle);

  // Print the border and the background
  virtual void printBorder();
  virtual void printBackground();
  
 protected:
  // Write header and footer
  virtual void writeHeader();
  virtual void writeFooter();
  
  // Set hardware clipping
  virtual void setHardwareClip();

  // Compute clipping limits
  SbBox2f getClippingLimits() const;

 private:
  // Miscellaneous methods

  void assignColor(SbColor color, float linewidth, int *pen_color);
  
  // data
  int           m_currentColor;
  EndLineStyle  m_currentLineEndStyle;
  JoinLineStyle m_currentLineJoinsStyle;
  float         m_currentMiterLimit;
  float         m_currentThickness;
  u_short       m_currentLinePattern;
  int           m_currentPatternScaleFactor;
  float         m_scaleFont;
  SbString      m_fontname;
  int           m_justification;
  float         m_textAngle;
};


/*****************************************************************************/

#endif //__SO_VECTORIZE_HPGL_ACTION_

