/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Mott (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_INTERACTION_
#define  _SO_INTERACTION_


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoInteraction
//
//  Class with one static function to initialize all interaction node classes.
//  SoInteraction::init MUST be called in order for interaction classes to
//  function. SoInteraction::init() calls SoDB::init().
//  SoInteraction::threadInit() calls SoDB::threadInit().
//
//////////////////////////////////////////////////////////////////////////////

#include <Inventor/SbBasic.h>

/**
 * Initializes Open Inventor interaction classes.
 * 
 * @ingroup General
 * 
 * @DESCRIPTION
 *   SoInteraction has static functions which initialize all Open Inventor
 *   interaction classes, as well as nodekits and the database. 
 *   
 *   For standard single thread support, call the standard init() method. For
 *   multiple thread support, call threadInit().
 *   
 *   Note that SoInteraction::init() is called by SoWin::init(), just as
 *   SoInteraction::threadInit is called by SoWin::threadInit().
 * 
 * @SEE_ALSO
 *    SoDB,
 *    SoNodeKit,
 *    SoWin
 * 
 *
 * [OIV-WRAPPER-NO-WRAP]
 */ 

class INVENTOR_API SoInteraction {
 public:
  /**
   * Initializes all interaction classes with single thread support.
   * 
   * It calls SoDB::init() and SoNodeKit::init(), calls
   * initClasses() on SoDragger, and calls initClass() on the following
   * classes: SoAntiSquish, SoBoxHighlightRenderAction, SoCenterballManip,
   * SoDirectionalLightManip, SoExtSelection, SoHandleBoxManip, SoInteractionKit, SoJackManip,
   * SoLineHighlightRenderAction, SoPointLightManip, SoSelection, SoSpotLightManip,
   * SoSurroundScale, SoTabBoxManip, SoTrackballManip, SoTransformBoxManip, and
   * SoTransformManip. 
   */
  static void init();

  /** 
   * Frees Open Inventor's internal static memory 
   * allocations. This avoids false positives from memory
   * leak checking software. We recommend calling this method
   * and it should be the last Open Inventor method called by
   * the application.
   */
  static void finish();

  /**
   * Initializes all interaction classes with multiple thread support.
   * 
   * @B Note @b: Although it's only necessary to call init() once in a
   * single-threaded program, in a multithreaded program, every thread that uses Open
   * Inventor classes must call threadInit().
   */
  static void threadInit();   // init all interaction classes with MT support
  static void threadFinish();   // init all interaction classes with MT support
  static bool isInitialized();

 private:
  
  static void internalInit();

  static void internalFinish();

  // has interaction been initialized
  static int s_initRefCount;
};

#endif /* _SO_INTERACTION_ */

