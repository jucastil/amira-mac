/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Nick Thompson (MMM yyyy)
** Modified by : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef _SO_DB_
#define _SO_DB_

#include <Inventor/SoType.h>
#include <Inventor/SbTime.h>
#include <Inventor/threads/SbThread.h>
#include <Inventor/threads/SbThreadLocalStorage.h>

#ifndef LIBRARYBUILD
// uneeded header be kept for application built compatibility
#include <Inventor/sensors/SoSensorManager.h>
#include <Inventor/SbPList.h>
#include <Inventor/SoPreferences.h>
#endif

class SbPList;
class SoBase;
class SoSFRealTime;
class SoGroup;
class SoSeparator;
class SoInput;
class SoPath;
class SoNode;
class SoField;
class SoVRMLGroup;
class SoVRMLPROTODef;
class SbColor;
class SoGlobalField;
class SoSensorManager;
class SoTimerSensor;
class SoSensor;

#include <Inventor/SoModule.h>
SO_MODULE_HEADER(SoInventor, __INVDLL)

#if defined(_WIN32)
// Detect compilation that uses any form of /clr
#if ((_MANAGED == 1) || (_M_CEE == 1))
#if defined(SO_MODULE_CHECK)
static SoModuleCheck myModule(_SECURE_SCL);
#endif
#elif !defined HIDDEN_FROM_DOC && !defined(LIBRARYBUILD)
static SoModuleCheck myModule(_SECURE_SCL);
#endif /* (_MANAGED == 1) || (_M_CEE == 1) */
#endif /* _WIN32 */

typedef void SoDBHeaderCB(void *userData, SoInput *in);

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoDB
//
//  Inventor database class.  This class maintains all the global
//  information necessary for reading and writing, naming classes, and
//  so on. All public methods on this class are static - users should
//  never explicitly create instances of this class. Initialization of
//  the database class causes a global instance to be created.
//
//////////////////////////////////////////////////////////////////////////////

#ifdef OIV_NET_DOC
/**
* Scene graph database class.
*
* @ingroup General
*
* @DESCRIPTION
*   The SoDB class holds all scene graphs, each representing a 3D scene used by an
*   application. A scene graph is a collection of SoNode objects which come in
*   several varieties (see SoNode). All methods on this class are static.
*
*   SoDB also provides convenient methods for reading data files. For example,
*   SoDB.ReadAll. Open Inventor has built-in support for reading the following file formats:
*   - Open Inventor
*   - VRML/X3D
*   - OpenFlight
*   - DXF
*   - Catia V5  *
*   - STEP      *
*   - IGES      *
*
*   *NOTE: Loading these formats requires a separate license.
*
* @SEE_ALSO
*    SoBase,
*    SoNode,
*    SoEngine,
*    SoField,
*    SoInput,
*    SoFile,
*    SoPath,
*    SoOneShotSensor,
*    SoDataSensor,
*    SoWin
*
*
*/
#else
/**
* Scene graph database class.
*
* @ingroup General
*
* @DESCRIPTION
*   The SoDB class holds all scene graphs, each representing a 3D scene used by an
*   application. A scene graph is a collection of SoNode objects which come in
*   several varieties (see SoNode). 
*
*   Application programs must initialize the
*   database by calling SoDB::init() before calling any other database routines and
*   before constructing any nodes, paths, functions, or actions. Note that
*   SoDB::init() is called by SoInteraction::init(),
*   SoNodeKit::init(), and SoWin::init(), so if you are calling any of
*   these methods, you do not need to call SoDB::init() directly. All methods on
*   this class are static.
*
*   Application programs should close and cleanup the database by calling
*   SoDB::finish() after deleting all explicitly created Open Inventor objects.
*   Note that in when using C++ API, "reference counted" objects like nodes and
*   paths cannot be explicitly deleted.
*
*   Example program database initialization and scene loading:
*
*   \code
*    #include <Inventor/SoDB.h>
*    #include <Inventor/SoInput.h>
*    #include <Inventor/nodes/SoSeparator.h>
*
*      SoDB::init(); // or e.g. SoWin::init()
*
*      SoInput in;
*      in.openFile( filename );
*
*      SoSeparator *rootSep = SoDB::readAll(&in);
*      if (rootSep == NULL)
*        printf("Error on read...\\n");
*      ...
*
*      SoDB::finish(); // or e.g. SoWin::finish()
*   \endcode
*
*   @B Data Files: @b 
*
*   SoDB also provides convenient methods for reading data files. For example,
*   SoDB::readAll. Open Inventor
*   has built-in support for reading the following file formats:
*   - Open Inventor
*   - VRML/X3D
*   - OpenFlight
*   - DXF
*   - *Catia V5
*   - *STEP    
*   - *IGES    
*
*   *NOTE: Loading these formats requires a separate license.
*
*   @B Multithread Programming: @b 
*
*   Application programs that use Open Inventor classes from more than one thread
*   must call SoDB::threadInit instead of SoDB::init.
*
*   Although it's only necessary to call SoDB::init once in a single-threaded program,
*   in a multithreaded program, every thread that uses Open Inventor classes must call
*   SoDB::threadInit.
*
*   Since SoDB::init is called by SoInteraction::init, SoNodeKit::Init, and
*   SoWin::init, do not call these methods in a multithread program. Call (for
*   example), SoInteraction::threadInit instead.
*
*   @B Version Number: @b 
*
*   You can query a descriptive string using the #getVersion() method or a floating
*   point value using the #getLicensingVersionNumber() method.  You can find other integer 
*   and string constants in SoVersion.h.  For example @B SO_INVENTOR_VERSION @b can be 
*   used with preprocessor directives to isolate version specific code.  It encodes the 
*   major, minor and patch numbers as an integer. For example "8600" for version 8.6.0.
*
* @SEE_ALSO
*    SoBase,
*    SoNode,
*    SoEngine,
*    SoField,
*    SoInput,
*    SoFile,
*    SoPath,
*    SoOneShotSensor,
*    SoDataSensor,
*    SoWin
*
*
*/
#endif //OIV_NET_DOC


class INVENTOR_API SoDB {

 public:

   /** Render cache modes */
  enum RenderCacheMode {
    /**
     *  Display lists are created with COMPILE mode. (Default)
     */
    COMPILE,
    /**
     *  Display lists are created with COMPILE_AND_EXECUTE mode.
     */
    COMPILE_AND_EXECUTE,
    /**
     *  Automatically choose mode depending on the hardware.
     */
    AUTO_RENDER_CACHE
  };

  /**
   * Initializes the database. This must be called before calling any other database
   * routines, including the construction of any nodes, paths, engines, or actions.
   * [OIV-WRAPPER-NOT-WRAP]
   */
  static void init();

  /**
   * Frees Open Inventor's internal static memory
   * allocations. This avoids false positives from memory
   * leak checking software. We recommend calling this method
   * and it should be the last Open Inventor method called by
   * the application.
   *
   * @B Note@b : Open Inventor objects must be destroyed before you call this method.
   * See SoXt::finish() method for additional info.
   * [OIV-WRAPPER-NOT-WRAP]
   */
  static void finish();

  /**
   * Initializes the database with support for multithread programs. This must be
   * called before calling any other database routines, including the construction of
   * any nodes, paths, engines, or actions. This method calls SoDB::init. Application
   * programs that use Open Inventor classes from more than one thread must call this
   * method instead of SoDB::init.
   *
   * @B Note@b: Although it's only necessary to call SoDB::init once in a
   * single-threaded program, in a multithreaded program, every thread that uses Open
   * Inventor classes must call SoDB::threadInit.
   * [OIV-WRAPPER-CUSTOM-CODE]
   */
  // Thread initialization routine.
  // It should be called as the first line of a new thread starting
  // routine, though it can be safely called several times by a
  // same thread. It should as well be called by all threads, if
  // one thread requests more local storage and other threads will
  // want to access the corresponding local storage. threadInit
  // should be called instead of init.
  static void threadInit();

  /**
   * Returns a character string identifying the version of the Open Inventor library
   * in use.
   * For example: "@(#)OpenInventor 8.6.0 for 64 bits, © 1996-2011 VSG"
   *
   * For a floating point version number see #getLicensingVersionNumber.  For integer
   * and string constants, see SoVersion.h.
   */
  static const char *getVersion();

#ifdef OIV_NET_DOC
  /**
  * Reads a graph from the file specified by the given SoInput, returning a reference
  * to the resulting root node in rootNode. There is an alternate read routine
  * that returns a reference to the resulting path.
  * The programmer is responsible for determining which routine to use, based
  * on the contents of the input. These routines return false if any error occurred
  * during reading.
  *
  * If the passed SoInput was used to open a file and the name of the file contains a
  * directory, SoDB automatically adds the directory to the end of the current
  * directory search path in the SoInput. This means that nested files named in
  * SoFile nodes may be found relative to that directory. The directory is removed
  * from the search path when reading is complete.
  */

#else
  /**
  * Reads a graph from the file specified by the given SoInput, returning a pointer
  * to the resulting root node in rootNode. There is an alternate read routine
  * that returns a pointer to the resulting path.
  * The programmer is responsible for determining which routine to use, based
  * on the contents of the input. These routines return FALSE if any error occurred
  * during reading.
  *
  * If the passed SoInput was used to open a file and the name of the file contains a
  * directory, SoDB automatically adds the directory to the end of the current
  * directory search path in the SoInput. This means that nested files named in
  * SoFile nodes may be found relative to that directory. The directory is removed
  * from the search path when reading is complete.
  */

#endif //OIV_NET_DOC
  static SbBool read(SoInput *in, SoNode *&rootNode);

#ifdef OIV_NET_DOC
  /**
  * Reads a graph from the file specified by the given SoInput, returning a reference
  * to the resulting path in path. There is an alternate read routine
  * that returns a reference to the resulting root node.
  * The programmer is responsible for determining which routine to use, based
  * on the contents of the input. These routines return false if any error occurred
  * during reading.
  *
  * If the passed SoInput was used to open a file and the name of the file contains a
  * directory, SoDB automatically adds the directory to the end of the current
  * directory search path in the SoInput. This means that nested files named in
  * SoFile nodes may be found relative to that directory. The directory is removed
  * from the search path when reading is complete.
  * [OIVJAVA-WRAPPER NAME{readPath}]
  */

#else
  /**
  * Reads a graph from the file specified by the given SoInput, returning a pointer
  * to the resulting path in path. There is an alternate read routine
  * that returns a pointer to the resulting root node.
  * The programmer is responsible for determining which routine to use, based
  * on the contents of the input. These routines return FALSE if any error occurred
  * during reading.
  *
  * If the passed SoInput was used to open a file and the name of the file contains a
  * directory, SoDB automatically adds the directory to the end of the current
  * directory search path in the SoInput. This means that nested files named in
  * SoFile nodes may be found relative to that directory. The directory is removed
  * from the search path when reading is complete.
  * [OIVJAVA-WRAPPER NAME{readPath}]
  */

#endif //OIV_NET_DOC
  static SbBool read(SoInput *in, SoPath *&path);

#ifdef OIV_NET_DOC
  /**
  * Reads all graphs and paths from the file specified by the given SoInput. If
  * there is only one graph in the file and its root is an SoSeparator, a reference to
  * the root is returned. In all other cases, this creates an SoSeparator, adds the
  * root nodes of all graphs read as children of it, and returns a reference to it.
  * This returns null on error. This processes directory paths in the same way as
  * the other reading routines.
  *
  * Reading an OpenFlight file into Open Inventor is just
  * like reading in an Open Inventor format file. Open Inventor
  * will open the file and automatically detect that it is an
  * OpenFlight file. Optionally, you can tell Open Inventor
  * explicitly that the file type is OpenFlight. See SoInput for details about
  * support of the OpenFlight format.
  *
  * Reading a DXF file into Open Inventor is just
  * like reading in an Open Inventor format file. Open Inventor
  * will open the file and automatically detect that it is a
  * DXF file. Optionally, you can tell Open Inventor
  * explicitly that the file type is DXF. See SoInput for details about
  * support of the DXF format.
  *
  * Reading a Catia V5 file into Open Inventor is just
  * like reading in an Open Inventor format file. Open Inventor
  * will open the file and automatically detect that it is a
  * Catia V5 file. Optionally, you can tell Open Inventor
  * explicitly that the file type is CATIA5. See SoInput for details about
  * support of the Catia V5 format.
  *
  * Reading an STEP file into Open Inventor is just
  * like reading in an Open Inventor format file. Open Inventor
  * will open the file and automatically detect that it is a
  * STEP file. Optionally, you can tell Open Inventor
  * explicitly that the file type is STEP. See SoInput for details about
  * support of the STEP format.
  *
  * Reading an IGES file into Open Inventor is just
  * like reading in an Open Inventor format file. Open Inventor
  * will open the file and automatically detect that it is a
  * IGES file. Optionally, you can tell Open Inventor
  * explicitly that the file type is IGES. See SoInput for details about
  * support of the IGES format.
  */

#else
  /**
  * Reads all graphs and paths from the file specified by the given SoInput. If
  * there is only one graph in the file and its root is an SoSeparator, a pointer to
  * the root is returned. In all other cases, this creates an SoSeparator, adds the
  * root nodes of all graphs read as children of it, and returns a pointer to it.
  * This returns NULL on error. This processes directory paths in the same way as
  * the other reading routines.
  *
  * Reading an OpenFlight file into Open Inventor is just
  * like reading in an Open Inventor format file. Open Inventor
  * will open the file and automatically detect that it is an
  * OpenFlight file. Optionally, you can tell Open Inventor
  * explicitly that the file type is OpenFlight. See SoInput for details about
  * support of the OpenFlight format.
  *
  * Reading a DXF file into Open Inventor is just
  * like reading in an Open Inventor format file. Open Inventor
  * will open the file and automatically detect that it is a
  * DXF file. Optionally, you can tell Open Inventor
  * explicitly that the file type is DXF. See SoInput for details about
  * support of the DXF format.
  *
  * Reading a Catia V5 file into Open Inventor is just
  * like reading in an Open Inventor format file. Open Inventor
  * will open the file and automatically detect that it is a
  * Catia V5 file. Optionally, you can tell Open Inventor
  * explicitly that the file type is CATIA5. See SoInput for details about
  * support of the Catia V5 format.
  *
  * Reading an STEP file into Open Inventor is just
  * like reading in an Open Inventor format file. Open Inventor
  * will open the file and automatically detect that it is a
  * STEP file. Optionally, you can tell Open Inventor
  * explicitly that the file type is STEP. See SoInput for details about
  * support of the STEP format.
  *
  * Reading an IGES file into Open Inventor is just
  * like reading in an Open Inventor format file. Open Inventor
  * will open the file and automatically detect that it is a
  * IGES file. Optionally, you can tell Open Inventor
  * explicitly that the file type is IGES. See SoInput for details about
  * support of the IGES format.
  */

#endif //OIV_NET_DOC
  static SoSeparator *readAll(SoInput *in);

#ifdef OIV_NET_DOC
  /**
  * Reads all graphs and paths from the VRML file specified by the given
  * SoInput. If there is only one graph in the file and its root is an SoVRMLGroup,
  * a reference to the root is returned. In all other cases, this creates an
  * SoVRMLGroup, adds the root nodes to its @B children @b field, and returns a
  * reference to it. This returns null on error. This processes directory paths in the
  * same way as the other reading routines.
  */

#else
  /**
  * Reads all graphs and paths from the VRML file specified by the given
  * SoInput. If there is only one graph in the file and its root is an SoVRMLGroup,
  * a pointer to the root is returned. In all other cases, this creates an
  * SoVRMLGroup, adds the root nodes to its @B children @b field, and returns a
  * pointer to it. This returns NULL on error. This processes directory paths in the
  * same way as the other reading routines.
  */

#endif //OIV_NET_DOC
  static SoVRMLGroup *readAllVRML(SoInput *in);

  /**
   * Reads all PROTOs in the specified input file up to and including
   * the named PROTO and returns the definition of the named PROTO
   * in @B protoDef@b.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE static SbBool readPROTOFromFile(SoInput *in, char *name,
                                  SoVRMLPROTODef *&protoDef);


  /**
   * Reads all PROTOs in the specified input file up to and including
   * the named PROTO and returns the definition of the named PROTO
   * in @B protoDef@b.
   */
  static SbBool readPROTOFromFile(SoInput *in, const SbString& name,
                                  SoVRMLPROTODef *&protoDef);

  /**
   * Creates a VRML 2.0 ROUTE-TO connection. The connection is made from the
   * @B pFromNode @b's @B fromEventOut @b eventOut to the @B pToNodes @b's
   * @B toEventIn @b eventIn. This is equivalent to
   *
   * ROUTE pFromNode.fromEventOut @BR
   * TO pToNode.toEventIn
   *
   * in a VRML 2.0 file.
   */
  static void createRoute(SoNode *pFromNode, const char *fromEventOutName,
                          SoNode *pInNode,   const char *toEventInName);
  /**
   * Removes a VRML 2.0 ROUTE-TO connection.
   */
  static void removeRoute(SoNode *pFromNode, const char *fromEventOutName,
                          SoNode *pInNode,   const char *toEventInName);

  /**
   * Registers the given string as a valid header for input files. The string must be
   * 80 characters or less, and start with the comment character '#'. If the passed
   * @B isBinary @b flag is true, any file with this header will be read as a binary
   * file. Usually, a user-defined header represents a file format that is a superset
   * of the Open Inventor file format. The @B ivVersion @b number indicates which
   * Open Inventor file version this header corresponds to. The user-defined callback
   * functions @B preCB @b and @B postCB @b are called before and after a file with
   * this header is read. The @B userData @b is passed to both callback functions.
   * The method returns TRUE if the header is successfully registered. Note, nothing
   * prevents you from registering the same string multiple times.
   */
  static SbBool registerHeader(const SbString &headerString,
                               SbBool isBinary,
                               float ivVersion,
                               SoDBHeaderCB *preCB,
                               SoDBHeaderCB *postCB,
                               void *userData = NULL);
  /**
  * Passes back the data registered with the given header string, including the flag
  * specifying whether the string is for a binary file, pointers to the callback
  * functions invoked before and after reading the file, and a pointer to the user
  * data passed to the callback functions. If the given header string does not match
  * any of the registered headers, and the @B substringOK @b flag is TRUE, then the
  * method will search for a registered header that is a substring of the given
  * string. The method returns TRUE if a matching registered header, or subheader,
  * was found.
  * [OIVJAVA-WRAPPER PACK{HeaderData}]
  */
  static SbBool getHeaderData(const SbString &string,
                              SbBool &isBinary,
                              float &ivVersion,
                              SoDBHeaderCB *&preCB,
                              SoDBHeaderCB *&postCB,
                              void *&userData,
                              SbBool substringOK = FALSE);
  /**
   * Returns the number of valid headers, including standard Open Inventor headers,
   * and user-registered headers.
   */
  static int getNumHeaders();

  /**
   * Returns the i'th header.
   */
  static SbString getHeaderString(int i);

  /**
   * This returns TRUE if the given character string is one of the valid Open
   * Inventor file headers, (e.g., "#Inventor V2.0 binary"), or if the string has been
   * registered as a valid header through the registerHeader() method.
   */
  static SbBool isValidHeader(const char *testString);

#ifdef OIV_NET_DOC
  /**
  * The database maintains a namespace for global fields, making sure that there is
  * at most one instance of a global field with any given name in the database. This
  * routine is used to create new global fields. If there is no global field with
  * the given name, it will create a new global field with the given name and type.
  * If there is already a global field with the given name and type, it will return
  * it. If there is already a global field with the given name but a different type,
  * this returns NULL.
  *
  * All global fields must be derived from SoField; typically the result of this
  * routine is cast into the appropriate type.
  */

#else
  /**
  * The database maintains a namespace for global fields, making sure that there is
  * at most one instance of a global field with any given name in the database. This
  * routine is used to create new global fields. If there is no global field with
  * the given name, it will create a new global field with the given name and type.
  * If there is already a global field with the given name and type, it will return
  * it. If there is already a global field with the given name but a different type,
  * this returns NULL.
  *
  * All global fields must be derived from SoField; typically the result of this
  * routine is cast into the appropriate type; for example:
  *
  * <PRE>
  *  SoSFInt32 *longField = (SoSFInt32 *) SoDB::createGlobalField("Frame",
  *                                       SoSFInt32::getClassTypeId());
  * </PRE>
  *
  */

#endif //OIV_NET_DOC
  static SoField *createGlobalField(const SbName &name, SoType type);

  /**
   * Returns the global field with the given name, or NULL if there is none. The type
   * of the field may be checked using the SoField::isOfType(),
   * SoField::getClassTypeId(), and SoField::getTypeId() methods.
   */
  static SoField *getGlobalField(const SbName &name);

  /**
   * Renames the global field named oldName. Renaming a global field to an empty name
   * ("") deletes it. If there is already a global field with the new name, that
   * field will be deleted (the getGlobalField() method can be used to guard
   * against this).
   */
  static void renameGlobalField(const SbName &oldName, const SbName &newName);

  /**
   * The database automatically creates one global field when SoDB::init() is called.
   * The @B realTime @b global field, which is of type SoSFTime, can be connected to
   * engines and nodes for real-time animation. The database will automatically
   * update the @B realTime @b global field 12 times per second, using a timer
   * sensor. Typically, there will be a node sensor on the root of the scene graph
   * which schedules a redraw whenever the scene graph changes; by updating the
   * @B realTime @b global field periodically, scene graphs that are connected to
   * @B realTime @b (and are therefore animating) will be redrawn. The rate at which
   * the database updates @B realTime @b can be controlled with this routine.
   * Passing in a zero time will disable automatic update of @B realTime @b. If
   * there are no enabled connections from the @B realTime @b field to any other
   * field, the sensor is automatically disabled. Note that the SoSceneManager class
   * automatically updates realTime immediately after redrawing, which will result in
   * as high a frame rate as possible if the scene is continuously animating. This
   * method ensures that engines that do not
   * continuously animate (such as SoTimeCounter) will eventually be scheduled.
   * See also #getRealTimeInterval().
   * The realTime global field can be accessed like this:
   * \code
   * SoSFTime* realTimeField = (SoSFTime*)SoDB::getGlobalField( "realTime" );
   * \endcode
   */
  static void setRealTimeInterval(const SbTime &deltaT);

  /**
   * Returns how often the database is updating the @B realTime @b global field.
   * See also #setRealTimeInterval().
   * The realTime global field can be accessed like this:
   * @code
   * SoSFTime* realTimeField = (SoSFTime*)SoDB::getGlobalField( "realTime" );
   * @endcode
   */
  static const SbTime &getRealTimeInterval();

  /**
   * This sets the timeout value for sensors that are delay queue sensors (one-shot
   * sensors, data sensors). Delay queue sensors are triggered whenever there is idle
   * time. If a long period of time elapses without any idle time (as when there are
   * continuous events to process), these sensors may not be triggered. Setting this
   * timeout value ensures that if the specified length of time elapses without any
   * idle time, the delay queue sensors will be processed anyway.
   *
   * The default timeout for delay queue sensors is 0.083 seconds.
   * So if delay queue sensors are only triggered by the timeout,
   * then by default the viewer animation can only run at about
   * 12 frames per second. To trigger the delay queue sensors at,
   * for example, 30 frames per second, make this call:
   *
   * SoDB::setDelaySensorTimeout( 0.03f );
   */
  static void setDelaySensorTimeout(const SbTime &t);

  /**
   * Returns the current delay queue timeout value.
   */
  static const SbTime &getDelaySensorTimeout();

  /**
   * @B UNIX/Linux Only @b @BR
   * In order to keep timer and idle sensors running as expected, it is necessary
   * that an Open Inventor application not block while waiting for input. If the Open
   * Inventor application uses the SoXt component library, this can be handled
   * automatically. However, if the application is using its own event loop, this
   * function is provided as a wrapper around select() that will handle Open
   * Inventor tasks if necessary instead of blocking.
   * [OIV-WRAPPER-NOT-WRAP]
   */
  static int doSelect(int nfds, fd_set *readfds, fd_set *writefds,
                      fd_set *exceptfds, struct timeval *userTimeOut);

  /**
   * Returns whether multi-thread support is enabled in Open Inventor.
   * Always returns FALSE before SoDB::init or SoDB::threadInit has been called.
   */
  static SbBool isMultiThread();

  /**
   * Acquire the global scene graph write-lock.
   *
   * The calling thread will block until the write-lock is available
   * (no threads hold a global read-lock).  The global write-lock is exclusive.
   * Only a single thread can hold this lock and while it is held, no thread
   * can acquire a global read-lock.  While holding the global write-lock it is
   * safe to modify the scene graph including adding/removing nodes, modifying
   * field values, etc.  Do not hold the global write-lock longer than necessary.
   *
   * @B Note: @b Be sure the global write-lock is always released or there is a
   * good chance the application will "dead lock" because all standard actions
   * automatically attempt to acquire a global read-lock.
   */
  static void writelock();

  /**
   * Release the global scene graph write-lock.
   */
  static void writeunlock();

  /**
   * Acquire a non-exclusive global scene graph read-lock.
   *
   * The calling thread will block until a read-lock is available
   * (no thread is holding the global write-lock).  Multiple threads may
   * hold global read-locks at the same time.  While holding a read-lock
   * it is safe to traverse the scene graph and to query values of fields,
   * but not to modify the scene graph (see method SoDB::writelock).
   */
  static void readlock();

  /**
   * Release a non-exclusive global scene graph read-lock.
   */
  static void readunlock();

  /**
   * This method sets the maximum number of caches for nodes that
   * create render caches.  Examples of nodes that create render
   * caches are SoSeparator (OpenGL display lists) and SoTexture2
   * (OpenGL texture objects).  This method affects only nodes that
   * are created after it is called, not nodes that were created
   * before it.  Setting the number of caches to zero disables
   * render caching for all nodes created after the call.
   *
   * By default, each node maintains 2 render caches. (This is to
   * allow two different representations, e.g., filled and wireframe,
   * to both be cached.)  Each render cache uses memory, so
   * decreasing this number may decrease the memory requirements of
   * the application.  However multi-pipe applications should
   * generally set the number of render caches equal to the number
   * of pipes because pipes may not be able to share display lists.
   *
   * This value can also be specified globally using the environment
   * variable OIV_MAX_CACHES.  This value can also be specified
   * separately for classes that have a setNumRenderCaches method.
   */
  static void setNumRenderCaches( int num );

  /**
   * Returns the current maximum number of render caches. @BR
   * See method setNumRenderCaches().
   */
  static int  getNumRenderCaches();

  /**
   * This method specifies the way render caches (display lists) will be created.
   * By default, under each separator node, GL commands are merely compiled and
   * executed when the display list is created (mode = #COMPILE). This can increase
   * performances on some graphics board. With this method you can ask OIV to
   * execute GL commands as they are compiled into the display list (mode =
   * #COMPILE_AND_EXECUTE).
   * You can also use the #AUTO_RENDER_CACHE to allow Open Inventor to detect the best
   * mode.
   */
  static void setRenderCacheMode( RenderCacheMode mode );

  /**
   * Returns the current render cache mode.
   */
  static RenderCacheMode getRenderCacheMode();

  /**
   * Set the priority to children caching. When set to TRUE, render caches are built from the
   * "bottom up", meaning caches are built for the lowest level separators in the scene graph
   * first. Higher level separators will build caches during subsequent traversals.
   * Several scene graph traversals may be needed to build all possible caches.
   *
   * When set to FALSE, render caches are built from the top down, meaning caches are built
   * for the highest level separators in the scene graph first.
   *
   * Setting TRUE may increase rendering performance
   * because of a finer granularity in cache creation and calling.
   * The default is TRUE. Prior to Open Inventor version 6.0, the default was FALSE.
   * The value can also be set using the OIV_PRIORITIZE_CHILDREN_CACHING configuration parameter.
   */
  static void prioritizeChildrenCaching(SbBool onOff);

  /**
   * Returns the children caching priority state.
   */
  static SbBool isPrioritizedChildrenCaching();

  /**
   * Returns the current time.
   */
  static SbTime getCurrentTime();

SoEXTENDER_Documented public:
  /**
   * Registers a field conversion engine that can be used to
   * convert from one type of field to another. The type id's of the
   * two fields are passed in, as is the type id of the field
   * converter engine (derived from SoFieldConverter).
   */
  static void addConverter(SoType fromField, SoType toField,
                           SoType converterEngine);

  /**
   * Returns the field conversion engine registered for the two
   * given field types. If no such engine exists,
   * SoType::badType() is returned.
   */
  static SoType getConverter(SoType fromField, SoType toField);

  /**
   * Remove a previously added converter.
   */
  static void removeConverter(SoType fromField, SoType toField);

  /**
   * Returns current version number for license checking.
   * See method #LicenseCheck.
   *
   * If you need a descriptive string see #getVersion. If you just need the version 
   * number as an integer or string, see the macros in SoVersion.h.
   */
  static float getLicensingVersionNumber()
    { return (float)SO_INVENTOR_VERSION/1000;  /* SO_INVENTOR_VERSION is an int, e.g. 8600 */ }

  /**
   * Query if Open Inventor or an extension module is licensed on this machine.
   *
   * @return < 0 If product or version is NOT licensed on this machine. @BR
   *         >= 0 If product and version are licensed and can be used.
   *
   * Note: If productName is "ScaleViz" and ScaleViz is licensed on this machine.
   *       Then the return value is the number of render nodes allowed.
   *
   * @param productName : Product to be licensed (no blanks), e.g. OpenInventor or VolumeVizLDM.
   * @param version     : Version to be licensed (see #getLicensingVersionNumber).
   * @param licenseString : (optional) Embedded application password string, if any.
   * @param printWarning : If true, error and warning messages (if any) will be displayed to user.
   * @param errReport    : If not NULL, will be set to point to the text of the error
   *                       or warning messages (if any). @BR Note! This address is an internal static
   *                       buffer and must not be freed by the application.
   *
   * FlexNet Notes:
   * - Before checking for a FlexNet license token, LicenseCheck will automatically append 
   *   "SDK" to the productName when you need an SDK license to run on the current machine.
   * - If a FlexNet license is used to answer this query, then the corresponding
   *       FlexNet token will be checked out.
   * [OIVNET-WRAPPER STANDALONE]
   */
  static int LicenseCheck(const char *productName, float version,
                             const char *licenseString = NULL,
                             SbBool printWarning = TRUE, char **errReport=NULL);

SoEXTENDER public:
  /**
   * @deprecated Use SoDB::LicenseCheck instead.
   * @DEPRECATED_SINCE_OIV 8.0
   */
  SoDEPRECATED static inline int TGSLicenseCheck(const char *productName, float version,
                             const char *licenseString = NULL,
                             SbBool printWarning = TRUE)
  { return LicenseCheck(productName, version, licenseString, printWarning, NULL); }

#ifdef _WIN32
  /**
   * Registry Utility Function
   * You must have Administrator privileges to use these functions
   * All methods work off of the key
   * \\HKEY_CURRENT_USER\\SOFTWARE\\VSG
   * If the key does not exist it is created.
   * Call this if you are going to make multiple calls to getRegistryKeyValue
   */
  static long openRegistryKey(const SbBool readOnlyFlag=FALSE);

  /**
   * This calls RegQueryValueEx.
   * If openRegistryKey has not been called the key is opened and closed,
   * otherwise the currently open key is used.
   */
  static long getRegistryKeyValue(LPTSTR keyName,
                             LPTSTR lpValueName, // address of name of value to query
                             LPDWORD lpType,     // address of buffer for value type
                             LPBYTE lpData,      // address of data buffer
                             LPDWORD lpcbData,   // address of data buffer size
                             const SbBool readOnlyFlag=FALSE // readOnly access if TRUE
                             );

  /**
   * This closes the key opened by openRegistryKey
   */
  static long closeRegistryKey();

  /**
   * @deprecated Use SoDB::openRegistryKey instead.
   * @DEPRECATED_SINCE_OIV 8.1
   */
  SoDEPRECATED static long openTGSRegistryKey(SbBool flag=FALSE)
  { return SoDB::openRegistryKey(flag); }

  /**
   * @deprecated Use SoDB::getRegistryKeyValue instead.
   * @DEPRECATED_SINCE_OIV 8.1
   */
  SoDEPRECATED static long getTGSKeyValue(LPTSTR keyName, LPTSTR lpValueName, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData, SbBool flag=FALSE)
  { return SoDB::getRegistryKeyValue(keyName, lpValueName, lpType, lpData, lpcbData, flag); }

  /**
   * @deprecated Use SoDB::closeRegistryKey instead.
   * @DEPRECATED_SINCE_OIV 8.1
   */
  SoDEPRECATED static long closeTGSRegistryKey()
  { return SoDB::closeRegistryKey(); }

#endif //_WIN32


 SoINTERNAL public:

  /**
   * Called from SoDB::finish()
   */
  static void threadFinish();

  // The following two functions are internal-only for now because we do
  // not have a reliable cross-platform implementation of trylock for a
  // read-write lock.

  // Provides a global try-write-lock mutex (see threads/SbThreadRWMutex.h)
  static SbBool trywritelock();

  // Provides a global try-read-lock mutex (see threads/SbThreadRWMutex.h)
  static SbBool tryreadlock();

  //  Return whether mutexs should be created.
  static SbBool shouldCreateMutex();

  // Get ptr to global RWMutex for use with autolock
  // just an alias to SoInventorBase::getGlobalMutex()
  static SbThreadRWMutex *getGlobalMutex()
  { return SoInventorBase::getGlobalMutex(); }

  // Accesses sensor manager
  static SoSensorManager *getSensorManager();

  // Initialization routine with sensor manager as parameters.
  static void init(SoSensorManager *sensorMgr);

  // Accesses UNLOCK sensor manager
  SoSensorManager *getUnlockSensorManager();

  // Returns TRUE if database is initialized (for error checking)
  static bool isInitialized();

  // Returns FALSE if pick culling has been disabled
  static SbBool getPickCullingEnabled()
    { return m_pickCullingEnabled; }

  static const char* profileName;

  // This is called when some instance begins or ends a notification
  // process. It increments or decrements a counter of notifications
  // in progress. When the counter reaches 0, all priority 0
  // (immediate) delay queue sensors are triggered. By doing this,
  // all notification has a chance to finish before any evaluation
  // (due to data sensors, primarily) takes place.
  static void startNotify();
  static SbBool isNotifying();
  static void endNotify();

  // Enables/disables realTime sensor processing
  static void enableRealTimeSensor(SbBool enable);

  // Reads a base of any type, returning a pointer to it. Returns
  // FALSE on error.
  static SbBool read(SoInput *in, SoBase *&base);

  // 3DMSJava needs this sensor in order to delete the sensor callback
  // When using 3DMSJava, the realTime must never be updated
  // by InventorC++
  static SoTimerSensor *getRealTimeSensor();

  static SbBool m_readingAll;

  // Returns a copy of the path to the SoInput file (dirname).
  // If in does not contain a filename or if in is NULL, returns an empty string.
  // Returns empty string on error.
  static SbString getDirNameFromFullFileName(SoInput *in);

  //Returns if IvTune is allowed or not
  static void setIvTuneAllowed(SbBool ivTuneAllowed);

  //Returns if IvTune is allowed or not
  static SbBool getIvTuneAllowed();

  // Flag to control use of valid names
  static SbBool useNameCompat;

  // check database (only available in debug mode)
  static void checkDatabase( const char* className, void* thisPtr, SoType classType, SoType& classTypeId );

  // Returns the threadId of the first thread that called SoDB::init()
  // it is usefull for nodes that do not support Multi-thread
  static SbThreadId_t getMainThreadId();

  /** True if in main thread */
  static bool isInMainThread();

  // OpenInventor Java internal usage only
  static void resetMainThreadId();

  // declare TLS class
  SB_THREAD_TLS_HEADER();

 private:
#ifdef _WIN32
  // Key used by openRegistryKey, getRegistryKeyValue, and closeRegistryKey
  static HKEY s_vsgRegistryKeys;
#endif

	SoDB();
	virtual ~SoDB();

  // Protects notification
  static SbThreadMutex *notifyMutex;

  // Used to read all graphs and paths from the Open Inventor or VRML 2.0 file
  // specified by the given SoInput.
  static SoGroup *internalReadAll(SoInput *, SoGroup *);

  // Reads the graph from the OpenFlight file specified by the given SoInput.
  // This returns NULL if nothing is read.
  static SoSeparator *readAllOpenFlight(SoInput *in);

  // Reads the graph from the Dxf file specified by the given SoInput.
  // This returns NULL if nothing is read.
  static SoSeparator *readAllDxf(SoInput *in);

  // Reads the graph from the Acis file, Catia V5 file or STEP file
  // specified by the given SoInput.
  // This returns NULL if nothing is read.
  static SoSeparator *readAllAcis(SoInput *in);

  // Flag to control what time is used
  static SbBool useGlobalFieldTime;

  // Returned by getVersion()
  static const char *s_versionString;

  // Struct that contains all the information about the Global Database
  class SoGlobalDBInfos
  {
  public:
    // Constructor (allocate the sensorManager)
    SoGlobalDBInfos();

    // Init members that depends on node/field
    void init();
    // Cleanup members that depends on node/field
    void cleanup();

    // Destructor
    ~SoGlobalDBInfos();

    SoSensorManager* m_sensorManager;
    SoGlobalField* m_globalField;
    SoTimerSensor* m_realTimeSensor;
    SoSFRealTime *m_realTime;
    bool m_isInit;
  };

  // Thread local storage struct declaration
  struct MTstruct
  {
    SoGlobalDBInfos* globalDBInfos;
  };

  // get access to global database info
  // depending on the OIV mode used it is local to Thread or
  // global to all thread
  static SoGlobalDBInfos* getGlobalDBInfos();

  // WARNING: this static vars should never be access directly
  // always use getGlobalDBInfos() accessor
  static SoGlobalDBInfos* s_globalInfos;

  // How many current notifications
  static int notifyCount;

  static void realTimeSensorCallback(void *data, SoSensor *sensor);

  // List of valid header strings, and their corresponding callbacks
  static SbPList *headerList;

  // This dictionary stores field conversion engine types. The key
  // is created by mangling the types of the two fields to convert
  // from. The dictionary maps the key to the type of the conversion
  // engine.
  static SbDict *conversionDict;

  // Returns a conversionDict key from the two given field type id's.
  static uint32_t getConversionKey(SoType fromField, SoType toField);

  static void iv2_1PreCallback(void *userData, SoInput *in);
  static void iv2_0PreCallback(void *userData, SoInput *in);
  static void iv1_0PreCallback(void *userData, SoInput *in);
  static void iv2_0PostCallback(void *userData, SoInput *in);
  static void iv1_0PostCallback(void *userData, SoInput *in);

  // Global maximum number of render caches per node
  // (used by nodes that create OpenGL display lists or texture objects)
  static int m_numRenderCaches;
  static SbBool m_ivTuneAllowed;

  // Render cache creation mode
  // (used by nodes that create OpenGL display lists)
  static RenderCacheMode m_renderCacheMode;

  static SbBool m_pickCullingEnabled;

  static SbBool m_cacheChildrenFirst;

  static int s_initRefCount;

  static SbThreadId_t m_mainThreadId;

  friend class SoGlobalField;
};

#endif /* _SO_DB_ */


