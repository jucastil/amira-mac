/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _SO_MEDIATOR_
#define _SO_MEDIATOR_

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

#include <Inventor/STL/vector>
#include <Inventor/SbBox.h>
#include <LDM/SoLDMTileID.h>
#include <LDM/SoLDMTileManager.h>
#include <LDM/SoLDMResourceManager.h>
#include <LDM/nodes/SoLDMResourceParameters.h>

#include <LDM/SoLDMDataAccess.h>

#include <LDM/elements/SoDataSetElement.h>


// LDM
class SoLDMTileVisitor;
class SoLDMProximityVisitor;
class SoLDMMultiIOTileManager;
class SoLDMNodeFrontManager;
class SoLDMTextureManager;
class SoLDMGeometry;
class SoLDMResourceManager;
class SoLDMDataEditor;
class SoDataCompositor;
class LDMDefaultSliceAccessor;
class SoGLRenderAction;
class SoDataSet;
class SoState;
class SoTimeHints;
class SoLdmParameterNode;
class SoBufferObject;
class SbThreadSemaphore;
class SoDataSetId;
class SoLdmValuationAction;
class SoLDMTileInfo;

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
*   SoDataSet
*/
SoEXTENDER_Documented class LDM_API SoLDMMediator
{
public:
  /** Constructor */
  SoLDMMediator();

  /** Destructor */
  virtual ~SoLDMMediator();

SoEXTENDER public:

  void registerNode(const SoLDM::DataSetIdPair& dsIdPair, bool sync);
  void unregisterNode(const SoLDM::DataSetIdPair& dsIdPair, SoLDMMediator *newMediator = NULL);

  void readTile(int dataSetId, SoLDMTileID tileID, unsigned char* buffer, bool transform) ;

  void readTile(const int dataSetId, const SoLDMTileID tileID, SoBufferObject* buffer, const bool transform) ;

  size_t readTile(SoLDMTileInfo* tileInfo, const int dataSetId, bool transform);

  uint64_t getTileSize(int dataSetId, const SoLDMTileID* tileId = NULL)const ;
  SbVec3i32 getTileDimension()const ;

  const SbVec3i32& getDimension()const ;
  const SbBox3f&   getExtent()const ;
  int getOverlapping() const;

  void renderNotify()const;

  /**
   * Returns a vector containing the current data set Ids.
   */
  const std::vector<int>& getNumData() const ;

  /**
   * Returns a vector containing the current data set Ids
   * which contains time dependant data.
   *
   * @NOTES
   *    Only supported by ReservoirViz module extension.
   */
  const std::vector<int>& getNumTimeDependantData() const ;

  /**
   * Returns a vector containing the current data set Ids
   * which contains time independant data.
   */
  const std::vector<int>& getNumTimeIndependantData() const ;

  /**
   * Indicates if a data is time dependant.
   *
   * @NOTES
   *    Only supported by ReservoirViz module extension.
   */
  SbBool isDataTimeDependant(unsigned short id) const ;

  /**
   * Returns the current step.
   *
   * @NOTES
   *    Only supported by ReservoirViz module extension.
   */
  unsigned short getCurrentTimeStep() const ;

  /**
   * Returns the number of time steps.
   *
   * @NOTES
   *    Only supported by ReservoirViz module extension.
   */
  unsigned short getNumTimeSteps() const ;

  SbBool getBbox(SoLDMTileID tileID, SbBox3f& box)const;
  bool getCenter(SoLDMTileID tileID, SbVec3f& center)const;

  //stuff I dont know what to do with yet
  SbBool getListChange(){return m_listChange;};

  ////// for multi-data //////
  int getDataEntry(unsigned short id)const ;
  int getDataEntry(SoDataSet*)const ;

  /** Return true if volume don't have the same tile size, borders... */
  inline bool hasMultiDataError() const;

  ////////////////////////////
SoINTERNAL public:

  /** Register given dataset with the list of ids */
  void registerWithIds(SoDataSet* ds, std::vector<int> ids, bool sync);

  /** Unregister all ds/id pair with the given ds */
  void unregisterAllIds(SoDataSet* ds, SoLDMMediator* newMediator = NULL);

  /** Remove all dataset */
  void unregisterAll();

  //for user defined LDM component
  bool m_userVisitor;
  SoLDMProximityVisitor*   m_internalVisitor;
  bool m_userTileManager;
  SoLDMMultiIOTileManager* m_internalTileManager;
  SoTimeHints* getCurrentTimeHints() const { return m_currentTimeHints; }
  SoLDMTileManager* getTileManager() { return m_tileManager; }
  SoLDMTextureManager*  getTextureManager() { return m_textureManager; }
  SoLDMGeometry*    getVVizGeometry() { return m_vvizGeometry; }

  SoLDMTileManager::LDMSliceAccessor* getSliceAccessor(const SoLDM::DataSetIdPair& p)const;
  void startRenderTraversal(SoLdmValuationAction*, SoDataSet*);

  void updateRegions(const SbBox3i32* region, int numRegions);
   /*
  * This function will only be called if in multiple data mode.
  * Called to check if the list of SoDataSet currently stored in the state are also in the list
  * of data set registered to this tile manager (subsequent calls to registerVolumeData).
  * Allows to detect scene graph change ( e.g. a switch node was turned off, the SoDataSet under
  * the switch node is still registered in the tile manager but is not part of the state anymore ).
  * The data compositor present in the state (if any) is also passed to check if it corresponds to the one
  * used by the tile manager (getVolumeData()->getDataCompositor()).
  * If any change occured, tile manager's state must be set accordingly.
  */
  void checkList(SoAction* action, SoDataCompositor* dc);

  //Return the biggest buffer id in the m_volumeDataList. When a dataset is no more in the
  //state but is still registered(because of a switch change or a delayed delete in ScaleViz)
  //this number is different from m_volumeDataList.size()-1. So this is this value which must
  //be used for SoLDMTileInfo::extendNumBuffer(int).
  //Ex: bufferIDs(0, 1, 2) -> bufferIDs(0, 2) and m_volumeDataList.size(3) -> m_volumeDataList.size(2)
  int getBiggestBufferEntry() const;

  //Do a start/endNumDataNotify without sync in order to be sure that SoLDMMultiIOTileManager::loadingThreadRoutine
  //is running (if there is at least one dataset registered)
  void restartLoadingThread();

  // SoDataSet ids vectors
  void updateDataIds() ;

  SoDataSet* getVolumeOfId(unsigned short dataSetId)const;
  void getVolumeElements(SoLDM::DataSetIdPairList& dsIdPairList) const;

  /** Return the list of registered dataset without their ids */
  void getDataSetList(SoLDM::DsVector& dsList) const;

  /** Return ids associated to given dataset */
  void getDataSetIds(const SoDataSet* ds, std::vector<int>& ids) const;

  /**
   * Returns the first data set registered in data set list.
   */
  inline SoDataSet* getFirstDataSet() const;

  /**
   * Returns a vector containing the current dataset/Id pairs
   * which contains time dependant data.
   */
  inline const SoLDM::DataSetIdPairList& getTimeDependantDsIds() const { return m_dataTimeDepDsIds; }

  /**
   * Returns a vector containing the current dataset/Id pairs
   * which contains time dependant data.
   */
  inline const SoLDM::DataSetIdPairList& getTimeIndependantDsIds() const { return m_dataTimeIndDsIds; }

  //After this call, data handled by this mediator will be loaded by LDM's threads
  void addToLDM();

  SoDataCompositor* getDataCompositor()const { return m_dc; }
  void setDataCompositor(SoDataCompositor *dc);

  /// multi-data list ////
  struct DataSetInfo
  {
    SoLDM::DataSetIdPair dsIdPair;
    int bufferId;
    bool m_timeDependent;
  };
  typedef std::vector<DataSetInfo> DataSetInfoList;

  DataSetInfoList & getVolumeDataList();

SoINTERNAL public:
  SoLDMTileManager      *m_tileManager;
  SoLDMTileVisitor      *m_tileVisitor;
  SoLDMNodeFrontManager *m_nodeFrontManager;

protected:
  SoLDMTextureManager   *m_textureManager;
  SoLDMGeometry     *m_vvizGeometry;
  SoDataCompositor      *m_dc;

private:
  const DataSetInfo& getDataInfo(const SoLDM::DataSetIdPair& dsIdPair) const;

  bool isUsedByLDM() { return m_isUsedByLDM; }
  void setUsedByLDM(bool flag) { m_isUsedByLDM = flag; }
  bool m_isUsedByLDM;

  // Time Series variables
  SoTimeHints *m_currentTimeHints ;
  int m_numTimeSteps ;

  // SoDataSet ids vectors
  std::vector<int> m_dataTimeDepIds ;    // vector containing the current volume Ids for time dependant data
  std::vector<int> m_dataTimeIndIds ;    // vector containing the current volume Ids for time independant data
  std::vector<int> m_dataIds ;           // vector containing the current volume Ids

  /**
   * vector containing the current volume ds/Ids for time dependant data
   * sorted by ds pointer
   */
  SoLDM::DataSetIdPairList m_dataTimeDepDsIds;

  /**
   * vector containing the current volume ds/Ids for time independant data
   * sorted by ds pointer
   */
  SoLDM::DataSetIdPairList m_dataTimeIndDsIds;

  // Type of data sets contained by the mediator
  enum DataTimeStatus {
    ONLY_TIME_IND,          // only time independent data sets
    ONLY_TIME_DEP,          // only time dependant data sets
    BOTH_TIME_IND_AND_DEP   // both time dependant and time independant data sets
  } ;

  DataTimeStatus m_dataTimeStatus ;
  bool m_dataTimeStatusChanged ;

  std::vector<DataSetInfo> m_volumeDataList;
  bool isInList(const SoLDM::DataSetIdPair& dsIdPair)const;

  // Available buffer entries (ie id) for time independant data
  std::vector<int> m_availBufferEntryTimeInd;

  // Available buffer entry (ie id) for time dependant data
  std::vector<int> m_availBufferEntryTimeDep;

  void addToList(const SoLDM::DataSetIdPair& dsIdPair);
  void removeFromList(const SoLDM::DataSetIdPair& dsIdPair);
  void setListChange(bool val){m_listChange = val;};
  bool m_listChange;
  /////////////////////////

  void createLDMCore();
  void deleteLDMCore();

  void setMinResolutionThreshold();

  /**
   * Returns true if dataset list can be used in multidata mode.
   * (check tilesize, tile dim, overlapping)
   */
  bool isMultiDataPossible();

  /** True if there is a multidata error */
  bool m_multiDataError;

  /** If true display debug infos */
  static int s_debugMediator;

//////////////////////////////////////////////////////////////////////////
//////////////////////// INNER CLASSES ///////////////////////////////////
SoEXTENDER_Documented public:

  /**
  *
  * @LDMEXT Data set LDM manager access.
  *
  * @ingroup LDMKernel
  *
  * @DESCRIPTION
  * This class contains all functions in charge of setting/getting LDM managers.
  * The LDM manager classes are declared SoEXTENDER and are provided to allow advanced users
  * to customize LDM functionality.
  *
  */
  SoEXTENDER_Documented class LDM_API LDMManagerAccess {

  public:
    /** Default Constructor. */
    LDMManagerAccess(){};

    /**
     * Allows you to provide an application-defined subclass of SoLDMMediator.
     */
    void setMediator(SoLDMMediator* mediator)
    { m_mediator = mediator; };

    /**
    * Allows you to provide an application-defined subclass of SoLDMNodeFrontManager.
    */
    void setNodeFrontManager( SoLDMNodeFrontManager* );

    /**
    * Returns a pointer to the application-defined subclass of SoLDMNodeFrontManager.
    */
    inline SoLDMNodeFrontManager* getNodeFrontManager() { return m_mediator->m_nodeFrontManager; }

    /**
    * Allows you to provide an application-defined subclass of SoLDMTileVisitor.
    * Passing NULL sets the visitor to the LDM internal default visitor (SoLDMProximityVisitor).
    * By default, LDM will not gain ownership of a custom tile visitor, but it is
    * possible to let LDM handle the deletion of the tile visitor by passing FALSE as
    * the second parameter (ownedByUser). Note when a dataset is added under a MultiDataSeparator
    * the mediator of this dataset is unregistered. The only mediator taken in account
    * is the one associated to the MultiDataseparator and, as a result, custom tile visitor set 
    * previously is not available anymore. It is then mandatory to set this custom tile visitor
    * on the global mediator.
    */
    void setTileVisitor(SoLDMTileVisitor*, SbBool ownedByUser = TRUE);

    /**
    * Returns a pointer to the application-defined subclass of SoLDMTileVisitor.
    */
    inline SoLDMTileVisitor* getTileVisitor() { return m_mediator->m_tileVisitor; }

    /**
    *
    * Allows you to provide an application-defined subclass of SoLDMTileManager.
    * By default, LDM will not gain ownership of a custom tile manager, but it is
    * possible to let LDM handle the deletion of the tile manager by passing FALSE as
    * the second parameter (ownedByUser).
    */
    void setTileManager(SoLDMTileManager* tilemgr, SbBool ownedByUser = TRUE);

    /**
    * Returns a pointer to the application-defined subclass of SoLDMTileManager.
    */
    SoLDMTileManager* getTileManager() { return m_mediator->getTileManager(); }

    /**
    * Returns a pointer to mediator's SoLDMTextureManager.
    */
    SoLDMTextureManager*  getTextureManager() { return m_mediator->getTextureManager(); }

    /**
    * Returns a pointer to mediator's SoLDMGeometry.
    */
    SoLDMGeometry*    getVVizGeometry() { return m_mediator->getVVizGeometry(); }

    /**
     * Returns a pointer to mediator's SoLDMResourceManager.
     */
    SoLDMResourceManager* getResourceManager(int id = -1);

    /**
     * Returns true if the attached tileVisitor set by the application is owned by it.
     */
    bool isTileVisitorOwnedByUser() const;

  private:
    SoLDMMediator* m_mediator;
  };// END LDMManagerAccess definition

SoINTERNAL public:
  LDMManagerAccess      ldmManagerAccess;
  SoLDMDataAccess&        getDataAccess ( int id = -1 );
  SoLDMDataAccess&        getDataAccess ( SoDataSet* ds );

  SoLDMDataEditor&        getDataEditor ( int id = -1 );
  SoLDMDataEditor&        getDataEditor ( SoDataSet* ds );


  LDMResourceParameter* getResourceParameter(int dataEntry);
protected:
  // We use a map of LDMDataAccess to be able to
  // support multi thread. One Data Access per thread id
  typedef std::map<SbThreadId_t, SoLDMDataAccess*> t_dataAccessList;

  // We use a map of LDMDataEditor to be able to
  // support multi thread. One Data Editor per thread id
  typedef std::map<SbThreadId_t, SoLDMDataEditor*> t_dataEditorList;


  t_dataAccessList ldmDataAccessList;
  SbThreadMutex m_semDataAccessList;

  t_dataEditorList ldmDataEditorList;
  SbThreadMutex m_semDataEditorList;

};

/*****************************************************************************/
SoDataSet*
SoLDMMediator::getFirstDataSet() const
{
  if ( m_volumeDataList.empty() )
    return NULL;

  return m_volumeDataList[0].dsIdPair.first;
}

/*****************************************************************************/
bool
SoLDMMediator::hasMultiDataError() const
{
  return m_multiDataError;
}

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif
