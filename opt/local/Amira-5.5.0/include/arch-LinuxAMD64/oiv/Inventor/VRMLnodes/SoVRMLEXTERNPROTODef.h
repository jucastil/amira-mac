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



#ifndef  _SO_VRMLEXTERNPROTODEF_
#define  _SO_VRMLEXTERNPROTODEF_

#include <Inventor/misc/SoBase.h>
#include <Inventor/SbPList.h>
#include <Inventor/SbString.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/VRMLnodes/SoVRMLPROTODef.h>


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLEXTERNPROTODef
//
//  This class stores the EXTERNPROTO definitions
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Contains the internal definition of an externprototype.
 * 
 * @ingroup OtherVRML2
 * 
 * @DESCRIPTION
 *   This class contains all the information required to set up an instance of a VRML97
 *   externprototype. It is derived from SoBase and is created when an
 *   externprototype is read from a file or buffer.
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

class INVENTOR_API SoVRMLEXTERNPROTODef : public SoBase {

 public:
                                         
  // Constructor
  SoVRMLEXTERNPROTODef();

  // Returns type identifier for VRMLEXTERNPROTODef instance
  virtual SoType      getTypeId() const;

  /**
   * Returns type identifier for this class.
   */
  static SoType       getClassTypeId();

#ifdef OIV_NET_DOC
  /**
  * Appends references to all of this object's fields to resultList and returns the
  * number of fields appended. Each item in the list is a reference to an
  * SoVRMLEXTERNPROTOField.
  */

#else
  /**
  * Appends pointers to all of this object's fields to resultList and returns the
  * number of fields appended. Each item in the list is a pointer to an
  * SoVRMLEXTERNPROTOField.
  */

#endif //OIV_NET_DOC
  virtual int getFields(SoVRMLEXTERNPROTOFieldList &list) const;
#ifdef OIV_NET_DOC
  /**
  * Appends references to all of the SoVRMLEXTERNPROTO nodes that have been defined to
  * list, and returns the number of SoVRMLEXTERNPROTO node references appended.
  */

#else
  /**
  * Appends pointers to all of the SoVRMLEXTERNPROTO nodes that have been defined to
  * list, and returns the number of SoVRMLEXTERNPROTO node pointers appended.
  */

#endif //OIV_NET_DOC
  static int getEXTERNPROTOList(SoBaseList &list);
  /**
   * Returns the name of the EXTERNPROTO defined by this SoVRMLEXTERNPROTODef.
   */
  SbString  getEXTERNPROTOName() {return externprotoName;}

 SoEXTENDER public:

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

  SbString            externprotoName; // The EXTERNPROTO name
  SbPList            *fieldList;       // List of the fields, eventIns, etc
  SoMFString          url;             // URL's
  // internal to this EXTERNPROTO
  char *             writeBuffer;      // Pointer to the buffer that
  // contains the EXTERNPROTO.
  // Used if it needs to be written
  // out.
  int                writeBufSize;     // Number of characters in the
  // write buffer.
  SoVRMLPROTODef *   protoDef;

 protected:

  ~SoVRMLEXTERNPROTODef();

  // Reads stuff into instance of SoVRMLEXTERNPROTODef. Returns FALSE on error.
  virtual SbBool      readInstance(SoInput *in, unsigned short flags);

 private:

  // Returns new SoVRMLEXTERNPROTODef; called by SoType::createInstance()
  static void *       createInstance(SoType* dynamicType = NULL);

  static SoType      classTypeId;    // TypeId of paths

};

#endif /* _SO_VRMLEXTERNPROTODEF_ */

