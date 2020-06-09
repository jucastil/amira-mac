/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef __SO_VECTORIZE_PS_ACTION_
#define __SO_VECTORIZE_PS_ACTION_

#include <HardCopy/SoVectorizeAction.h>

/**
 * @HCEXT Class used to write vector formatted files in PostScript format.
 * 
 * @ingroup HardCopy
 * 
 * @DESCRIPTION
 *   This class is used for writing vector formatted files in Adobe PostScript format. 
 *   It provides some convenience functions for handling files. An instance of 
 *   SoPSVectorOutput is contained in an SoVectorizePSAction; this is typically the 
 *  only instance needed.
 * 
 */

class HARDCOPY_API SoPSVectorOutput : public SoVectorOutput {

 public:

  /**
   * Constructor. The default constructor writes to stdout. 
   */
  SoPSVectorOutput();

  /**
   * Destructor. The destructor closes any files opened by the 
   * SoPSVectorOutput.
   */
  virtual ~SoPSVectorOutput();

  /**
   * Sets the colored output flag. By default, the flag is set to TRUE.
   */
  void setColored(SbBool flag = TRUE) 
    { m_color = flag; }

  /**
   * Gets the colored output flag. 
   */
  SbBool getColored() const 
    { return m_color; }

  //@{
  /**
   * Sets the PostScript language level. Supported levels range from 1 to 3.
   * The default level is 2.
   * With levels 1 and 2, only flat shading is supported whereas with 
   * level 3 and higher, smooth shading is supported. 
   * See also SoVectorizeAction::setShadeModel().
   *
   */
  void setLevel(unsigned int level) ;

  /**
   * Returns the PostScript language level.
   */
  unsigned int getLevel() const
  { return m_langLevel ; }
  //@}

  //@{
  /**
   * Sets the factor used to compute the accuracy of all real numeric values.
   * The default value is 0.1.
   *
   * In order to reduce the PostScript file size, all real numeric values are stored
   * as integer values.
   * The formula used to compute an integer value from a real numeric value is the following:
   *
   * Integer part of (realValue / (0.24 * NumericAccuracyFactor)) + 0.5
   * 
   * All integer values are globally scaled by 0.24 * NumericAccuracyFactor.
   * Thus this factor allows you to specify higher or lower accuracy,
   * which will have a significant influence
   * on the size of the resulting file.
   * The range of this factor is usually 0.01 <= NumericAccuracyFactor <= 1.0
   */
  void setNumericAccuracyFactor(float factor) 
  { m_numericAccuracyFactor = factor ; } 
  /**
   * 
   * Returns the factor used to compute the accuracy of all real numeric values.
   * See setNumericAccuracyFactor() for details.
   */

  float getNumericAccuracy() const
  { return m_numericAccuracyFactor ;}
  //@}

 private:

  SbBool        m_color;
  unsigned int  m_langLevel ;
  float         m_numericAccuracyFactor ;


};

/**
 * @HCEXT Realizes the vectorization of a scene graph to a file in PostScript format.
 * 
 * @ingroup HardCopy
 * 
 * @DESCRIPTION
 *   This class is used for vectorizing scene graphs to PostScript format files. It 
 *   contains an SoPSVectorOutput instance which writes by default to standard 
 *   output. Methods on SoPSVectorOutput can be called to specify what file to 
 *   write to.
 *  
 *  LIMITATIONS:
 *    - End line style TRIANGULAR is not supported; end line style ROUND is 
 *      assumed instead.
 *    - Join line style NONE, MITERED_BEVELED, and TRIANGULAR are not 
 *      supported; join line styles BEVELED, MITERED, and ROUNDED are 
 *      assumed instead.
 *    - For LANDSCAPE orientation, the start position is the upper-left 
 *      corner.
 *
 * 
 */

class HARDCOPY_API SoVectorizePSAction : public SoVectorizeAction {
  
  SO_ACTION_HEADER(SoVectorizePSAction);

 public:

  /**
   * Constructor.
   */
  SoVectorizePSAction();

  /**
   * Destructor.
   */
  virtual ~SoVectorizePSAction();

#ifdef OIV_NET_DOC
  /**
  * Returns reference to SoPSVectorOutput instance in action.
  */

#else
  /**
  * Returns pointer to SoPSVectorOutput instance in action.
  */

#endif //OIV_NET_DOC
  SoPSVectorOutput *getPSVectorOutput() const; 

  /**
   * @deprecated use getPSVectorOutput().
   * @DEPRECATED_SINCE_OIV 6.0
   */
  SoPSVectorOutput *getOutput() const; 

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

 private:
  // Miscellaneous methods
#ifndef NO_TGS_OIV
  void   createBitmap(int markerIndex, const SbVec2s &size);
  SbBool isBitmapExist(int markerIndex);
#endif
  void assignColor(SbColor color, float linewidth);
  void pcp079( char* buffer );

  void writePixel(unsigned char pixel);
  void initWritePixel();
  void initDefaultCurrentValues();

  // data
  int           m_numCreatedBitmaps;
  int           m_createdBitmaps[1000];
  int           m_currentBitmapIndex;
  SbVec3s       m_currentColor;
  float         m_currentPointSize;
  float         m_currentThickness;
  u_short       m_currentLinePattern;
  int           m_currentPatternScaleFactor;
  float         m_scaleFont;
  SbString      m_fontname;
  int           m_numWritenPixels;
  int           m_currentPattableIndex;
  int           m_nbPattableIndex;
  unsigned int  m_langLevel ;
  SbBool        m_gouraudShadingPossible ;

  float         m_scaleNumVal ;

  // For Pattern
  SbPList       m_patternList;
};


//*****************************************************************************

#endif //__SO_VECTORIZE_PS_ACTION_

