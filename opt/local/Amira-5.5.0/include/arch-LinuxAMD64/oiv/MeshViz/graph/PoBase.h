/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_BASE_
#define  _PO_BASE_

class    PbBase ;
class    SoAction ;
class    SoFieldSensor ;
class    PbDataMapping ;
class    SoMaterial;
class    SoMaterialBinding;
class    SoQuadMesh;
class    SoIndexedTriangleStripSet;
class    SoIndexedFaceSet;
class    SoIndexedLineSet;
class    SoLineSet;
class    SoCache ;
class    SoShape;

#include <MeshViz/PoMeshViz.h>
#include <MeshViz/PbBasic.h>
#include <MeshViz/graph/PbDomain.h>

#include <Inventor/nodekits/SoBaseKit.h>
#include <Inventor/nodekits/SoAppearanceKit.h>
#include <Inventor/nodes/SoLightModel.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoCallback.h>
#include <Inventor/caches/SoCache.h>

#define PO_KIT_ADD_FIELD(_fieldName,_defValue,_fieldList)\
        _fieldList.append(&_fieldName) ;\
        SO_KIT_ADD_FIELD(_fieldName, _defValue) ;

/**
 * @DTEXT  Abstract base class for all Graph Master & 3D Data Master classes.
 *
 * @ingroup MeshVizMisc
 *
 * @DESCRIPTION
 *    All representations depend on the current domain which defines the data
 *    limits of the graphic to be generated. If the method setDomain(domain) is
 *    called, the current domain is "domain". Otherwise the current domain is
 *    specified in the current inherited state (cf property node PoDomain).
 *
 *    Be careful, do not use the method rebuild() if you use MeshViz
 *    property nodes (PoDomain, PoMeshProperty,...), because a representation
 *    (axis, legend, 2D and 3D mesh representation,..) depends on the current
 *    inherited state. If you need to do an extra work after a representation has
 *    been built, do it in a post-rebuild \oivnetdoc delegate \else callback \endoivnetdoc (cf PoBase::addPostRebuildCallback).
 *
 */

class MESHVIZ_API PoBase : public SoBaseKit {

  SO_KIT_ABSTRACT_HEADER(PoBase) ;

  SO_KIT_CATALOG_ENTRY_HEADER(catchActionCallback) ;
  SO_KIT_CATALOG_ENTRY_HEADER(alternateRep)   ;
  SO_KIT_CATALOG_ENTRY_HEADER(catchActionLevel2Callback) ;
  SO_KIT_CATALOG_ENTRY_HEADER(appearance)   ;
  SO_KIT_CATALOG_ENTRY_HEADER(domainTransform)   ;


 public:



  /**
   *  Type of update method
   */
  enum UpdateMethodType {
    /**
     *  The kit is rebuilt immediately after each modification.
     */
    UPDATE_METHOD_IMMEDIATE,
    /**
     *  The kit is rebuilt during a traversal (that is an action).
     */
    UPDATE_METHOD_ON_ACTION
  } ;

  /**
   *  Type of write format
   */
  enum NodeWriteFormat {
    /**
     *  All MeshViz nodekits are written in a fold format.
     */
    FOLD_NODE_WRITE_FORMAT,
    /**
     *  All MeshViz nodekits are written in an unfold format.
     */
    UNFOLD_NODE_WRITE_FORMAT
  } ;

  /**
   *  Type of Text.
   */
  enum TextType {
    SO_TEXT3,
    SO_ANNO_TEXT3
  } ;


  /**
   * [OIV-WRAPPER NAME{RebuildCB}]
   */
  typedef void PoRebuildCB(void *userData, PoBase *base) ;

  /**
   * Sets scene graph update method. #UPDATE_METHOD_IMMEDIATE
   * indicates that each time a Graph Master or 3D Data Master object is modified,
   * the scene graph must be updated. #UPDATE_METHOD_ON_ACTION
   * indicates that the scene graph does not have to be modified when a Graph
   * Master or 3D Data Master object changes; the scene graph being modified
   * when it is necessary (before a rendering action for instance). The faster method
   * is #UPDATE_METHOD_ON_ACTION and is particularly useful for
   * representations where more than one field has to be set to obtain the definitive
   * representation, because with the other method, each time a field is changed, the
   * representation is rebuilt. (#UPDATE_METHOD_ON_ACTION by default).
   */
  void setUpdateMethod(UpdateMethodType type) { m_updateMethodType = type ; }

  /**
   * Gets update method. See setUpdateMethod for more details.
   */
  UpdateMethodType getUpdateMethod() const    { return m_updateMethodType ; }

#ifdef OIV_NET_DOC
  /**
  * Sets the node write format. #FOLD_NODE_WRITE_FORMAT indicates
  * that all nodes will not be unfolded when they are written with a
  * SoWriteAction. #UNFOLD_NODE_WRITE_FORMAT indicates on the
  * contrary, that all nodes will be unfolded when they are written with a
  * SoWriteAction. This format may be useful if you want to convert the
  * generated file into a VRML format. Be careful, when using
  * the format #FOLD_NODE_WRITE_FORMAT, the references to basic objects
  * (Pb objects) are not written in <iv> file. In this case (and if you need to
  * save this information), use the corresponding property node (for instance, replace
  * the PbDomain object with the PoDomain property node).
  *
  * (#FOLD_NODE_WRITE_FORMAT by default).
  */

#else
  /**
  * Sets the node write format. #FOLD_NODE_WRITE_FORMAT indicates
  * that all nodes will not be unfolded when they are written with a
  * SoWriteAction. #UNFOLD_NODE_WRITE_FORMAT indicates on the
  * contrary, that all nodes will be unfolded when they are written with a
  * SoWriteAction. This format may be useful if you want to convert the
  * generated file into a VRML format. Be careful, when using
  * the format #FOLD_NODE_WRITE_FORMAT, the pointers to basic objects
  * (Pb objects) are not written in <iv> file. In this case (and if you need to
  * save this information), use the corresponding property node (for instance, replace
  * the PbDomain object with the PoDomain property node).
  *
  * (#FOLD_NODE_WRITE_FORMAT by default).
  */

#endif //OIV_NET_DOC
  static void setNodeWriteFormat(NodeWriteFormat format);

  /**
   * Gets the node write format. See setNodeWriteFormat for more details.
   */
  static NodeWriteFormat getNodeWriteFormat();

  /**
   * Sets a reference to a PbDomain object used to define the data limits of the
   * graphics to be generated. If this method is not called
   * (or called passing NULL as argument), this is the domain defined in the current
   * inherited state (defined with the node PoDomain) which is used.
   */
  void setDomain(PbDomain *dom) ;

  /**
   * Gets a reference to a PbDomain object used to define the data limits of the
   * graphics to be generated.
   */
  const PbDomain* getDomain() const ;

  /**
   * Indicates the node kit is modified. (Simulates a change).
   */
  void touchKit() ;

  /**
   * Return TRUE, if the kit has been modified, else otherwise
   */
  SbBool isModified() const { return m_hasBeenModified ; }

  /**
   * Indicates if the node kit has been built at least once.
   */
  SbBool isBuilt() const
    { return m_isObjBuilt ; }

  /**
   * Forces the node kit to be rebuilt immediately.
   * The rebuild consists in updating all catalog parts
   * (which contains shapes forming the visualization) of the node kit
   * according to field values and other property values (domain, data mapping,...).
   * Be careful, do not use the method rebuild() if you use MeshViz
   * property nodes (PoDomain, PoMeshProperty,...), because a representation
   * (axis, legend, 2D and 3D mesh representation,..) depends on the current
   * inherited state. If you need to do an extra work after a representation has
   * been built, do it in a post-rebuild \oivnetdoc delegate \else callback \endoivnetdoc (cf PoBase::addPostRebuildCallback).
   */
  virtual void  rebuild() {} ;

  /**
   * Add a callback function to call when the node kit is rebuilt. This
   * callback is called just before the kit is rebuilt.
   * [OIV-WRAPPER EVENT_NAME{PreRebuild}]
   */
  void addPreRebuildCallback(PoRebuildCB *cb, void *data)  ;

  /**
   * Add a callback function to call when the node kit is rebuilt. This
   * callback is called just after the kit is rebuilt.
   * [OIV-WRAPPER EVENT_NAME{PostRebuild}]
   */
  void addPostRebuildCallback(PoRebuildCB *cb, void *data) ;


  /**
   * Remove a callback function to call when the node kit is rebuilt. This
   * callback is called just before the kit is rebuilt.
   * [OIV-WRAPPER EVENT_NAME{PreRebuild}]
   */
  void removePreRebuildCallback(PoRebuildCB *cb, void *data=NULL)  ;

  /**
   * Remove a callback function to call when the node kit is rebuilt. This
   * callback is called just after the kit is rebuilt.
   * [OIV-WRAPPER EVENT_NAME{PostRebuild}]
   */
  void removePostRebuildCallback(PoRebuildCB *cb, void *data) ;

  /**
   * Sets the type of text used.
   * Possible values :
   *   - type = #SO_TEXT3 : All texts used for representations are SoText3 nodes.
   *   - type = #SO_ANNO_TEXT3 : All text used for representations are
   *     SoAnnoText3 (this type of text has more attributes than SoText3 which
   *     can be specified with the property node SoAnnoText3Property).
   *
   * type = #SO_ANNO_TEXT3 by default.
   */
  static void setTextType(TextType type) ;

  /**
   * Gets the type of text used.
   */
  static TextType getTextType();

  /**
   * Set the VRML2 mode.
   * This mode allows the user to configure MeshViz to prepare
   * the conversion in VRML2 format with the best possible result.
   * In this way, MeshViz realizes some particular actions :
   * - Whatever text type specified by the method setTextType(), all
   *   texts used are SoAsciiText in order to minimize VRML2 file size (other
   *   text types are tessellated during a VRML2 conversion which increases VRML2 file size).
   * - For all materials generated by MeshViz where the light model is SoLightModel::BASE_COLOR
   *   (There is no equivalence in VRML2), the emissive component is set at the same
   *   value as the diffuse components (By this way, we simulate SoLightModel::BASE_COLOR light model).
   * - A Z Offset is added for all coplanar faces generated by MeshViz representation
   *   (All these representations are planar as for instance legends so the
   *   SoAnnotation node solves their problems, but there is no equivalence in VRML2).
   *
   * This mode is inactive by default.
   */
  static void   setVRML2Mode(SbBool flag) ;

  /**
   * Gets the VRML2 mode (TRUE = VRML2 mode, FALSE Inventor mode)
   */
  static SbBool isVRML2Mode() ;

  /**
   * Copy method.
   */
  virtual SoNode *copy(SbBool copyConnections = FALSE) const ;

  /**
   * See SoNode::affectState() for explanations.
   */
  virtual SbBool affectsState() const ;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:

  /**
   * Initializes all nodekit classes of MeshViz by registering them in the
   * database. This function needs to be called before any other nodekit
   * class of MeshViz may be constructed or accessed. Deprecated.
   */
  static void init() ;
	static void finish() ;
  static bool isInitialized();

  static void initClass() ;
	static void exitClass() ;

  // Overload the method write to store the current write action
  virtual void write(SoWriteAction *action) ;

  // Manage the connection with PbBase objects
  virtual void basicObjectChange(PbBase *basicObj) ;

  // Enable domain transform
  void enableDomainTransform(SbBool flag)
    { m_isDomainTrans = flag ; }

  SoShape* deleteTransparencyParts(const PbDataMapping *data_mapping, const SoMaterial *material, SoMaterialBinding *material_binding,
                               SoGroup *group);
  SoShape* deleteTransparencyParts(const PbDataMapping *data_mapping, const SoMaterial *material, SoMaterialBinding *material_binding,
                               SoQuadMesh *shape, SoGroup *father_of_shape, int child_index);
  SoShape* deleteTransparencyParts(const PbDataMapping *data_mapping, const SoMaterial *material, SoMaterialBinding *material_binding,
                               SoIndexedTriangleStripSet *shape, SoGroup *father_of_shape, int child_index);
  SoShape* deleteTransparencyParts(const PbDataMapping *data_mapping, const SoMaterial *material, SoMaterialBinding *material_binding,
                               SoIndexedFaceSet *shape, SoGroup *father_of_shape, int child_index);
  SoShape* deleteTransparencyParts(const PbDataMapping *data_mapping, const SoMaterial *material, SoMaterialBinding *material_binding,
                               SoIndexedLineSet *shape, SoGroup *father_of_shape, int child_index);
  SoShape* deleteTransparencyParts(const PbDataMapping *data_mapping, const SoMaterial *material, SoMaterialBinding *material_binding,
                               SoLineSet *shape, SoGroup *father_of_shape, int child_index);

  SoEXTENDER public:
  // Implements actions
  virtual void        GLRender(SoGLRenderAction *action);

 protected:
  // structure of a list of sensors
  struct FieldSensorList {
    int           numSensors ;
    SoFieldSensor **sensors ;
  } ;

  // Constructor and destructor
  // actionCallback is the callback function called
  // when the kit is traversed (callback of the node
  // SoCallback).
  PoBase(SoCallbackCB *actionCallback=NULL) ;
  virtual ~PoBase() ;

  // Methods
  virtual void  setDefaultOnNonWritingFields() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;

   // Copies the contents of the given nodekit into this instance
  virtual void        copyContents(const SoFieldContainer *fromFC,
                                   SbBool copyConnections);

  // Change connection with a PbBase object
  void changeConnection(PbBase *oldObj, PbBase *newObj) ;

  // Called when a Pb object change
  virtual void manageBasicObjectChange(PbBase *basicObj, PbBase **obj) ;

  // Indicate if a field has changed
  SbBool isFieldHasChanged(const SoField *field) ;

  // Indicate if one of fields has changed
  SbBool isAnyFieldsHasChanged()
    { return m_someFieldsHasChanged ; }

  // Empty list of changed fields
  void emptyListFieldsChanged() { m_listFieldsChanged.truncate(0) ; }

  // Set a list of field at default value.
  void setListFieldsDefault(const SoFieldList &fieldLst) ;

  // Set domain scale transformation
  void setDomainTransform(PbDomain *domain) ;

  // Is domain scale transform
  SbBool isDomainTransformEnabled() const
    { return m_isDomainTrans ; }

  // Set domain used or not for rebuild
  void setDomainUsedForRebuild(SbBool flag)
    { m_isDomUseForRebuild = flag ; }

  // Is domain used for rebuild
  SbBool isDomainUsedForRebuild() const
    { return m_isDomUseForRebuild ; }

  // Method  which does somethings before rebuild a node
  virtual void preRebuild() ;

  // Method which does somethings after rebuild a node
  virtual void postRebuild() ;

  // Set light model for the part "appearence"
  void setLightModel(SoLightModel::Model model) ;

  // Set draw style (only field style) for am Appearence Kit
  void setDrawStyleAK(const SbString& partName, SoDrawStyle::Style style=SoDrawStyle::LINES) ;

  // Indicate if fields have changed must be stored
  // Not store by default
  void storeFieldsChanged(SbBool store)
    { needToStoreFieldsChanged = store ; }

  // Methods to handles list of sensors attached to fields
  // The method createFieldSensorList() must be called after all
  // field was created
  void createFieldSensorList(int numFields, FieldSensorList *sensorList) ;
  void deleteFieldSensorList(FieldSensorList *sensorList) ;
  void attachFieldSensorList(const FieldSensorList &sensorList,
                             const SoFieldList &fieldList) ;
  void detachFieldSensorList(const FieldSensorList &sensorList) ;
  static void fieldSensorCB(void *data, SoSensor *sensor) ;

  // Store and Get the current state
  void     setState(SoAction *action) ;
  SoState* getState() const ;

  // Indicate if the state is valid that is we are
  // in a traversal
  SbBool isStateValid() const
    { return m_isStateValid ; }

  // Add an element in the cache for caching
  // Example of call : addElementCache(PoDomainElement::getClassStackIndex())
  template<typename T>
  void addElementCache()
  {
    if(isStateValid() && !isCacheValid())
      m_cache->addElement(getState()->template getConstElement<T>());
  }


  // Remove all elements in a cache
  // and rebuild it
  void rebuildCache(SoCache **cache) ;

  // Add all MeshViz used elements in all the cache
  // to be sure that a modification of one the them
  // will break the current cache
  virtual void addElementsAllCaches() ;

  // Indicate if the cache is rebuilt at each rebuild
  // even if the cache is valid.
  // That allows the user to manage the cache according to
  // the value of some fields.
  // FALSE by default
  void setCacheAlwaysRebuild(SbBool flag)
    { m_isCacheAlwaysRebuild = flag ; }
  SbBool isCacheAlwaysRebuild() const
    { return m_isCacheAlwaysRebuild ; }


  // Indicate if the cache if valid
  SbBool isCacheValid() const
    { return m_isCacheValid ; }

  // Vars
  SoFieldList      m_listFieldsChanged ;
  SbBool           needToStoreFieldsChanged ;

  // Indicate if the state is valid (only during an action)
  SbBool           m_isStateValid ;

 private:
  // Vars
  UpdateMethodType m_updateMethodType ;
  SbBool           m_hasBeenModified ;
  SbBool           m_isObjBuilt ;
  SbBool           m_isDomainTrans ;
  SbBool           m_isDomUseForRebuild ;
  SbBool           m_someFieldsHasChanged ;
  PbDomain         *m_domain, m_defaultDomain ;
  SoCallbackCB     *m_actionCallback ;

  SbBool           m_hasBeenBuilt ;

  // Indicate if the cache is rebuilt at each rebuild
  // even if the cache is valid.
  // That allows the user to manage the cache according to
  // the value of some fields.
  SbBool           m_isCacheAlwaysRebuild ;

  // Current state (update for each action)
  SoState          *m_currentState ;

  // Current cache for MeshViz elements
  SoCache          *m_cache ;

  // Current cache for domain
  SoCache          *m_domainCache ;

  // Indicate if the cache is valid
  SbBool           m_isCacheValid ;

  // Store the current write action
  SoWriteAction    *m_currentWriteAction ;

  PoRebuildCB      *m_preRebuildCB, *m_postRebuildCB ;
  void             *m_preRebuildData, *m_postRebuildData ;

  // Static Vars
  static NodeWriteFormat m_nodeWriteFormat ;
  static TextType        m_textType ;
  static SbBool          m_isVRML2Mode ;

  // Methods
  static void catchActionCB(void *, SoAction *) ;
  static void catchActionLevel2CB(void *, SoAction *) ;

  // Init/finish ref counter status
  static int s_initRefCount;
} ;
/*---------------------------------------------------------------------------*/

#endif /* _PO_BASE_ */

