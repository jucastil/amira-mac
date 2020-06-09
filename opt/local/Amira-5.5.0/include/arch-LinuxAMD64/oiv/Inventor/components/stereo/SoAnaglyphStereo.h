/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _SO_WIN_ANAGLYPH_STEREO
#define _SO_WIN_ANAGLYPH_STEREO

#include <Inventor/components/stereo/SoBaseStereo.h>

class SoStereoViewer;

/**
 * @VSGEXT Class for anaglyph stereo support.
 * 
 * @ingroup Stereo
 * 
 * @DESCRIPTION
 *   This type is similar to the raw stereo type (SoRawStereo). But it adds a color
 *   filter for each view rendered. The default is Red/Cyan.
 *   There are three kinds of filters (#ColorFilter). You can reverse the left and rights views,
 *   making three new kinds of filters (CYAN_RED, etc.). The Alpha channel is used in
 *   both views.
 * 
 * @SEE_ALSO
 *    SoStereoViewer,
 *    SoBaseStereo,
 *    SoWinViewer
 *    SoXtViewer
 * 
 * [OIVJAVA-WRAPPER-CLASS NO_WRAP]
 * 
 */ 

class INVENTORW_API SoAnaglyphStereo : public SoBaseStereo
{
 public:
  /**
   * Color Filter.
   * There is 3 types of filters. Note that you can reverse the view,
   * making 3 new types of filters (CYAN_RED,etc.). Note also that this
   * types are able to deal with two-colors glasses (rather than 3 colors) :
   * RED_CYAN is also adpated for red/green glasses, and so on.
   * Note that the Alpha channel is kept in both views.
   */
  enum ColorFilter {
    /** Default value */
    RED_CYAN,
    GREEN_MAGENTA,
    BLUE_YELLOW //, GRAYSCALE // not implemented
  };
  
  /**
   * Constructor.
   */
  SoAnaglyphStereo(SoStereoViewer *stereoVwr = NULL) :
    SoBaseStereo(stereoVwr),
    colorFilter(RED_CYAN),
    reversed(FALSE),
    clearBuffer(TRUE) {}
    
  /**
   * Destructor.
   */
  ~SoAnaglyphStereo() {}
    
  /**
   * Sets stereo reversal.
   */
  virtual void reverseStereoView(SbBool reverse);
  /**
   * Queries stereo reversal.
   */
  virtual SbBool isStereoViewReversed();
  
  /**
   * Renders the stereo view.
   */
  virtual void renderStereoView();
 
  /**
   * Queries ability to clear before rendering.
   */
  virtual SbBool canClearBeforeRender();
  
  /**
   * Always returns FALSE.
   */
  SbBool requireHardware() { return FALSE; }
  /**
   * Always returns SoBaseStereo::ANAGLYPH_STEREO.
   */
  StereoViewType getStereoViewType() { return ANAGLYPH_STEREO; }
  /**
   * Clears stereo.
   */
  virtual void clearStereo();
  
  /**
   * Sets the filter type.
   */
  void setColorFilter(ColorFilter filter) { colorFilter = filter; }
  /**
   * Queries the filter type.
   */
  ColorFilter getColorFilter() { return colorFilter; }
  
  /** setup left eye settings for MPViewers stereo */
  void doLeftEyeSettings();
  /** setup right eye settings for MPViewers stereo */
  void doRightEyeSettings();
  /** setup monoscopic settings for MPViewers stereo */
  void doMonoscopicSettings();

    
 private:
  ColorFilter colorFilter;
  SbBool reversed;
  SbBool clearBuffer;

};

#endif // _SO_WIN_ANAGLYPH_STEREO


