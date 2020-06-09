/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : J.HUMMEL (Dec 2002)
** Modified by : T.DUFOUR (MMM yyyy)
**=======================================================================*/
#ifndef  _SO_LDM_LARGE_DATA_MANAGEMENT_
#define  _SO_LDM_LARGE_DATA_MANAGEMENT_

class SoLDMTileManager;
class SoLDMTileVisitor;
class SoLDMNodeFrontManager;
class SoLDMTextureManager;
class SoLDMGeometry;
class SoLDMResourceManager;
class SoLDMMediator;
class SoAlgorithms;
class SoAction;

#include <Inventor/nodes/SoSubNode.h>

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

#include <LDM/SoLDM.h>

/**
* @LDMEXT Large Data Management
*
* @ingroup LDMKernel
*
* @DESCRIPTION
*
* This class is only needed for advanced users who intend to extend or replace
* internal LDM algorithms.
*
* This class is used by the LDM (Large Data Management)
* managers to communicate with each other.
*
* @SEE_ALSO
* SoLDMNodeFrontManager, SoLDMResourceManager, SoLDMTileManager
*
*/
SoEXTENDER_Documented class LDM_API SoLDMLargeDataManagement
{

public:

   /**
    * global initialization called once by the module using LDM
    * [OIV-WRAPPER-NO-WRAP] 
    */
   static void init();

   /**
    * global deinitialization called once by the module using LDM
    * [OIV-WRAPPER-NO-WRAP] 
    */
   static void finish();

  /**
   * Returns TRUE if module is currently initialized.
   * [OIV-WRAPPER-NO-WRAP]
   */
  static bool isInitialized();

  /**
   * Constructor.
   */
   SoLDMLargeDataManagement();

  /**
   * Destructor.
   */
   virtual ~SoLDMLargeDataManagement(){};

  /**
   * The reset function is useful when using a customized LDM manager.
   * When the SoDataSet node changes data then the reset function will
   * be called if any cache needs to be deleted or any data reseted.
   */
  virtual void reset(){};

  //------------------------------------------------------------------------------

SoINTERNAL public:

  /**
   * Sets the associated data set.
   */
  void           setMediator(SoLDMMediator* m);
  inline SoLDMMediator* getMediator() const;

  /**
   * Return true if LDM must create threads
   */
  static bool needCreatingThreads();

  /**
   * This function returns the pointer on the Algorithms module use for computation.
   */
  static SoAlgorithms* getAlgorithmsInterface();

  /** True in multipipe if doing rendering in main thread */
  static bool isInMainMultipipeThread(SoAction* action);

  /** helper function, return true if  p1.id < p2.id */
  inline static bool lessId(const SoLDM::DataSetIdPair& p1, const SoLDM::DataSetIdPair& p2)
  {
    return p1.second < p2.second;
  }

SoEXTENDER protected:

  SoLDMTileManager      *getTileManager() const;
  SoLDMTileVisitor      *getTileVisitor() const;
  SoLDMNodeFrontManager *getNodeFrontManager() const;
  SoLDMTextureManager   *getTextureManager() const;
  SoLDMGeometry     *getVVizGeometry() const;
  SoLDMResourceManager  *getResourceManager() const;

private:
  SoLDMMediator* m_mediator;
  static int s_initRefCount;
  static const char* s_versionString;

  static SoAlgorithms* s_algorithmsInterface;
  static bool m_envNeedCreateThread;

  static bool s_useCuda;
  static bool s_useOpenCL;
};
//--------------------------------------------------------------------------------

/*******************************************************************************/
SoLDMMediator*
SoLDMLargeDataManagement::getMediator() const
{
  return m_mediator;
}


//--------------------------------------------------------------------------------
inline SoAlgorithms*
SoLDMLargeDataManagement::getAlgorithmsInterface()
{
  return s_algorithmsInterface;
}


//--------------------------------------------------------------------------------

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif // _SO_LDM_LARGE_DATA_MANAGEMENT_
