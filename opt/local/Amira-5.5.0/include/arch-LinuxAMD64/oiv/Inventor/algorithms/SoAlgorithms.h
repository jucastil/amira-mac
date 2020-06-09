/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined SOALGORITHMS_H
#define SOALGORITHMS_H

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif


#include <Inventor/SbString.h>
#include <Inventor/algorithms/SoAlgorithmsDefs.h>
#include <Inventor/STL/vector>
#include <Inventor/threads/SbThreadMutex.h>

#include <Inventor/SoModule.h>
SO_MODULE_HEADER(SoAlgorithms, __INVALGORITHMSDLL)

class SoBufferObject;
class SoDeviceContext;

class SoDataExtract;
class SoSeismic;
class SoConversion;
class SoConvolution;
class SoArithmetic;
class SoLDMAlgorithms;

/** On WIN32 platforms we must export the function using the dllexport feature. */
/**
 * This macro allows you to build your algorithms module with the mandatory base functions.
 *
 * It declares and implements the createAlgorithmsInterface() function.
 * The initClass function of your module is automatically called by this function
 */
#define DECLARE_ALGORITHMS_MODULE( CLASS_NAME ) \
  extern "C" VC_DLL_EXPORT SoAlgorithms* createAlgorithmsInterface() \
  { \
     CLASS_NAME::init(); \
     return new CLASS_NAME(); \
  }

/**
* @VSGEXT Utility functions for loading algorithm modules
*
* @ingroup Algorithms
*
* @DESCRIPTION
*  This class provides convenience methods for loading an algorithm module,
*  extracting specific algorithm interfaces and creating appropriate
*  context and buffer objects for the device that implements the algorithms.
*
* Examples:
*
*
*/

class INVENTORALGORITHMS_API  SoAlgorithms
{
public:

  /** Static init function to initialize the algorithms module. 
   */
  static void init();

  /**
   * Returns TRUE if module is currently initialized.
   */
  static bool isInitialized();

  /** Static finish function to free the memory allocated by the algorithms module. 
   */
  static void finish();

  /** Algorithms interface constructor */
  SoAlgorithms();

  /** Algorithms interface destructor */
  virtual ~SoAlgorithms();

  /** Loads a module and returns an instance
    * of the implementation of SoAlgorithms in this module.
    *
    * If the module is already loaded this function just increments the reference count and returns
    * a new instance of the algorithms interface.
    *
    * @param moduleFileName The module filename.
    *                       See the description of this class for more information.
    *
    * @return An instance of the Algorithms interface from the module, or NULL if the module cannot be load.
    */
  static SoAlgorithms* loadAlgorithmsModule( const SbString& moduleFileName );

  /**
   * Unloads a module.
   *
   * The module is unloaded only if it is not used anymore, it uses a references counter
   * in order to figure out if the module can be unloaded or not.
   *
   * @param moduleFileName The module filename to unload.
   *
   */
  static SbBool unloadAlgorithmsModule( const SbString& moduleFileName );

  /**
   * Returns an instance of a SoBufferObject according to the hardware used
   * by the loaded module (eg. It returns an SoCudaBufferObject if a CUDA module was loaded.).
   *
   * If there is no loaded module this function returns an SoCpuBufferObject.
   *
   * @return An Instance of a SoBufferObject.
   */
  virtual SoBufferObject* createBufferObject();

  /**
   * Returns a DeviceContext that can be used with the algorithms module and
   * SoBufferObject returned by the createBufferObject function.
   *
   * @return An instance of an SoDeviceContext object.
   */
  virtual SoDeviceContext* createContext();


  /**
   * Returns an instance of the SoDataExtract interface defined in the loaded
   * module. If there is no loaded module it returns the default CPU version.
   *
   * @return Instance of the SoDataExtract interface.
   */
  virtual SoDataExtract* createDataExtractInterface();


  /**
   * Returns an instance of the SoSeismic interface defined in the loaded
   * module. If there is no loaded module it returns the default CPU version.
   *
   * @return Instance of the SoSeismic interface.
   */
  virtual SoSeismic* createSeismicInterface();



  /**
   * Returns an instance of the SoConversion interface defined in the loaded
   * module. If there is no loaded module it returns the default CPU version.
   *
   * @return Instance of the SoConversion interface.
   */
  virtual SoConversion* createConversionInterface();


  /**
   * Returns an instance of the SoConvolution interface defined in the loaded
   * module. If there is no loaded module it returns the default CPU version.
   *
   * @return Instance of the SoConvolution interface.
   */
  virtual SoConvolution* createConvolutionInterface();


  /**
   * Returns an instance of the SoArithmetic interface defined in the loaded
   * module. If there is no loaded module it returns the default CPU version.
   *
   * @return Instance of the SoArithmetic interface.
   */
  virtual SoArithmetic* createArithmeticInterface();


  /**
   * Returns an instance of the SoLDMAlgorithms interface defined in the loaded
   * module. If there is no loaded module it returns the default CPU version.
   *
   * @return Instance of the SoLDMAlgorithms interface.
   */
  virtual SoLDMAlgorithms* createLDMAlgorithmsInterface();

protected:

  /** Thread mutex to protect the initClass and the exitClass functions. */
  static SbThreadMutex s_initThreadMutex;

private:

  /** Basic structure to store the information about a loaded module. */
  struct Module
  {
    SbString name;
    void* func;
    unsigned int refCount;
  };

  /** List of loaded modules. */
  static std::vector< Module* > s_loadedModules;

  /** The init/exit references counter. */
  static int s_initRefCount;
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif // SOALGORITHMS_H

