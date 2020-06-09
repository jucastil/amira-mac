/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef SO_GL_DIPLAY_LIST
#define SO_GL_DIPLAY_LIST

#include <Inventor/SbBasic.h>
#include <Inventor/sys/SoGLType.h>

#include <Inventor/devices/SoBaseContextObject.h>

#ifdef _WIN32
#pragma warning( push )
#pragma warning(disable:4251)
#endif


#ifndef GLhandle
typedef unsigned long GLhandle;
#endif

class SoGLRenderCache;
class SoGLContext;
class SoState;

/**
 * @VSGEXT OpenGL display list management class.
 *
 * @ingroup helpers
 *
 * @DESCRIPTION
 *
 *  A helper class used to store OpenGL display-list-like objects.
 *  Currently, it can store either texture objects (which must be
 *  treated like display lists; texture objects bound inside a display
 *  list must be reference counted, etc) and display lists.
 *
 */

SoEXTENDER_Documented class INVENTOR_API SoGLDisplayList : public SoBaseContextObject
{
 public:

  enum Type
  {
    DISPLAY_LIST,
    TEXTURE1D_OBJECT,
    TEXTURE2D_OBJECT,
    TEXTURE2D_ARRAY_OBJECT,
    TEXTURE3D_OBJECT,
    TEXTURE_CUBE_MAP_OBJECT,
    FRAGMENT_PROGRAM_OBJECT,
    VERTEX_PROGRAM_OBJECT,
    TEXTURE_RECTANGLE_OBJECT,
    GLSL_FRAGMENT_SHADER_OBJECT,
    GLSL_VERTEX_SHADER_OBJECT,
    GLSL_GEOMETRY_SHADER_OBJECT,
    GLSL_PROGRAM_OBJECT,
    BUFFER_OBJECT,
    FRAMEBUFFER_OBJECT,
    ARRAY_BUFFER_OBJECT,
    ELEMENT_ARRAY_BUFFER_OBJECT,
    RENDERBUFFER_OBJECT,
    QUERY
  };

  /**
   * Constructor.  Takes state, type, and number of OpenGL objects to create.
   *
   * numToAllocate > 1 is currently only meaningful for display lists.
   *
   * Calls the appropriate glGen or glCreate function to
   * create empty objects/display lists.  If a texture object is
   * requested and texture objects are not supported, the type
   * will revert to DISPLAY_LIST.
   */
  SoGLDisplayList(SoState *state, Type type, int numToAllocate=1);

  /**
   * For DISPLAY_LIST objects, creates a new OpenGL display
   * list (calls glNewList).
   *
   * For other object types, calls the appropriate glBind or glUse function.
   */
  void open(SoState *state, int index = 0);

  /**
   * For DISPLAY_LIST objects, closes the display list (calls glEndList).
   * Returns FALSE if display list cannot be closed properly.
   * If the display mode is COMPILE_AND_EXECUTE , the display list will
   * automatically be invoked, else use the call() method to invoke it.
   * COMPILE_AND_EXECUTE is the default, see the setCompileAndExecute() method.
   *
   * For other object types, does nothing.
   */
  bool close(SoState *state);

  /**
   * For DISPLAY_LIST objects, invokes the display list (calls glCallList).
   *
   * For other object types, calls the appropriate glBind or glUse function.
   *
   * This automatically adds a dependency (calls addDependency()) if there
   * is another display list open in the state.
   * You can also use the get() methods below and make the OpenGL
   * calls yourself, in which case you should call the addDependency()
   * method directly to do the correct reference counting.
   */
  void call(SoState *state, int index = 0);

  /**
   * Adds a dependency on this object if there is another display list
   * open in the state.
   */
  void addDependency(SoState *state);

  /**
   * Returns the object type (display list, texture, etc)
   */
  Type getType() { return type; }

  /**
   * Returns number of OpenGL objects owned by this instance.
   */
  int getNumAllocated() { return num; }

  /**
   * Returns id of first OpenGL object owned by this instance.
   */
  GLuint getFirstIndex() { return startIndex; }

  /**
   * Returns the parent render cache (initially NULL).
   */
  SoGLRenderCache * getParentRenderCache()
  { return parentRenderCache; }

  /**
   * Sets the parent render cache.
   */
  void setParentRenderCache(SoGLRenderCache *parent);

  /**
   * Sets whether to use GL_COMPILE or GL_COMPILE_AND_EXECUTE
   * mode for display lists. Default is COMPILE_AND_EXECUTE.
   */
  void   setCompileAndExecute( SbBool flag );


  /**
   * Returns TRUE if current display list mode is GL_COMPILE_AND_EXECUTE.
   * Default is COMPILE_AND_EXECUTE.
   */
  SbBool getCompileAndExecute() const;

SoINTERNAL public:
  /**
   * this constructor is defined on ly to avoid compilation problems with template
   * but should never be called.
   */
    SoGLDisplayList(SoState *state);

 protected:

   // Destructor. (used by unref() )
   virtual ~SoGLDisplayList();

private:
  GLenum m_bufferObjectType;

  SoGLRenderCache *parentRenderCache;
  Type type;
  GLuint startIndex;
  int num;

  // Display list creation mode: GL_COMPILE or GL_COMPILE_AND_EXECUTE
  GLenum newListMode;
};

#ifdef WIN32
#pragma warning( pop )
#endif

#endif //SO_GL_DIPLAY_LIST
