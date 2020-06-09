/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined SoOpenCLCONTEXT_H
#define SoOpenCLCONTEXT_H

#include <Inventor/devices/SoDeviceContext.h>
#include <Inventor/threads/SbThread.h>
#include <Inventor/threads/SbThreadMutex.h>

#include <Inventor/STL/map>
#include <Inventor/STL/vector>

#include <Inventor/OpenCL/SoOpenCLDefs.h>

#include <Inventor/sys/SoCL.h>

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

class SoOpenCLDevice;

/**
* @VSGEXT OpenCL device context API
*
* @ingroup OpenCLDevice
*
* @DESCRIPTION
*
* This class provides functions to manage OpenCL contexts. Each context defines a 
* private working area for the threads which use it. 
*
* Before using any OpenCL contexts the application must initialize the Open
* Inventor OpenCL module by calling SoCuda::init().
*
* A valid OpenCL context is required to use OpenCL buffer objects, to call OpenCL
* functions or to execute OpenCL algorithms (e.g. SoOpenCLConvolution).
*
* The context can only be current for one thread at a time.  If thread1 binds a
* context, then any other thread that tries to bind the context will block until
* thread1 unbinds the context.
*
* @EXAMPLE
*
* \code
*  // OpenInventor Initialization
*  ...
*
*  SoOpenCL::init();
*  SoOpenCLDevice* pMainDevice = SoOpenCLDevice::findFirstAvailableDevice();
*  if ( pMainDevice ) {
*    SoOpenCLContext* pContext = new SoOpenCLContext( pMainDevice );
*    if ( pContext ) {
*      pContext->bind();
*      SoOpenCLHandle* pHandle = SoOpenCL::findFunction( "ModuleName", "FunctionName" );
*      if ( pHandle ) {
*        SoOpenCLApi::launch( pHandle, 10, 1 );
*        SoOpenCLApi::freeHandle( pHandle );
*      }
*      pContext->unbind();
*    }
*  }
*  SoOpenCL::finish();
*  \endcode
*
* @SEE_ALSO
*
*   SoOpenCL, SoOpenCLApi, SoOpenCLDevice, SoOpenCLBufferObject,
*   SoOpenCLArithmetic, SoOpenCLConversion, SoOpenCLConvolution, SoOpenCLSeismic
*
* [OIVJAVA-WRAPPER-CLASS NO_WRAP]
* 
*/

class INVENTOROPENCL_API SoOpenCLContext : public SoDeviceContext
{
public:
  /**
   * Regular constructor.
   *
   * @param device Device on which to create the context.
   */
  SoOpenCLContext( SoOpenCLDevice* device );

  /**
   * Bind this context to the current thread.
   *
   * @NOTES
   * When the context is bound it is locked, so if a separate thread trys to bind it,
   * that thread will be locked until the first thread calls the unbind function.
   */
  void bind();

  /**
   * Unbind this context from the current thread and unlock it. @BR
   * After this call the context can be bound in any thread.
   */
  void unbind();

  /**
   * Returns the currently bound context (if any) for the current thread.
   *
   * @return The current OpenCL context.
   */
  static SoOpenCLContext* getCurrent();

  /**
   * Query if the context is valid and currently active.
   */
  virtual bool isCurrent() const;

  /**
   * Indicates if the specified context and this one are compatible. @BR
   *
   * Compatible means that using a buffer from one of these contexts inside 
   * the other will not require copying the data.
   *
   * @param context The context to compare with this one.
   * @return True if the specified context is compatible with this one.
   */
  virtual bool isCompatible( SoDeviceContext* context ) const;

  /**
   * OpenCL context accessor 
   */
  inline cl_context getOpenCLContext() const
  { return m_context; }

  /**
   * OpenCL context accessor 
   */
  inline cl_command_queue getOpenCLCommandQueue() const
  { return m_command_queue; }

  /**
   * Return attached device.
   */
  inline SoOpenCLDevice *getDevice() const
  { return m_device; }

protected:
  /** Destructor (used by ref/unref) */
  virtual ~SoOpenCLContext();

  /** This function locks the data mutex. */
  static void lockListsMutex();

  /** This function unlocks the data mutex. */
  static void unlockListsMutex();

private:

  /** The context data. */
  cl_context m_context;

  /** The default command queue attached to this context */
  cl_command_queue m_command_queue;

  /** Static data mutex. */
  static SbThreadMutex s_contextsMutex;

  /** This list keep an eye on the binded contexts for each thread. */
  static std::map< SbThreadId_t, std::vector< SoOpenCLContext* > > s_bindedContexts;

  /** The attached device */
  SoOpenCLDevice *m_device;

SoINTERNAL public:

  virtual SbString getInfos();

};

#ifdef _MSC_VER
#pragma warning( pop )
#endif


#endif //SoOpenCLCONTEXT_H

