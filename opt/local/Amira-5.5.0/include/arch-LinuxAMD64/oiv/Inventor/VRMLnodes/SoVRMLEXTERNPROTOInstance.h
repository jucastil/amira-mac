/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_VRMLEXTERNPROTOINSTANCE_
#define  _SO_VRMLEXTERNPROTOINSTANCE_

#include <Inventor/SbLinear.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoGroup.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/VRMLnodes/SoVRMLEXTERNPROTODef.h>
#include <Inventor/VRMLnodes/SoVRMLPROTODef.h>
#include <Inventor/VRMLnodes/SoVRMLNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLEXTERNPROTOInstance
//
//  VRMLEXTERNPROTOInstance source node.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Instance of an externprototype.
 * 
 * @ingroup OtherVRML2
 * 
 * @DESCRIPTION
 *   An externprototype definition read from a file or a buffer does not define an
 *   actual node instance. This class is used to create the instance of a previously
 *   defined externprototype.
 * 
 * @VRML2_SPECIFICATION
 *    This section describes the expected behavior of the node in a conforming VRML97
 *   browser application. In some cases, the application is responsible for
 *   implementing portions of the expected behavior. Open Inventor viewer classes and
 *   IVF classes implement some of the application behaviors.
 *   
 *   This section may reference portions of the VRML97 specification that are not
 *   present in this help file. The complete VRML97 spec is available at
 *   @B http://www.web3d.org @b.
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLEXTERNPROTOInstance : public SoVRMLNode {

 public:

  /**
   * Returns type identifier for this class. 
   */
  static SoType       getClassTypeId();       /* Returns class type id */
  virtual SoType        getTypeId() const;

  #ifdef OIV_NET_DOC
 /**
   * Finishes setting up an instance of an externprototype. The steps required to
   * create an instance of an externprototype are:
   * 
   * 1. Read in the externprototype. You can read it in from a file or a buffer using
   * the @B readAllVRML @b method of SoDB. 
   * 
   * 2. Find the externprototype definition from the externprototype's name using the
   * static method @B findEXTERNPROTO @b in SoBase.
   * 
   * 3. Create an instance of the prototype.
   * 
   * 4. Set the values of the fields.
   * 
   * 5. Finish the setup of the instance.
   * 
   */
 #else
  /**
   * Finishes setting up an instance of an externprototype. The steps required to
   * create an instance of an externprototype are:
   * 
   * 1. Read in the externprototype. You can read it in from a file or a buffer using
   * the @B readAllVRML @b method of SoDB. 
   * 
   * 2. Find the externprototype definition from the externprototype's name using the
   * static method @B findEXTERNPROTO @b in SoBase.
   * 
   * <PRE> 
   *  SoVRMLEXTERNPROTODef *goldProtoDef = (SoVRMLEXTERNPROTODef *)
   *  SoBase::findEXTERNPROTO(SbName("newGold"));
   *  </PRE>
   *  3. Create an instance of the prototype.
   * 
   * <PRE> 
   *  SoVRMLEXTERNPROTOInstance *goldInst = new
   * SoVRMLEXTERNPROTOInstance(goldProtoDef);
   *  </PRE>
   *  This will partially set up the instance and create the fields.
   * 
   * 4. Set the values of the fields.
   * 
   * <PRE>
   *  ((SoSFColor *) (goldInst->getField("diffColor")))->setValue(0.8, 0.6,
   * 0.0));
   *  </PRE>
   *  5. Finish the setup of the instance.
   * 
   * <PRE> 
   *  goldInst->setupInstance();
   *  </PRE>
   *  The order of the calls is important. If the value of the field is to be
   * changed from the default, it must be changed before setupInstance() is
   * called.
   */
#endif

  void                setupInstance();
  /**
   * Returns the type of the externprototype being instanced. A type of an
   * externprototype determines where it can be instanced. The first node found in
   * the PROTO defined in the externproto definition defines the type of the
   * externprototype.
   */
  SoType              getEXTERNPROTOType() {return pDefinition->protoType;}

  SoVRMLEXTERNPROTOInstance();

  /**
   * Creates an instance of the externprototype defined by the definition
   * externprotoDef.
   */
  SoVRMLEXTERNPROTOInstance(SoVRMLEXTERNPROTODef *protoDef);

 SoINTERNAL public:

  // Constructor

  static void         initClass();
  static void         exitClass();

  // Returns number of children
  int                 getNumChildren() const;

  // Returns pointer to children
  virtual SoChildList *getChildren() const;

  virtual SbBool      getIsBuiltIn() const;


 SoEXTENDER public:

  virtual void doAction(SoAction *action);
  virtual void callback(SoCallbackAction *action);
  virtual void GLRender(SoGLRenderAction *action);
  virtual void getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void pick(SoPickAction *action);
  virtual void        getMatrix(SoGetMatrixAction *action);
  virtual void search(SoSearchAction *action);
  virtual void handleEvent(SoHandleEventAction *action);
  //virtual void write(SoWriteAction *action);
  virtual void getPrimitiveCount(SoGetPrimitiveCountAction *action);
  static int copyingEXTERNPROTO;
  SbString getEXTERNPROTOName();
  SoVRMLPROTODef *getEXTERNPROTODef();
  SoVRMLEXTERNPROTODef *getEXTERNDef();

 protected:

  ~SoVRMLEXTERNPROTOInstance();
  virtual SbBool readInstance(SoInput *in, unsigned short flags);
  virtual void copyContents(const SoFieldContainer *fromFC,
                            SbBool copyConnections);
  SoChildList *children;

 private:
  static SbThreadMutex classMutex; 

  void setupFields(SoVRMLEXTERNPROTODef *externprotoDef);
  int checkInterface(SbPList *fList, SbString name);
  static void *createInstance(SoType* dynamicType = NULL);
  static SoType classTypeId;
  static SbBool isBuiltIn;
  virtual const SoFieldData *getFieldData() const;
  static const SoFieldData **parentFieldData;
  SoFieldData *fieldData;

  // Reads stuff into instance of SoVRMLEXTERNPROTOInstance. Returns FALSE on error.
  SoVRMLPROTODef           *pDefinition;
  SoVRMLEXTERNPROTODef     *externDefinition;
  SoType                    protoType;
  SbString                  pName;
  SbDict                    *pDict;
  SoField                   *fld;
  SoGroup                   *m_group_copy;
  SbPList                   *copyDictionary;
  SoSFNode                  *protoNode;
  SbBool                    error;
  SbPList                   *disconnectList;


};

#endif /* _SO_VRMLEXTERNPROTOINSTANCE_ */

