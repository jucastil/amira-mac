/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined SOCUDACONTEXT_H
#define SOCUDACONTEXT_H

#include <Inventor/devices/SoDeviceContext.h>
#include <Inventor/threads/SbThread.h>
#include <Inventor/threads/SbThreadMutex.h>

#include <Inventor/STL/map>
#include <Inventor/STL/vector>

#include <Inventor/cuda/SoCudaDefs.h>

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

class SoCudaDevice;

/**
* @VSGEXT CUDA context management class
*
* @ingroup CudaDevice
*
* @DESCRIPTION
*
* This class provides functions to manage CUDA contexts. Each context defines a 
* private working area for the threads which use it. 
*
* Before using any CUDA contexts the application must initialize the Open
* Inventor CUDA module by calling SoCuda::init().
*
* A valid CUDA context is required to use CUDA buffer objects, to call CUDA
* functions or to execute CUDA algorithms (e.g. SoCudaConvolution).
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
*  SoCuda::init();
*  SoCudaDevice* pMainDevice = SoCudaDevice::findFirstAvailableDevice();
*  if ( pMainDevice ) {
*    SoCudaContext* pContext = new SoCudaContext( pMainDevice );
*    if ( pContext ) {
*      pContext->bind();
*      SoCudaHandle* pHandle = SoCuda::findFunction( "ModuleName", "FunctionName" );
*      if ( pHandle ) {
*        SoCudaApi::launch( pHandle, 10, 1 );
*        SoCudaApi::freeHandle( pHandle );
*      }
*      pContext->unbind();
*    }
*  }
*  SoCuda::finish();
*  \endcode
*
* @SEE_ALSO
*
*   SoCuda, SoCudaApi, SoCudaDevice, SoCudaBufferObject,
*   SoCudaArithmetic, SoCudaConversion, SoCudaConvolution, SoCudaSeismic
*
* [OIVJAVA-WRAPPER-CLASS NO_WRAP]
* 
*/

class INVENTORCUDA_API SoCudaContext : public SoDeviceContext
{
public:
  /**
   * Regular constructor.
   *
   * @param device Device on which to create the context.
   */
  SoCudaContext( SoCudaDevice* device );

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
   * @return The current CUDA context.
   */
  static SoCudaContext* getCurrent();


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

protected:

  /** Destructor (used by ref/unref) */
  virtual ~SoCudaContext();

  /** This function locks the data mutex. */
  static void lockListsMutex();

  /** This function unlocks the data mutex. */
  static void unlockListsMutex();

private:

  /** The context data. */
  void* m_context;

  /** Static data mutex. */
  static SbThreadMutex s_contextsMutex;

  /** This list keep an eye on the binded contexts for each thread. */
  static std::map< SbThreadId_t, std::vector< SoCudaContext* > > s_bindedContexts;

SoINTERNAL public:

  virtual SbString getInfos();

};

#ifdef _MSC_VER
#pragma warning( pop )
#endif


#endif //SOCUDACONTEXT_H

