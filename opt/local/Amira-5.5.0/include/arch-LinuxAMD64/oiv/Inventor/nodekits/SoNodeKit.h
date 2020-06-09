/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul Isaacs (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_NODE_KIT_
#define  _SO_NODE_KIT_

#include <Inventor/SbBasic.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoNodeKit
//
//  Class with one static function to initialize all nodeKit node classes,
//  and their catalogs.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Initializes nodekit classes.
 * 
 * @ingroup nodekits
 * 
 * @DESCRIPTION
 *   This class is used to initialize all nodekit classes.
 *   
 *   For standard single thread support, call the standard init() method. For
 *   multiple thread support, call threadInit().
 * 
 * @SEE_ALSO
 *    SoAppearanceKit,
 *    SoBaseKit,
 *    SoCameraKit,
 *    SoInteraction,
 *    SoLightKit,
 *    SoNodeKitDetail,
 *    SoNodeKitListPart,
 *    SoNodeKitPath,
 *    SoNodekitCatalog,
 *    SoSceneKit,
 *    SoSeparatorKit,
 *    SoShapeKit,
 *    SoWrapperKit,
 *    SoWin
 * 
 * [OIV-WRAPPER-NO-WRAP]
 */ 

class INVENTOR_API SoNodeKit {
 public:
  /**
   * Initialize all nodekit classes by registering them with the database. This
   * function needs to be called before @B any @b other nodekit class may be
   * constructed or accessed. Note that this is called automatically by
   * SoInteraction::init() and SoWin::init(), so if you have made
   * either of these calls, there is no need to call SoNodeKit::init() directly.
   */
  static void         init();

  /** 
   * Frees Open Inventor's internal static memory 
   * allocations. This avoids false positives from memory
   * leak checking software. We recommend calling this method
   * and it should be the last Open Inventor method called by
   * the application.
   */
  static void         finish();

  /**
   * Initialize all nodekit classes with multiple thread support. This function needs
   * to be called before @B any @b other nodekit class may be constructed or
   * accessed. Note that this is called automatically by
   * SoInteraction::threadInit() and SoWin::threadInit(), so if you
   * have made either of these calls, there is no need to call
   * SoNodeKit::threadInit() directly.
   * 
   * @B Note @b: Although it's only necessary to call init() once in a
   * single-threaded program, in a multithreaded program, every thread that uses Open
   * Inventor classes must call threadInit().
   */
  static void         threadInit(); // init all nodeKit classes with MT support
  static void         threadFinish();

  static bool isInitialized();

private:

  /** Does the actual init of the module */
  static void internalInit();

  /** Does the actual finish of the module */
  static void internalFinish();

 private:
  static int s_initRefCount;    // has nodekit been initialized
};

#endif /* _SO_NODE_KIT_ */

