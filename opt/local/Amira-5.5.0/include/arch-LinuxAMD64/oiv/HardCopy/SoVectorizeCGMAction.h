/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef __SO_VECTORIZE_CGM_ACTION_
#define __SO_VECTORIZE_CGM_ACTION_

#include <HardCopy/SoVectorizeAction.h>

/**
 * @HCEXT  Class used to write vector formatted CGM files.
 * 
 * @ingroup HardCopy
 * 
 * @DESCRIPTION
 *  This class is used for writing vector formatted files in CGM format. 
 *  It provides some convenience functions for handling files. An instance of 
 *  SoCGMVectorOutput is contained in an SoVectorizeCGMAction; this is typically
 *  the only instance needed.
 *  
 *  The environment variable OIV_CGM_HARDCOPY_BUFSIZE
 *  specifies the buffer size in bytes for storing CGM calls before writing 
 *  them to the disk. The default buffer size is 1048576 bytes (1 megabyte).
 *  If set to 1, no buffering is done.
 * 
 */

class HARDCOPY_API SoCGMVectorOutput : public SoVectorOutput
{

 public:

  /**
   * Constructor. The default constructor writes to stdout. 
   */
  SoCGMVectorOutput ();

  /**
   * Destructor. The destructor closes any files opened by the 
   * SoCGMVectorOutput.
   */
  virtual ~SoCGMVectorOutput ();

 public:

#ifdef OIV_NET_DOC
	 /**
	 * Opens named file, and 
	 * returns false on error.
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
	 SoNONUNICODE virtual SbBool openFile(const char* file_name);

#ifdef OIV_NET_DOC
	 /**
	 * Opens named file, and 
	 * returns false on error.
	 */

#else
	 /**
	 * Opens named file, sets file pointer to result. 
	 * It returns FALSE on error.
	 */

#endif //OIV_NET_DOC
	 virtual SbBool openFile( const SbString& file_name );

 public:

  /**
   * Sets the output mode. This mode can be clear text encoding or binary 
   * mode encoding. 
   * The default mode is clear text encoding.
   */
  void setBinary(SbBool flag = TRUE)
    { m_binary = flag; }

  /**
   * Gets the output mode.
   */
  SbBool isBinary() const 
    { return m_binary; }

 public:

  /**
   * Sets the version of the output CGM file. The default version is 1.
   *   - When the version of CGM is less than 3, the setLineEndStyle(), 
   *     getLineEndStyle(), setLineJoinStyle(), 
   *     getLineJoinStyle(), setMiterLimit(), and getMiterLimit() methods
   *     have no effect on the output. 
   *   - In versions 1 and 2 of CGM, dashed line patterns are default 
   *     patterns defined by CGM (solid, dash, dot, dash-dot, dash-dot-dot).
   *
   */
  void setVersion(int vers = 1)
    { m_cgm_version = vers; }

  /**
   * Gets the version of the output CGM file. 
   */
  int getVersion() const
    { return m_cgm_version; }

 public:

  /**
   * Sets the color mode. The default color mode is Indexed and the 
   * other mode is Direct (RGB).
   */
  void setIndexed(SbBool flag = TRUE)
    { m_indexed = flag; }

  /**
   * Gets the color mode.
   */
  SbBool isIndexed() const
    { return m_indexed; }
 private:
  SbBool m_binary;
  int    m_cgm_version;
  SbBool m_indexed;
};

/**
 * @HCEXT Realizes the vectorization of a scene graph to a file in CGM format.
 * 
 * @ingroup HardCopy
 * 
 * @DESCRIPTION
 *  This class is used for vectorizing scene graphs to CGM format files. 
 *  It contains an SoCGMVectorOutput instance which writes by default to 
 *  standard output. 
 *  Methods on SoCGMVectorOutput can be called to specify what file to 
 *  write to.
 * 
 *  LIMITATIONS:
 *  - setOrientation() has no effect for CGM format. 
 *  - The orientation is translator dependent. 
 *
 * 
 */

class HARDCOPY_API SoVectorizeCGMAction : public SoVectorizeAction {
  
  SO_ACTION_HEADER(SoVectorizeCGMAction);

 public:

  /**
   * Constructor.
   */
  SoVectorizeCGMAction();

  /**
   * Destructor.
   */
  virtual ~SoVectorizeCGMAction();

#ifdef OIV_NET_DOC
  /**
  * Returns reference to SoCGMVectorOutput instance in action.
  */

#else
  /**
  * Returns pointer to SoCGMVectorOutput instance in action.
  */

#endif //OIV_NET_DOC
  SoCGMVectorOutput *getCGMVectorOutput() const; 

  /**
   * @deprecated use getCGMVectorOutput().
   * @DEPRECATED_SINCE_OIV 6.0
   */
  SoCGMVectorOutput *getOutput() const; 

SoINTERNAL public:
  /**
   * Internally used to initialize the class.
   */
  static void initClass();
  static void exitClass();

  /*****************************************************************************/


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
  virtual void writeHeader ();
  virtual void writeFooter ();

  // Set hardware clipping
  virtual void setHardwareClip();

  // Compute clipping limits
  SbBox2f getClippingLimits() const;
  
 private:
  // Miscellaneous methods
  void assignColor(SbColor color, 
                   float linewidth, 
                   int *pen_color, 
                   SbColor *return_colors);
  void PWriteChar(unsigned int c_param);
  void PWriteWord(unsigned int word);
  char *RSHORT(int i, float r);
  void Pbegmf(const SbString& name);
  void Pmfversion(int version);
  void Pmfdesc(const SbString& description);
  void Pmfelemlist(const SbString& names);
  void Pvdctype(int type);
  void Pintegerprec(int minint, int maxint);
  void Prealprec(double minreal, double maxreal, int digits);
  void Pindexprec(int minint,int maxint);
  void Pcolrindexprec(int maxin);
  void Pcolrvalueext(int br, int bg, int bb, int wr, int wg, int w);
  void Pmaxcolrindex(int maxind);
  void Pcolrprec(int maxcomp);
  void Pfontlist(int nfont, const SbString font[]);
  void Pbegpic(const SbString& name);
  void Pscalemode(int specmode,double factor);
  void Plinewidth(double width);
  void Plinewidthmode(int width);
  void Pmarkersizemode(int mode);
  void Pedgewidth(double width);
  void Pedgewidthmode(int mode);
  void Pbackcolr(float r, float g, float b);
  void Pcolrmode(int colourmode);
  void Pbegpicbody();
  void Pvdcrealprec(double minreal, double maxreal, int digits);
  void Pvdcext(float x_min, float y_min, float size_x, float size_y);
  void Pedgevis(int sw);
  void Pendmf();
  void Pendpic();
  int  PStrLen(const SbString& str);
  void Plinecap_join(int cap, int join, float limit);
  void Plineedgetype(int index, float size, int nbdash, int *dash);
  void Plinecolr(int colour);
  void Plinecolr(SbColor colour);
  void Pline(int n, const SbVec4f *points);
  void Pcolrtable(int index, int ncol, SbColor *colors);
  void Pmarkertype(int type);
  void Pmarkersize(double size);
  void Pmarkercolr(int colour);
  void Pmarkercolr(SbColor colour);
  void Pmarker(int n, const SbVec4f *points);
  void Pintstyle(int style);
  void Pfillcolr(int colour);
  void Pfillcolr(SbColor colour);
  void Ppolygon(int n, const SbVec4f* points);
  void Ptextcolr(int colour);
  void Ptextcolr(SbColor colour);
  void Pcharori(double upx, double upy, double bax, double bay);
  void Pcharheight(double height);
  void Ptextfontindex(int index);
  void Ptextprec(int precision);
  void Ptextpath(int path);
  void Pcharspace(double spacing);
  void Pcharexpan(double expansion);
  void Ptext010(SbVec4f pt,int final, const SbString& str);
  void Ptextjustif(int justif);
  void Pcliprect(float x_min, float y_min, float x_max, float y_max);
  void Plinetype(int type);
  void PtranspcellcolrI(unsigned int indicator, unsigned int indexColor);
  void PtranspcellcolrD(unsigned int indicator, SbColor &directColor);

  void PWriteVDC(double v);
  void PWritePoint(SbVec4f p);
  void PWriteColorD(int r, int g, int b);
  void PWriteHeader(int classe, int id, int length);
  void PWriteBuffer(const SbString& str, int len);
  void PWriteString(const SbString& str);
  void PWriteInt(unsigned int l);
  void PWriteEnum(unsigned int l);
  void PWriteIndex(int l);
  void PWriteColorI(unsigned int l);
  void PWriteReal(double r);

  // Buffering management
  void fillWriteBufferChar(char c) ;
  void flushWriteBuffer() ;

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
  int           m_currentPattableIndex;
  int           m_nbPattableIndex;
  
  // For CGM.
  int           m_cgmMarkerColor;
  int           m_cgmLineColor;
  int           m_cgmPolygonColor;
  int           m_cgmTextColor;
  SbColor       m_cgmPolygonColorRGB;

  // For Pattern
  SbPList       m_patternList;
  /****************************************************************************/
  // For Miscellaneous functions.
  int   PIntPrec;
  int   PRealPrec;
  int   PIndexPrec;
  int   PColorMode;
  int   PColorIndexPrec;
  int   PColorPrec;
  int   PVDCType;
  int   PVDCIntPrec;
  int   PVDCRealPrec;
  int   PLineWidthMode;
  int   PMarkerSizeMode;
  int   PEdgeWidthMode;
  int   PHeaderLenght;
  int   PCharWritten;
  int   WordSync;
 
  // Buffering management
  int    m_indFillWriteBuffer ;
  int    m_writeBufferSize ;
  char  *m_writeBuffer ;
};

/*****************************************************************************/

#endif //__SO_VECTORIZE_CGM_ACTION_


