/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Beilloin (MMM yyyy)
**=======================================================================*/

#ifndef _SO_INVENTOR_BASE_
#define _SO_INVENTOR_BASE_

#include <Inventor/SbBase.h>
#include <Inventor/STL/set>
#include <Inventor/STL/map>

#include <Inventor/threads/SbThreadMutex.h>

class SbThreadRWMutex;

/**
* General basic object database.
*
* @ingroup General
*
* @DESCRIPTION
*  Allows a minimal set of core Open Inventor functionality, specifically
*  NOT including the scene graph, to be initialized.  This is only useful
*  in special cases like using the MeshVizXLM Extraction module separate
*  from the Open Inventor scene graph. In the normal case applications
*  should use the SoDB methods (which call these methods).
*
* @SEE_ALSO
*    SoDB
*
*/

SoINTERNAL class INVENTORBASE_API SoInventorBase
{
public:
  /**
   * Initializes the basic inventor nodes.
   * This must be called before calling any other database routines.
   * [OIV-WRAPPER-NO-WRAP]
   */
  static void init();

  /**
   * Frees Open Inventor's internal static memory
   * allocations. This avoids false positives from memory
   * leak checking software. 
   * [OIV-WRAPPER-NO-WRAP]
   */
  static void finish();

  /**
   * Returns TRUE if database is initialized (for error checking)
   * [OIV-WRAPPER-NO-WRAP]
   */
  static bool isInitialized();

  /**
   * Return whether mutexes should be created.
   */
  static SbBool shouldCreateMutex();

  /**
   * Return whether threadMode has been setup by user.
   */
  static SbBool threadModeIsSet()
  { return s_threadModeIsSet; }

  /**
   * Return whether threadMode is enabled.
   */
  static SbBool isMultithread()
  { return s_isMultithreaded; }

  /**
   * Enables multithread mode for Open Inventor
   * same as defining OIV_MULTITHREAD envvar to TRUE
   **/
  static void enableMultithread(const SbBool flag)
  {
	  if (!threadModeIsSet())
	  {
		  s_isMultithreaded = flag;
		  s_threadModeIsSet = TRUE;
	  }
  }
SoINTERNAL public:

  // We are able to manage 2 multi-threads cases on MS Windows platforms:
  // 1- standard case where all threads share common global objects
  // and can interact each other (notification/rendering/multiGPU...)
  //
  // => this mode is enabled through envvar OIV_MULTITHREAD
  // 
  // 2- Experimental case where each threads can be considered as a separate Open Inventor application
  // each thread do not share anything, and then are independent from each other.
  // The following objects are thread specific:
  // - SoSensorManager::m_pThreadSensorMgr : SoSensorManagerThread handling notification queues
  // - SoDB::SoGlobalDBInfos               : main globalField, realTimeSensor sensor, realTime field
  // - SoGlobalField::nameDict             : globalField's dictionnary
  // - 
  // IMPORTANT: When using this mode, no notification MUST be done from a a thread to anoher.
  // (ie, it is not allowed to modified an Open Inventor field/node/scenegraph... from another 
  // thread than the one who created the given object.
  //
  // => this mode is enabled through envvar OIV_MULTITHREAD_APPLICATION (required also OIV_MULTITHREAD to be set)
  //
  static SbBool isMultiThreadApplication();

  static void threadInit();
  static void threadFinish();

  static bool checkMultithread();

  // globalMutex provides a way for any application to use a global mutex.
  // It is also used inside OIV in some instances
  static SbThreadRWMutex* getGlobalMutex();

  // returns true if OIV_MULTITHREAD_APPLICATION_DISABLE_LOCK is set, it allows to 
  // - disable any mutex lock even if OIV_MULTITHREAD is defined.
  // - do internal performance test with OIV_MULTITHREAD_APPLICATION mode set
  static SbBool forceShouldCreateMutex();

  // global lock for init/finish operation
  static SbThreadMutex s_initFinishLock;

private:
  // library usage counter
  static int s_initRefCount;

  // The isMultithreaded flag can be set to true or false only one time, that's
  // why we need a threadModeIsSet flag.
  static SbBool s_threadModeIsSet;
  static SbBool s_isMultithreaded;
  static const char *s_versionString;
  // Global mutex
  static SbThreadRWMutex *globalMutex;

  static bool m_checkMultithread;
};

#endif /* _SO_INVENTOR_BASE_ */
