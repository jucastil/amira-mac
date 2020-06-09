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



#ifndef  _SO_VRMLEXTERNPROTOFIELD_
#define  _SO_VRMLEXTERNPROTOFIELD_

#include <Inventor/misc/SoBase.h>
#include <Inventor/SbString.h>
#include <Inventor/nodes/SoNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLEXTERNPROTOField
//
//  This class stores the EXTERNPROTO definitions
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Contains the internal definition for one of an externprototype's fields,
 * exposedFields, eventIns or eventOuts.
 * 
 * @ingroup OtherVRML2
 * 
 * @DESCRIPTION
 *   The interface to an externprototype is through the public fields, exposedFields,
 *   eventIns and eventOuts of an externprototype declaration. This class defines one
 *   of these interfaces. The list of SoVRMLEXTERNPROTOField definitions is created
 *   when the externprototype is read from a file or buffer and cannot be created
 *   programmatically.
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

class INVENTOR_API SoVRMLEXTERNPROTOField : public SoBase {

 public:
 
    /** Kind */
  enum Kind {
    /**
     *  Regular field 
     */
    EXTERNPROTO_FIELD,
    /**
     *  Field with implied set_ and _changed eventIn and eventOut 
     */
    EXTERNPROTO_EXPOSEDFIELD,
    /**
     *  eventIn 
     */
    EXTERNPROTO_EVENTIN,
    /**
     *  eventOut 
     */
    EXTERNPROTO_EVENTOUT
  };

  /**
   * Returns the kind of field this is.
   */
  Kind getFieldKind() { return fieldKind;}
  /**
   * Returns the type of field this is.
   */
  SoType getFieldType() {return fieldType;}
  /**
   * Returns the name of the field.
   */
  SbString getFieldName() {return fieldName;}
  
  // Constructor
  SoVRMLEXTERNPROTOField();

  // Returns type identifier for VRMLEXTERNPROTOField instance
  virtual SoType getTypeId() const;

  /**
   * Returns type identifier for this class.
   */
  static SoType getClassTypeId();

 SoEXTENDER public:

 SoINTERNAL public:

  Kind fieldKind;   // field, eventIn, etc
  SoType fieldType;   // Such as SFFloat
  SbString fieldName;   // The name of the field, eventIn, etc.
  // or exposedFields

  static void initClass();
  static void exitClass();

  // Returns new SoVRMLEXTERNPROTOField; called by SoType::createInstance()
  static void * createInstance(SoType* dynamicType = NULL);

 protected:
  virtual ~SoVRMLEXTERNPROTOField();

  // Reads stuff into instance of SoVRMLEXTERNPROTOField. 
  // Returns FALSE on error.
  virtual SbBool readInstance(SoInput *in, unsigned short flags);

 private:
  static SoType classTypeId;    // TypeId 
};

#endif /* _SO_VRMLEXTERNPROTOFIELD_ */

