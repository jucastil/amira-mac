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



#ifndef  _SO_VRMLPROTODEF_
#define  _SO_VRMLPROTODEF_

#include <Inventor/misc/SoBase.h>
#include <Inventor/SbPList.h>
#include <Inventor/SbString.h>
#include <Inventor/nodes/SoGroup.h>
#include <Inventor/nodes/SoNode.h>
class SoChildList;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLPROTODef
//
//  This class stores the PROTO definitions
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Contains the internal definition of a prototype.
 * 
 * @ingroup OtherVRML2
 * 
 * @DESCRIPTION
 *   This class contains all the information required to set up an instance of a VRML97
 *   prototype. It is derived from SoBase and is created when a prototype is read
 *   from a file or buffer.
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

class INVENTOR_API SoVRMLPROTODef : public SoBase {

 public:
                                         
  SbString            protoName;       // The PROTO name
  SoType              protoType;       // The type of the PROTO
  SbPList            *fieldList;       // List of the fields, eventIns, etc
  SbPList            *routeList;       // List of the ROUTEs
  SoGroup            *node_group;
  SbDict             *ISRefs;          // A list of the IS connections
  // internal to this PROTO
  SbDict             *DEFDict;         // DEF dictinary for this proto def
  char *             writeBuffer;      // Pointer to the buffer that
  // contains the PROTO. Used if it
  // needs to be written out.    
  int                writeBufSize;     // Number of characters in the 
  // write buffer.

  // Constructor
  SoVRMLPROTODef();

  // Returns type identifier for VRMLPROTODef instance
  virtual SoType      getTypeId() const;

  /**
   * Returns type identifier for this class.
   */
  static SoType       getClassTypeId();

#ifdef OIV_NET_DOC
  /**
  * Appends references to all of this object's fields to resultList and returns the
  * number of fields appended. Each item in the list is a reference to an
  * SoVRMLPROTOField.
  */

#else
  /**
  * Appends pointers to all of this object's fields to resultList and returns the
  * number of fields appended. Each item in the list is a pointer to an
  * SoVRMLPROTOField.
  */

#endif //OIV_NET_DOC
  virtual int getFields(SoVRMLPROTOFieldList &list) const;

#ifdef OIV_NET_DOC
  /**
  * Appends references to all of the SoVRMLPROTO nodes that have been defined to list,
  * and returns the number of SoVRMLPROTO node references appended.
  */

#else
  /**
  * Appends pointers to all of the SoVRMLPROTO nodes that have been defined to list,
  * and returns the number of SoVRMLPROTO node pointers appended.
  */

#endif //OIV_NET_DOC
  static int getPROTOList(SoBaseList &list);

  /**
   * Returns the name of the PROTO defined by this SoVRMLPROTODef.
   */
  SbString  getPROTOName() {return protoName;}
 SoEXTENDER public:

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

  // Returns pointer to children
  virtual SoChildList *getChildren() const;

  // Returns number of children
  int                 getNumChildren() const;

  SoVRMLPROTODef *    copy(SoVRMLPROTODef *protoDef);

 protected:

  ~SoVRMLPROTODef();

  // Reads stuff into instance of SoVRMLPROTODef. Returns FALSE on error.
  virtual SbBool      readInstance(SoInput *in, unsigned short flags);
 
 private:

  SbBool         findInPROTODef(SoVRMLPROTODef *protoDef);


  // Returns new SoVRMLPROTODef; called by SoType::createInstance()
  static void *       createInstance(SoType* dynamicType = NULL);

  static SoType      classTypeId;    // TypeId of paths

};

#endif /* _SO_VRMLPROTODEF_ */

