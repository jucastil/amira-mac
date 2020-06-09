/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef __SO_VECTORIZE_GDI_ACTION_
#define __SO_VECTORIZE_GDI_ACTION_

#include <inttypes.h>

#ifdef _WIN32
#  ifdef _SO_QT_
#    include <windows.h>
#    include <wingdi.h>
#  else
#    include <Inventor/Win/SoWinDef.h>
#  endif
#elif defined(__NUTC__)
#  include <windows.h>
#  include <wingdi.h>
#else
#  define HPEN void *
#  define HGDIOBJ void *
#  define HBRUSH void *
#  define HGDIOBJ void *
   typedef uint32_t DWORD;
   typedef DWORD COLORREF;
   typedef struct {
     long x;
     long y;
   } POINT;
#endif

#include <HardCopy/SoVectorizeAction.h>

/**
 * @HCEXT Manage vector output to GDI devices.\ @WIN32_CLASS
 *
 * @ingroup HardCopy
 * 
 * @DESCRIPTION
 *   This class is used for writing vector formatted files (Enhanced Metafiles .EMF),
 *   for printing directly under MS-Windows, or with a application device context (DC).
 *
 *   An instance of SoGDIVectorOutput is contained in an SoVectorizeGDIAction.
 *   This is typically the only instance needed.
 * 
 */

class HARDCOPY_API SoGDIVectorOutput : public SoVectorOutput
{

 public:

  /**
   * Constructor. The default constructor enables the printer job. 
   */
  SoGDIVectorOutput();

  /**
   * Destructor. The destructor closes any output opened 
   * by the SoGDIVectorOutput.
   */
  virtual ~SoGDIVectorOutput();

  /**
   * Opens the GDI output as a Windows Enhanced MetaFile (.EMF) 
   * from the given file name.
   * @UNICODE_WARNING
   * Use the SbString version.
   */
  SoNONUNICODE SbBool openFile(const char *file_name);

  /**
   * Opens the GDI output as a Windows Enhanced MetaFile (.EMF) 
   * from the given file name.
   */
  SbBool openFile( const SbString& file_name );

  /**
   * Initializes GDI output using the given device context (type HDC).
   * But the device context must be first converted into a MM_HIMETRIC 
   * mapmode (units: 1/100th mm, the origin being in the bottom left corner, 
   * positive x to the right and positive y up). 
   * The mapmode can be restored after output processing.
   */
  void openFile(HDC hdc);

  /**
   * Default method: Opens the printer dialog box for paper output.
   */
  void openFile();

  /**
   * Fully optional.
   * Inactive but exists for consistency with the other output formats.
   */
  void closeFile();

 SoINTERNAL public:

  SbString getGDIOutputName();
  
  HDC getGDIHdc();

 private:
  // data
  SbString m_filename;
  HDC m_hdc;
};

/**
 * @HCEXT Vectorize a scene graph to MS-Windows GDI formats.
 * @WIN32_CLASS
 *
 * @ingroup HardCopy
 * 
 * @DESCRIPTION
 *   This class is used for vectorizing scene graphs to GDI format outputs. It 
 *   contains an SoGDIVectorOutput instance which writes by default to the standard 
 *   output (printer). Methods on the SoGDIVectorOutput can be called to specify the 
 *   output type and its attributes (such as the EMF file name).
 *
 *  NOTE: 
 *    If margin values are not valid for the targeted printer driver,
 *    it will be automatically reset to a correct one by the driver without prompting the 
 *    user that the resulting output may not be exactly what he expected.
 *
 *  Printer Control: @BR
 *    By default this class controls the printer (making the StartDoc, StartPage,
 *    etc Windows system calls) and defines the logical to device coordinate
 *    system mapping.  In some cases the application, or application framework
 *    (e.g. MFC) may wish to control the printer directly.  This is possible by
 *    setting the preference variable OIV_HCGDI_APPCONTROL to a non-zero value,
 *    using either a config file or the SoPreferences class.  When this variable
 *    is non-zero, the application is responsible for calling StartDoc, StartPage,
 *    EndPage and EndDoc to manage the printer.  There are two modes, depending
 *    on the value of OIV_HCGDI_APPCONTROL:
 *    - 1 : This is the most flexible mode.  The application is responsible for
 *          setting the map mode, logical to device mapping, etc. (in addition
 *          to managing the printer).  This mode is normally used in MFC applications.
 *    - 2 : This is the most convenient mode if you only need to manage the
 *          printer.  SoVectorizeGDIAction will set up the mapping as usual.
 *          This mode is only available in Open Inventor 7.2 and higher.
 *
 *    @B NOTE: @b When OIV_HCGDI_APPCONTROL is set, the methods that take parameters
 *    in physical units (e.g. millimeters) actually expect the values in current
 *    device units.  For example, in this mode most applications call the GDI
 *    method SetMapMode() with HI_METRIC, meaning that device units are now .01 
 *    millimeter (provides better resolution for detailed drawings).
 *    As a result methods like setDrawingDimensions() and setNominalWidth must
 *    now be called with HI_METRIC units.  For 1 mm, pass the value 100.
 *
 *  Polygon edge width: @BR
 *  GDI uses a "brush" to draw the interior of a polygon and a "pen" to draw the
 *  edges of the polygon.  By default the action uses a minimum width line for
 *  the polygon edges, but it is possible to specify the edge width by setting
 *  the environment variable OIV_HCGDI_EDGE_WIDTH (see SoPreferences).
 *  Zero means minimum width. Values > 0 are a scale factor applied to the 
 *  "nominalWidth" (see SoVectorizeAction::setNominalWidth) similar to the
 *  line width set with SoDrawStyle::lineWidth. This value is fetched in
 *  the constructor so it must be set before creating an SoVectorizeGDIAction.
 *  
 *  LIMITATIONS :
 *
 *    - End line style TRIANGULAR is not supported  end line style ROUND is 
 *      assumed instead.
 *    - Join line style NONE, MITERED_BEVELED, and TRIANGULAR are not 
 *      supported; join line styles BEVELED, MITERED, and ROUNDED are  
 *      assumed instead.
 *    - End and Join line styles are only supported for solid lines.
 *    - User's DC must be of HDC type.
 *    - Vertical text orientation may not be kept when editing .emf files in third parties applications,
 *      for instance MS Word.
 *    - A big value for the line width (defined with an SoDrawStyle) may result in previewing or printing   
 *      solid lines though they remain patterned. It depends on how big gaps are in the pattern.
 * 
 */

class HARDCOPY_API SoVectorizeGDIAction : public SoVectorizeAction
{

  SO_ACTION_HEADER(SoVectorizeGDIAction);

 public:

  /**
   * Constructor.
   */
  SoVectorizeGDIAction();

  /**
   * Destructor.
   */
  virtual ~SoVectorizeGDIAction();

  /* Access methods */

#ifdef OIV_NET_DOC
  /**
  * Returns reference to SoGDIVectorOutput instance in action.
  */

#else
  /**
  * Returns pointer to SoGDIVectorOutput instance in action.
  */

#endif //OIV_NET_DOC
  SoGDIVectorOutput *getGDIVectorOutput() const;

  /**
   * @deprecated use getGDIVectorOutput().
   * @DEPRECATED_SINCE_OIV 6.0
   */
  SoGDIVectorOutput *getOutput() const;

  /**
   * Returns TRUE if the printer is set. Initial value is FALSE.
   **/
  SbBool hasPrinter() { return m_hasPrinter; };

SoINTERNAL public:
  /**
   * Internally used to initialize the class.
   */
  static void initClass();
  static void exitClass();

 protected:
  /* Functions which really draw */
  virtual void printPolyMark(const SbVec4f* points, int num_points, 
                             const SbColor* colors, SbBool color_flag, float size);
  virtual void printPolyMark(const SbVec4f* points, int num_points, 
                             const SbColor* colors, SbBool color_flag, 
                             SoMarkerSet *markerSet);
  virtual void printImage(const SbVec4f &origin, const unsigned char *imagePixels, 
                          SbVec2s &sourceSize, SbVec2s &requestedSize, 
                          int numComponents,
                          SoImage::HorAlignment  horAlign,
                          SoImage::VertAlignment vertAlign);
  virtual void printPolyLine(const SbVec4f* points, int num_points, 
                             const SbColor* colors, SbBool color_flag,
                             float thickness, u_short pattern, int linePatternScaleFactor);
  virtual void printPolygon(const SbVec4f* points, int num_points, 
                            const SbColor* colors, SbBool color_flag, const SbString &category, 
                            const SbString &name, const unsigned char* pattern);
  virtual void printText2(const SbVec4f point, const SbColor color,
                          const SbString& font_name, float font_size, 
                          const SbString& string, int justif, float angle);
  
  // Retrieves the printer DC
  HDC getPrinterDC(void);
  
  // Write header and footer
  virtual void writeHeader();
  virtual void writeFooter();
  
  // Print the border and the background
  virtual void printBorder();
  virtual void printBackground();
  
  // Set hardware clipping
  virtual void setHardwareClip();
  
  // Miscellaneous methods
 private:
  void assignColor(SbColor, float);
  void selectPen(DWORD, DWORD, COLORREF, SbBool);
  SbBool isPenUsedAgain(DWORD, DWORD, COLORREF, SbBool);
  void pointsToLandscape(POINT *, int);
  
  // data
  typedef struct {
    DWORD style;
    DWORD thickness;
    COLORREF color;
  } structCurrentPen;
  
  structCurrentPen currentPen;
  HPEN m_currentPen;
  HGDIOBJ m_oldPen;
  HBRUSH m_currentBrush;
  HGDIOBJ m_oldBrush;
  COLORREF m_currentBrushColor;
  SbBool m_patternFlag;
  
  SbColor m_currentColor;
  EndLineStyle m_currentLineEndStyle;
  JoinLineStyle m_currentLineJoinsStyle;
  float m_currentMiterLimit;
  
  SbString m_filename;
  
  HDC m_hdc;
  SbBool m_hasPrinter;
  
  SbBool m_printerFlag;
  SbBool m_solidPenFlag;
  int m_offsetX, m_offsetY;
  int m_portraitWidth;
  int m_unitRatio;
};

//***************************************************************************************
#endif //__SO_VECTORIZE_GDI_ACTION_

