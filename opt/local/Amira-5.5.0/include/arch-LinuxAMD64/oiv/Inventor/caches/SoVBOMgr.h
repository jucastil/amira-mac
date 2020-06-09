/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R.ALBOU (Dec 2003)
**=======================================================================*/

#ifndef _SO_VBO_MGR_
#define _SO_VBO_MGR_

#include <Inventor/STL/vector>
#include <Inventor/threads/SbThreadLocalStorage.h>

#define SO_MAX_VBO_IN_MGR 36

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

/*----------------------------------------------------------------------------*/

SoINTERNAL class INVENTOR_API SoVBOMgr
{
public:
  // Possible buffer type.
  // TEX_COORDS_BUFFER+n 0<n<31 : specifies the buffer for storing 
  // texture coordinate of the nth unit.
  enum BufferType {
    VERTEX_BUFFER,
    NORMAL_BUFFER,
    COLOR_BUFFER,
    INDEX_BUFFER,
    TEX_COORDS_BUFFER
  } ;

  // Returns an instance of SoVBOMgr if the VBO extension is available,
  // NULL otherwise.
  static SoVBOMgr *createInstance() ;

  // Should be called to delete an instance
  void unref(SoState *state=NULL) ;


  // Creates, if not already created by a previous call, and loads, one of the buffer specified 
  // by bufferType, with data.
  // Returns TRUE if the loading is successful, FALSE otherwise.
  // If the buffer is locked, data are not reloaded.
  // After this call, this buffer becomes active whatever the lock status.
  // context is the OpenGL context used by this buffer.
  SbBool loadData(int context, BufferType bufferType, int size, void *data) ;

  // Loads sub-data of the buffer specified by bufferType with data.
  // Considers that the buffer is active (bind called).
  // If the buffer is locked nothing is done.
  // context is the OpenGL context used by this buffer.
  void loadSubData(int context, BufferType bufferType, int offset, int size, void *data) ;

  //**************** Lock/Unlock a buffer ***************
  // context is the OpenGL context used by a buffer.
  // If context=-1, all buffers of bufferType will be unlocked 
  // -1 is ignored by lock().

  void lock(int context, BufferType bufferType) ;

  void unlock(BufferType bufferType, int context=-1) ;

  SbBool isLocked(int context, BufferType bufferType) ;

  // Unlock all texture buffers
  void unlockTextureBuffers(int context=-1) ;
  //*****************************************************

  // Binds one of the buffer specified by bufferType.
  // Returns the OpenGL target which could be GL_ARRAY_BUFFER or GL_ELEMENT_ARRAY_BUFFER.
  GLenum bind(int context, BufferType bufferType) ;

  // Desactivate the VBO usage.
  static void desactivate() ;

  // Indicates if VBO could be used.
  // If state is different from NULL, SoShapeHintsElement is used to
  // check if VBO should be use (cf SoShapeHints::useVBO).
  // If state is NULL, only the graphic board capabilities are checked.
  static SbBool canUseVBO(SoState *state=NULL) ;

  // Delete all vertex buffer objects which have not been deleted
  // when the destructor was called because the context associated
  // was different from the context at destruction time.
  static void deleteWaitingToBeFreed (int context) ;

  // bind and map buffer in Write mode
  void* map(int context, BufferType bufferType);

  // bind and unamp buffer
  void unmap(int context, BufferType bufferType);

SoINTERNAL public:
  // Info associated to a vertex buffer object
  class SoVBOInfo {
   public:
    /** Constructor */
    SoVBOInfo() ;

    /** Destructor */
    ~SoVBOInfo() ;

    /** Destroys a vertex buffer object */
    void destroy() ;

    // private members
  public:
    int     m_obj ;        // Open GL buffer object
    GLenum  m_usageHints ; // Usage associed to this buffer 
    bool    m_locked ;     // Indicate if the buffer is locked
  } ;

  static void initClass();
  static void exitClass();

  void unlockIgnoreContext(BufferType bufferType) ;

  SB_THREAD_TLS_HEADER();

private:
  // Constructor
  SoVBOMgr() ;

  // Destructor
  ~SoVBOMgr() ;

  // List of vertex buffer objects associated to one context
  class SoVBOContext {
   public:
    SoVBOContext(int context)
    { m_context = context ; }

    int       m_context ;
    SoVBOInfo m_VBOList[SO_MAX_VBO_IN_MGR] ;
  } ;

  // List of contexts containing vertex buffer objects
  typedef std::vector<SoVBOContext*> SoVBOContextsList  ;
  SoVBOContextsList m_VBOContextsList ;

  // Retreives a SoVBOContext associates to context.
  // Creates one if not found.
  SoVBOContext* getVBOContext(int context) ;

  // Per thread static storage.
  struct MTstruct
  {
    // List of all vertex buffer objects which have not been deleted
    // when the destructor was called because the context associated
    // was different from the context at destruction time.
    SoVBOContextsList* m_waitingToBeFreed ;
  };
};/*----------------------------------------------------------------------------*/

#ifdef WIN32
#pragma warning( pop )
#endif

#endif // _SO_VBO_MGR_
