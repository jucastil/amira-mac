/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined SOGLCONTEXT_H
#define SOGLCONTEXT_H

#include <Inventor/devices/SoDeviceContext.h>
#include <Inventor/devices/SoGLFormat.h>
#include <Inventor/STL/vector>
#include <Inventor/STL/list>
#include <Inventor/STL/map>
#include <Inventor/helpers/SbGlContextHelper.h>
#include <Inventor/threads/SbThreadSpinlock.h>
#include <Inventor/errors/SoError.h>

#include <Inventor/SbPList.h> // For SbStringList

#if defined(_WIN32)
#include <windows.h>
#endif

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

class SbThreadMutex;

/**
* @VSGEXT OpenGL context management class.
*
* @ingroup GLDevice
*
* @DESCRIPTION
*
* This class provides functions to manage OpenGL device contexts.
*
* Starting with Open Inventor 8.5, the application can control sharing
* of OpenGL contexts (previously this was done internally for rendering
* contexts).  When OpenGL contexts are shared it means that display
* lists, texture objects, buffer objects, etc created in any context in
* that share group can be used by any other context in that group.  This
* saves time and memory when rendering into multiple windows, buffers, etc.
*/

class INVENTORGL_API SoGLContext : public SoDeviceContext
{
public:

  /**
   * Sharing Policy. @BR
   * User can change sharing policy by defining the OIV_SHARE_LISTS environment variable.
   */
  enum SharedGroupPolicy
  {
    /** Disables context sharing (same behavior as v2.6 and older) */
    DISABLED,
    
    /**
     * Conservative sharing (not available on Unix) @BR
     * Only add context to a share group containing contexts with the
     * constraint (ex: same pixel format for SoGLContext objects).
     * This mode matchs the official behavior of the wglShareLists() function.
     * (Please refer to Microsoft documentation for more details.)
     */
    CONSERVATIVE,
    
    /**
     * Aggressive sharing (default) @BR
     * Tries to share contexts, independent of their sharing constraint.
     * When sharing succeeds, shared contexts are part of the same sharedGroup,
     * else, a new sharedGroup is created.
     */
   AGGRESSIVE
  };

  /**
   *  Constructor which creates an SoGLContext based on the attributes of the current context. @BR
   *  If the current context is NULL, the function tries to create a context on a temporary window.
   *  If this doesn't work, the resulting SoGLContext will not be valid!
   *
   *  @param shared Indicates if we want to share the context. If TRUE, context is shared with
   *  current context, depending on the currently defined SharedGroupPolicy. If FALSE, context is
   *  explicitly not shared.
   */
  SoGLContext( bool shared );

  /** 
   * Constructor which creates an SoGLContext based on the specifed parameters.
   *
   * On Microsoft Windows platforms the Display, VisualInfo and GLContext parameters
   * cannot be NULL. @BR
   * On Linux platforms the Display, Drawable, VisualInfo and GLContext parameters cannot
   * be NULL. @BR
   * On Mac platforms the Drawable, VisualInfo and GLContext parameters cannot
   * be NULL. @BR
   * Display is equal to zero for the first display, 1 for the second, ...
   */
  SoGLContext( SbGlContextHelper::Display dpy,
               SbGlContextHelper::VisualInfo vis,
               SbGlContextHelper::Drawable drawable,
               SbGlContextHelper::GLContext ctx );

  /** 
   * Constructor which creates a SoGLContext based on the specified parameters.
   *
   * The specified format must have been acticated before using it with this contructor.
   * The GLContext paramater cannot be NULL as long as this constructor is not supposed 
   * to create an OpenGL context but use an existing one. If the constructor must create a
   * context, you must use the constructor which takes only a SoGLFormat or the one which takes
   * a SoGLContext and a SoGLFormat.
   */
  SoGLContext( const SoGLFormat& format, SbGlContextHelper::GLContext ctx, SbGlContextHelper::Drawable drawable = 0 );

  /**
   * Constructor which creates a SoGLContext based on the specifed format. @BR
   * Note: Context will be shared with other contexts, depending on the currently
   * defined SharedGroupPolicy
   *
   * The specified format must have been activated before using it with this contructor.
   */
  SoGLContext( const SoGLFormat& format, SbGlContextHelper::Drawable drawable = 0 );

  /** 
   * Constructor which creates a SoGLContext based on the specified parameters. @BR
   * Note: Context will be shared with other contexts, depending on the currently defined
   * SharedGroupPolicy.
   *
   * On Microsoft Windows platforms the Display and VisualInfo parameters
   * cannot be NULL. @BR
   * On Linux platforms the Display, Drawable and VisualInfo parameters cannot
   * be NULL. @BR
   * On Mac platforms the Drawable and VisualInfo parameters cannot
   * be NULL. @BR
   * Display is equal to zero for the first display, 1 for the second, ...
   *
   * @param dpy The display/device context.
   * @param vis The visual/pixel format descriptor for the rendering context.
   * @param drawable The drawable (must be null under Windows).
   * @param shared Indicates if we want to share the context. If TRUE, context is shared with
   * one of the already created contexts, depending on the currently defined SharedGroupPolicy.
   * If FALSE, context is explicitly not shared.
   */
  SoGLContext( SbGlContextHelper::Display dpy,
               SbGlContextHelper::VisualInfo vis,
               SbGlContextHelper::Drawable drawable,
               bool shared = true );

  /**
   * Constructor which creates an SoGLContext based on the attributes of the specified context. 
   *
   * If @I shared @i is true then the created OpenGL context will be shared with the given context,
   * depending on the current SharedGroupPolicy.
   */
  SoGLContext( SoGLContext* context, bool shared );

  /**
   * Constructor which creates a SoGLContext shared with a specific context, but attached to
   * the display specified in the SoGLFormat.
   *
   * @param context The SoGLContext to be share with. Cannot be NULL.
   * @param format The format used for the drawable used by the new context.
   * @param drawable The drawable on which the context is created. Use the one from the context parameter if NULL is provided.
   */
  SoGLContext( SoGLContext* context, const SoGLFormat& format, SbGlContextHelper::Drawable drawable = 0 );
  
  /**
   * Bind the OpenGL context to the current thread.
   */
  virtual void bind();


  /**
   * Try to bind the OpenGL context to the current thread. @BR
   * Returns false if already bound, else calls bind() and returns true.
   */
  virtual bool tryBind();

  /**
   * Unbind the OpenGL context from the current thread.
   */
  virtual void unbind();

  /**
   * Returns true if the specified context and this context are shared.
   *
   * @return true if the two contexts are shared.
   */
  bool isSharedWith( const SoGLContext* context ) const;

  /**
   * Returns true if this context is valid.
   *
   * @return true if the context is valid.
   */
  bool isValid() const;

  /**
   * Returns the internal id for this context. @BR
   * The internal id is unique, it's not possible to get two contexts with the same id.
   *
   * @return The internal id of the context.
   */
  int getId() const;

  /**
   * Returns true if the specified context and this one are compatible. @BR
   * Compatible means that using a buffer from one of these contexts inside
   * the other will not require copying the data.
   * If two OpenGL contexts are compatible, they either have the same id or they are shared.
   *
   * @param context The context to compare with this one.
   * @return True if the specified context is compatible with this one.
   */
  virtual bool isCompatible( SoDeviceContext* context ) const;

  /** 
   * Returns true if this context is valid and currently active. @BR
   * If the current context is shared with this context then it returns true.
   */
  virtual bool isCurrent() const;

  /**
   * Returns the current active OpenGL context, if any, from the Open Inventor state.
   *
   * @param checkGLState If this parameter is true, the getCurrent()
   *  function checks if the actual OpenGL context is the same as the
   *  one Open Inventor thinks is current. This check is expensive if called many times.
   *
   * @return The current OpenGL context.
   */
  static SoGLContext* getCurrent( bool checkGLState = false );

  /**
   * Returns the OpenGL rendering context of this SoGLContext.
   *
   * @return The OpenGL rendering context.
   */
  const SbGlContextHelper::GLContext& getGLContext() const;

  /** 
   * Returns the SoGLContext which is attached to the specified context.
   *
   * @return The found SoGLContext of NULL if not found.
   */
  static SoGLContext* findGLContext( SbGlContextHelper::GLContext );

  /** 
   * Returns an SoGLContext that matches the specified SharedGroupDescription. @BR
   * On Windows, SharedGroupDescription is a PixelFormat id. @BR
   * On Unix, SharedGroupDescription is a display pointer.
   */
#if defined(_WIN32)
  typedef int SharedGroupDescription;
#else
  typedef SbGlContextHelper::Display SharedGroupDescription;
#endif
  static SoGLContext* findSharedContext( SharedGroupDescription );

  /**
   * Returns the Display of this SoGLContext.
   *
   * @return The Display.
   */
  const SbGlContextHelper::Display& getDisplay() const;

  /**
   * Returns the VisualInfo of this SoGLContext.
   *
   * @return The VisualInfo.
   */
  const SbGlContextHelper::VisualInfo& getVisualInfo() const;

  /**
   * Returns the SoGLFormat associated to the SoGLContext.
   *
   * @return the SoGLFormat.
   */

  const SoGLFormat& getFormat() const;

  /**
   * Returns the context corresponding to an internal id.
   *
   * @param id The internal id used to search for the context.
   * @return The context which has the specified id.
   */
  static SoGLContext* getContextFromId( int id );

  /** 
   * Returns the first context that belongs to the specified sharedIdGroup.
   *
   * @param sharedIdGroup The internal sharedIdGroup used to search for the context.
   * @return The first context that belongs to the specified sharedIdGroup.
   */
  static SoGLContext* getContextFromSharedId( int sharedIdGroup );

  /**
   * Returns true if the context is the current active context or
   * if it is shared with the current active context.
   */
  bool isValidForCurrent() const;

  /**
   * Assert this context and the current active context are the same.
   */
  void assertContext() const;

  /**
   * Swaps the buffers for the desired plane.
   *
   * -1 Uses the value stored in the SoGLFormat, which is set to the main plane by default.
   *  0 If there is an overlay context and we want to swap the main plane
   *  1 If there is an overlay context and we want to swap the overlay plane
   */
  bool swapBuffers( int plane = -1 );

  /** 
   * Returns an SbString containing the supported extensions for this context.
   */
  SbStringList getSupportedExtensions();

  /** Returns the current sharedGroupPolicy */
  static SharedGroupPolicy getSharedGroupPolicy();

  /** Force the context to be shared following the current SharedPolicy. */
  void applySharedGroupPolicy();

  SoINTERNAL public:

  static void initClass();
  static void exitClass();

  /** 
   * Returns the current active OpenGL context from the OpenGL state. @BR
   * This function can be used to ensure a valid state when makeCurrent() 
   * calls are made by a third party API.
   * 
   * @param supposedContext This parameter is used to speed up the process,
   * when the context is supposed to be current. Mainly used by the getCurrent()
   * function to ensure that the context on the internal stack is the actual one.
   *
   * @return The actual SoGLContext according to the OpenGL state.
   */
  static SoGLContext* getActualCurrentContext( SoGLContext* supposedContext );

  /** This function locks the data mutex. */
  static void lockListsMutex();

  /** This function unlocks the data mutex. */
  static void unlockListsMutex();

  /** This functions sets a user data. This function
    * should be used only by the viewers to store platform specific
    * data. */
  void setUserData( void* data )
  {
    m_userData = data;
  }

  /** Returns previously stored user data pointer */
  void* getUserData() const
  {
    return m_userData;
  }

  /** Adds the shared context to interna list of shared contexts and update the 
    * sharedId with the one from sharedContext */
  bool setSharedWith( SoGLContext* sharedContext );

  // internally used by PBuffer to change the display.
  void forceDisplay( const SbGlContextHelper::Display& display );

  // Used internally in remote to update the drawable (Linux only)
  void forceDrawable( const SbGlContextHelper::Drawable& drawable );

  // Used internally to avoid the destruction of the context
  // in some cases, like Qt because Qt destroy the context.
  void forceContext( const SbGlContextHelper::GLContext& context )
  {
    m_context = context;
  }

  // Used internally to get the drawable of this context
  const SbGlContextHelper::Drawable& getDrawable() const
  {
    return m_drawable;
  }

  // These methods return a pointer to the GLEWContext associated to the current context.
  static void* glewGetCurrentContextIV(const bool printError=false)
  {
    SoGLContext* ctx = SoGLContext::getCurrent();

    if ( ctx )
      return ctx->glewGetContextIV();
    else
    {
      if (printError)
        SoError::post("SoGLContext : Trying to access a NULL context");
      return NULL;
    }
  };

#  if defined(_WIN32)
  static void* wglewGetCurrentContextIV(const bool printError=false)
  {
    SoGLContext* ctx = SoGLContext::getCurrent();

    if ( ctx )
      return ctx->wglewGetContextIV();
    else
    {
      if (printError)
        SoError::post("SoGLContext : Trying to access a NULL context");
      return NULL;
    }
  };
#  elif !defined(__APPLE__) || defined(GLEW_APPLE_GLX)
  static void* glxewGetCurrentContextIV(const bool printError=false)
  {
    SoGLContext* ctx = SoGLContext::getCurrent();

    if ( ctx )
      return ctx->glxewGetContextIV();
    else
    {
      if (printError)
        SoError::post("SoGLContext : Trying to access a NULL context");
      return NULL;
    }
  };
#  endif // _WIN32

  // These methods return a pointer to the GLEWContext associated to this context.
  struct GLEWContextStruct* glewGetContextIV() const
  { return m_glewContext; }

#  if defined(_WIN32)
  void* wglewGetContextIV() const
  { return m_wglewContext; }

#  elif !defined(__APPLE__) || defined(GLEW_APPLE_GLX)
  void* glxewGetContextIV() const
  { return m_glxewContext; }

#  endif // _WIN32

  bool isGLEWInitialized() { return m_glewInit; }
  bool initGLEW();
  void cleanGLEWContext();

  virtual SbString getInfos();

  /** Prints out the information about the context. 
    * Available on X11 Only.
    */
  void printInformation();

  /** Prints information about the current context.
    * Available on X11 Only.
    */
  static void printCurrentContextInformation();

  /** Prints information about each context.
    * Available on X11 Only.
    */
  static void printContextsInformation();

  /**
   * Prevents deletion of the native openGL context in SoGLContext.
   * 
   * Note: Can be useful when the context will be destroyed by a third party
   *       API such as wxWidgets, to prevent crashes.
   */
  void setNoGLContextDelete() { m_noOGLContextDelete = true; };

  /**
   * This function is used to indicates to the SoGLContext which use the specified
   * drawable that it is not valid anymore. This prevent unexpected bind when there
   * is no valid drawable for the context.
   */
  static void invalidateDrawable(SbGlContextHelper::Drawable drawable);

  /**
   * This function is used to indicates to the SoGLContext which use the specified
   * display that it is not valid anymore. This prevent unexpected bind when there
   * is no valid display for the context.
   */
  static void invalidateDisplay(SbGlContextHelper::Display display);

protected:
  /**
   * Destructor (used by ref/unref)
   */
  virtual ~SoGLContext();

private:

  virtual bool setSharedWith( SoDeviceContext* sourceCtx );

  /** This list keep an eye on the binded contexts for each thread. */
  static std::map< SbThreadId_t, std::vector< SoGLContext* > > s_bindedContexts;

  bool initContext( SoGLContext* sourceContext, bool shared );
  void initGLEWContext();
  void preInitContext();
  bool postInitContext();

  void checkContextParameters( const char* function );

  typedef std::list< SoGLContext* > SoGLContextList;

  /** Static internal list of available contexts. */
  static SoGLContextList s_contexts;

  /** Static variable which indicates the first available id for the contexts. */
  static int s_firstAvailableId;

  /** Static data mutex. */
  static SbThreadSpinlock s_contextsMutex;

  /** The internal id of the context. */
  int m_id;

  SbGlContextHelper::GLContext m_context;
  SbGlContextHelper::Drawable m_drawable;

  SoGLFormat m_format;

  void* m_userData;

  // GLEWContext associated to this rendering context.
  struct GLEWContextStruct* m_glewContext;
#  if defined(_WIN32)
  struct WGLEWContextStruct* m_wglewContext;
#  elif !defined(__APPLE__) || defined(GLEW_APPLE_GLX)
  void* m_glxewContext;
#  endif // _WIN32

  bool m_glewInit;
  bool m_noOGLContextDelete;

  bool m_drawableIsValid;
  bool m_displayIsValid;

  static int s_checkContext;

  static int s_oivCompatibilityMode;

  /** Current global sharedGroupPolicy. */
  static SharedGroupPolicy s_sharedGroupPolicy;
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif


#endif //SOGLCONTEXT_H

